#include <bitcoin/algebra.hpp>
#include <iostream>

template<typename T>
struct multiply
{
    T operator () (T & a, T const & b) const
    {
        return a *= b;
    }
};

template<typename T>
struct sum
{
    T operator () (T & a, T const & b) const
    {
        return a += b;
    }
};

int main()
{
     // test power()
     {
        // c*a^b
        assert( bitcoin::detail::power(2,3,1,multiply<int>()) == 8 );
        assert( bitcoin::detail::power(2,3,5,multiply<int>()) == 40 );
        assert( bitcoin::detail::power(2,1,5,multiply<int>()) == 10 );
        assert( bitcoin::detail::power(2,0,5,multiply<int>()) == 5 );
        assert( bitcoin::detail::power(2,3,0,multiply<int>()) == 0 );
        assert( bitcoin::detail::power(1,3,0,multiply<int>()) == 0 );
        assert( bitcoin::detail::power(1,3,5,multiply<int>()) == 5 );
        
        // c + a*b
        assert( bitcoin::detail::power(2,3,0,sum<int>()) == 6 );
        assert( bitcoin::detail::power(3,2,0,sum<int>()) == 6 );
        assert( bitcoin::detail::power(2,3,5,sum<int>()) == 11 );
        assert( bitcoin::detail::power(2,1,5,sum<int>()) == 7 );
        assert( bitcoin::detail::power(2,0,5,sum<int>()) == 5 );
        assert( bitcoin::detail::power(0,3,0,sum<int>()) == 0 );
        assert( bitcoin::detail::power(0,3,5,sum<int>()) == 5 );
     }
     
     // test power_greater
     {
        // is a^c > b ?
        assert( bitcoin::detail::power_greater(2,4,2) == false );
        assert( bitcoin::detail::power_greater(2,3,2) == true );
        assert( bitcoin::detail::power_greater(1,3,2) == false );
        assert( bitcoin::detail::power_greater(1,4,2) == false );
        assert( bitcoin::detail::power_greater(1,3,2) == false );
        
        assert( bitcoin::detail::power_greater(6,35,2) == true );
        assert( bitcoin::detail::power_greater(6,36,2) == false );
        assert( bitcoin::detail::power_greater(6,37,2) == false );
        assert( bitcoin::detail::power_greater(6,1,2) == true );
        assert( bitcoin::detail::power_greater(6,6,2) == true );
     }
     // test root
     {
        // floor( power(a,1/b) )
        assert( bitcoin::detail::root(5,1) == 5);
        assert( bitcoin::detail::root(5,2) == 2);
        assert( bitcoin::detail::root(5,3) == 1);
        
        assert( bitcoin::detail::root(9,1) == 9);
        assert( bitcoin::detail::root(9,2) == 3);
        assert( bitcoin::detail::root(9,3) == 2);
        
        assert( bitcoin::detail::root(28,1) == 28);
        assert( bitcoin::detail::root(28,2) == 5);
        assert( bitcoin::detail::root(28,3) == 3);
        assert( bitcoin::detail::root(27,3) == 3);
        assert( bitcoin::detail::root(26,3) == 2);
     }
     // test gcd
     {
        int a=2,b=4;
        auto eu = bitcoin::detail::extended_euclid(a,b);
        assert(eu.x*a + eu.y*b == eu.gcd);
        assert(eu.gcd==2);
     }
     {
        int a=3,b=4;
        auto eu = bitcoin::detail::extended_euclid(a,b);
        assert(eu.x*a + eu.y*b == eu.gcd);
        assert(eu.gcd==1);
     }
     {
        int a=12,b=16;
        auto eu = bitcoin::detail::extended_euclid(a,b);
        assert(eu.x*a + eu.y*b == eu.gcd);
        assert(eu.gcd==4);
     }
    return 0;
}



