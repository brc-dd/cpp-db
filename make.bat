@echo off
@echo generating the key and iv...
g++ generator.cpp csprng.cpp -I -std=c++17 -lstdc++fs
a.exe
@echo compiling project...
g++ main.cpp admin.cpp callers.cpp constants.cpp credentials.cpp criminals.cpp loaders.cpp shade.cpp users.cpp validators.cpp -I -std=c++17 -lstdc++fs -lcryptopp
