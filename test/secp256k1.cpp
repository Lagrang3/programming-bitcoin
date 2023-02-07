#include <bitcoin/secp256k1.hpp>
#include <iostream>
#include <sstream>
#include <cassert>
using namespace bitcoin;

int main()
{
    std::stringstream sp ;
    
    // fiducial value taken from
    // https://en.bitcoin.it/wiki/Secp256k1
    std::string const P_hex = 
        "ffffffff" "ffffffff"
        "ffffffff" "ffffffff"
        "ffffffff" "ffffffff"
        "fffffffe" "fffffc2f";
    
    sp.str("");
    sp << std::hex << secp256k1_field::P;
    // check that the secp256k1 prime is correct
    assert(sp.str() == P_hex);
    
    
    // fiducial value taken from
    // https://en.bitcoin.it/wiki/Secp256k1
    std::string const G_hex = 
        "79be667e" "f9dcbbac"
        "55a06295" "ce870b07"
        "029bfcdb" "2dce28d9"
        "59f2815b" "16f81798"
        "-"
        "483ada77" "26a3c465"
        "5da4fbfc" "0e1108a8"
        "fd17b448" "a6855419"
        "9c47d08f" "fb10d4b8";
    
    
    sp.str("");
    sp << std::hex << secp256k1_ec::Gx << "-" << secp256k1_ec::Gy;
    // check that the secp256k1 base point is correct
    assert(sp.str() == G_hex);
    
    { // test elliptic curve multiplication
        const secp256k1_point G = secp256k1_point::generator();
        auto G2  = G*G;
        sp.str("");
        sp << std::hex << G2.x() << "-" << G2.y();
        
        assert(sp.str() == 
            "c6047f9441ed7d6d3045406e95c07cd85c778e4b8cef3ca7abac09b95c709ee5"
            "-"
            "1ae168fea63dc339a3c58419466ceaeef7f632653266d0e1236431a950cfe52a");
    }
    { // test elliptic curve exponentiation
        const secp256k1_point G = secp256k1_point::generator();
        auto G1  = pow(G,1);
        sp.str("");
        sp << std::hex << G1.x() << "-" << G1.y();
        // std::cout << sp.str() << '\n';
        assert(sp.str() == 
            "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798"
            "-"
            "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8");
    }
    { // test elliptic curve exponentiation
        const secp256k1_point G = secp256k1_point::generator();
        auto G2  = pow(G,2);
        sp.str("");
        sp << std::hex << G2.x() << "-" << G2.y();
        
        assert(sp.str() == 
            "c6047f9441ed7d6d3045406e95c07cd85c778e4b8cef3ca7abac09b95c709ee5"
            "-"
            "1ae168fea63dc339a3c58419466ceaeef7f632653266d0e1236431a950cfe52a");
    }
    { // test elliptic curve exponentiation
        const secp256k1_point G = secp256k1_point::generator();
        std::vector< std::string > gtest {
            "",
            "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798L",
            "0xc6047f9441ed7d6d3045406e95c07cd85c778e4b8cef3ca7abac09b95c709ee5L",
            "0xf9308a019258c31049344f85f89d5229b531c845836f99b08601f113bce036f9L",
            "0xe493dbf1c10d80f3581e4904930b1404cc6c13900ee0758474fa94abe8c4cd13L",
            "0x2f8bde4d1a07209355b4a7250a5c5128e88b84bddc619ab7cba8d569b240efe4L",
            "0xfff97bd5755eeea420453a14355235d382f6472f8568a18b2f057a1460297556L",
            "0x5cbdf0646e5db4eaa398f365f2ea7a0e3d419b7e0330e39ce92bddedcac4f9bcL",
            "0x2f01e5e15cca351daff3843fb70f3c2f0a1bdd05e5af888a67784ef3e10a2a01L",
            "0xacd484e2f0c7f65309ad178a9f559abde09796974c57e714c35f110dfc27ccbeL",
            "0xa0434d9e47f3c86235477c7b1ae6ae5d3442d49b1943c2b752a68e2a47e247c7L"
        };
        for(int i=1;i<gtest.size();++i)
        {
            auto A  = pow(G,i,secp256k1_point::identity());
            // std::cout << std::hex << A.x() << '\n';
            sp.str("");
            sp << "0x" << std::hex << A.x() << "L";
            // std::cout << sp.str() << " vs " << gtest[i] << '\n';
            // if(A.is_identity()) std::cout << "Identity!\n";
            assert(sp.str()==gtest[i]);
        }
    }
    
    return 0;
}
