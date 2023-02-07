#pragma once

#include <iostream>
#include <limits>
#include <boost/multiprecision/cpp_int.hpp>

namespace bitcoin
{
    // base integers
    typedef boost::multiprecision::uint256_t uint256_t;
    
    
   namespace detail
   {
        template<typename integer, typename Exp, typename op_t>
        integer power(const integer x,Exp n,const integer first, op_t op)
        /*
            Divide and conquer O(log n) complexity of ( x op x ... )
        */
        {
            assert(n>=0);
            integer r=first,aux=x;
            for(;n;n>>=1){
                if( n & 1 ) op(r,aux);
                op(aux,aux);
            }
            return r;
        }
        template <typename integer, typename Exp>
        constexpr bool power_greater(integer A, integer B, Exp p)
        /*
            auxiliary method.
            is A^p > B?
        */
        {
            // precondition: A,B,p > 0
            // returns true if A^p > B
            if (A == 1)
                return 1 > B;
            if (p > std::numeric_limits<integer>::digits)
                return true;

            while (p-- && B>0)
                B /= A;
            return 1 > B;
        }

        template <typename integer, typename Exp>
        constexpr integer root(const integer N, const Exp p)
        /*
            returns the p-rooth of N
            by binary search
            ie. the greatest number x, such that x^p <= N
        */
        {
            if (p == 1)
                return N;
            // no overflow
            integer down = 1, up = N;
            while (up - down > 1)
            {
                integer mid = down + (up - down) / 2;
                if (power_greater(mid, N, p))
                    up = mid;
                else
                    down = mid;
            }
            return down;
        }
        template <typename T>
        constexpr bool overflow_by_sum(const T mod)
        /*
            does T overflow when mod is used in sums?
        */
        {
            // the type that stores the sum is not necessarily T.
            // eg. if you sum two int8_t the machine will save the value in a 64 or 32 bit 
            // integer dependending on the architecture.
            typedef decltype(mod + T{0}) Tsum;
            constexpr Tsum max = std::numeric_limits<Tsum>::max();
            return (mod - 1) > max - (mod - 1);
        }
        template <typename T>
        constexpr bool overflow_by_multiplication(const T mod)
        /*
            does T overflow when mod is used in products?
        */
        {
            typedef decltype(mod * T{1}) Tmult;
            Tmult sqrt_max = root(std::numeric_limits<Tmult>::max(), 2);
            return mod - 1 > sqrt_max;
        }
        
        template <typename integer>
        struct euclid_return
        // return type of the extended Euclidean algorithm
        {
            integer gcd, x, y;
        };

        template <typename integer>
        euclid_return<integer> extended_euclid(const integer a, const integer b)
        // extended Euclidean algorithm,
        // it finds x,y,g, such that
        // g = a*x + b*y
        // and g is the gcd(a,b)
        {
            static_assert(std::numeric_limits<integer>::is_signed,
                          "Signed integers are needed");
            integer x = 1, y = 0, g = a;
            for (integer x1 = 0, y1 = 1, g1 = b; g1;)
            {
                integer q = g / g1;
                x = x - x1 * q;
                std::swap(x, x1);
                y = y - y1 * q;
                std::swap(y, y1);
                g = g - g1 * q;
                std::swap(g, g1);
            }
            return {g, x, y};
        }
    }
    template<typename field_t>
    class mint_field  : public field_t
    {
        public:
        using value_type = typename field_t::value_type;
        using field_t::P;
        
        value_type get() const
        {
            return value;
        }
        
        private:
        static constexpr value_type mod = field_t::P;
        value_type value{};
        
        static value_type modulo_sum(value_type a, value_type b)
        // carefully sum the values avoiding sum overflow
        // precondition: a,b>=0 and a,b<mod
        
        // FIXME: test, two different scenarios
        {
            if constexpr (detail::overflow_by_sum<value_type>(mod))
            {
                value_type r = mod - a;
                if(b>=r)
                    return b-r;
                return a+b;
            }
            return (a+b) % mod;
        }
        static value_type modulo_prod(value_type a, value_type b)
        // carefully multiply the values avoiding product overflow
        // precondition: a,b>=0 and a,b<mod
        // FIXME: test, two different scenarios
        {
            if constexpr (detail::overflow_by_multiplication<value_type>(mod))
            {
                // in this case a*b = a+a+a+...+a (b times)
                return detail::power(a,b,value_type{0},
                [](value_type& x, const value_type& y)
                {
                    return x = modulo_sum(x,y);
                });
            }
            return ( a*b )%mod;
        }
        
        static constexpr value_type modulo_init(value_type x)
        {
            const value_type r = x % mod;
            return r >= 0 ? r : r + mod ;
        }
        
        public:
        static value_type modulo_inverse_prime(value_type x)
        // FIXME: test
        {
            // precondition: mod is prime
            return detail::power(x,mod-2,value_type{1},
            [](value_type& a, const value_type& b)
            {
                return a = modulo_prod(a,b);
            });
        }
        static value_type modulo_inverse_signed(value_type x)
        // FIXME: test
        {
            // precondition: value_type is signed
            static_assert ( std::is_signed<value_type>::value);
            return modulo_init(detail::extended_euclid(x,mod).x);
        }
        
        public:
        
        constexpr mint_field(const mint_field<field_t>& other):
            value{other.value}
        {}
        constexpr explicit mint_field(const value_type x):
            value{modulo_init(x)}
        {}
        constexpr mint_field()
        {}
        
        explicit mint_field(const std::string x):
            value{x}
        {
            value = modulo_init(value);
        }
        
        mint_field inverse()const
        {
            if constexpr ( std::is_signed<value_type>::value)
                return mint_field{ modulo_inverse_signed(value) };
                
            value_type x = modulo_inverse_prime(value);
            return mint_field{x};
        }
        
        mint_field& operator+=(mint_field that)
        {
            //std::cerr << "value = " << value << '\n';
            //std::cerr << "that value = " << that.value << '\n';
            value = modulo_sum(value,that.value);
            //std::cerr << "value = " << value << '\n';
            return *this;
        }
        mint_field& operator-=(mint_field that)
        {
            value = modulo_sum( value,mod-that.value);
            return *this;
        }
        
        mint_field& operator *= (mint_field that)
        {
            value = modulo_prod(value,that.value);
            return *this;
        }
        mint_field& operator /= (mint_field that)
        {
            value_type x_inv ;
            if constexpr ( std::is_signed<value_type>::value)
                x_inv = modulo_inverse_signed(that.value);
            else
                x_inv = modulo_inverse_prime(that.value);
            
            value = modulo_prod(value,x_inv);
            return *this;
        }
        
        bool operator == (mint_field that) const
        {
            return value == that.value;
        }
        bool operator != (mint_field that) const
        {
            return !( (*this)==that );
        }
        operator bool() const
        {
            return value == 0;
        }
        
        template<typename T>
        friend std::ostream& operator << (std::ostream& os, const
        mint_field<T>& x);
    };
    template<typename T>
    mint_field<T> operator + (const mint_field<T>& x, const mint_field<T>& y)
    {
        mint_field<T> z{x};
        //std::cerr << "z = " << z << "\n";
        //z+=y;
        //std::cerr << "z = " << z << "\n";
        //return z;
        return z+=y;
    }
    template<typename T>
    mint_field<T> operator - (const mint_field<T>& x, const mint_field<T>& y)
    {
        mint_field<T> z{x};
        return z-=y;
    }
    template<typename T>
    mint_field<T> operator * (const mint_field<T>& x, const mint_field<T>& y)
    {
        mint_field<T> z{x};
        return z*=y;
    }
    template<typename T>
    mint_field<T> operator / (const mint_field<T>& x, const mint_field<T>& y)
    {
        mint_field<T> z{x};
        return z/=y;
    }
    
    template<typename T1, typename T2, typename T3>
    T1 pow(const T1& x, const T2 n, const T3& first)
    {
        return detail::power(x,n,T1(first),
            [](T1& x_in, const T1 y_in)
            {
                return x_in*=y_in;
            });
    }
    template<typename T1, typename T2>
    T1 pow(const T1& x, const T2 n)
    {
        // only when n>0 we don't need the identity
        assert(n>0);
        return detail::power(x,n-1,x,
            [](T1& x_in, const T1 y_in)
            {
                return x_in*=y_in;
            });
    }
    
    template<typename T>
    std::ostream& operator << (std::ostream& os, const mint_field<T>& x)
    {
        return os << x.value;
    }
    
}
