project('btc-song','cpp',
        default_options : ['cpp_std=c++17',
        'warning_level=3',
        'optimization=3'],
        version: '0.1')

cpp=meson.get_compiler('cpp')
boost = dependency('boost')

subdir('include')
libbitcoin = library('bitcoin',
    lib_headers,
    include_directories: lib_include,
    install: true,
    dependencies: [boost])

libbitcoin_dep = declare_dependency(include_directories: lib_include, link_with: libbitcoin)
    
subdir('examples')
subdir('test')
