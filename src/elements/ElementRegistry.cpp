//
// Created by Shrimp on 12/30/2021.
//

#include <iostream>
#include "ElementRegistry.h"
#include "weirds/Any.h"
#include "solids/moveables/Light.h"
#include "solids/moveables/Dirt.h"
#include "solids/moveables/Glass.h"

std::unordered_map<unsigned int, Element> ElementRegistry::idToElement{};
std::unordered_map<std::string, Element> ElementRegistry::nameToElement{};
Element ElementRegistry::emptyElement{};
Element ElementRegistry::anyElement = Any();
int ElementRegistry::lastID = 0;

void ElementRegistry::registerElement(const Element &element) {
    std::cout << "Registered " << element.getName() << "(" << element.getID() << ")" << " Element!" << std::endl;
    idToElement[element.getID()] = element;
    nameToElement[element.getName()] = element;
    lastID++;
}

void ElementRegistry::registerElements() {
    registerElement(anyElement);
    registerElement(Light());
    registerElement(Dirt());
    registerElement(Glass());
}

Element &ElementRegistry::getElementByName(const std::string &name) {
    if (nameToElement.find(name) == nameToElement.end()) {
        return emptyElement;
    }

    return nameToElement[name];
}

Element ElementRegistry::getElementByID(const unsigned int id) {
    if (id >= idToElement.size()) {
        return emptyElement;
    }

    if (idToElement.find(id) == idToElement.end()) {
        return emptyElement;
    }

    return idToElement[id];
}
