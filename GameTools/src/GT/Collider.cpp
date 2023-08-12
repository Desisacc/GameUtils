#include "gtpch.h"
#include "GT/Collider.h"

namespace GT {

	// Lines and Rectangle //
	bool Collider::LinesHaveIntersection(Line one, Line two)
	{
		const Line& lineWithLowerCoord = Line::GetLineWithLowerCoordinate(one, two);
		const float distanceBetweenLines = abs(one.Point - two.Point);

		return distanceBetweenLines < lineWithLowerCoord.Length;
	}

	bool Collider::RectanglesHaveIntersection(const Rectangle& one, const Rectangle& two)
	{
		const Vector2<Line> linesOne = { { one.Position.x, one.Size.x }, { one.Position.y, one.Size.y } };
		const Vector2<Line> linesTwo = { { two.Position.x, two.Size.x }, { two.Position.y, two.Size.y } };

		return LinesHaveIntersection(linesOne.x, linesTwo.x) && LinesHaveIntersection(linesOne.y, linesTwo.y);
	}
	// Lines and Rectangle //
	
	// Collisions //
	Collider::CollisionInformation Collider::FindIntersectionWithMovement(const Rectangle& rectangleBeforeMovement, const Rectangle& rectangleAfterMovement, const Rectangle& stillRectangle)
	{
		if (!RectanglesHaveIntersection(rectangleAfterMovement, stillRectangle))
			return { CollisionType::None_CT, -1.0f, -1.0f };
		//Assert(RectanglesHaveIntersection(rectangleBeforeMovement, stillRectangle) == CollisionType::None, "Rectangle without movement already collides!");

		const GT::Vector2<float> speed = { 
			rectangleAfterMovement.Position.x - rectangleBeforeMovement.Position.x, 
			rectangleAfterMovement.Position.y - rectangleBeforeMovement.Position.y 
		};

		const Vector2<float> distancesBetweenRectangles = {
			Line::GetDistanceBetweenLines({ rectangleBeforeMovement.Position.x, rectangleBeforeMovement.Size.x }, { stillRectangle.Position.x, stillRectangle.Size.x }),
			Line::GetDistanceBetweenLines({ rectangleBeforeMovement.Position.y, rectangleBeforeMovement.Size.y }, { stillRectangle.Position.y, stillRectangle.Size.y })
		};

		const Vector2<float> timeToReachCollision = { distancesBetweenRectangles.x / abs(speed.x), distancesBetweenRectangles.y / abs(speed.y) };

		CollisionInformation collisionInfo;
		if (timeToReachCollision.x < timeToReachCollision.y)
		{
			collisionInfo.RatioDistanceSpeedMain = timeToReachCollision.x;
			collisionInfo.RatioDistanceSpeedSecondary = timeToReachCollision.y;
			
			collisionInfo.CollisionAxis = rectangleBeforeMovement.Position.x < stillRectangle.Position.x ?
				CollisionType::LeftSide_CT : CollisionType::RightSide_CT;
		}
		else
		{
			collisionInfo.RatioDistanceSpeedMain = timeToReachCollision.y;
			collisionInfo.RatioDistanceSpeedSecondary = timeToReachCollision.x;

			collisionInfo.CollisionAxis = rectangleBeforeMovement.Position.y < stillRectangle.Position.y ?
				CollisionType::BottomSide_CT : CollisionType::TopSide_CT;
		}
		return collisionInfo;
	}

	float Collider::HandleAxisCollisionBasedOnSpeed(Line handledLine, float speed, Line stillLine)
	{
		if (speed > 0.0f)
			handledLine.Point = stillLine.Point - handledLine.Length;
		else
			handledLine.Point = stillLine.Point + stillLine.Length;

		return handledLine.Point;
	}
	
	float Collider::ReturnPositionAfterCollisionType(const Rectangle& rectangleToHandle, const Rectangle& stillRectangle, CollisionType collisionType)
	{
		switch (collisionType)
		{
		case CollisionType::LeftSide_CT:
		{
			return stillRectangle.Position.x - rectangleToHandle.Size.x;
		}
		case CollisionType::RightSide_CT:
		{
			return stillRectangle.Position.x + stillRectangle.Size.x;
		}
		case CollisionType::BottomSide_CT:
		{
			return stillRectangle.Position.y - rectangleToHandle.Size.y;
		}
		case CollisionType::TopSide_CT:
		{
			return stillRectangle.Position.y + stillRectangle.Size.y;
		}
		default:
			Assert(false, "Unknown CollisionType! :{0}", static_cast<uint32_t>(collisionType));
			return 0.0f;
		}
	}
	// Collisions //

	// Rotational //
	Collider::CircleQuadrant Collider::PositionIsInQuadrant(Vector2<float> position)
	{
		Vector2<size_t> quadrants = { 0, 0 };

		if (position.x >= 0.0f)
			quadrants.x |= CircleQuadrant::One_CQ | CircleQuadrant::Four_CQ;
		else
			quadrants.x |= CircleQuadrant::Two_CQ | CircleQuadrant::Three_CQ;

		if (position.y >= 0.0f)
			quadrants.y |= CircleQuadrant::One_CQ | CircleQuadrant::Two_CQ;
		else
			quadrants.y |= CircleQuadrant::Three_CQ | CircleQuadrant::Four_CQ;

		return static_cast<CircleQuadrant>(quadrants.x & quadrants.y);
	}

	float Collider::TurnAngleIntoAccordingQuadrant(float angleInDegree, Vector2<float> position)
	{
		Assert(angleInDegree >= 0.0f && angleInDegree <= 90.0f, "Only accepts angles in the range of [0, 90]! :{0}", angleInDegree);

		const CircleQuadrant circleQuadrant = PositionIsInQuadrant(position);

		switch (circleQuadrant)
		{
		case CircleQuadrant::One_CQ:
			break;

		case CircleQuadrant::Two_CQ:
			angleInDegree = 180.0f - angleInDegree;
			break;

		case CircleQuadrant::Three_CQ:
			angleInDegree += 180.0f;
			break;

		case CircleQuadrant::Four_CQ:
			angleInDegree = 360.0f - angleInDegree;
			break;

		default:
			Assert(false, "Invalid CircleQuadrant value! :{0}", static_cast<uint32_t>(circleQuadrant));
		}

		return angleInDegree;
	}
	// Rotational //
}