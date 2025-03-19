cmake_minimum_required(VERSION 3.10)
project(MeuProjeto)

add_executable(meu_programa src/main.cpp)

find_package(GTest REQUIRED)
target_link_libraries(meu_projeto GTest::GTest GTest::Main)

