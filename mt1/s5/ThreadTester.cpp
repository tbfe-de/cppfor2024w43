#include "ThreadTester.h"

#include <chrono>
#include <iostream>
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

void ThreadTester::run_foreground(int count, int delay) {
    run_loop(count, delay, std::cout);
}

void ThreadTester::run_as_thread(int count, int delay) {
    if (bg_run.joinable()) return; // thread running and not yet joined;
    run = true;
    bg_run = std::thread([=] { run_loop(count, delay, bg_output); });
    std::cout << "bg run started" << std::endl;
}

void ThreadTester::stop() {
    if (run == false) return; // thread not running or has requested to stop
    run = false;
    std::cout << "bg stop requested" << std::endl;
}

void ThreadTester::join() {
    bg_run.join();
    run = false;
    std::cout << "bg run terminated" << std::endl;
}
