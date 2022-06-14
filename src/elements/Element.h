//
// Created by Shrimp on 12/30/2021.
//

#ifndef INC_2DSAND_ELEMENT_H
#define INC_2DSAND_ELEMENT_H

#include "../utils/Maths.h"
#include "../utils/Vector3D.h"
#include "../utils/Vector2D.h"
#include "../core/RNG.h"

class Element {
private:
    std::string name;
    unsigned int id{};
    Vector3D color;
public:
    Element(std::string name, Vector3D color);

    Element();

    void setID(unsigned int _id);

    bool operator==(const Element &element) const;

    bool operator!=(const Element &element) const;
//
//    Vector3D getColor();
//
//    virtual Vector2D update(int x, int y) {
//        return {x, y};
//    }
//
//    virtual bool isDynamic() {
//        return true;
//    }

    [[nodiscard]] unsigned int getID() const;

    [[nodiscard]] std::string getName() const;
};


#endif //INC_2DSAND_ELEMENT_H
