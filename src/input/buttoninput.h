#ifndef BUTTONINPUT_H
#define BUTTONINPUT_H

#include <basicinput.h>


class ButtonInput : public BasicInput
{
public:
    ButtonInput();

    int joystickIndex;
    int buttonIndex;

    bool isDown;
    bool toggled;

};

#endif // BUTTONINPUT_H
