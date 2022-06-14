//
// Created by Shrimp on 1/1/2022.
//

#ifndef INC_2DSAND_PAIR_HASH_H
#define INC_2DSAND_PAIR_HASH_H


#include <iostream>

struct pair_hash {
    template<class T1, class T2>
    size_t operator()(const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};


#endif //INC_2DSAND_PAIR_HASH_H
