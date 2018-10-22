#include <PThreads.h>
#include <cstdlib>

namespace SLog {
        std::string getThreadId() {
            char buffer[4*sizeof(long)];
            int bufsize = sizeof(buffer)/sizeof(buffer[0]);
            int n = ::snprintf(buffer, bufsize, "0x%lx", pthread_self());	// thread id unsigned
            if (n >= bufsize) {
            	// escape to heap allocation
				char *buff_alloc;
				int size = ::asprintf(&buff_alloc, "0x%lx", pthread_self());	// thread id unsigned
				if (size < 0) {
					throw std::bad_alloc();
				}
				std::string res(buff_alloc);
				free(buff_alloc);
				return res;
            }
            return std::string(buffer);
        }
}
