#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

void run_loop(int count, int delay, char const* tty) {
    std::ofstream os{tty};
    os.setf(std::ios::fixed);
    os.precision(5);
    auto const start_tp = std::chrono::steady_clock::now();
    while (count-- > 0) {
        std::chrono::milliseconds const msec{delay};
        std::this_thread::sleep_for(msec);
        std::chrono::duration<float, std::ratio<1, 1000>> delta_sec{
                std::chrono::steady_clock::now() - start_tp
        };
        os << delta_sec.count() << std::endl;
    }
}

int main() {
    auto prompt_and_get_input = [](std::string& input_line) {
        std::cout << "type: count delay [msec] -- Ctrl-D to end\n? "
                  << std::flush;
        std::getline(std::cin, input_line);
        input_line +=  ' ';
        return std::cin.good();
    };
    std::string line{};
    while (prompt_and_get_input(line)) {
        std::istringstream is{line};
        int count;
        int delay;
        if ((is >> count >> delay >> std::ws).eof()) {
            run_loop(count, delay, "/dev/pts/1");
        }
    }
}
