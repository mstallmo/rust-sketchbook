//
// Created by mason on 9/20/2020.
//

#ifndef ABSTRACT_CLASSES_ABSTRACTLOGGER_H
#define ABSTRACT_CLASSES_ABSTRACTLOGGER_H

#include <string>

struct AbstractLogger {
    virtual void sayHi() = 0;
    virtual void logValue(const char* message) = 0;
};

#endif //ABSTRACT_CLASSES_ABSTRACTLOGGER_H
