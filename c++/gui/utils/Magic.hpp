#ifndef C8_GUI_MAGIC_HPP
#define C8_GUI_MAGIC_HPP

#include <string>
#include <SFML/Graphics/Color.hpp>

namespace Chip8::GUI::Magic {

    namespace Windows {
        namespace Names {
            static constexpr auto Main = "Chip8 Interpreter";
            static constexpr auto Game = "No game loaded";
            static constexpr auto Menu = "Interpreter's Menu";
            static constexpr auto Stats = "Interpreter's Stats";
        }

        namespace Sizes {
            static constexpr float Borders = 1;
            static constexpr int WinSep = 10;
            /* .x = width, .y = height */
            static const sf::Vector2f GUI{.x = 800, .y = 600};
            static const sf::Vector2f Game{.x = 512, .y = 256};
            static const sf::Vector2f Menu{
                .x = Game.x,
                .y = GUI.y - Game.y - WinSep * 3
            };
            static const sf::Vector2f Stats{
                .x  = GUI.x - Game.x - WinSep * 3,
                .y = GUI.y - WinSep * 2
            };
        }

        namespace Pos {
            static const sf::Vector2f Game{
                .x = Sizes::WinSep,
                .y = Sizes::WinSep
            };
            static const sf::Vector2f Menu{
                .x = 10,
                .y = Game.y + Sizes::Game.y + Sizes::WinSep
            };
            static const sf::Vector2f Stats{
                .x = Game.x + Sizes::Game.x + Sizes::WinSep,
                .y = 10
            };
        }
        static constexpr int SubwinCount = 3;
    }

    namespace Colors {
        static const sf::Color Filler = sf::Color(50, 50, 50, 175); // Dark grey
        static const sf::Color FillerFull = sf::Color(50, 50, 50, 255); // Dark grey
        static const sf::Color Border = sf::Color(246, 148, 0); // Dark Orange
        static const sf::Color Text = sf::Color(246, 148, 0); // Dark Orange
    }

    namespace Fonts {
        static constexpr unsigned int DefaultSize = 10;
        static constexpr auto DefaultPath = "gui/static/SCP-Regular.ttf";
    }

}

#endif /* C8_GUI_MAGIC_HPP */
