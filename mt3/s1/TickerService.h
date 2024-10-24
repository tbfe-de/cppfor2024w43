#ifndef TICKER_SERVICE_H
#define TICKER_SERVICE_H

#include <array>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
#include <tuple>

class TickerService {
public:
    using msec = std::chrono::milliseconds;
    using ClockWork = std::chrono::steady_clock;
    using ClockTP = ClockWork::time_point;
    using ClockTS = ClockWork::duration;
    using ClientResult = std::optional<ClockTP>;
    using ClientCB = std::function<auto(ClockTP) -> ClientResult>;
    struct ClientSlot {
        ClockTP nextRun;
        ClientCB callBack;
    };
    using InitialClientSpec = std::initializer_list<ClientSlot>;

private:
    TickerService() =default;
    TickerService(TickerService const&) =delete;
    TickerService(TickerService &&) =delete;
    TickerService& operator=(TickerService const&) =delete;
    TickerService& operator=(TickerService &&) =delete;
    ~TickerService() =default;

public:
    static ClockTP epoch;
    static void run(InitialClientSpec const& clientList);
};

#endif // include guard
