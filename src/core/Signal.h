//
// Created by Shrimp on 4/13/2022.
//

#ifndef INC_2DSAND_SIGNAL_H
#define INC_2DSAND_SIGNAL_H


#include <functional>

template<typename F>
class Signal {
private:
    std::vector<std::function<F>> listeners;
public:
    void add(const std::function<F> &listener) {
        listeners.push_back(listener);
    }

    template<typename... Args>
    void dispatch(Args &&... args) {
        if (listeners.empty()) {
            return;
        }

        static_assert(std::is_invocable_v<F, Args...>);
        for (auto &listener: listeners) {
            listener(std::forward<Args>(args)...);
        }
    }
};


#endif //INC_2DSAND_SIGNAL_H
