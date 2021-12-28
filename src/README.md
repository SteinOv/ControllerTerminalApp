# ControllerTerminalApp

Simple application that polls game controller state every 50 ms and prints pressed buttons, moved analog sticks and pressed bumpers.

CONTROLLER_INDEX can be between 0 and 3 (inclusive), if there is only one controller connected it is probably 0. If nothing is printed, try other values. <br>
If the triggers or analog sticks seem to move on their own, try increasing their corresponding DEAD_ZONE values.

Application uses the XInput API, which ships with Windows 10. So it should work out of the box.