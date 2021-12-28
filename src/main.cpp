#include <Windows.h>
#include <Xinput.h>

#include <iostream>
#include <string>

#include "GameController.h"

using namespace std;

int main() {
    const char CONTROLLER_INDEX = 1;

    /**/
    DWORD dwResult;

    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    // Simply get the state of the controller from XInput.
    dwResult = XInputGetState(CONTROLLER_INDEX, &state);

    if (dwResult == ERROR_SUCCESS)
    {
        while (true) {
            auto *gameController = new GameController(5000, CONTROLLER_INDEX);
            gameController->updateControllerState();
            int leftAnalog = gameController->getLeftAnalogState();
            int rightAnalog = gameController->getRightAnalogState();
            cout << "---------------" << endl;
            cout << "left analog; angle: " + to_string(leftAnalog % (int) pow(2, 15)) +
                    ", intensity: " + to_string((int) floor(leftAnalog / (int) pow(2, 15))) << endl;

            cout << "right analog; angle: " + to_string(rightAnalog % (int) pow(2, 15)) +
                    ", intensity: " + to_string((int) floor(rightAnalog / (int) pow(2, 15))) << endl;
            Sleep(500);
        }


//        cout << "controller connected!\n";
//        dwResult = XInputGetState(CONTROLLER_INDEX, &state);
//        float bLTrigger = state.Gamepad.bLeftTrigger;
//        cout << "back left trigger: " + to_string(bLTrigger);


    }
    else
    {
        cout << "No controller connected\n";
    }


    return 0;
}
