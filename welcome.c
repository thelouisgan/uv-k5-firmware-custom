/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <string.h>

#include "driver/eeprom.h"
#include "driver/st7565.h"
#include "external/printf/printf.h"
#include "helper/battery.h"
#include "settings.h"
#include "misc.h"
#include "ui/helper.h"
#include "ui/welcome.h"
#include "ui/status.h"
#include "version.h"

void UI_DisplayReleaseKeys(void)
{
	memset(gStatusLine,  0, sizeof(gStatusLine));
	UI_DisplayClear();

	UI_PrintString("RELEASE", 0, 127, 1, 10);
	UI_PrintString("ALL KEYS", 0, 127, 3, 10);

	ST7565_BlitStatusLine();  // blank status line
	ST7565_BlitFullScreen();
}

void UI_DisplayWelcome(void)
{
	char WelcomeString0[16];
	char WelcomeString1[16];

	memset(gStatusLine,  0, sizeof(gStatusLine));
	UI_DisplayClear();

	if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_NONE || gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_FULL_SCREEN) {
		ST7565_FillScreen(0xFF);
	} else {
		memset(WelcomeString0, 0, sizeof(WelcomeString0));
		memset(WelcomeString1, 0, sizeof(WelcomeString1));

		if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_VOLTAGE)
		{
			strcpy(WelcomeString0, "VOLTAGE");
			sprintf(WelcomeString1, "%u.%02uV %u%%",
				gBatteryVoltageAverage / 100,
				gBatteryVoltageAverage % 100,
				BATTERY_VoltsToPercent(gBatteryVoltageAverage));
		}
		else
		{
			EEPROM_ReadBuffer(0x0EB0, WelcomeString0, 16);
			EEPROM_ReadBuffer(0x0EC0, WelcomeString1, 16);
		}

		UI_PrintString(WelcomeString0, 0, 127, 0, 10);
		UI_PrintString(WelcomeString1, 0, 127, 2, 10);
		UI_PrintStringSmallNormal(Version, 0, 128, 6);

		if (gEeprom.POWER_ON_DISPLAY_MODE == POWER_ON_DISPLAY_MODE_IMAGE)
		{
#ifdef ENABLE_WELCOME_IMAGE
			uint8_t all[8][128] = {{0x0,0xfe,0xfe,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x86,0x86,0x86,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x86,0x86,0x86,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x86,0x6,0x86,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0x6,0xfe,0xfe,0x0},{0x0,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x43,0x84,0x3c,0x40,0xb0,0x40,0x50,0x90,0x70,0x80,0xb0,0x40,0x90,0x60,0xc8,0x1a,0xc6,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0x24,0x24,0x1b,0x0,0x1c,0x22,0x22,0x1c,0x0,0x4c,0x52,0x52,0x3e,0x0,0x4c,0x52,0x52,0x3e,0x0,0x1c,0x2a,0x2a,0x2c,0x0,0x2,0x1f,0x22,0x0,0x0,0x0,0x0,0x3f,0x4,0xc,0x33,0x0,0x12,0x2a,0x2a,0x3c,0x0,0x1c,0x22,0x22,0x3f,0x0,0x3e,0x0,0x1c,0x22,0x22,0x1c,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0x0},{0x0,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x60,0x84,0xfa,0x85,0xb2,0xaf,0xde,0xa7,0xcc,0xd9,0xb7,0xd4,0xb3,0xaa,0xca,0xb5,0xea,0x8c,0xff,0x8f,0xf4,0xab,0xc4,0xba,0xa0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3e,0x41,0x21,0x5e,0x0,0x3c,0x40,0x40,0x7c,0x0,0x24,0x54,0x54,0x78,0x0,0x7c,0x4,0x4,0x78,0x0,0x48,0x54,0x54,0x24,0x0,0x7f,0x4,0x4,0x78,0x0,0x38,0x54,0x54,0x58,0x0,0x7c,0x4,0x4,0x78,0x0,0x98,0xa4,0xa4,0x7c,0x0,0x0,0x0,0x0,0x3f,0x40,0x40,0x3f,0x0,0x3,0x1c,0x60,0x1c,0x3,0x0,0x7f,0x8,0x36,0x41,0x0,0x4f,0x49,0x49,0x31,0x0,0x0,0x0,0xff,0xff,0x0},{0x0,0xff,0xff,0x0,0x0,0xb4,0xb4,0xb4,0xb4,0xb4,0x4,0xd0,0xa4,0xda,0xf6,0x3c,0x4c,0xb3,0xcc,0x55,0xb3,0x6f,0x90,0x6f,0x88,0x7b,0x56,0xa4,0x4b,0x38,0xc7,0x38,0xb7,0x44,0x9b,0xb4,0xd7,0xa8,0x6f,0x90,0x67,0x9c,0xfa,0xf4,0x4c,0xd0,0x4,0x34,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0xb4,0x0,0x0,0xff,0xff,0x0},{0x0,0xff,0xff,0x0,0x0,0xfb,0xfb,0x3,0x58,0xa2,0xfc,0xeb,0x5c,0x1f,0xc3,0x0,0x6d,0x5a,0xb6,0xe5,0x9a,0xf5,0x49,0xbf,0xa8,0xcb,0x9b,0x74,0xcb,0x54,0x6b,0x8a,0x7d,0x84,0x7b,0xd6,0xaa,0x6c,0xdb,0x36,0xe5,0xa,0x1f,0xf5,0xdf,0xb4,0xf5,0x20,0x83,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0x7b,0x7b,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0x7b,0x7b,0x7b,0x7b,0xfb,0xfb,0x7b,0x7b,0xfb,0xfb,0x7b,0x7b,0xfb,0x7b,0x7b,0x7b,0x7b,0xfb,0xfb,0x7b,0x7b,0x7b,0x7b,0x7b,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0x7b,0x7b,0x7b,0x7b,0x7b,0xfb,0xfb,0x7b,0x7b,0x7b,0x7b,0xfb,0xfb,0x7b,0x7b,0xfb,0xfb,0x7b,0x7b,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0x0,0x0,0xff,0xff,0x0},{0x0,0xff,0xff,0x0,0x0,0xff,0xff,0xff,0xfe,0xfe,0xfe,0xfe,0xfe,0xff,0xff,0xff,0xff,0xf0,0xe7,0xe,0x9d,0xff,0xba,0xff,0xfa,0x7e,0xeb,0xfe,0x7a,0x7d,0xfd,0x77,0xfe,0xf5,0x7f,0xfa,0x5d,0x1f,0xc5,0xf3,0xf8,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xc0,0xdf,0xdf,0xdf,0xdf,0xff,0xe0,0xc0,0xdf,0xdf,0xc0,0xe0,0xff,0xe0,0xc0,0xdf,0xdf,0xc0,0xe0,0xff,0xdf,0xc0,0xc0,0xdf,0xff,0xee,0xcc,0xdd,0xdd,0xc1,0xe3,0xff,0xff,0xff,0xff,0xff,0xe0,0xc0,0xdf,0xdd,0xc1,0xe1,0xff,0xc0,0xc0,0xfd,0xfd,0xc0,0xc0,0xff,0xc0,0xc0,0xfc,0xf9,0xc0,0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0xff,0xff,0x0},{0x0,0xff,0xff,0x0,0x0,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0x80,0x96,0xba,0xa5,0xbe,0xb5,0xa7,0xbd,0x9f,0x80,0x80,0xbf,0x9b,0xb6,0xab,0xbe,0xb5,0xab,0x80,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0xbb,0x0,0x0,0xff,0xff,0x0},{0x0,0x7f,0x7f,0x60,0x60,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x65,0x60,0x60,0x7f,0x7f,0x0}};
#else
			uint8_t all[8][128];
			memset(all, 0, sizeof(gStatusLine));
#endif
			memcpy(gStatusLine, all[0], 128);
			memcpy(gFrameBuffer, all[1], 128 * 7);
		}

		ST7565_BlitStatusLine();  // blank status line
		ST7565_BlitFullScreen();
	}
}
