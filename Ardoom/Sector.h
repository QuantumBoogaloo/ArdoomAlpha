#pragma once

#include <stddef.h>
#include <stdint.h>

#include "Geometry.h"

class Sector
{
public:
	static constexpr uint8_t maxPoints = 16;

private:
	const unsigned char * data;
	uint8_t pointCount;

public:
	Sector(const unsigned char * data) :
		data{&data[1]}, pointCount{pgm_read_byte(&data[0])}
	{
		//this->z = pgm_read_byte(&sectorPointer[1]);
		//this->height = pgm_read_byte(&sectorPointer[2]);
	}

	constexpr Sector(const unsigned char * data, uint8_t pointCount) :
		data { data }, pointCount { pointCount }
	{
	}

	constexpr uint8_t getPointCount() const
	{
		return  this->pointCount;
	}

	Point2F getPoint(uint8_t index) const
	{
		// TODO: fix this
		// Temporary implementation for the sake of testing
		return { pgm_read_byte(&this->data[(index * 2) + 0]), pgm_read_byte(&this->data[(index * 2) + 1]) };
	}
};