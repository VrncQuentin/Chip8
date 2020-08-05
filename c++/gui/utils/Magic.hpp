#ifndef C8_GUI_MAGIC_HPP
#define C8_GUI_MAGIC_HPP

#include <string>
#include <SFML/Graphics/Color.hpp>

namespace Chip8::GUI::Magic {

    namespace Windows {
        namespace Names {
            static const std::string Main = "Chip8 Interpreter";
            static const std::string Game = "No game loaded";
            static const std::string Menu = "Interpreter's Menu";
            static const std::string Stats = "Interpreter's Stats";
        }

        namespace Sizes {
            static constexpr float Borders = 1;
            static constexpr int WinSep = 10;
            /* .x = width, .y = height */
            static constexpr Chip8::Common::v2i GUI{.x = 800, .y = 600};
            static constexpr Chip8::Common::v2i Game{.x = 512, .y = 256};
            static constexpr Chip8::Common::v2i Menu{
                .x = Game.x,
                .y = GUI.y - Game.y - WinSep * 3
            };
            static constexpr Chip8::Common::v2i Stats{
                .x  = GUI.x - Game.x - WinSep * 3,
                .y = GUI.y - WinSep * 2
            };
        }

        namespace Pos {
            static constexpr Chip8::Common::v2i Game{
                .x = Sizes::WinSep,
                .y = Sizes::WinSep
            };
            static constexpr Chip8::Common::v2i Menu{
                .x = 10,
                .y = Game.y + Sizes::Game.y + Sizes::WinSep
            };
            static constexpr Chip8::Common::v2i Stats{
                .x = Game.x + Sizes::Game.x + Sizes::WinSep,
                .y = 10
            };
        }
    }

    namespace Colors {
        static const sf::Color Filler = sf::Color(50, 50, 50, 175); // Dark grey
        static const sf::Color Border = sf::Color(246, 148, 0); // Dark Orange
        static const sf::Color Text = sf::Color(246, 148, 0); // Dark Orange
    }

    namespace Fonts {
        static constexpr unsigned int DefaultSize = 10;
        static const std::string DefaultPath = "gui/static/SCP-Regular.ttf";
    }

}

#endif /* C8_GUI_MAGIC_HPP */
