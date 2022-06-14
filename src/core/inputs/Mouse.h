//
// Created by Shrimp on 4/13/2022.
//

#ifndef INC_2DSAND_MOUSE_H
#define INC_2DSAND_MOUSE_H


#include "../../utils/Vector2D.h"
#include "../Signal.h"

class Mouse {
private:
    Vector2D position;
    Vector2D delta;

    bool pressedList[8]{};
public:
    static const int maxMouseButtons = 8;

    Signal<void(int)> mouseScroll;

    Signal<void()> leftMousePress;
    Signal<void()> rightMousePress;
    Signal<void()> middleMousePress;

    Signal<void()> leftMouseRelease;
    Signal<void()> rightMouseRelease;
    Signal<void()> middleMouseRelease;

    static void initialize();

    static void update();

    bool isButtonDown(int button);

    Vector2D getPosition();

    Vector2D getDelta();
};


#endif //INC_2DSAND_MOUSE_H
