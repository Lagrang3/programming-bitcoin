#include <bitcoin/algebra.hpp>
#include <iostream>

class f19
{
    public:
    using value_type =  int;
    static constexpr value_type P = 31;
};

using mint_f19 = bitcoin::mint_field<f19>;

void test()
{
    for(int i=1;i<f19::P;++i)
    {
        mint_f19 x{i};
        std::cout << " i = " << i << " -> i ^ p-1 = " <<
            bitcoin::pow(x,f19::P-1).get() << "\n";
    }
}

int main()
{
    try
    {
        test();
    }
    catch (...){
    }
    return 0;
}
