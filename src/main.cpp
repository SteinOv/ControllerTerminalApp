#include <Windows.h>
#include <Xinput.h>

#include <iostream>
#include <string>

#include "GameController.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
using namespace std;

int main()
{
    const char CONTROLLER_INDEX = 0;
    const short ANALOG_DEAD_ZONE = 3000;
    const BYTE TRIGGER_DEAD_ZONE = 0;

    static const string buttonMapping[] = {
            "dpad up",
            "dpad down",
            "dpad left",
            "dpad right",
            "start",
            "back",
            "analog left",
            "analog right",
            "bumper left",
            "bumper right",
            "none",
            "none",
            "A",
            "B",
            "X",
            "Y",
    };

    DWORD dwResult;

    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    // Simply get the state of the controller from XInput.
    dwResult = XInputGetState(CONTROLLER_INDEX, &state);

    if (dwResult == ERROR_SUCCESS)
    {
        auto *gameController = new GameController(CONTROLLER_INDEX, ANALOG_DEAD_ZONE, TRIGGER_DEAD_ZONE);
        while (true)
        {
            bool printedAnything = false;
            gameController->updateControllerState();
            unsigned int leftAnalog = gameController->getLeftAnalogState();
            unsigned int rightAnalog = gameController->getRightAnalogState();
            unsigned short buttons = gameController->getButtonStates();
            BYTE leftTrigger = gameController->getLeftTriggerState();
            BYTE rightTrigger = gameController->getRightTriggerState();

            if (leftAnalog > 0)
            {
                cout << "left analog; angle: " + to_string(leftAnalog % (int) pow(2, 15)) +
                        ", intensity: " + to_string((int) floor(leftAnalog / (int) pow(2, 15))) << endl;
                printedAnything = true;
            }
            if (rightAnalog > 0)
            {
                cout << "right analog; angle: " + to_string(rightAnalog % (int) pow(2, 15)) +
                        ", intensity: " + to_string((int) floor(rightAnalog / (int) pow(2, 15))) << endl;
                printedAnything = true;
            }
            if (leftTrigger > 0)
            {
                cout << "left trigger: " + to_string(leftTrigger) << endl;
                printedAnything = true;
            }
            if (rightTrigger > 0)
            {
                cout << "right trigger: " + to_string(rightTrigger) << endl;
                printedAnything = true;
            }

            Sleep(50);
            if (buttons > 0)
            {
                for (const string &i : buttonMapping)
                {
                    if (buttons & 0x01) cout << i + " pressed" << endl;
                    buttons = buttons >> 1; // Shift bits to the right
                }
                printedAnything = true;
            }

            if (printedAnything)
            {
                cout << "---------------" << endl;
            }
        }
    }
    else
    {
        cout << "No controller connected\n";
    }


    return 0;
}

#pragma clang diagnostic pop