#ifndef _SIMPLELOG_CONFIGURATOR_HH
#define _SIMPLELOG_CONFIGURATOR_HH

#include <string>
#include <stdexcept>

namespace SLog {
    class ConfigureFailure : public std::runtime_error {
        public:
        ConfigureFailure(const std::string& reason);
    };
}

#endif // _SIMPLELOG_CONFIGURATOR_HH
