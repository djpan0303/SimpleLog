#include <Appender.h>
#include <iostream>

namespace SLog {
    Appender::Appender(const std::string& name) :
        _name(name) {
    }
    
    Appender::~Appender() {
    }
}
