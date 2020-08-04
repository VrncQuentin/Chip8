#ifndef C8_GUI_ERRORS_HPP
#define C8_GUI_ERRORS_HPP

#include <exception>

namespace Chip8::GUI::Errors {

    class Base : public std::exception
    {
    public:
        Base(const std::string& what) : what_(what) {}
        const char *what() const noexcept override {return what_.c_str();}

    private:
        std::string what_;
    };

    class Font : public Base
    {
    public:
        Font(const std::string& what) : Base(what) {}
    };
}

#endif /* C8_GUI_ERRORS_HPP */
