#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>

struct Texture
{
private:
	const uint8_t * texture;
	uint8_t width;
	uint8_t height;

public:
	Texture() = default;

	constexpr Texture(const uint8_t * texture, uint8_t width, uint8_t height) :
		texture{texture}, width{width}, height{height}
	{
	}

	constexpr uint8_t getWidth() const
	{
		return this->width;
	}

	constexpr uint8_t getHeight() const
	{
		return this->height;
	}

	uint8_t getPixel(uint8_t x, uint8_t y) const
	{
		const uint8_t row = (y / 8);
		const size_t index = ((row * this->getWidth()) + x);

		const uint8_t bitShift = (y % 8);
		const uint8_t bitMask = (1 << bitShift);

		return ((this->texture[index] & bitMask) >> bitShift);
	}

	uint8_t setPixel(uint8_t x, uint8_t y, uint8_t value)
	{
		const uint8_t row = (y / 8);
		const size_t index = ((row * this->getWidth()) + x);

		const uint8_t bitShift = (y % 8);
		const uint8_t bitMask = (1 << bitShift);

		if(value != 0)
			this->texture[index] |= bitMask;
		else
			this->texture[index] &= ~bitMask;
	}
};

struct ProgmemTexture
{
private:
	const uint8_t * texture;

public:
	Texture() = default;

	constexpr Texture(const uint8_t * texture) :
		texture{texture}
	{
	}

	uint8_t getWidth() const
	{
		return pgm_read_byte(&texture[0]);
	}

	uint8_t getHeight() const
	{
		return pgm_read_byte(&texture[1]);
	}

	uint8_t getPixel(uint8_t x, uint8_t y) const
	{
		const uint8_t row = (y / 8);
		const size_t index = ((row * this->getWidth()) + x);

		const uint8_t bitShift = (y % 8);
		const uint8_t bitMask = (1 << bitShift);

		return ((pgm_read_byte(&this->texture[index]) & bitMask) >> bitShift);
	}
};