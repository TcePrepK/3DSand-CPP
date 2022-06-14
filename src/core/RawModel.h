//
// Created by Shrimp on 4/10/2022.
//

#ifndef INC_2DSAND_RAWMODEL_H
#define INC_2DSAND_RAWMODEL_H


class RawModel {
private:
    const unsigned int vaoID;
    const int vertexCount;

public:
    RawModel(unsigned int vaoID, int vertexCount);

    [[nodiscard]] unsigned int getVaoID() const;

    [[nodiscard]] int getVertexCount() const;
};


#endif //INC_2DSAND_RAWMODEL_H
