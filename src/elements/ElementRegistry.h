//
// Created by Shrimp on 12/30/2021.
//

#ifndef INC_2DSAND_ELEMENTREGISTRY_H
#define INC_2DSAND_ELEMENTREGISTRY_H


//#include <memory>
//#include "../utils/Pair_Hash.h"

#include <unordered_map>
#include "Element.h"

class ElementRegistry {
private:
    static std::unordered_map<unsigned int, Element> idToElement;
    static std::unordered_map<std::string, Element> nameToElement;

    static void registerElement(const Element &element);

public:
    static int lastID;

    static Element emptyElement;
    static Element anyElement;

    const static unsigned int emptyID = 0;

    static void registerElements();

    static Element &getElementByName(const std::string &name);

    static Element getElementByID(unsigned int id);
};


#endif //INC_2DSAND_ELEMENTREGISTRY_H
