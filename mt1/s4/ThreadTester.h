#ifndef THREAD_TESTER
#define THREAD_TESTER

#include <iostream>

#define MUST_BE_IMPLEMENTED(...)\
    (void)(std::cout << "TBD: " << __PRETTY_FUNCTION__ << __VA_ARGS__ << std::endl)

class ThreadTester {
private:
    void run_loop(int, int, std::streambuf*);
public:
    void run_foreground(int count, int delay) {
        auto sbuf = std::cout.rdbuf();
        run_loop(count, delay, sbuf);
    }
    void run_as_thread(int count, int delay) {
        MUST_BE_IMPLEMENTED(" count=" << count << " << delay=" << delay);
    }
    void stop() {
        MUST_BE_IMPLEMENTED("");
    }
    void join() {
        MUST_BE_IMPLEMENTED("");
    }
};

#endif
