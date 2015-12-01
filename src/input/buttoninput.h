#ifndef BUTTONINPUT_H
#define BUTTONINPUT_H

#include <basicinput.h>


class ButtonInput : public BasicInput
{
public:
    ButtonInput();
    ButtonInput(std::string,int);

    int buttonIndex;

    bool isDown;
    bool toggled;

};

#endif // BUTTONINPUT_H
