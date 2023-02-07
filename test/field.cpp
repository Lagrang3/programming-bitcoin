#include <bitcoin/algebra.hpp>
#include <iostream>
#include <cstdint>

class f251_uint
{
    public:
    using value_type = std::uint8_t;
    static constexpr value_type P = 251;
    
    // P is prime, type is unsigned
};

class f113_uint
{
    public:
    using value_type = std::uint8_t;
    static constexpr value_type P = 113;
    
    // P is prime, type is unsigned
};
class f113_int
{
    public:
    using value_type = std::int8_t;
    static constexpr value_type P = 113;
    
    // P is prime, type is signed
};
class fbig_int
{
    public:
    using value_type = std::int32_t;
    static constexpr value_type P = 1000000009;
    
    // P is prime, type is signed
};
class fbig_uint
{
    public:
    using value_type = std::int32_t;
    static constexpr value_type P = 1000000009;
    
    // P is prime, type is signed
};
class fbigger_uint
{
    public:
    using value_type = std::uint32_t;
    static constexpr value_type P = 2000000009;
    
    // P is prime, type is signed
};

int main()
{
     // test sum.
     {
        bitcoin::mint_field<f113_uint> x{44}, y{33};
        assert( (x+y).get() == 77 );
     }
     {
        bitcoin::mint_field<f113_uint> x{44}, y{100};
        assert( (x+y).get() == 31 );
     }
     {
        bitcoin::mint_field<f113_uint> x{101}, y{100};
        assert( (x+y).get() == 88 );
     }
     {
        bitcoin::mint_field<f113_uint> x{13}, y{100};
        assert( (x+y).get() == 0 );
     }
     {
        bitcoin::mint_field<f113_int> x{44}, y{33};
        assert( (x+y).get() == 77 );
     }
     {
        bitcoin::mint_field<f113_int> x{44}, y{100};
        assert( (x+y).get() == 31 );
     }
     {
        bitcoin::mint_field<f113_int> x{101}, y{100};
        assert( (x+y).get() == 88 );
     }
     {
        bitcoin::mint_field<f113_int> x{13}, y{100};
        assert( (x+y).get() == 0 );
     }
     
     {
        bitcoin::mint_field<f251_uint> x{44}, y{33};
        assert( (x+y).get() == 77 );
     }
     {
        bitcoin::mint_field<f251_uint> x{60}, y{200};
        assert( (x+y).get() == 9 );
     }
     {
        bitcoin::mint_field<f251_uint> x{201}, y{200};
        assert( (x+y).get() == 150 );
     }
     {
        bitcoin::mint_field<f251_uint> x{51}, y{200};
        assert( (x+y).get() == 0 );
     }
     
     
     {
        bitcoin::mint_field<fbig_uint> x{44}, y{33};
        assert( (x+y).get() == 77 );
     }
     {
        bitcoin::mint_field<fbig_uint> x{50}, y{1000000000};
        assert( (x+y).get() == 41);
     }
     {
        bitcoin::mint_field<fbig_uint> x{1000000001}, y{1000000000};
        assert( (x+y).get() == 999999992 );
     }
     {
        bitcoin::mint_field<fbig_uint> x{9}, y{1000000000};
        assert( (x+y).get() == 0 );
     }
     {
        bitcoin::mint_field<fbig_int> x{44}, y{33};
        assert( (x+y).get() == 77 );
     }
     {
        bitcoin::mint_field<fbig_int> x{50}, y{1000000000};
        assert( (x+y).get() == 41);
     }
     {
        bitcoin::mint_field<fbig_int> x{1000000001}, y{1000000000};
        assert( (x+y).get() == 999999992 );
     }
     {
        bitcoin::mint_field<fbig_int> x{9}, y{1000000000};
        assert( (x+y).get() == 0 );
     }
     
     
     
     
     {
        bitcoin::mint_field<fbigger_uint> x{44}, y{33};
        assert( (x+y).get() == 77 );
     }
     {
        bitcoin::mint_field<fbigger_uint> x{50}, y{2000000000};
        assert( (x+y).get() == 41);
     }
     {
        bitcoin::mint_field<fbigger_uint> x{2000000001}, y{2000000000};
        assert( (x+y).get() == 1999999992 );
     }
     {
        bitcoin::mint_field<fbigger_uint> x{9}, y{2000000000};
        assert( (x+y).get() == 0 );
     }
    return 0;
}


