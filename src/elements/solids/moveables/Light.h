//
// Created by Shrimp on 4/15/2022.
//

#ifndef INC_2DSAND_LIGHT_H
#define INC_2DSAND_LIGHT_H

#include "../../Element.h"

class Light : public Element {
public:
    Light() : Element("Light", {1, 1, 1}) {}
};

#endif //INC_2DSAND_LIGHT_H
