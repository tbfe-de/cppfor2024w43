#include <iostream>
#include <sstream>
#include <cstdio>

void run_foreground(int count, int delay) {
    std::cout << __PRETTY_FUNCTION__
              << " count=" << count << ", delay=" << delay
              << "\n** NOT YET IMPLEMENTED **"
              << std::endl;
}

void run_in_thread(int count, int delay) {
    std::cout << __PRETTY_FUNCTION__
              << " count=" << count << ", delay=" << delay
              << "\n** NOT YET IMPLEMENTED **"
              << std::endl;
}

void run_in_thread(int delay) {
    std::cout << __PRETTY_FUNCTION__
              << " delay=" << delay
              << "\n** NOT YET IMPLEMENTED **"
              << std::endl;
}

void stop() {
    std::cout << __PRETTY_FUNCTION__
              << "\n** NOT YET IMPLEMENTED **"
              << std::endl;
}

void join() {
    std::cout << __PRETTY_FUNCTION__
              << "\n** NOT YET IMPLEMENTED **"
              << std::endl;
}

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
    std::string line{};
    auto prompt_and_get_input = [&line] {
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
            run_foreground(count, delay);
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "bg" >> delay >> std::ws).eof() and not is.fail()) {
            run_in_thread(delay);
            continue;
        }
        is.clear(); is.seekg(0);
        if (!(is >> "bg" >> count >> delay >> std::ws).eof() and not is.fail()) {
            run_in_thread(count, delay);
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "join" >> std::ws).eof() and not is.fail()) {
            join();
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "stop" >> std::ws).eof() and not is.fail()) {
            stop();
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "." >> std::ws).eof() and not is.fail()) {
            std::cout << "bye, bye\n";
            break;
        }
    }
}
