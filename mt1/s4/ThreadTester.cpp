#include "ThreadTester.h"

#include <chrono>
#include <thread>

void ThreadTester::run_loop(int count, int delay, std::ostream& out) {
    std::ostream os{out.rdbuf()};
    os.setf(std::ios::fixed);
    os.precision(5);
    namespace sc = std::chrono;
    auto const start_tp = std::chrono::steady_clock::now();
    for (int i = 1; i <= count; ++i) {
        auto const wakeup = start_tp + i*sc::milliseconds{delay};
        std::this_thread::sleep_until(wakeup);
        sc::duration<float, std::ratio<1, 1000>> delta_sec{
                sc::steady_clock::now() - start_tp
        };
        os << delta_sec.count() << std::endl;
    }
}
