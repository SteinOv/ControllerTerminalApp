#include <Windows.h>
#include <Xinput.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "GameController.h"

#include <string>
#include <iostream>
using namespace std;

GameController::GameController(char _controllerIndex, short _analogDeadZone, BYTE _triggerDeadZone) :
    controllerIndex(_controllerIndex), analogDeadZone(_analogDeadZone), triggerDeadZone(_triggerDeadZone) {}

void GameController::updateControllerState() {
    DWORD dwResult;
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    dwResult = XInputGetState(controllerIndex, &state);

    leftTrigger = state.Gamepad.bLeftTrigger;
    rightTrigger = state.Gamepad.bRightTrigger;

    leftX = state.Gamepad.sThumbLX;
    leftY = state.Gamepad.sThumbLY;
    rightX = state.Gamepad.sThumbRX;
    rightY = state.Gamepad.sThumbRY;

    buttons = state.Gamepad.wButtons;
}

unsigned short GameController::getButtonStates() const {
    return buttons;
}

unsigned int GameController::getLeftAnalogState() const {
    return toBitmask(leftX, leftY);
}

unsigned int GameController::getRightAnalogState() const {
    return toBitmask(rightX, rightY);
}

unsigned int GameController::toBitmask(short X, short Y) const {
    if (abs(X) < analogDeadZone && abs(Y) < analogDeadZone) return 0;

    // Clockwise angle (0° at 12 o'clock)
    unsigned short angleRounded;
    if (Y != 0) {
        float angle = atanf((float) X / (float) Y) * 180 / (float) M_PI;
        if (Y < 0) angle += 180;
        else if (X < 0) angle += 360;
        angleRounded = (unsigned short) round(angle);
    } else {
        angleRounded = X < 0 ? 270 : 90;
    }

    // Intensity normalized from 0 to sizeof(BYTE) (
    unsigned short intensity = (unsigned short) round(sqrt(X * X + Y * Y));

    // Map 2 shorts into int
    unsigned int bitmask = intensity * pow(2, 15) + angleRounded;
    return bitmask;
}

BYTE GameController::getLeftTriggerState() const {
    return leftTrigger;
}

BYTE GameController::getRightTriggerState() const {
    return rightTrigger;
}


