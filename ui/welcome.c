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
			uint8_t all[8][128] = {{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x3f,0x1f,0x1f,0xf,0xf,0xf,0xf,0x2f,0x1f,0x7f,0x17,0x11,0x1,0x1,0x1,0x1,0x81,0x1,0x86,0x8e,0x80,0x81,0x81,0x1,0x3,0x7,0x3,0x1,0x80,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x40,0xe0,0xf0,0xf0,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0x78,0x78,0xf8,0xf8,0xf0,0xf0,0xf0,0xf0,0xe0,0xe0,0xc0,0x80,0x0,0x1,0x3,0x3,0x3,0x7,0xf,0x1f,0x3f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xf6,0xfd,0xed,0x0,0x0,0x80,0xe0,0xf0,0x80,0x0,0x0,0x0,0x0,0xb4,0x70,0xfa,0xc6,0xfd,0x8f,0x88,0xff,0xf7,0xfe,0xf9,0xc6,0x72,0x1,0x20,0x34,0xf6,0xff,0xff,0xfc,0xe3,0xc4,0xfe,0xf8,0xe8,0xe0,0x0,0x0,0x0,0x0,0x0,0x80,0xf6,0xce,0xaf,0xb7,0xc7,0xcf,0xff,0xff,0xff,0xf7,0xff,0xff,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfc,0xf8,0xe0,0x80,0x0,0x0,0x0,0x0,0xc0,0xc3,0xf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xfd,0x3f,0xdf,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xfe,0xfc,0xfc,0xfb,0xdf,0xd7,0xf7,0xef,0xef,0xae,0x3f,0x5f,0xff,0xbf,0xa7,0xa3,0x20,0x0,0xc0,0xe1,0xcb,0xd7,0xef,0xef,0xf7,0xff,0xf3,0xfb,0xf1,0xe0,0xc0,0x80,0x0,0x0,0x1,0xc3,0x3,0xf,0x83,0x8,0xb8,0xff,0xff,0xfd,0xfe,0xfe,0xfc,0xfe,0xfe,0xfc,0xfd,0xfd,0x3b,0x9f,0xdf,0xdf,0xdd,0x1,0xff,0xff,0x3f,0xdf,0xdf,0xde,0x0,0x0,0x0,0x0,0xb,0x5f,0xdf,0x9f,0x1f,0xff,0xdf,0x13,0x9f,0xff,0xff,0x9f,0xdf,0xdf,0x1f,0x3f,0xff,0xdf,0x1f,0xff,0xdf,0xdf,0x1f,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x77,0xff,0xff,0xff,0xff,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xbc,0xf9,0xc3,0x2,0xc8,0xfd,0xed,0xfa,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0xff,0xff,0xff,0xff,0xf9,0xff,0xf8,0xd,0x0,0x7f,0xff,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x73,0xe7,0xe7,0xf7,0xe0,0x7f,0x7f,0xf0,0xe6,0xee,0x6e,0x0,0x0,0x0,0xe0,0xe0,0xef,0xef,0xf7,0xf8,0xff,0xef,0xe0,0xef,0xff,0xf3,0xe1,0xee,0xf6,0xf0,0xf0,0xff,0xef,0xe0,0xef,0xff,0xef,0xe0,0xe0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfc,0xf8,0xe0,0xf3,0xf7,0xff,0xff,0xfc,0x81,0x7,0xff,0xe7,0xe3,0x71,0x71,0xf1,0xf1,0xf1,0xf8,0xf7,0xdf,0xff,0xfb,0xf7,0xff,0xf9,0xf9,0x73,0xf3,0xff,0xff,0xff,0xff,0xff,0xff,0xef,0xef,0xcf,0xef,0xff,0xd8,0xb0,0xc3,0xc7,0x9f,0x3f,0x3f,0x7f,0xff,0xff,0xff,0xfb,0xfb,0xb,0x7,0xff,0xff,0xff,0xff,0x7f,0x3f,0x3f,0x1e,0x1f,0x8e,0x47,0x60,0xf0,0xfc,0x8,0x7,0xff,0x7f,0x7e,0xfe,0xfe,0xff,0x5f,0x5f,0xff,0xff,0xff,0x7f,0x7f,0x7f,0xfe,0xfe,0xff,0xff,0x7f,0xff,0x7e,0x7f,0xff,0xff,0xff,0xff,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1f,0x1f,0xf,0xf,0xf,0xf,0x1f,0x3f,0x7f,0x7f,0xe0,0xe0,0xe0,0xfc,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1c,0x99,0x2b,0xc7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x7f,0x3f,0xff,0xff,0xff,0xff,0xff,0xfd,0xfd,0xea,0xf8,0xf4,0xf4,0xfc,0xf9,0xb9,0x80,0x80,0xb9,0xe0,0x80,0xb8,0xb8,0xba,0xd8,0xff,0x99,0xb3,0xb3,0xa6,0xcf,0xff,0xc0,0x80,0xbe,0xbf,0xbe,0xc0,0xfb,0xbf,0x80,0x80,0xbf,0xff,0x84,0xb7,0xbf,0xda,0x80,0xbf,0xbf,0x80,0x80,0xfe,0xff,0x80,0x80,0xbf,0xff,0xb8,0xb3,0xb7,0xc4,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x1f,0x1f,0x1f,0xf,0xc,0x8,0x8,0x4,0x4,0x0,0x0,0x0,0x0,0x0,0x1,0x3,0xb,0x1f,0x3f,0x7f,0x3f,0x1f,0xf,0xf,0xf,0xe,0xf,0xf,0xe,0xf,0x3f,0x5f,0x97,0xb7,0x1f,0xf,0xf,0xf,0x7,0x3,0x0,0x2,0x2,0x3,0x3,0x3,0xf,0x1f,0x3f,0x3f,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xf8,0xf8,0xf8,0xe0,0x80,0x80,0x0,0x0,0x0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xc,0x18,0x0,0x0,0x0,0x0,0x4,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x10,0x18,0x18,0x18,0x10,0x4,0x4,0x4,0x4,0x0,0xc,0x10,0x30,0x30,0x30,0x30,0x30,0x30,0x0,0x0,0x0,0x1,0x1,0xc3,0xe3,0xf7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}};
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
