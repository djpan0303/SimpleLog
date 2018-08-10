#ifndef _SIMPLELOG_THREADING_PTHREADS_HH
#define _SIMPLELOG_THREADING_PTHREADS_HH

#include <stdio.h>
#include <pthread.h>
#include <string>
#include <assert.h>


namespace SimpleLog {
        /** 
         * returns the thread IDs
         **/
        std::string getThreadId();
        
        /**
         **/
        class Mutex {
            private:
            pthread_mutex_t mutex;

            public:
            inline Mutex() {
                ::pthread_mutex_init(&mutex, NULL);
            }

            inline void lock() {
                ::pthread_mutex_lock(&mutex);
            }

            inline void unlock() {
                ::pthread_mutex_unlock(&mutex);
            }

            inline ~Mutex() {
                ::pthread_mutex_destroy(&mutex);
            }

            private:
            Mutex(const Mutex& m);
            Mutex& operator=(const Mutex &m);
        };

        /**
         *	definition of ScopedLock;
         **/
        class ScopedLock {
            private:
            Mutex& _mutex;

            public:
            inline ScopedLock(Mutex& mutex) :
                _mutex(mutex) {
                _mutex.lock();
            }

            inline ~ScopedLock() {
                _mutex.unlock();
            }
        };
}
#endif
