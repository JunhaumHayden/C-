cmake_minimum_required(VERSION 3.14)
project(edita_texto_test)

set(CMAKE_CXX_STANDARD 17)

# Adiciona o GoogleTest manualmente
# Isso diz ao CMake onde estão os includes e libs
include_directories(/opt/homebrew/opt/googletest/include)
link_directories(/opt/homebrew/opt/googletest/lib)

# Adiciona o arquivo de teste
add_executable(edita_textoTest edita_textoTest.cpp)

# Linka com a lib do Google Test
target_link_libraries(edita_textoTest gtest gtest_main pthread)
