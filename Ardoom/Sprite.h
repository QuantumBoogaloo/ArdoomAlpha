#pragma once

#include <stddef.h>

#include "Geometry.h"

struct Sprite
{
	Point2F position;
	Vector2F velocity;
	size_t textureIndex;
	//size_t textureIndices[4];
	float xScale;
	float yScale;
	float verticalOffset;
};

struct SpriteRenderInfo
{
	size_t index;
	float distance;
};