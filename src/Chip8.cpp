#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "Chip8.hpp"

Chip8::Chip8::Chip8() {
    srand(time(nullptr));
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

const Chip8::Chip8::jumpTable Chip8::Chip8::instructions{
        {0x0, &Chip8::clear_or_return},
        {0x1, &Chip8::jump},
        {0x2, &Chip8::call},
        {0x3, &Chip8::skipIfRegEqNN},
        {0x4, &Chip8::skipIfRegNeqNN},
        {0x5, &Chip8::skipIfRegEqReg},
        {0x6, &Chip8::setRegWithNN},
        {0x7, &Chip8::addNNtoReg},
        {0x8, &Chip8::doMathOperations},
        {0x9, &Chip8::skipIfRegNeqReg},
        {0xA, &Chip8::setAddrReg},
        {0xB, &Chip8::jumpWithOffset},
        {0xC, &Chip8::random},
        {0xD, &Chip8::display},
        {0xE, &Chip8::skipIfKey},
        {0xF, &Chip8::doMiscOperations}
};

void Chip8::Chip8::exec(const uint16_t op) noexcept {
    const auto opFamily = decodeMajor(op);
    const auto instrFn = instructions.find(opFamily);

    if (instrFn != instructions.end()) {
        (this->*(instrFn->second))(op);
    } else {
        std::cout << "Unsupported OP: " << std::uppercase << std::setbase(16) << op << std::endl;
    }
}

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

const Chip8::Chip8::jumpTable Chip8::Chip8::mathInstructions{
        {0x0, &Chip8::Chip8::doMathSet},
        {0x1, &Chip8::Chip8::doMathOr},
        {0x2, &Chip8::Chip8::doMathAnd},
        {0x3, &Chip8::Chip8::doMathXor},
        {0x4, &Chip8::Chip8::doMathAdd},
        {0x5, &Chip8::Chip8::doMathSubXY},
        {0x6, &Chip8::Chip8::doMathSHR},
        {0x7, &Chip8::Chip8::doMathSubYX},
        {0xE, &Chip8::Chip8::doMathSHL}
};

void Chip8::Chip8::doMathOperations(uint16_t op) noexcept {
    const auto what = decodeN(op);
    const auto opFn = mathInstructions.find(what);

    if (opFn == instructions.end()) {
        (this->*(opFn->second))(op);
    } else {
        std::cout << "Unsupported OP: " << std::uppercase << std::setbase(16) << op << std::endl;
    }
}

void Chip8::Chip8::doMathSet(const uint16_t op) noexcept {
    const auto vx = decodeRegX(op);
    const auto valY = regs_.getDataAt(decodeRegY(op));
    regs_.setData(valY, vx);
}

void Chip8::Chip8::doMathOr(const uint16_t op) noexcept {
    const auto vx = decodeRegX(op);
    const auto valX = regs_.getDataAt(vx);
    const auto valY = regs_.getDataAt(decodeRegY(op));
    regs_.setData(valX | valY, vx);
}

void Chip8::Chip8::doMathAnd(const uint16_t op) noexcept {
    const auto vx = decodeRegX(op);
    const auto valX = regs_.getDataAt(vx);
    const auto valY = regs_.getDataAt(decodeRegY(op));
    regs_.setData(valX & valY, vx);
}

void Chip8::Chip8::doMathXor(const uint16_t op) noexcept {
    const auto vx = decodeRegX(op);
    const auto valX = regs_.getDataAt(vx);
    const auto valY = regs_.getDataAt(decodeRegY(op));
    regs_.setData(valX ^ valY, vx);
}

void Chip8::Chip8::doMathAdd(const uint16_t op) noexcept {
    const auto vx = decodeRegX(op);
    const auto valX = regs_.getDataAt(vx);
    const auto valY = regs_.getDataAt(decodeRegY(op));
    const uint16_t res = valX + valY;
    const bool overflow = res > __UINT8_MAX__;
    regs_.setData(static_cast<byte>(res), vx);
    regs_.setCarry(overflow);
}

void Chip8::Chip8::doMathSubXY(const uint16_t op) noexcept {
    const auto vx = decodeRegX(op);
    const auto valX = regs_.getDataAt(vx);
    const auto valY = regs_.getDataAt(decodeRegY(op));
    const auto res = static_cast<int8_t>(valX - valY);
    const bool notUnderflow = valX > valY; // if we underflow the carry must be 0
    regs_.setData(static_cast<byte>(res), vx);
    regs_.setCarry(notUnderflow);
}

void Chip8::Chip8::doMathSubYX(const uint16_t op) noexcept {
    const auto vx = decodeRegX(op);
    const auto valX = regs_.getDataAt(vx);
    const auto valY = regs_.getDataAt(decodeRegY(op));
    const auto res = static_cast<int8_t>(valY - valX);
    const bool notUnderflow = valY < valX; // if we underflow the carry must be 0
    regs_.setData(static_cast<byte>(res), vx);
    regs_.setCarry(notUnderflow);
}

void Chip8::Chip8::doMathSHR(const uint16_t op) noexcept {
    // CHIP-48 / SUPER-CHIP style shift, we ignore Y
    const auto vx = decodeRegX(op);
    const auto valX = regs_.getDataAt(vx);
    const auto outBit = valX >> 7u;
    const auto res = static_cast<byte>(valX << 1u);
    regs_.setData(res, vx);
    regs_.setCarry(outBit);
}

void Chip8::Chip8::doMathSHL(const uint16_t op) noexcept {
    // CHIP-48 / SUPER-CHIP style shift, we ignore Y
    const auto vx = decodeRegX(op);
    const auto valX = regs_.getDataAt(vx);
    const auto outBit = valX & 1u;
    const auto res = static_cast<byte>(valX >> 1u);
    regs_.setData(res, vx);
    regs_.setCarry(outBit);
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
    static constexpr uint16_t IS_EQUAL = 0x9E;
    static constexpr uint16_t IS_DIFF  = 0xA1;
    const auto how = decodeNN(op);
    const auto what = win_.getInput();
    const auto valX = regs_.getDataAt(decodeRegX(op));

    switch (how) {
        case IS_EQUAL: {
            if (what == valX)
                ram_.incrementPC();
            break;
        }
        case IS_DIFF: {
            if (what != valX)
                ram_.incrementPC();
            break;
        }
        default:
            std::cout << "Unsupported OP: " << std::uppercase << std::setbase(16) << op << std::endl;
    }
}

const Chip8::Chip8::jumpTable Chip8::Chip8::miscInstructions{
        {0x07, &Chip8::setRegWithDelayTimer},
        {0x15, &Chip8::setDelayTimerWithReg},
        {0x18, &Chip8::setSoundTimerWithReg},
        {0x1E, &Chip8::addRegToAddr},
        {0x0A, &Chip8::getKey},
        {0x29, &Chip8::getFontChar},
        {0x33, &Chip8::setInMemWithConversion},
        {0x55, &Chip8::setInMem},
        {0x65, &Chip8::loadFromMem}
};

void Chip8::Chip8::doMiscOperations(uint16_t op) noexcept {
    const auto what = decodeNN(op);
    const auto opFn = miscInstructions.find(what);

    if (opFn == instructions.end()) {
        (this->*(opFn->second))(op);
    } else {
        std::cout << "Unsupported OP: " << std::uppercase << std::setbase(16) << op << std::endl;
    }
}

void Chip8::Chip8::setRegWithDelayTimer(uint16_t op) noexcept {
    const auto vx = decodeRegX(op);
    const auto delayValue = regs_.getDelayTimer().get();
    regs_.setData(delayValue, vx);
}

void Chip8::Chip8::setDelayTimerWithReg(uint16_t op) noexcept {
    const auto valX = regs_.getDataAt(decodeRegX(op));
    regs_.setDelayTimer(valX);
}

void Chip8::Chip8::setSoundTimerWithReg(uint16_t op) noexcept {
    const auto valX = regs_.getDataAt(decodeRegX(op));
    regs_.setSoundTimer(valX);
}

void Chip8::Chip8::addRegToAddr(uint16_t op) noexcept {
    const auto valX = regs_.getDataAt(decodeRegX(op));
    const auto valI = regs_.getAddr();
    const addr res = valX + valI;
    regs_.setAddr(res);
}

void Chip8::Chip8::getKey(uint16_t op) noexcept {
    const auto what = win_.getInput();

    if (what != GUI::None) {
        const auto vx = decodeRegX(op);
        regs_.setData(static_cast<byte>(what), vx);
    } else {
        ram_.decrementPC();
    }
}

void Chip8::Chip8::getFontChar(uint16_t op) noexcept {
    const auto valX = regs_.getDataAt(decodeRegX(op));
    regs_.setAddr(valX * 5);
}

void Chip8::Chip8::setInMemWithConversion(uint16_t op) noexcept {
    byte valX = regs_.getDataAt(decodeRegX(op));
    byte buf[3] = {0};

    // Retrieves each digit of valX but reversed, ie: 251 becomes 152
    for (byte i = 0; valX != 0; i += 1) {
        buf[i] = valX % 10;
        valX /= 10;
    }
    const auto where = regs_.getAddr();
    for (byte i = 0; i != 3; i += 1) {
        ram_.putInMem(where + i, buf[2 - i]); // Store in mem while reversing (hence 2-i)
    }
}

void Chip8::Chip8::setInMem(uint16_t op) noexcept {
    const uint16_t stop = decodeRegX(op) + 1; // + 1 because we loop 'till VX
    const auto where = regs_.getAddr();

    for (byte i = 0; i != stop; i += 1) {
        const auto what = regs_.getDataAt(i);
        ram_.putInMem(where + i, what);
    }
}

void Chip8::Chip8::loadFromMem(uint16_t op) noexcept {
    const uint16_t  stop = decodeRegX(op) + 1; // + 1 becuse we loop 'till VX
    const auto where = regs_.getAddr();

    for (byte i = 0; i != stop; i += 1) {
        const auto what = ram_[where + i];
        regs_.setData(what, i);
    }
}
