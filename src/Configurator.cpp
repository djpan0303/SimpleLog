#include <Configurator.h>

namespace SimpleLog {

    ConfigureFailure::ConfigureFailure(const std::string& reason) :
        std::runtime_error(reason) 
	{

    }
}




