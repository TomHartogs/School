#pragma once

#include <stdint.h>

struct buttonStates
{
	bool digitalButtonState[15];
	uint16_t analogButtonState[6];
};

enum ledModes
{
	AllBlinking = 0x01,
	OneFlashThenOn = 0x02,
	TwoFlashesThenOn = 0x03,
	ThreeFlashesThenOn = 0x04,
	FourFlashesThenOn = 0x05,
	OneOn = 0x06,
	TwoOn = 0x07,
	ThreeOn = 0x08,
	FourOn = 0x09,
	Rotating = 0x0a,
	Blinking = 0x0b,
	SlowBlinking = 0x0c,
	Alternating = 0x0d
};

enum digitalButtons
{
	dPadUp = 0,
	dPadDown,
	dPadLeft,
	dPadRight,
	startBtn,
	bckBtn,
	leftStickPress,
	rightStickPress,
	LBBtn,
	RBBtn,
	xboxLogo,
	ABtn,
	BBtn,
	XBtn,
	YBtn,
};

enum analogButtons
{
	leftTrigger = 0,
	rightTrigger,
	leftStickX,
	leftStickY,
	rightStickX,
	rightStickY
};
