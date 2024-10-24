#include "TickerService.h"

#include <atomic>
#include <iostream>

using namespace std::chrono_literals;

TickerService::ClockTP TickerService::epoch{ClockWork::now()};

std::ostream& operator<<(std::ostream& lhs, TickerService::ClockTP rhs) {
    std::ostream os{lhs.rdbuf()};
    os.setf(std::ios::fixed);
    os.precision(5);
    auto const ts = rhs - TickerService::epoch;
    using msfd = std::chrono::duration<float, std::ratio<1, 1000>>;
    os << '[' << msfd{ts}.count() << ']';
    return lhs;
}

static std::atomic_bool keep_greeter_running{true};
TickerService::ClientResult greeter(TickerService::ClockTP tp) {
    if (not keep_greeter_running) return {};
    std::cout << tp << " hello ticker" << std::endl;
    return {tp + 500ms};
}

class MyClass {
    int count_;
public:
    MyClass(int count) : count_{count} {};
    auto operator()(TickerService::ClockTP tp) {
        auto now = TickerService::ClockWork::now();
        std::cout << now << " .. oh boy .." << std::endl;
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
        {now + 11s, [](auto tp) -> TickerService::ClientResult {
                        std::cout << tp << " 'nuff greets!"
                                  << std::endl;
                        keep_greeter_running = false;
                        return {};
                    }},
    });
}
