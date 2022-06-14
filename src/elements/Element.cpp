//
// Created by Shrimp on 12/30/2021.
//

#include "Element.h"

#include <utility>
#include "ElementRegistry.h"

Element::Element(std::string name, Vector3D color) :
        name(std::move(name)), color(color), id(ElementRegistry::lastID) {}

Element::Element() :
        name("Empty"), color({0, 0, 0}), id(ElementRegistry::emptyID) {}

void Element::setID(const unsigned int _id) {
    id = _id;
}

unsigned int Element::getID() const {
    return id;
}

std::string Element::getName() const {
    return name;
}

bool Element::operator==(const Element &element) const {
    return id == element.id && name == element.name;
}

bool Element::operator!=(const Element &element) const {
    return !(id == element.id && name == element.name);
}
