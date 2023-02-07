test_secp256k1 = executable('test_secp256k1','secp256k1.cpp',
    dependencies: [boost,libbitcoin_dep])
test('SECP256k1',test_secp256k1,
   is_parallel: false)

test_fields = executable('test_fields','field.cpp',
    dependencies: [boost,libbitcoin_dep])
test('Modular field',test_fields,
   is_parallel: false)

test_arithmetics = executable('test_arithmetics','arithmetics.cpp',
    dependencies: [boost,libbitcoin_dep])
test('Arithmetic functions',test_arithmetics,
   is_parallel: false)

test_modint = executable('test_modint','mod_int.cpp',
    dependencies: [boost,libbitcoin_dep])
test('Modular integer field',test_modint,
   is_parallel: false)
