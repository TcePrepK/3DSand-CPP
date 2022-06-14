//
// Created by Shrimp on 4/17/2022.
//

#ifndef INC_2DSAND_SSBO_H
#define INC_2DSAND_SSBO_H


#include <vector>

class SSBO {
private:
    unsigned int id{};
    const int index, usage;

public:
    SSBO(int index, int usage);

    void create(std::vector<uint64_t> data);

    void bind() const;
};


#endif //INC_2DSAND_SSBO_H
