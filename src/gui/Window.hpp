#ifndef C8_GUI_WINDOW_HPP
#define C8_GUI_WINDOW_HPP

#include <map>
#include <SFML/Graphics.hpp>

namespace Chip8::GUI {


    enum Input{None = -1, One, Two, Three, C, Four, Five, Six, D, Seven, Eight, Nine, E, A, Zero, B, F};

    class Window : public sf::RenderWindow {
    public:
        Window();
        ~Window() override;

    public:
        const sf::Font& getFont() const noexcept;
        Input getInput() noexcept;

    private:
        using inputLayout = std::map<sf::Keyboard::Key, Input>;
        static const inputLayout azerty;

    private:
        sf::Font font_;
    };
}

#endif /* C8_GUI_WINDOW_HPP */