#ifndef THREAD_TESTER
#define THREAD_TESTER

#include <atomic>
#include <iosfwd>
#include <thread>

#define MUST_BE_IMPLEMENTED(...)\
    (void)(std::cout << "TBD: " << __PRETTY_FUNCTION__ << __VA_ARGS__ << std::endl)

class ThreadTester {
private:
    std::thread bg_run{};
    std::atomic_bool run{};
    std::ostream& bg_output;
    void run_loop(int, int, std::ostream&);
public:
    ThreadTester(std::ostream& bg_out) : bg_output{bg_out} {}
    void run_foreground(int count, int delay);
    void run_as_thread(int count, int delay);
    void stop();
    void join();
};

#endif
