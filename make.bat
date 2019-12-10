@echo off
@echo generating the key and iv...
g++ generator.cpp csprng.cpp -I -std=c++17 -lstdc++fs
a
@echo initialising setup...
g++ build.cpp admin.cpp callers.cpp constants.cpp credentials.cpp criminals.cpp csprng.cpp loaders.cpp shade.cpp users.cpp validators.cpp -I -std=c++17 -lstdc++fs -lcryptopp
set /p pwd="Enter new admin password: "
a %pwd%
@echo compiling project...
g++ main.cpp admin.cpp callers.cpp constants.cpp credentials.cpp criminals.cpp csprng.cpp loaders.cpp shade.cpp users.cpp validators.cpp -I -std=c++17 -lstdc++fs -lcryptopp
@echo you're ready to go...
del "constants.cpp"
pause
exit 0