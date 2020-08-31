#ifndef C8_GUI_WINDOW_HPP
#define C8_GUI_WINDOW_HPP

#include <SFML/Graphics.hpp>

namespace Chip8::GUI {

class Window : public sf::RenderWindow {
    public:
        Window();
        ~Window() override;

    public:
        const sf::Font& getFont() const noexcept;

    private:
        sf::Font font_;
    };
}

#endif /* C8_GUI_WINDOW_HPP */