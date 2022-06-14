//
// Created by Shrimp on 6/4/2022.
//

#ifndef INC_3DSAND_GLASS_H
#define INC_3DSAND_GLASS_H

#include "../../Element.h"

class Glass : public Element {
public:
    Glass() : Element("Glass", {1, 1, 1}) {}
};

#endif //INC_3DSAND_GLASS_H
