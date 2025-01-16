#pragma once 

#include <cstdint>
#include <iostream>

class RGB {
public:
    // RGBA channels
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;

    RGB(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
        : r(r), g(b), b(b) {}
    ~RGB() {}

public:
    std::uint8_t get_grayscale_avg() {
        if (!r || !g || !b)
            std::cout << "Channel/RGB values are invalid\n";
        std::uint8_t gray_value = (static_cast<unsigned int>(r) + static_cast<unsigned int>(g) + static_cast<unsigned int>(b)) / 3;
        return gray_value;
    }

    static std::uint8_t grayscale_avg(std::uint8_t r_t, std::uint8_t g_t, std::uint8_t b_t) {
        std::uint8_t value = (static_cast<unsigned int>(r_t) + static_cast<unsigned int>(g_t) + static_cast<unsigned int>(b_t)) / 3;
        return value;
    }
};
