#pragma once

#include "GT/Utils/Vectors.h"

namespace GT {

	struct Line
	{
		float Point = 0.0f;
		float Length = 0.0f;

		Line() = default;
		Line(float point, float length) noexcept
			: Point(point), Length(length) {}
		Line(GT::Vector2<float> values) noexcept
			: Point(values[0]), Length(values[1]) {}

		// Returns signed distance
		float GetDistanceToPoint(float otherPoint) const
		{
			return Point - otherPoint;
		}
		// Returns signed distance
		float GetDistanceToLine(Line other) const
		{
			const float lineLengthWithHigherCoord = GetLineWithHigherCoordinate(*this, other).Length;
			const float distanceBetweenLines = GetDistanceBetweenPoints(this->Point, other.Point) - lineLengthWithHigherCoord;

			return distanceBetweenLines;
		}
		// Returns unsigned distance
		static float GetDistanceBetweenPoints(float one, float two)
		{
			return abs(one - two);
		}
		// Returns unsigned distance
		static float GetDistanceBetweenLines(Line one, Line two)
		{
			const float lineLengthWithLowerCoord = GetLineWithLowerCoordinate(one, two).Length;
			const float distanceBetweenLines = abs(GetDistanceBetweenPoints(one.Point, two.Point) - lineLengthWithLowerCoord);

			return distanceBetweenLines;
		}

		static Line GetLineWithHigherCoordinate(const Line& one, const Line& two)
		{
			if (one.Point > two.Point)
				return one;
			else
				return two;
		}
		static Line GetLineWithLowerCoordinate(const Line& one, const Line& two)
		{
			if (one.Point < two.Point)
				return one;
			else
				return two;
		}
	};

	struct Rectangle
	{
		Vector2<float> Position = { 0.0f, 0.0f };
		Vector2<float> Size = { 0.0f, 0.0f };

		Rectangle() = default;
		void Init(Vector2<float> coordinates, Vector2<float> size)
		{
			Position = coordinates;
			Size = size;
		}

		Line GetHorizontalLine() const { return { Position.x, Size.x }; }
		Line GetVerticalLine() const { return { Position.y, Size.y }; }

		void MoveHorizontally(float speed) { Position.x += speed; }
		void MoveVertically(float speed) { Position.y += speed; }
	};

}