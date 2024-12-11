#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

const float verticalSpeed = 6400.0;
const float verticalAcc = 6400.0;

const byte channelWidth = 12;
const bool alwaysStart = false;

/**
 * 
 * 0: second
 * 1: R1, R2, R3, R4
 * 5: Rotation Speed (pulse/s), Rotation Acc
 * 7: Height
 * 8: R5, R5-V
 * 10: frequency, duty cycle
 * 
 */
const int32_t animConfig[][channelWidth] = {

{1, 1, 1, 1, 1, 600, 60, 0, 0, 0, 60, 20, },
{16, 1, 1, 1, 1, 600, 60, 105000, 1, 0, 60, 20, },
{30, 1, 0, 1, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{32, 1, 0, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{34, 0, 0, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{46, 0, 0, 0, 1, 9600, 700, 105000, 1, 0, 60, 20, },
{47, 0, 0, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{48, 0, 0, 1, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{49, 0, 0, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{50, 0, 1, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{51, 0, 0, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{52, 1, 0, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{53, 0, 0, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{55, 0, 0, 0, 0, 9600, 700, 105000, 0, 0, 60, 20, },
{56, 1, 1, 1, 1, 9600, 700, 105000, 0, 0, 60, 20, },
{59, 1, 0, 1, 1, 9600, 700, 105000, 0, 0, 60, 20, },
{60, 0, 0, 0, 0, 9600, 700, 105000, 1, 1, 60, 20, },
{62, 0, 0, 0, 1, 9600, 700, 105000, 1, 0, 60, 20, },
{63, 0, 1, 0, 1, 9600, 700, 105000, 1, 0, 60, 20, },
{64, 0, 1, 0, 1, 9600, 700, 105000, 0, 0, 60, 20, },
{67, 0, 0, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{70, 0, 0, 0, 0, 9600, 700, 105000, 1, 1, 60, 20, },
{73, 0, 0, 0, 0, 9600, 700, 105000, 1, 0, 60, 20, },
{74, 1, 1, 1, 1, 9600, 700, 105000, 1, 1, 60, 20, },
{90, 1, 1, 1, 0, 9600, 700, 105000, 1, 1, 60, 20, },
{94, 1, 1, 0, 0, 9600, 700, 105000, 1, 1, 60, 20, },
{96, 0, 0, 1, 1, 9600, 700, 105000, 1, 1, 60, 20, },
{98, 0, 1, 0, 1, 9600, 700, 105000, 1, 1, 60, 20, },
{100, 0, 1, 0, 1, 0, 700, 0, 1, 1, 60, 20, },
{101, 1, 0, 1, 0, 0, 700, 0, 1, 1, 60, 20, },
{106, 0, 0, 0, 0, 0, 700, 0, 1, 1, 60, 20, },
{116, 0, 0, 0, 0, 0, 700, 0, 0, 1, 60, 20, },
{118, 1, 1, 1, 1, 0, 700, 0, 0, 1, 60, 20, },
{121, 1, 1, 1, 1, 0, 700, 0, 0, 0, 60, 20, },
{127, 0, 0, 0, 0, 0, 700, 0, 0, 0, 60, 20, },

};

#endif

