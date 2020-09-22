//
// Created by mason on 9/20/2020.
//

#ifndef ABSTRACT_CLASSES_BINDINGS_H
#define ABSTRACT_CLASSES_BINDINGS_H

#include "Engine.h"

extern "C" {
struct AbstractLoggerBinding {
    void (*sayHi)(void *cont);

    void (*logValue)(void *cont, const char * message);

    void *context;
};

class LoggerBindingConcrete : public AbstractLogger {
public:
    explicit LoggerBindingConcrete(AbstractLoggerBinding *_binding);

    ~LoggerBindingConcrete();

    void sayHi() override;

    void logValue(const char *message) override;

private:
    AbstractLoggerBinding *binding;
};

struct IMultiplierBinding {
    void (*mult_int)(void *cont, int &other);

    void *context;
};

class Multiplier : public IMultiplier {
public:
    explicit Multiplier(IMultiplierBinding *_multiplier);

    ~Multiplier();

    void mult_int(int &other) override;

private:
    IMultiplierBinding *binding;
};
};

extern "C" Execution::Engine *engine_factory(int inital_value);

extern "C" void register_logger(Execution::Engine *engine, AbstractLoggerBinding *logger);

extern "C" void register_multiplier(Execution::Engine *engine, IMultiplierBinding *multiplier);

extern "C" void add(Execution::Engine *engine, int other);

extern "C" void multiply(Execution::Engine *engine);

extern "C" void say_something(AbstractLoggerBinding *logger);

#endif //ABSTRACT_CLASSES_BINDINGS_H
