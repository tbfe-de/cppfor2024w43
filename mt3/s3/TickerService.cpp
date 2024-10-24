#include "TickerService.h"

bool operator<(TickerService::ClientSlot const& lhs,
               TickerService::ClientSlot const& rhs) {
    return (lhs.nextRun > rhs.nextRun);
}

void TickerService::run(InitialClientSpec const& subscriberList) {
    std::priority_queue<ClientSlot> subscriberQueue;
    for (auto subscriber : subscriberList)
        subscriberQueue.push(subscriber);
    while (not subscriberQueue.empty()) {
        auto const client = subscriberQueue.top();
        subscriberQueue.pop();
        auto const wakeup = client.nextRun;
        std::this_thread::sleep_until(wakeup);
        auto rerun = client.callBack(wakeup);
        if (rerun.has_value()) {
            subscriberQueue.push({rerun.value(), client.callBack});
        }
    }
}
