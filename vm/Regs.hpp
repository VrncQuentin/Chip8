#ifndef C8_REGS_HPP
#define C8_REGS_HPP

namespace Chip8 {
    using data_reg = uint8_t;
    using addr_reg = uint16_t;

    class Regs {
    public:

    private:
        std::array<data_reg, 16> data;
        addr_reg addr;
    };
};

#endif /* C8_REGS_HPP */
