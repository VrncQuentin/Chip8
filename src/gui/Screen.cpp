#include "Screen.hpp"

using namespace Chip8::GUI;

Screen::Screen() {
    const sf::Vector2f base(PixelSize, PixelSize);

    for (int height = 0; height != Height; height += 1)
        for (int width = 0; width != Width; width += 1) {
            const auto idx = width + (height * Width);
            const auto xRectPos = static_cast<const float>(width * PixelSize);
            const auto yRectPos = static_cast<const float>(height * PixelSize);
            scr_[idx] = sf::RectangleShape(base);
            scr_[idx].setPosition(xRectPos, yRectPos);
            scr_[idx].setFillColor(PixOFF);
        }
}

void Screen::draw(sf::RenderWindow &win) const noexcept {
    for (const auto &rect : scr_) {
        win.draw(rect);
    }
}

void Screen::clear() noexcept {
    for (auto &rect : scr_)
        rect.setFillColor(PixOFF);
}

bool Screen::toggle(const byte x, const byte y) noexcept {
    sf::RectangleShape& target = scr_[x + y * Width];
    bool isOff = target.getFillColor() == PixOFF;

    target.setFillColor(isOff ? PixON : PixOFF);
    return isOff;
}
