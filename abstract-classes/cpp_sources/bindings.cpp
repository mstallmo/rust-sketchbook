//
// Created by mason on 9/20/2020.
//

#include "bindings.h"

#include <iostream>

LoggerBindingConcrete::LoggerBindingConcrete(AbstractLoggerBinding *_binding) : binding(_binding) {}

LoggerBindingConcrete::~LoggerBindingConcrete() {
    delete binding;
}

void LoggerBindingConcrete::sayHi() {
    (*binding->sayHi)(binding->context);
}

void LoggerBindingConcrete::logValue(const char *message) {
    (*binding->logValue)(binding->context, message);
}

Multiplier::Multiplier(IMultiplierBinding *_multiplier) : binding(_multiplier) {}

Multiplier::~Multiplier() {
    delete binding;
}

void Multiplier::mult_int(int &other) {
    (*binding->mult_int)(binding->context, other);
}

void say_something(AbstractLoggerBinding *logger) {
    auto *concrete = new LoggerBindingConcrete(logger);
    concrete->sayHi();
    delete concrete;
}

Execution::Engine *engine_factory(int inital_value) {
    return new Execution::Engine(inital_value);
}

void register_logger(Execution::Engine *engine, AbstractLoggerBinding *logger) {
    auto *concrete = new LoggerBindingConcrete(logger);
    engine->registerLogger(concrete);
}

void register_multiplier(Execution::Engine *engine, IMultiplierBinding *multiplier) {
    auto *concrete = new Multiplier(multiplier);
    engine->registerMultiplier(concrete);
}

void add(Execution::Engine *engine, int other) {
    engine->add(other);
}

void multiply(Execution::Engine *engine) {
    engine->multiply();
}
