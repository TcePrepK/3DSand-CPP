//
// Created by Shrimp on 4/29/2022.
//

#ifndef INC_2DSAND_DIRT_H
#define INC_2DSAND_DIRT_H

#include "../../Element.h"

class Dirt : public Element {
public:
    Dirt() : Element("Dirt", {1, 1, 1}) {}
};

#endif //INC_2DSAND_DIRT_H
