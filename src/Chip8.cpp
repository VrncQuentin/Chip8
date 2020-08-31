#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "Chip8.hpp"

int Chip8::Chip8::run()  noexcept {
    if (!loadNewGame("games/IBM Logo.ch8"))
        return 1;
    while (win_.isOpen()) {
        // handle input
        uint16_t op = ram_.fetch();
        std::cout << "Fetched: 0x" << std::uppercase << std::setbase(16) << op << std::endl;
        std::cout << "PC: 0x" << std::uppercase << std::setbase(16) << ram_.getPC() << std::endl;
        exec(op);
        draw();
        usleep(500000);
    }
    return 0;
}

bool Chip8::Chip8::loadNewGame(const std::string &gamePath) noexcept {
    return ram_.loadGame(gamePath);
}

void Chip8::Chip8::draw() noexcept {
    win_.clear(sf::Color::White);
    scr_.draw(win_);
    // Draw everything
    win_.display();
}
enum {
    JUMP = 0x1,
    CALL = 0x2,
    RETURN = 0xEE,
    CLEAR = 0xE0,
    SKIP_IF_REGX_EQ_NN = 0x3,
    SKIP_IF_REGX_NEQ_NN = 0x4,
    SKIP_IF_REGX_EQ_REGY = 0x5,
    SKIP_IF_REGX_NEQ_REGY = 0x9,
    SET_REGX_WITH_NN = 0x6,
    ADD_NN_TO_REGX = 0x7,
    SET_REG_I = 0xA,
    DISPLAY = 0xD
};
void Chip8::Chip8::exec(const uint16_t op) noexcept {
    switch (decodeMajor(op)) {
        case 0x0: {
            switch (decodeNN(op)) {
                case CLEAR: {
                    scr_.clear();
                    break;
                }
                case RETURN: {
                    const auto returnTo = stack_.pop();
                    ram_.setPC(returnTo);
                    break;
                }
                default:
                    std::cout << "Unsupported OP: 0x" << std::uppercase << std::setbase(16) << op << std::endl;
            }
            break;
        }
        case JUMP: {
            const auto jumpTo = decodeNNN(op);
            ram_.setPC(jumpTo);
            break;
        }
        case CALL: {
            const auto curPC = ram_.getPC();
            const auto newPC = decodeNNN(op);
            stack_.push(curPC);
            ram_.setPC(newPC);
            break;
        }
        case SKIP_IF_REGX_EQ_NN: {
            const auto regValue = regs_.getDataAt(decodeRegX(op));
            const auto expected = decodeNN(op);
            if (regValue == expected)
                ram_.incrementPC();
            break;
        }
        case SKIP_IF_REGX_NEQ_NN: {
            const auto regValue = regs_.getDataAt(decodeRegX(op));
            const auto expected = decodeNN(op);
            if (regValue != expected)
                ram_.incrementPC();
            break;
        }
        case SKIP_IF_REGX_EQ_REGY: {
            const auto valueRegX = regs_.getDataAt(decodeRegX(op));
            const auto valueRegY = regs_.getDataAt(decodeRegY(op));
            if (valueRegX == valueRegY)
                ram_.incrementPC();
            break;
        }
        case SET_REGX_WITH_NN: {
            const byte what = static_cast<byte>(decodeNN(op));
            const byte where = static_cast<byte>(decodeRegX(op));
            regs_.setData(what, where);
            break;
        }
        case ADD_NN_TO_REGX: {
            const byte howMuch = static_cast<byte>(decodeNN(op));
            const byte where = static_cast<byte>(decodeRegX(op));
            regs_.addData(howMuch, where);
            break;
        }
        case 0x8: {
            break;
        }
        case SKIP_IF_REGX_NEQ_REGY: {
            const auto valueRegX = regs_.getDataAt(decodeRegX(op));
            const auto valueRegY = regs_.getDataAt(decodeRegY(op));
            if (valueRegX != valueRegY)
                ram_.incrementPC();
            break;
        }
        case SET_REG_I: {
            regs_.setAddr(decodeNNN(op));
            break;
        }
        case 0xB: {
            break;
        }
        case 0xC: {
            break;
        }
        case DISPLAY: {
            const byte posX = regs_.getDataAt(decodeRegX(op)) % GUI::Screen::Width;
            const byte posY = regs_.getDataAt(decodeRegY(op)) % GUI::Screen::Height;
            const uint16_t height = decodeN(op);
            regs_.clearCarry();

            for (byte y = 0; y != height && posY + y < GUI::Screen::Height; y += 1) {
                const byte sprite = ram_[regs_.getAddr()];
                for (byte x = 0; x != __CHAR_BIT__ * sizeof(sprite) && posX + x < GUI::Screen::Width; x += 1) {
                    const bool pix = (sprite >> (7 - x)) & 1;
                    if (!pix)
                        continue;
                    if (!scr_.toggle(posX + x, posY + y))
                        regs_.setCarry();
                }
                regs_.setAddr(regs_.getAddr() + 1);
            }
            break;
        }
        case 0xE: {
            break;
        }
        case 0xF: {
            break;
        }
        default:
            std::cout << "Unsupported OP: " << std::uppercase << std::setbase(16) << op << std::endl;
    }
}