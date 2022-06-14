//
// Created by Shrimp on 4/15/2022.
//

#ifndef INC_2DSAND_EMPTY_H
#define INC_2DSAND_EMPTY_H

#include "../Element.h"

class Empty : public Element {
public:
    Empty() : Element("Empty", {0, 0, 0}) {}
};

#endif //INC_2DSAND_EMPTY_H
