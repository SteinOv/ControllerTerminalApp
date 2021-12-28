#pragma once

/**
 * Holds state of game controller. Current state of game controller is read upon calling updateControllerState().<br>
 * The state of the buttons, triggers and analog sticks can be retrieved with getters.
 * <p>
 * @see Uses XInput API: https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput
 */
class GameController
{
public:
    explicit GameController(char _controllerIndex, short _analogDeadZone, BYTE _triggerDeadZone);
    ~GameController() = default;

    /**
     * Updates the state of the controller.
     */
    void updateControllerState();

    /**
     * Get the state of the buttons, will retrieve the state at the previous call to updateControllerState(). <br>
     * <br>
     * The order of the buttons in the returned bitmask is as follows: <br>
     * dpad up, dpad down, dpad left, dpad right, start, back, left analog, right analog, left bumper,
     * right bumper, none, none, A, B, X, Y
     * <p>
     * @see GameController#updateControllerState: Will retrieve state at time of last call to this method
     * @see https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad Bitmask is directly taken from XInput API
     * @return A bitmask where each bit represents one button
     */
    unsigned short getButtonStates() const;

    /**
     * Get the state of the buttons, will retrieve the state at the previous call to updateControllerState(). <br>
     * The angle is clockwise with 0° at 12 o`clock. The lowest possible value for the intensity is the analogDeadZone value.
     * The highest possible value depends on the controller, it will be around 40000 and never above 46341.
     * <p>
     * @see GameController#updateControllerState: Will retrieve state at time of last call to this method
     * @return A bitmask containing the angle and intensity of the analog stick. The first two bytes (0x____FFFF) represent the angle
     * and the last two bytes (0xFFFF____) the intensity.
     */
    unsigned int getLeftAnalogState() const;

    /**
     * Get the state of the buttons, will retrieve the state at the previous call to updateControllerState(). <br>
     * The angle is clockwise with 0° at 12 o`clock. The lowest possible value for the intensity is the analogDeadZone value.
     * The highest possible value depends on the controller, it will be around 40000 and never above 46341.
     * <p>
     * @see GameController#updateControllerState: Will retrieve state at time of last call to this method
     * @return A bitmask containing the angle and intensity of the analog stick. The first two bytes (0x____FFFF) represent the angle
     * and the last two bytes (0xFFFF____) the intensity.
     */
    unsigned int getRightAnalogState() const;

    /**
     * Get the state of the left trigger.
     * @return A value between 0 and 255, where 0 is not pressed and 255 pressed completely.
     */
    BYTE getLeftTriggerState() const;

    /**
     * Get the state of the right trigger.
     * @return A value between 0 and 255, where 0 is not pressed and 255 pressed completely.
     */
    BYTE getRightTriggerState() const;


private:
    const BYTE controllerIndex;
    const short analogDeadZone;
    const BYTE triggerDeadZone;

    short leftX{};
    short leftY{};
    short rightX{};
    short rightY{};

    BYTE leftTrigger{};
    BYTE rightTrigger{};

    unsigned short buttons{};

    unsigned int toBitmask(short X, short Y) const;
};

