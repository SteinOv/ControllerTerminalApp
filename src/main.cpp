#include <Windows.h>
#include <Xinput.h>

#include <iostream>
#include <string>

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
        cout << "controller connected!\n";
        dwResult = XInputGetState(CONTROLLER_INDEX, &state);
        float bLTrigger = state.Gamepad.bLeftTrigger;
        cout << "back left trigger: " + to_string(bLTrigger);


    }
    else
    {
        cout << "No controller connected\n";
    }


    return 0;
}
