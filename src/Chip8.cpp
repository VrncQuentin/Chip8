#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "Chip8.hpp"

Chip8::Chip8::Chip8() {
    srand(time(nullptr));
}

int Chip8::Chip8::run()  noexcept {
    if (!loadNewGame("games/IBM Logo.ch8"))
        return 1;
    while (win_.isOpen()) {
        // handle input
        uint16_t op = ram_.fetch();
        exec(op);
        draw();
        usleep(100000);
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

const Chip8::Chip8::instrFnPtr Chip8::Chip8::jumpTable[] = {
        &Chip8::Chip8::clear_or_return, /* 0x0 */
        &Chip8::Chip8::jump, /* 0x1 */
        &Chip8::Chip8::call, /* 0x2 */
        &Chip8::Chip8::skipIfRegEqNN, /* 0x3 */
        &Chip8::Chip8::skipIfRegNeqNN, /* 0x4 */
        &Chip8::Chip8::skipIfRegEqReg, /* 0x5 */
        &Chip8::Chip8::setRegWithNN, /* 0x6 */
        &Chip8::Chip8::addNNtoReg, /* 0x7 */
        &Chip8::Chip8::doMathOperations, /* 0x8 */
        &Chip8::Chip8::skipIfRegNeqReg, /* 0x9 */
        &Chip8::Chip8::setAddrReg, /* 0xA */
        &Chip8::Chip8::jumpWithOffset, /* 0xB */
        &Chip8::Chip8::random, /* 0xC */
        &Chip8::Chip8::display /* 0xD */
};

void Chip8::Chip8::clear_or_return(const uint16_t op) noexcept {
    static constexpr uint16_t CLEAR = 0xE0;
    static constexpr uint16_t RETURN = 0xEE;
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
            std::cout << "Unsupported OP: " << std::uppercase << std::setbase(16) << op << std::endl;
    }
}

void Chip8::Chip8::jump(const uint16_t op) noexcept {
    const auto jumpTo = decodeNNN(op);
    ram_.setPC(jumpTo);
}

void Chip8::Chip8::call(const uint16_t op) noexcept {
    const auto curPC = ram_.getPC();
    const auto newPC = decodeNNN(op);
    stack_.push(curPC);
    ram_.setPC(newPC);
}

void Chip8::Chip8::skipIfRegEqNN(const uint16_t op) noexcept {
    const auto regValue = regs_.getDataAt(decodeRegX(op));
    const auto expected = decodeNN(op);
    if (regValue == expected)
        ram_.incrementPC();
}

void Chip8::Chip8::skipIfRegNeqNN(const uint16_t op) noexcept {
    const auto regValue = regs_.getDataAt(decodeRegX(op));
    const auto expected = decodeNN(op);
    if (regValue != expected)
        ram_.incrementPC();
}

void Chip8::Chip8::skipIfRegEqReg(const uint16_t op) noexcept {
    const auto valueRegX = regs_.getDataAt(decodeRegX(op));
    const auto valueRegY = regs_.getDataAt(decodeRegY(op));
    if (valueRegX == valueRegY)
        ram_.incrementPC();
}

void Chip8::Chip8::skipIfRegNeqReg(const uint16_t op) noexcept {
    const auto valueRegX = regs_.getDataAt(decodeRegX(op));
    const auto valueRegY = regs_.getDataAt(decodeRegY(op));
    if (valueRegX != valueRegY)
        ram_.incrementPC();
}

void Chip8::Chip8::setRegWithNN(const uint16_t op) noexcept {
    const byte what = static_cast<byte>(decodeNN(op));
    const byte where = static_cast<byte>(decodeRegX(op));
    regs_.setData(what, where);
}

void Chip8::Chip8::addNNtoReg(const uint16_t op) noexcept {
    const byte howMuch = static_cast<byte>(decodeNN(op));
    const byte where = static_cast<byte>(decodeRegX(op));
    regs_.addData(howMuch, where);
}

void Chip8::Chip8::doMathOperations(uint16_t op) noexcept {

}

void Chip8::Chip8::setAddrReg(const uint16_t op) noexcept {
    regs_.setAddr(decodeNNN(op));
}

void Chip8::Chip8::jumpWithOffset(const uint16_t op) noexcept {
    const addr jumpTo = decodeNNN(op);
    const addr offset = regs_.getDataAt(Interp::Regs::v0);
    ram_.setPC(jumpTo + offset);
}

void Chip8::Chip8::random(const uint16_t op) noexcept {
    const auto reg = decodeRegX(op);
    const auto limit = decodeNN(op);
    regs_.setData(std::rand() & limit, reg);
}

void Chip8::Chip8::display(const uint16_t op) noexcept {
    static constexpr byte rowSize = __CHAR_BIT__ * sizeof(byte);
    const byte posX = regs_.getDataAt(decodeRegX(op)) % GUI::Screen::Width;
    const byte posY = regs_.getDataAt(decodeRegY(op)) % GUI::Screen::Height;
    const uint16_t height = decodeN(op);
    regs_.clearCarry();

    for (byte y = 0; y != height && posY + y < GUI::Screen::Height; y += 1) {
        const byte sprite = ram_[regs_.getAddr()];
        for (byte x = 0; x != rowSize && posX + x < GUI::Screen::Width; x += 1) {
            const bool pix = (sprite >> (7u - x)) & 1u;
            if (!pix)
                continue;
            if (!scr_.toggle(posX + x, posY + y))
                regs_.setCarry();
        }
        regs_.setAddr(regs_.getAddr() + 1);
    }
}

void Chip8::Chip8::skipIfKey(uint16_t op) noexcept {

}

void Chip8::Chip8::doMiscOperations(uint16_t op) noexcept {

}

void Chip8::Chip8::exec(const uint16_t op) noexcept {
    const auto opFamily = decodeMajor(op);
    if (opFamily < sizeof(jumpTable) / sizeof(*jumpTable)) {
        (this->*jumpTable[opFamily])(op);
    } else {
        std::cout << "Unsupported OP: " << std::uppercase << std::setbase(16) << op << std::endl;
    }
}