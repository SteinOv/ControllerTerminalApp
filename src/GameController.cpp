#include <Windows.h>
#include <Xinput.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "GameController.h"

GameController::GameController(short _deadZone, char _controllerIndex) : deadZone(_deadZone), controllerIndex(_controllerIndex) {}

void GameController::updateControllerState() {
    DWORD dwResult;
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    dwResult = XInputGetState(controllerIndex, &state);

    bLeftTrigger = state.Gamepad.bLeftTrigger;
    bRightTrigger = state.Gamepad.bRightTrigger;

    leftX = state.Gamepad.sThumbLX;
    leftY = state.Gamepad.sThumbLY;
    rightX = state.Gamepad.sThumbRX;
    rightY = state.Gamepad.sThumbRY;

    buttons = state.Gamepad.wButtons;
}

unsigned int GameController::getLeftAnalogState() {
    return toBitmap(leftX, leftY);
}

unsigned int GameController::getRightAnalogState() {
    return toBitmap(rightX, rightY);
}


unsigned int GameController::toBitmap(short X, short Y) const {
    if (abs(X) < deadZone && abs(Y) < deadZone) return 0;

    //X = abs(X) < deadZone ? 0 : X;
    //Y = abs(Y) < deadZone ? 0 : Y;

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
    unsigned int bitmap = intensity * pow(2, 15) + angleRounded;
    return bitmap;
}


