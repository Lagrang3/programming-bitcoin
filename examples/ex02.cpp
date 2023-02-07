/*
    Eduardo Quintana Miranda 2022
    
    Building a static modular arithmetic field.
*/
#include <bitcoin/secp256k1.hpp>
#include <iostream>
using namespace bitcoin;

class f57
{
    public:
    using value_type =  unsigned int;
    static constexpr value_type P = 57;
};

using mint_f57 = mint_field<f57>;

int main()
{
     // Modular addition
     std::cout << std::dec;
     {
         mint_f57 x{44},y{33};
         std::cout << x+y << "\n"; // 20
     }
     {
         mint_f57 x{9},y{29};
         std::cout << x-y << "\n"; // 37
     }
     {
         mint_f57 a{17},b{42},c{49};
         std::cout << a+b+c << "\n"; // 51
     }
     {
         mint_f57 a{52},b{30},c{38};
         std::cout << a-b-c << "\n"; // 41
     }
     // Modular multiplication
     {
         mint_f57 a{44},b{33};
         std::cout << a*b << '\n'; // 27
     }
     // Modular exponentiation
     {
         mint_f57 a{44};
         int n{4};
         std::cout << pow(a,n) << '\n'; // 4
     }
     // modular inverse
     {
         const auto P{secp256k1_field::P};
         secp256k1_field a{44};
         secp256k1_field b{a.inverse()};
         std::cout << a << '\n'; 
         std::cout << b << '\n'; 
         std::cout << a*b << '\n';
     }
    return 0;
}

