#ifndef C8_GUI_MAGIC_HPP
#define C8_GUI_MAGIC_HPP

namespace Chip8::GUI::Magic {
    static const std::string WinName = "Chip8 Interpreter";
    static const std::string FontPath = "gui/utils/SCP-Regular.ttf";

    static const std::string NoGame = "No game loaded";
    static const std::string CtrlName = "Interpreter's Controller";
    static const std::string StatsName = "Interpreter's Stats";

    static const sf::Color FillColor = sf::Color(50, 50, 50, 175); // Dark grey
    static const sf::Color BorderColor = sf::Color(246, 148, 0); // Dark Orange
    static constexpr float BorderSize = 1;

}

#endif /* C8_GUI_MAGIC_HPP */
