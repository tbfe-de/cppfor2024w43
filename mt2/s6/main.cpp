#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>

#include "ThreadTester.h"

std::istream& operator>>(std::istream& lhs, char const* rhs) {
    char c;
    char const *cp = rhs;
    while (*cp != '\0') {
        if (lhs.get(c).good() && (*cp++ == c)) continue;
        lhs.clear(std::ios::failbit); // actually WILL SET this bit (sic!)
        break;
    }
    return lhs;
}

int main() {
    std::ofstream xtty{"/dev/ttys226"};
    xtty << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
            "*** bg output appears here ***" << std::endl;

    ThreadTester tt{xtty};

    std::string line{};
    auto prompt_and_get_input = [&line]() {
        std::cout << "fg count delay [msec]\n"
                     "bg count delay [msec]\n"
                     "bg delay [msec]\n"
                     "stop\n"
                     "join\n"
                     ". end program"
                     "\n? ";

        std::getline(std::cin, line);
        line +=  ' ';
        return std::cin.good();
    };
    while (prompt_and_get_input()) {
        std::istringstream is{line};
        int count;
        int delay;
        if ((is >> "fg" >> count >> delay >> std::ws).eof() and not is.fail()) {
            tt.run_foreground(count, delay);
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "bg" >> count >> delay >> std::ws).eof() and not is.fail()) {
            tt.run_as_thread(count, delay);
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "bg" >> delay >> std::ws).eof() and not is.fail()) {
            count = std::numeric_limits<decltype(count)>::max();
            tt.run_as_thread(count, delay);
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "join" >> std::ws).eof() and not is.fail()) {
            tt.join();
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "stop" >> std::ws).eof() and not is.fail()) {
            tt.stop();
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "." >> std::ws).eof() and not is.fail()) {
            std::cout << "bye, bye\n";
            break;
        }
    }
}
