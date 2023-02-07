/*
    Eduardo Quintana Miranda 2022
    
    Print secp256k1 constants in decimal and hexadecimal format:
    prime P, a and b values,
    all print the X and Y coordinates of the generator G
*/

#include <bitcoin/secp256k1.hpp>
#include <iostream>
using namespace bitcoin;

int main()
{
    // SECP256k1 constants
    std::cout << "SECP256k1 prime:\n" 
              << "DEC: " << std::dec << secp256k1_field::P << '\n'
              << "HEX: " << std::hex << secp256k1_field::P << "\n\n";
    std::cout << "SECP256k1 a:\n" 
              << std::dec << secp256k1_ec::a << "\n\n";
    std::cout << "SECP256k1 b:\n" 
              << std::dec << secp256k1_ec::b <<"\n\n";
    
    std::cout << "SECP256k1 generator (G.x):\n" 
              << "DEC: " << std::dec << secp256k1_ec::Gx << '\n'
              << "HEX: " << std::hex << secp256k1_ec::Gx << "\n\n";
    std::cout << "SECP256k1 generator (G.y):\n" 
              << "DEC: " << std::dec << secp256k1_ec::Gy << '\n'
              << "HEX: " << std::hex << secp256k1_ec::Gy << "\n\n";
    
    return 0;
}
