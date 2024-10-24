#include "ThreadTester.h"

#include <chrono>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
    // std::stringstream
#include <thread>
#include <vector>

void ThreadTester::run_loop(int count, int delay, std::ostream& out) {
    std::ostream os{out.rdbuf()};
    os.setf(std::ios::fixed);
    os.precision(5);
    namespace sc = std::chrono;
    auto const start_tp = std::chrono::steady_clock::now();
    for (int i = 1; i <= count; ++i) {
        if (not run) return;
        auto const wakeup = start_tp + i*sc::milliseconds{delay};
        std::this_thread::sleep_until(wakeup);
        sc::duration<float, std::ratio<1, 1000>> delta_sec{
                sc::steady_clock::now() - start_tp
        };
        os << delta_sec.count() << std::endl;
    }
}

void ThreadTester::run_foreground(int count, int delay) {
    std::stringstream times{};
    run = true;
    run_loop(count, delay, times);
    std::vector<float> times_as_float;
    times_as_float.reserve(count);
    std::vector<float> time_deltas;
    time_deltas.reserve(count);
{
    float value;
    while (times >> value)
        times_as_float.push_back(value);
    for (std::size_t i = 1; i < times_as_float.size(); ++i)
        time_deltas.push_back(times_as_float[i] - times_as_float[i-1]);
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::lowest();
    float sum = 0;
    for (auto e : time_deltas) {
        if (e < min) min = e;
        if (e > max) max = e;
        sum += e;
    }
    float avg = sum/time_deltas.size();
    std::cout << "min=" << min << ", max=" << max << ", avg=" << avg << std::endl;
}
{
    using InIt = std::istream_iterator<float>;
    using OutIt = std::back_insert_iterator<std::vector<float>>;
    times.clear();
    times.seekg(0);
    times_as_float.clear();
    time_deltas.clear();
    std::copy(InIt{times}, InIt{}, OutIt{times_as_float});
    std::adjacent_difference(times_as_float.begin(),
                             times_as_float.end(),
                             OutIt{time_deltas});
    auto minmax = std::minmax_element(time_deltas.begin()+1, time_deltas.end());
    auto min = *minmax.first;
    auto max = *minmax.second;
    auto avg = std::accumulate(time_deltas.begin()+1,
                               time_deltas.end(),
                               0.0f) / (time_deltas.size()-1);
    std::cout << "min=" << min << ", max=" << max << ", avg=" << avg << std::endl;
}
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
