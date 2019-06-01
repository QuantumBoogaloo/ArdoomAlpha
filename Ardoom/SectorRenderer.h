#pragma once

#include "Constants.h"
#include "Geometry.h"
#include "Camera.h"
#include "Sector.h"
#include "Maths.h"

template<typename Renderer>
struct SectorRenderer
{
	// TODO: Eliminate the array by fusing the two loops
	static void render3D(Renderer & renderer, const Camera & camera, const Sector & sector)
	{
		// Allocate a point buffer
		Point2F pointsTransformed[Sector::maxPoints];

		// Cache the sine and cosine to avoid recalculation
		const float cosine = cos(-camera.angle);
		const float sine = sin(-camera.angle);

		for(uint8_t i = 0; i < sector.getPointCount(); ++i)
		{
			const Point2F & point = sector.getPoint(i);

			// Translate local to camera
			const Vector2F cameraOffset = (point - camera.position);

			// Rotate around camera
			const Point2F rotatedPoint { (cameraOffset.x * cosine) - (cameraOffset.y * sine), (cameraOffset.x * sine) + (cameraOffset.y * cosine) };

			pointsTransformed[i] = rotatedPoint;
		}

		// Cache the screen dimensions
		const uint8_t screenWidth = renderer.width();
		const uint8_t screenHeight = renderer.height();
		const uint8_t halfScreenWidth = (screenWidth / 2);
		const uint8_t halfScreenHeight = (screenHeight / 2);

		// Calculate the centre of the screen
		const Point2F screenCentre { halfScreenWidth, halfScreenHeight };

		const float viewWidth = screenWidth;
		const float viewHeight = screenHeight;

		for(uint8_t i = 0, j = 1; i < sector.getPointCount(); ++i, ++j)
		{
			if(j == sector.getPointCount())
				j = 0;

			// Don't render if both vertices are off screen
			if((pointsTransformed[i].x <= 0) && (pointsTransformed[j].x <= 0))
				continue;

			// TODO: Multiply by the inverse
			// const float inverseY = (1.0f / pointsTransformed[i].y);
			// const float inverseFOV = (viewWidth * inverseY);
			// const float inverseHeight = (viewHeight * inverseY);

			const auto adjustedStartX = (pointsTransformed[i].x <= 0) ? 1.0f : pointsTransformed[i].x;

			// TODO: consider decomposing 'maths::map' to reduce the number of calculations involved
			// (The compiler is probably doing this already)
			const auto adjustedStartY = (pointsTransformed[i].x <= 0) ? maths::map(1.0f, pointsTransformed[i].x, pointsTransformed[j].x, pointsTransformed[i].y, pointsTransformed[j].y) : pointsTransformed[i].y;

			const auto startX = (adjustedStartY * (viewWidth / adjustedStartX));
			const auto startLineHeight = (viewHeight / adjustedStartX);

			const auto adjustedEndX = (pointsTransformed[j].x <= 0) ? 1.0f : pointsTransformed[j].x;

			// TODO: consider decomposing 'maths::map' to reduce the number of calculations involved
			// (The compiler is probably doing this already)
			const auto adjustedEndY = (pointsTransformed[j].x <= 0) ? maths::map(1.0f, pointsTransformed[i].x, pointsTransformed[j].x, pointsTransformed[i].y, pointsTransformed[j].y) : pointsTransformed[j].y;

			const auto endX = (adjustedEndY * (viewWidth / adjustedEndX));
			const auto endLineHeight = (viewHeight / adjustedEndX);

			const auto startRight = (screenCentre.x + startX);
			const auto startTop = (screenCentre.y - startLineHeight);
			const auto startBottom = (screenCentre.y + startLineHeight);

			const auto endRight = (screenCentre.x + endX);
			const auto endTop = (screenCentre.y - endLineHeight);
			const auto endBottom = (screenCentre.y + endLineHeight);

			// Top
			renderer.drawLine(startRight, startTop, endRight, endTop);

			// Bottom
			renderer.drawLine(startRight, startBottom, endRight, endBottom);

			// Left
			renderer.drawFastVLine(startRight, startTop, startLineHeight * 2);

			// Right
			renderer.drawFastVLine(endRight, endTop, endLineHeight * 2);

			// Debug info: identify which map coordinate you're looking at
			const Point2F & point = sector.getPoint(i);
			renderer.setCursor(startRight, startTop - 8);
			renderer.print(point.x);
			renderer.setCursor(startRight, startTop);
			renderer.print(point.y);
		}

		renderer.drawPixel(screenCentre.x, screenCentre.y);
	}

	// TODO: Eliminate the array by fusing the two loops
	static void render2D(Renderer & renderer, const Camera & camera, const Sector & sector)
	{
		// Calculate the centre of the screen
		const Point2F screenCentre { static_cast<float>(renderer.width() / 2), static_cast<float>(renderer.height() / 2) };

		// Allocate a point buffer
		Point2F pointsTransformed[Sector::maxPoints];

		// Transform the points
		for(uint8_t i = 0; i < sector.getPointCount(); ++i)
		{
			const Point2F & point = sector.getPoint(i);
			pointsTransformed[i] = (screenCentre + (point - camera.position));
		}

		// Render the points
		for(uint8_t i = 0, j = 1; i < sector.getPointCount(); ++i, ++j)
		{
			if(j == sector.getPointCount())
				j = 0;

			renderer.drawLine(pointsTransformed[i].x, pointsTransformed[i].y, pointsTransformed[j].x, pointsTransformed[j].y);
		}

		// TODO: Find a better place to put this
		constexpr float lineLength = 4;

		// Calculate the direction vector of the camera
		const Vector2F cameraDirection { cos(camera.angle), sin(camera.angle) };

		// Calculate the end point of the line representing the player
		const Point2U8 endPoint = static_cast<Point2U8>(screenCentre + (cameraDirection * lineLength));

		// Render the camera line
		renderer.drawLine(screenCentre.x, screenCentre.y, endPoint.x, endPoint.y);
	}
};