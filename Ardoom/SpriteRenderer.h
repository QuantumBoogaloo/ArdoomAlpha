#pragma once

// For uint8_t
#include <stdint.h>

// For size_t
#include <stddef.h>

// For cos, sin
#include <math.h>

#include "Constants.h"
#include "Geometry.h"
#include "Camera.h"
#include "Maths.h"
#include "Sprite.h"
#include "Texture.h"

template<typename Renderer>
struct SpriteRenderer
{
	template< size_t spriteCount, size_t textureCount >
	static void render(Renderer & renderer, const Camera & camera, Sprite (&sprites)[spriteCount], Texture (&textures)[textureCount])
	{
		const size_t windowWidth = static_cast<size_t>(renderer.width());
		const size_t windowHeight = static_cast<size_t>(renderer.height());

		const size_t windowStartX = 0;
		const size_t windowEndX = (windowWidth - 1);

		const size_t windowStartY = 0;
		const size_t windowEndY = (windowHeight - 1);

		const Vector2F cameraDirection = { cos(angle), sin(angle) };
		// TODO: camera plane

		for(size_t index = 0; index < spriteCount; ++index)
		{
			const auto & sprite = sprites[index];

			// Sprite offset relative to camera
			const Vector2F spriteOffset = (sprite.position - camera.position);

			// Matrix magic
			const float inverseDeterminant = (1.0f / ((camera.plane.x * camera.direction.y) - (camera.direction.x * camera.plane.y)));

			// These are in 2D camera space
			const float transformX = (inverseDeterminant * ((camera.direction.y * spriteOffset.x) - (camera.direction.x * spriteOffset.y)));
			const float transformY = (inverseDeterminant * ((-camera.plane.y * spriteOffset.x) + (camera.plane.x * spriteOffset.y)));

			// Don't draw if sprite isn't visible
			if(transformY <= 0)
				continue;

			// Cache for better calculation
			const float scaleFactor = (windowHeight / transformY);

			// Fear not, this is correct
			const size_t spriteWidth = static_cast<size_t>(scaleFactor * sprite.xScale);
			const size_t spriteHeight = static_cast<size_t>(scaleFactor * sprite.yScale);

			// Cache calculated values
			const int halfWindowWidth = static_cast<int>(windowWidth / 2);
			const int halfSpriteWidth = static_cast<int>(spriteWidth / 2);

			// Calculate X range
			const int xMidpoint = static_cast<int>(halfWindowWidth * (1 + (transformX / transformY)));
			const int xStart = (xMidpoint - halfSpriteWidth);
			const int xEnd = (xMidpoint + halfSpriteWidth);

			// If the sprite is offscreen, skip it
			if((xEnd <= 0) || (xStart >= static_cast<int>(windowWidth)))
				continue;

			// Clamp the loop limits to skip values outside the window
			const std::size_t clampedXStart = std::max<int>(xStart, windowStartX);
			const std::size_t clampedXEnd = std::min<std::size_t>(xEnd - 1, windowEndX);
			// std::min<std::size_t>(xEnd, windowWidth);

			// Precalculate start and end x
			const std::size_t startIndex = clampedXStart;
			const std::size_t endIndex = clampedXEnd;
			// std::min(clampedXEnd - 1, windowEndX);

			// If the sprite is completely occluded, skip it
			/*if((transformY > this->distanceBuffer[startIndex]) && (transformY > this->distanceBuffer[endIndex]))
				continue;*/

			// Cache calculated values
			const int halfWindowHeight = static_cast<int>(windowHeight / 2);
			const int halfSpriteHeight = static_cast<int>(spriteHeight / 2);

			// Calculate vertical offset
			const int verticalOffset = static_cast<int>((sprite.verticalOffset * halfWindowHeight) / transformY);

			// Tranformed half window height
			const int ceilingOffset = static_cast<int>(halfWindowHeight / transformY);
			const int floorOffset = static_cast<int>(halfWindowHeight / transformY);

			// Calculate ceilingY
			const int ceilingY = (halfWindowHeight - ceilingOffset);
			
			// Calculate floorY
			const int floorY = (halfWindowHeight + floorOffset);

			// Calculate Y range
			const int yMidpoint = (halfWindowHeight + verticalOffset);
			const int yStart = (yMidpoint - halfSpriteHeight);
			const int yEnd = (yMidpoint + halfSpriteHeight);

			// If the sprite is offscreen, skip it
			if((yEnd <= 0) || (yStart >= static_cast<int>(windowHeight)))
				continue;

			// Clamp the loop limits to skip values outside the window
			const size_t clampedYStart = utils::max<int>(utils::max<int>(yStart, ceilingY), 0);
			const size_t clampedYEnd = utils::min<size_t>(utils::min<int>(yEnd, floorY), windowHeight);

			// Get texture
			const auto & texture = this->textures[sprite.textureIndex];
			
			/*const Direction direction =
				(utils::abs(spriteOffset.x) > utils::abs(spriteOffset.y))
				? ((spriteOffset.x >= 0) ? Direction::PositiveX : Direction::NegativeX)
				: ((spriteOffset.y >= 0) ? Direction::PositiveY : Direction::NegativeY);

			const size_t textureIndex = getIndex(direction);

			const auto & texture = this->textures[sprite.textureIndices[textureIndex]];*/
			
			const size_t textureWidth = texture.getWidth();
			const size_t textureHeight = texture.getHeight();

			// TODO: Implement occlusion

			// Draw the sprite
			for(size_t x = clampedXStart; x <= clampedXEnd; ++x)
			{
				// Only draw a sprite column if it's not occluded by a block
				/*if(transformY > this->distanceBuffer[x])
					continue;*/

				// Convert screen coordinate to texture coordinate
				const size_t textureX = static_cast<size_t>(map<float>(x, xStart, xEnd, 0, textureWidth));

				for(size_t y = clampedYStart; y < clampedYEnd; ++y)
				{
					// Convert screen coordinate to texture coordinate
					const size_t textureY = static_cast<size_t>(map<float>(y, yStart, yEnd, 0, textureHeight));

					const uint8_t colour = texture.getPixel(textureX, textureY);

					#if defined(BLACK_TRANSPARENT)
					if(colour != 0)
						this->renderer.drawPixel(x, y);
					#elif defined(BIT2_TRANSPARENT)
					if(colour < 2)
						this->renderer.drawPixel(x, y, colour);
					#else
					this->renderer.drawPixel(x, y, colour);
					#endif
				}
			}

			#if defined(DEBUG_RENDER_SPRITE_ANCHORS)
			this->renderer.drawPixel(xMidpoint, std::max(ceilingY, 0));
			this->renderer.drawPixel(xMidpoint, std::min(floorY, static_cast<int>(windowHeight - 1)));
			#endif
		}
	}
};