#include <bitcoin/algebra.hpp>
#include <iostream>

class f19
{
    public:
    using value_type =  int;
    static constexpr value_type P = 19;
};


using mint_f19 = bitcoin::mint_field<f19>;

int main()
{
    // test modular inverse by Euclid algorithm
    for(int i=1;i<f19::P;++i)
    {
        mint_f19 a{i};
        mint_f19 b{ mint_f19::modulo_inverse_signed(i) };
        
        std::cout << a.get() << " " << b.get() << "\n";
        std::cout << (a*b).get() << "\n";
        
        assert((a*b).get()==1);
    }
    // test modular inverse by Fermat's little theorem
    for(int i=1;i<f19::P;++i)
    {
        mint_f19 a{i};
        mint_f19 b{ mint_f19::modulo_inverse_prime(i) };
        
        std::cout << a.get() << " " << b.get() << "\n";
        std::cout << (a*b).get() << "\n";
        
        assert((a*b).get()==1);
    }
    return 0;
}




