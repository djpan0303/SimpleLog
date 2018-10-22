#include <Configurator.h>

namespace SLog {

    ConfigureFailure::ConfigureFailure(const std::string& reason) :
        std::runtime_error(reason) 
	{

    }
}




