#include <Appender.h>
#include <iostream>

namespace SimpleLog {
    Appender::Appender(const std::string& name) :
        _name(name) {
    }
    
    Appender::~Appender() {
    }
}
