#include <avr/io.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "led_driver.h"

/*
static const uint16_t gammatable[] PROGMEM = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 23, 25, 28, 30, 33, 36, 39, 43, 46, 49, 53, 57, 61, 64, 69, 73, 77, 82, 86, 91, 96, 101, 106, 111, 116, 122, 128, 133, 139, 145, 151, 157, 164, 170, 177, 184, 191, 197, 205, 212, 219, 227, 234, 242, 250, 258, 266, 274, 283, 291, 300, 309, 317, 326, 336, 345, 354, 364, 373, 383, 393, 403, 413, 423, 434, 444, 455, 466, 477, 488, 499, 510, 522, 533, 545, 556, 568, 580, 593, 605, 617, 630, 642, 655, 668, 681, 694, 708, 721, 735, 748, 762, 776, 790, 804, 818, 833, 847, 862, 877, 892, 907, 922, 937, 953, 968, 984, 1000, 1016, 1032, 1048, 1064, 1081, 1097, 1114, 1131, 1148, 1165, 1182, 1199, 1217, 1234, 1252, 1270, 1288, 1306, 1324, 1342, 1361, 1379, 1398, 1417, 1436, 1455, 1474, 1494, 1513, 1533, 1552, 1572, 1592, 1612, 1632, 1653, 1673, 1694, 1715, 1735, 1756, 1777, 1799, 1820, 1841, 1863, 1885, 1907, 1929, 1951, 1973, 1995, 2018, 2040, 2063, 2086, 2109, 2132, 2155, 2179, 2202, 2226, 2250, 2273, 2297, 2322, 2346, 2370, 2395, 2419, 2444, 2469, 2494, 2519, 2544, 2570, 2595, 2621, 2647, 2672, 2698, 2725, 2751, 2777, 2804, 2830, 2857, 2884, 2911, 2938, 2965, 2993, 3020, 3048, 3076, 3104, 3132, 3160, 3188, 3217, 3245, 3274, 3303, 3331, 3360, 3390, 3419, 3448, 3478, 3507, 3537, 3567, 3597, 3627, 3658, 3688, 3719, 3749, 3780, 3811, 3842, 3873, 3905, 3936, 3968, 3999, 4031, 4063, 4095};
*/
void pushDot(dot_t *dot)
{
	uint8_t i, j;
	for (i = 0 ; i < NUM_COLORS; i++)
	{
//		uint16_t val = pgm_read_word(*((uint16_t *) dot) + i);
		uint16_t val = *((uint16_t *) dot) + i;
		for (j = 0 ; j < BITSPERLAMP; j++)
		{
			if (val & 0x0800) // if bit 11 is set
				RGB_PORT |= RGB_DATA;
			else
				RGB_PORT &= ~RGB_DATA;
			RGB_PORT |= RGB_CLK;
			RGB_PORT &= ~RGB_CLK;
			val <<= 1;
		}
	}
}

// need some delay after push
void updateDots()
{
	for (uint8_t i = 0; i < 5; i++)
	{
		RGB_PORT |= RGB_DATA;
		RGB_PORT &= ~RGB_DATA;
	}
}

