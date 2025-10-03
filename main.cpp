#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "fusebyte.h"

std::vector<bool> convertToBits(const uint8_t &number)
{
    std::vector<bool> bitVector;

    for (int i = 7; i >= 0; --i) { // Iterate over each bit (8 bits for uint8_t)
        bitVector.push_back((number >> i) & 1);
    }

    return bitVector;
}

uint8_t convertFromBits(const std::vector<bool> &bits)
{
    uint8_t number = 0;

    for (int i = 0; i < 8; ++i) {
        number = (number << 1) | bits[i];
    }

    return number;
}

int main()
{
    FuseByte fuseByte;

    std::vector<std::vector<bool>> bitset;

    for (int i = 0; i < 256; ++i) {
        bitset.push_back(convertToBits(i));
    }

    auto bitsequence = fuseByte.fuse(bitset);

    std::cout << "Below you can see the result of the best combination of bits." << std::endl;
    std::cout << std::endl;

    for (auto bit : bitsequence) {
        std::cout << bit;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "This operation produces a 263-bit output, where the last 7 bits are a repetition of the first 7 bits, "
              "forming a circular sequence. As a result, all values between 0 and 255 can be represented within 256 bits, "
              "equivalent to 32 bytes. This represents the optimal value for this fusion process." << std::endl;


    std::cout << "Below you can see the new sequence of numbers between 0-255." << std::endl;

    // Remove last 7 bits to make it 256
    bitsequence.resize(bitsequence.size() - 7);

    for (size_t i = 0; i < 256; i++) {
        std::vector<bool> bits;

        for (size_t j = i; j < i + 8; j++) {
            bits.push_back(bitsequence[j % 256]);
        }

        std::cout << static_cast<int>(convertFromBits(bits)) << std::endl;
    }

    return 0;
}
