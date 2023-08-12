#pragma once

#include "GT/Utils/Vectors.h"
#include "GT/Utils/Geometry.h"
#include "GT/Utils/GlobalData.h"

#include "GT/Components/Components.h"

namespace GT {

	class Collider
	{
	public:
		enum CircleQuadrant : uint32_t
		{
			One_CQ = 1, Two_CQ = 2, Three_CQ = 4, Four_CQ = 8
		};
		enum BorderCollision : uint32_t
		{
			AxisX_BC = 1, AxisY_BC = 2, LowCoordinate_BC = 4, HighCoordinate_BC = 8,

			LeftBorder_BC = AxisX_BC | LowCoordinate_BC,
			RightBorder_BC = AxisX_BC | HighCoordinate_BC,
			BottomBorder_BC = AxisY_BC | LowCoordinate_BC,
			TopBorder_BC = AxisY_BC | HighCoordinate_BC
		};
		enum CollisionType : uint32_t
		{
			None_CT = 0, AxisX_CT = 1, AxisY_CT = 2, LowCoordinate_CT = 4, HighCoordinate_CT = 8,

			LeftSide_CT = AxisX_CT | LowCoordinate_CT,
			RightSide_CT = AxisX_CT | HighCoordinate_CT,
			BottomSide_CT = AxisY_CT | LowCoordinate_CT,
			TopSide_CT = AxisY_CT | HighCoordinate_CT
		};

		struct CollisionInformation
		{
			CollisionType CollisionAxis = CollisionType::None_CT;
			float RatioDistanceSpeedMain = -1.0f;
			float RatioDistanceSpeedSecondary = -1.0f;
		};
		template<typename ComponentType> struct MovementCollision
		{
			const ComponentType* CollidedComponent;
			CollisionInformation CollisionInfo;

			MovementCollision(const ComponentType* collidedComponent, CollisionInformation collisionInfo) noexcept
				: CollidedComponent(collidedComponent), CollisionInfo(collisionInfo) {}
		};
	public:
		Collider() = delete;

		static bool LinesHaveIntersection(Line one, Line two);
		static bool RectanglesHaveIntersection(const Rectangle& one, const Rectangle& two);

		static CollisionInformation FindIntersectionWithMovement(const Rectangle& rectangleBeforeMovement, const Rectangle& rectangleAfterMovement, const Rectangle& stillRectangle);
		static float HandleAxisCollisionBasedOnSpeed(Line handledLine, float speed, Line stillLine);
		static float ReturnPositionAfterCollisionType(const Rectangle& rectangleToHandle, const Rectangle& stillRectangle, CollisionType collisionType);

		static CircleQuadrant PositionIsInQuadrant(Vector2<float> position);
		static float TurnAngleIntoAccordingQuadrant(float angleInDegree, Vector2<float> position);

		template<typename PositionalType, typename Func>
		static void HandleCollisions(const Component::Positional& positionalToCollide, std::vector<PositionalType>& objectsToCheck, Func colliderFunc)
		{
			for (const Component::Positional& objectToCheck : objectsToCheck)
			{
				if (&positionalToCollide == &objectToCheck)
					continue;

				if (RectanglesHaveIntersection(positionalToCollide.GetRectangle(), objectToCheck.GetRectangle()))
					colliderFunc(objectToCheck);
			}
		}
		
		template<typename PositionalType, typename Func>
		static void HandleMovementCollisions(Component::Directional& directionalToCollide, std::vector<PositionalType>& objectsToCheck, Func colliderFunc)
		{
			std::vector<MovementCollision<PositionalType>> collisions;
			for (const PositionalType& objectComponents : objectsToCheck)
			{
				const Component::Positional& objectPositional = objectComponents;
				const CollisionInformation collisionInfo = FindIntersectionWithMovement(directionalToCollide.GetPreviousRectangle(), directionalToCollide.GetRectangle(), objectPositional.GetRectangle());

				if (collisionInfo.CollisionAxis != CollisionType::None_CT)
					collisions.emplace_back(&objectComponents, collisionInfo);
			}

			std::sort(collisions.begin(), collisions.end(), [](const MovementCollision<PositionalType>& one, const MovementCollision<PositionalType>& two)
			{ 
				if (one.CollisionInfo.RatioDistanceSpeedMain == two.CollisionInfo.RatioDistanceSpeedMain)
					return one.CollisionInfo.RatioDistanceSpeedSecondary > two.CollisionInfo.RatioDistanceSpeedSecondary; 

				return one.CollisionInfo.RatioDistanceSpeedMain > two.CollisionInfo.RatioDistanceSpeedMain;
			});

			for (size_t currentCollisionIndex = 0; currentCollisionIndex < collisions.size(); currentCollisionIndex++)
			{
				const MovementCollision<PositionalType>& currentCollision = collisions[currentCollisionIndex];
				const Component::Positional& currentCollidedPositional = *currentCollision.CollidedComponent;

				const float positionAfterCollision = ReturnPositionAfterCollisionType(directionalToCollide.GetRectangle(), currentCollidedPositional.GetRectangle(), currentCollision.CollisionInfo.CollisionAxis);
				currentCollision.CollisionInfo.CollisionAxis & CollisionType::AxisX_CT ? directionalToCollide.SetHorizontally(positionAfterCollision) : directionalToCollide.SetVertically(positionAfterCollision);
				colliderFunc(*currentCollision.CollidedComponent, currentCollision.CollisionInfo.CollisionAxis);

				for (currentCollisionIndex++; currentCollisionIndex < collisions.size(); currentCollisionIndex++)
				{
					const Component::Positional& currentCollidedPositionalToCheck = *collisions[currentCollisionIndex].CollidedComponent;

					if (GT::Collider::RectanglesHaveIntersection(directionalToCollide.GetRectangle(), currentCollidedPositionalToCheck.GetRectangle()))
						break;
				}
			}
		}

		/*template<typename PositionalAndDirectionalType, typename Func>
		static void HandleMovementCollisionsWithMovingObjects(Component::Positional& positionalToCollide, std::vector<PositionalAndDirectionalType>& objectsToCheck, Func colliderFunc)
		{
			std::vector<MovementCollision<PositionalAndDirectionalType>> collisions;
			for (const PositionalAndDirectionalType& objectComponents : objectsToCheck)
			{
				const Component::Positional& objectPositional = objectComponents;
				const CollisionInformation collisionInfo = FindIntersectionWithMovement(positionalToCollide.GetPreviousRectangle(), positionalToCollide.GetRectangle(), objectPositional.GetRectangle());
				
				if (collisionInfo.CollisionAxis != CollisionType::None_CT)
					collisions.emplace_back(&objectComponents, collisionInfo);
			}

			std::sort(collisions.begin(), collisions.end(), [](const MovementCollision<PositionalAndDirectionalType>& one, const MovementCollision<PositionalAndDirectionalType>& two)
				{ return one.CollisionInfo.ratioDistanceSpeed > two.CollisionInfo.ratioDistanceSpeed; });

			for (size_t currentCollisionIndex = 0; currentCollisionIndex < collisions.size(); currentCollisionIndex++)
			{
				const MovementCollision<PositionalAndDirectionalType>& currentCollision = collisions[currentCollisionIndex];
				const Component::Positional& currentCollidedPositional = *currentCollision.CollidedComponent;
				const Component::Directional& currentCollidedDirectional = *currentCollision.CollidedComponent;

				const float positionAfterCollision = ReturnPositionAfterCollisionType(positionalToCollide.GetRectangle(), currentCollidedPositional.GetRectangle(), currentCollision.CollisionInfo.CollisionAxis);
				currentCollision.CollisionInfo.CollisionAxis& CollisionType::AxisX_CT ? positionalToCollide.SetHorizontally(positionAfterCollision) : positionalToCollide.SetVertically(positionAfterCollision);
				colliderFunc(currentCollidedPositional, currentCollidedDirectional, currentCollision.CollisionInfo.CollisionAxis);

				for (currentCollisionIndex++; currentCollisionIndex < collisions.size(); currentCollisionIndex++)
				{
					const Component::Positional& currentCollidedPositionalToCheck = *collisions[currentCollisionIndex].CollidedComponent;

					if (GT::Collider::RectanglesHaveIntersection(positionalToCollide.GetRectangle(), currentCollidedPositionalToCheck.GetRectangle()))
						break;
				}
			}
		}*/

		template<typename Func>
		static void HandleBorderCollisions(Component::Directional& objectDirectional, Func colliderFunc)
		{
			const Vector2<float>& position = objectDirectional.GetRectangle().Position;
			const Vector2<float>& size = objectDirectional.GetRectangle().Size;

			if (position.x < 0.0f)
			{
				objectDirectional.SetHorizontally(0.0f);
				colliderFunc(BorderCollision::LeftBorder_BC);
			}
			else if (position.x + size.x > (float)GlobalData::GetMapWidth())
			{
				const float rightBorderPosition = (float)GT::GlobalData::GetMapWidth() - size.x;
				objectDirectional.SetHorizontally(rightBorderPosition);
				colliderFunc(BorderCollision::RightBorder_BC);
			}

			if (position.y < 0.0f)
			{
				objectDirectional.SetVertically(0.0f);
				colliderFunc(BorderCollision::BottomBorder_BC);
			}
			else if (position.y + size.y > (float)GlobalData::GetMapHeight())
			{
				const float topBorderPosition = (float)GT::GlobalData::GetMapHeight() - size.y;
				objectDirectional.SetVertically(topBorderPosition);
				colliderFunc(BorderCollision::TopBorder_BC);
			}
		}
	};

}