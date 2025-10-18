cmake_minimum_required(VERSION 4.0)
project(Atividade_md2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Atividade_md2 main.c
        rsa.c
        "Chaves Periodicas(Q2).c"
        extra_1.c)
