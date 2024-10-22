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

std::istream& operator>>(std::istream& lhs, char const* rhs) {
    char c;
    char const *cp = rhs;
    while (*cp != '\0') {
        if (lhs.get(c).good() && (*cp++ == c)) continue;
        lhs.unget();
        lhs.clear(std::ios::failbit); // actually WILL SET this bit (sic!)
        break;
    }
    return lhs;
}

int main() {
    std::string line{};
    auto prompt_and_get_input = [&line]() {
        std::cout << "fg count delay [msec]\n"
                     "bg count delay [msec]\n"
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
        if ((is >> "fg" >> count >> delay >> std::ws).eof()) {
            run_foreground(count, delay);
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "bg" >> count >> delay >> std::ws).eof()) {
            run_in_thread(count, delay);
            continue;
        }
        is.clear(); is.seekg(0);
        if ((is >> "." >> std::ws).eof()) {
            std::cout << "bye, bye\n";
            break;
        }
    }
}
