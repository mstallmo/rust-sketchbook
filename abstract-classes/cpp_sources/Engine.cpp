//
// Created by mason on 9/20/2020.
//

#include "Engine.h"

#include <sstream>
#include <iostream>

namespace Execution {
    Engine::Engine(int initialValue): _initial(initialValue){}

    void Engine::registerLogger(AbstractLogger *logger) {
        _logger = logger;
    }

    void Engine::registerMultiplier(IMultiplier *multiplier) {
        _multipliers.push_back(multiplier);
    }

    void Engine::add(int other) {
        std::stringstream ss;
        ss << "Initial value started as: " << _initial;
        std::string str(ss.str());
        _logger->logValue(str.c_str());
        _initial += other;
        std::stringstream ss2;
        ss2 << "Initial value is now: " << _initial;
        std::string str2(ss2.str());
        _logger->logValue(str2.c_str());
    }

    void Engine::multiply() {
        std::stringstream ss1;
        ss1 << "Initial value: " << _initial;
        std::string initMessage (ss1.str());
        _logger->logValue(initMessage.c_str());

        for (auto* const mul : _multipliers) {
            mul->mult_int(_initial);
            std::stringstream ss2;
            ss2 << "Value after applying multipliers: " << _initial;
            std::string finalMessage(ss2.str());
            _logger->logValue(finalMessage.c_str());
        }
    }
}