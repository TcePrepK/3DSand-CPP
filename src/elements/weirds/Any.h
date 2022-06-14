//
// Created by Shrimp on 4/15/2022.
//

#ifndef INC_2DSAND_ANY_H
#define INC_2DSAND_ANY_H

#include "../Element.h"

class Any : public Element {
public:
    Any() : Element("Any", {0, 0, 0}) {}
};

#endif //INC_2DSAND_ANY_H
