#ifndef THREAD_TESTER
#define THREAD_TESTER

#include <iostream>

#define MUST_BE_IMPLEMENTED(...)\
    (void)(std::cout << __PRETTY_FUNCTION__ << __VA_ARGS__ << std::endl)

class ThreadTester {
public:
    void run_as_thread(int count, int delay) {
        MUST_BE_IMPLEMENTED(" count=" << count << " delay=" << delay);
    }
    void run_foreground(int count, int delay) {
        MUST_BE_IMPLEMENTED(" count=" << count << " delay=" << delay);
    }
    void stop() {
        MUST_BE_IMPLEMENTED("");
    }
    void join() {
        MUST_BE_IMPLEMENTED("");
    }
};

#endif