/*
 * SPDX-License-Identifier: MIT
 * SPDX-FileCopyrightText: Copyright (c) 2024 OpenStickCommunity (gp2040-ce.info)
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>
#include <hardware/i2c.h>
#include "OneBitDisplay.h"
#include "BoardConfig.h"
#include "gpaddon.h"
#include "gamepad.h"
#include "storagemanager.h"
#include "peripheralmanager.h"
#include "peripheral_i2c.h"
#include "peripheral_spi.h"
#include "addons/inputhistory.h"

#ifndef HAS_I2C_DISPLAY
#define HAS_I2C_DISPLAY 0
#endif

#ifndef DISPLAY_I2C_ADDR
#define DISPLAY_I2C_ADDR 0x3C
#endif

#ifndef I2C_SDA_PIN
#define I2C_SDA_PIN -1
#endif

#ifndef I2C_SCL_PIN
#define I2C_SCL_PIN -1
#endif

#ifndef I2C_BLOCK
#define I2C_BLOCK i2c0
#endif

#ifndef I2C_SPEED
#define I2C_SPEED 800000
#endif

#ifndef DISPLAY_SIZE
#define DISPLAY_SIZE OLED_128x64
#endif

#ifndef DISPLAY_FLIP
#define DISPLAY_FLIP 0
#endif

#ifndef DISPLAY_INVERT
#define DISPLAY_INVERT 0
#endif

#ifndef DISPLAY_USEWIRE
#define DISPLAY_USEWIRE 1
#endif

#ifndef DISPLAY_SAVER_TIMEOUT
#define DISPLAY_SAVER_TIMEOUT 0
#endif

#ifndef BUTTON_LAYOUT
#define BUTTON_LAYOUT BUTTON_LAYOUT_STICK
#endif

#ifndef BUTTON_LAYOUT_RIGHT
#define BUTTON_LAYOUT_RIGHT BUTTON_LAYOUT_VEWLIX
#endif

#ifndef SPLASH_MODE
#define SPLASH_MODE SPLASH_MODE_NONE
#endif

#ifndef SPLASH_CHOICE
#define SPLASH_CHOICE SPLASH_CHOICE_MAIN
#endif

#ifndef SPLASH_DURATION
#define SPLASH_DURATION 7500 // Duration in milliseconds
#endif

#ifndef DISPLAY_TURN_OFF_WHEN_SUSPENDED
#define DISPLAY_TURN_OFF_WHEN_SUSPENDED 0
#endif

#ifndef DEFAULT_SPLASH
#define DEFAULT_SPLASH \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xDF,0xC0, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xC1,0xFF,0xA0, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xCF,0xFE,0x80, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xE0,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xAB,0xC0,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x00,0x00,0xFB,0x83,0xFF,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x01,0xFF,0x00,0x01,0xF3,0x07,0xFC,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x07,0xFF,0x00,0x03,0xE0,0x3F,0xF4,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x2C,0x38,0x0A,0xE7,0x80,0x03,0xC0,0x5F,0x80,0x00, \
	0x00,0x00,0x00,0x20,0x07,0x81,0xFF,0x39,0xC3,0xC7,0x01,0xD7,0x80,0x3F,0x00,0x00, \
	0x00,0x00,0x00,0xE0,0x1F,0xE7,0xFF,0x79,0xC7,0x87,0x9F,0xA7,0x80,0x6E,0x3C,0x00, \
	0x00,0x00,0xA0,0xC0,0x3F,0xEA,0xE7,0xF3,0xEF,0x07,0x7F,0xC7,0x01,0xCF,0xFF,0x80, \
	0x00,0x03,0x8F,0xFC,0x7F,0xC3,0xC7,0x7F,0xFE,0x0F,0x7E,0x8F,0x87,0xDF,0xFC,0x00, \
	0x00,0x0F,0xFF,0xFF,0x73,0xC7,0x87,0xFF,0xDE,0x0E,0x50,0x07,0x1F,0x1F,0xD0,0x00, \
	0x00,0x1F,0x57,0xFF,0xE7,0x8F,0x07,0xFF,0x1C,0x3E,0x00,0x0F,0xFF,0x7F,0x00,0x00, \
	0x00,0x7E,0x0B,0x8F,0x8F,0x8E,0x0F,0xFF,0x9E,0x7C,0x00,0x07,0xFD,0xFC,0x00,0x00, \
	0x00,0x7C,0x37,0x9F,0x1F,0x1E,0x0F,0x87,0x1E,0xF8,0x00,0x07,0xF0,0x30,0x00,0x00, \
	0x00,0xF1,0xF7,0xFE,0x1E,0x1C,0x3E,0x0E,0x1F,0xF0,0x00,0x01,0x40,0x28,0x00,0x00, \
	0x01,0xEF,0xE7,0xF8,0x3C,0x3E,0x7C,0x0F,0x1F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x03,0xFF,0x8F,0xF0,0x7F,0xFE,0xF8,0x0E,0x0F,0x80,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x03,0xFF,0xCF,0xC0,0xFF,0xFF,0xF0,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x07,0x8B,0xFF,0x01,0xFF,0x8F,0xC0,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x07,0x87,0xFE,0x01,0xFE,0x0F,0x80,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x07,0x1F,0xDE,0x03,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x07,0xBF,0x9E,0x01,0xC0,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x07,0xFF,0x9C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x07,0xFB,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x03,0xE7,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x01,0x47,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x0E,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
#endif

// i2c Display Module
#define I2CDisplayName "I2CDisplay"

// i2C OLED Display
class I2CDisplayAddon : public GPAddon
{
public:
	virtual bool available();
	virtual void setup();
	virtual void preprocess() {}
	virtual void process();
	virtual std::string name() { return I2CDisplayName; }
	virtual void attachInputHistoryAddon(InputHistoryAddon*);
private:
	int initDisplay(int typeOverride);
	bool isSH1106(int detectedDisplay);
	void clearScreen(int render); // DisplayModule
	void drawStickless(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawWasdBox(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawArcadeStick(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawStatusBar(Gamepad*);
	void drawText(int startX, int startY, std::string text);
	void initMenu(char**);
	//Adding my stuff here, remember to sort before PR
	void drawDiamond(int cx, int cy, int size, uint8_t colour, uint8_t filled);
	void drawUDLR(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawMAMEA(int startX, int startY, int buttonSize, int buttonPadding);
	void drawOpenCore0WASDA(int startX, int startY, int buttonSize, int buttonPadding);
	void drawOpenCore0WASDB(int startX, int startY, int buttonSize, int buttonPadding);
	void drawMAMEB(int startX, int startY, int buttonSize, int buttonPadding);
	void drawMAME8B(int startX, int startY, int buttonSize, int buttonPadding);
	void drawKeyboardAngled(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawVewlix(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawVewlix7(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawSega2p(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawNoir8(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawCapcom(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawCapcom6(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawSticklessButtons(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawWasdButtons(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawArcadeButtons(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawSplashScreen(int splashMode, uint8_t* splashChoice, int splashSpeed);
	void drawDancepadA(int startX, int startY, int buttonSize, int buttonPadding);
	void drawDancepadB(int startX, int startY, int buttonSize, int buttonPadding);
	void drawTwinStickA(int startX, int startY, int buttonSize, int buttonPadding);
	void drawTwinStickB(int startX, int startY, int buttonSize, int buttonPadding);
	void drawBlankA(int startX, int startY, int buttonSize, int buttonPadding);
	void drawBlankB(int startX, int startY, int buttonSize, int buttonPadding);
	void drawVLXA(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawVLXB(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawButtonLayoutLeft(ButtonLayoutParamsLeft& options);
	void drawButtonLayoutRight(ButtonLayoutParamsRight& options);
	void drawFightboard(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawFightboardMirrored(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawFightboardStick(int startX, int startY, int buttonRadius, int buttonPadding);
	void drawFightboardStickMirrored(int startX, int startY, int buttonRadius, int buttonPadding);
	bool pressedUp();
	bool pressedDown();
	bool pressedLeft();
	bool pressedRight();
	const DisplayOptions& getDisplayOptions();
	bool isDisplayPowerOff();
	void setDisplayPower(uint8_t status);
	uint32_t displaySaverTimeout = 0;
	int32_t displaySaverTimer;
	uint8_t displayIsPowerOn = 1;
	uint32_t prevMillis;
	uint8_t ucBackBuffer[1024];
	OBDISP obd;
	std::string statusBar;
	Gamepad* gamepad;
	Gamepad* pGamepad;
	bool configMode;

	enum DisplayMode {
		CONFIG_INSTRUCTION,
		BUTTONS,
		SPLASH
	};

	DisplayMode getDisplayMode();
	DisplayMode prevDisplayMode;
	uint16_t prevButtonState;
	bool turnOffWhenSuspended;
	bool isInputHistoryEnabled;
	InputHistoryAddon* inputHistoryAddon;
};

#endif
