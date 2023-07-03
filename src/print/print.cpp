#include "print.hpp"

namespace strange_whiskers::print {
    void Print(std::string& message, bool flush) {
        std::cout << message;
        if (flush) std::cout << std::flush;
    }

    void Println(std::string& message, bool flush) {
        std::cout << message << std::endl;
        if (flush) std::cout << std::flush;
    }

    void Print(std::string message, bool flush) {
        std::cout << message;
        if (flush) std::cout << std::flush;
    }

    void Println(std::string message, bool flush) {
        std::cout << message << std::endl;
        if (flush) std::cout << std::flush;
    }


    void Flush() {
        std::cout << std::flush;
    }
}