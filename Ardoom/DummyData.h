#pragma once

#include <avr/pgmspace.h>

#include <stdint.h>

// Temporary data for the sake of testing
const uint8_t dummyData[] PROGMEM
{
	5,
	10, 0,
	20, 10,
	20, 20,
	0, 20,
	0, 10,
};