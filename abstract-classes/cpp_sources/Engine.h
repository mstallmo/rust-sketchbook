//
// Created by mason on 9/20/2020.
//

#ifndef ABSTRACT_CLASSES_ENGINE_H
#define ABSTRACT_CLASSES_ENGINE_H

#include "AbstractLogger.h"
#include "Multiplier.h"

#include <vector>

namespace Execution {
    class Engine {
    public:
        explicit Engine(int initialValue);

        void registerLogger(AbstractLogger *logger);

        void registerMultiplier(IMultiplier *multiplier);

        void add(int other);

        void multiply();

    private:
        int _initial;
        AbstractLogger *_logger;
        std::vector<IMultiplier *> _multipliers;
    };
}

#endif //ABSTRACT_CLASSES_ENGINE_H
