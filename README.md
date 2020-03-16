This is the js engine from serenity os

Compile:

`clang++ -g -I. -o js js.cpp AK/*.cpp LibJS/*.cpp -std=c++2a -lstdc++ -fno-exceptions -fno-rtti -fstack-protector -Wall`


