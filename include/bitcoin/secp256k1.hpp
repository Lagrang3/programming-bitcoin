#pragma once

#include <bitcoin/algebra.hpp>
#include <bitcoin/ecc.hpp>

namespace bitcoin
{
    namespace detail
    {
        template<typename T>
        class secp256k1_field_template
        {
            public:
            using value_type = T;
            
            // Prime number that fixes the field
            static constexpr value_type P = 
                ((value_type{1}<<255) - (value_type{1}<<31))*2 - 977;
        
        };
        
        
        template<typename T>
        class secp256k1_ec_template
            /*
                SECP256k1 constants
                
                The type must be an integer with at least 256 bits
                support for arithmetic operators:
                operator + ()
                operator - ()
                operator * ()
                operator / ()
                operator % ()
                
                and bit-shift
                operator << ()
                operator >> ()
            */
        {
            public:
            using value_type = T;
            
            // a and b parameters in the elliptic curve equation
            // y^2 = x^3 + a x + b
            static constexpr value_type a = 0;
            static constexpr value_type b = 7;
            
            // X and Y coordinates of the SECP256k1 point generator
            static constexpr value_type Gx = 
                (value_type{0x79be667e}<<224) + 
                (value_type{0xf9dcbbac}<<192) +
                (value_type{0x55a06295}<<160) +
                (value_type{0xce870b07}<<128) +
                (value_type{0x029bfcdb}<<96) +
                (value_type{0x2dce28d9}<<64) +
                (value_type{0x59f2815b}<<32)+
                 value_type{0x16f81798} ;
            static constexpr value_type Gy = 
                (value_type{0x483ada77}<<224) + 
                (value_type{0x26a3c465}<<192) +
                (value_type{0x5da4fbfc}<<160) +
                (value_type{0x0e1108a8}<<128) +
                (value_type{0xfd17b448}<<96) +
                (value_type{0xa6855419}<<64) +
                (value_type{0x9c47d08f}<<32)+
                 value_type{0xfb10d4b8} ;
            
        };
    } // namespace detail
    
    using secp256k1_ec = detail::secp256k1_ec_template<uint256_t>;
    
    using secp256k1_field =
    mint_field<detail::secp256k1_field_template<uint256_t>>;
    
    using secp256k1_point = detail::ec_point_t<secp256k1_field,secp256k1_ec>;
}
