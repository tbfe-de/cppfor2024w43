#include "TickerService.h"

#include <atomic>
#include <iostream>

using namespace std::chrono_literals;

static std::atomic_bool keep_greeter_running{true};
TickerService::ClientResult greeter(TickerService::ClockTP tp) {
    if (not keep_greeter_running) return {};
    std::cout << " hello ticker" << std::endl;
    return {tp + 500ms};
}

class MyClass {
    int count_;
public:
    MyClass(int count) : count_{count} {};
    auto operator()(TickerService::ClockTP tp) {
        std::cout << " .. oh boy .." << std::endl;
        TickerService::ClientResult result{};
        if (--count_ > 0) result.emplace(tp + 133ms);
        return result;
    }
};

int main() {
    using TS = TickerService;
    auto const now = TS::ClockWork::now();

    TS::run({
        {now + 1s, greeter},
        {now + 5s, MyClass{12}},
        {now + 11s, [](auto) -> TickerService::ClientResult {
                        std::cout << " shut up!" << std::endl;
                        keep_greeter_running = false;
                        return {};
                    }},
    });
}
