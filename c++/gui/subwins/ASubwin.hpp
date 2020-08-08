#ifndef C8_GUI_SUBWIN_HPP
#define C8_GUI_SUBWIN_HPP

#include <SFML/Graphics.hpp>

namespace Chip8::GUI::Subwin {

    class Name {
    public:
        Name(const std::string &name, const sf::Vector2f& winPos) noexcept;
        ~Name() = default;

    public:
        Name& setFont(const sf::Font& f) noexcept;

    public:
        const sf::RectangleShape& getRect() const noexcept;
        const sf::Text& getText() const noexcept;

    private:
        sf::RectangleShape rect_;
        sf::Text text_;
    };

    class ASubwin {
    public:
        explicit ASubwin(const sf::Vector2f& size, const sf::Vector2f& pos, const std::string& name);
        ~ASubwin() = default;

    public:
        const sf::RectangleShape& getWin() const noexcept;
        const Name& getName() const noexcept;
        const sf::Vector2f& getPosition() const noexcept;

    public:
        ASubwin& setFont(const sf::Font& f) noexcept;

    protected:
        sf::RectangleShape win_;
        const sf::Vector2f pos_;
        Name name_;
    };

    sf::RenderWindow& operator<<(sf::RenderWindow &win, const ASubwin& sub);
}

#endif /* C8_GUI_SUBWIN_HPP */
