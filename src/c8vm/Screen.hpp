#ifndef C8_VM_SCREEN_HPP
#define C8_VM_SCREEN_HPP

/* LibC & STL */
#include <iostream>
#include <string>
#include <array>

/* Project */
namespace Chip8::VM {

    struct Screen {
    public: /* Specs */
        static constexpr uint8_t Width = 64;
        static constexpr uint8_t Height = 32;

    public: /* Useful types */
        using Pixel = uint8_t;
        using Buffer = std::array<std::array<Pixel, Width>, Height>;

    private: /* Members */
        static constexpr Buffer buf_{0};

    private: /* Helper Methods */
        static constexpr auto printBorderLine = []()
            {
                std::cout << std::string(Width + 2, '-') << std::endl;
            };

        static constexpr auto convertLine = [](const auto line, char *buf)
            {
                for (const Pixel p : line)
                    *buf++ = p ? '*' : ' ';
            };

        static constexpr auto printLines = []()
            {
                for (const auto line : buf_) {
                    char tmp[Width+1] = {0};
                    convertLine(line, tmp);
                    std::cout << '|' << tmp << '|' << std::endl;
                }
            };

    public: /* Methods */
        static constexpr auto clearConsole = []()
            {
                std::cout << std::string(100, '\n');
            };

        static constexpr auto dumpScreen = []()
            {
                clearConsole();
                printBorderLine();
                printLines();
                printBorderLine();
            };
    };
}

#endif /* C8_VM_SCREEN_HPP */
