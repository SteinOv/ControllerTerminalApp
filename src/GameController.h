#pragma once

class GameController
{
public:
    explicit GameController(short _deadZone, char controllerIndex);
    ~GameController() = default;

    void updateControllerState();
    unsigned int getLeftAnalogState();
    unsigned int getRightAnalogState();

private:
    const short deadZone;
    const BYTE controllerIndex;

    short leftX{};
    short leftY{};
    short rightX{};
    short rightY{};

    BYTE bLeftTrigger{};
    BYTE bRightTrigger{};

    unsigned short buttons;

    unsigned int toBitmap(short X, short Y) const;
};

