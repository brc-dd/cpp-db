# Description

This project is a (criminal) database management system, originally written in C\+\+98/11. The project was submitted by me for the partial fulfilment of AISSCE 2019 practical exam. Since submission, I have worked on this project to improve it alongwith my skills in C\+\+. The project is now using C\+\+17. The code is still not much appreciable though, but indeed better than earlier version, and now involves many new things.

## Project Status

Under Development - open for code reviews and bug reports

## System Requirements

Microsoft Windows (10, recommended)

## Pre-Requisites

>`mingw-w64 (i686-7.3.0-posix-dwarf-rt_v5-rev0, recommended)`
`crypto++ (8.2, recommended)`

### Download them From Here

<https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z>

<https://github.com/weidai11/cryptopp/archive/CRYPTOPP_8_2_0.zip>

### Installing mingw-w64 and crypto\+\+

1. Extract the downloaded .7z file to `C:\mingw-w64\i686-7.3.0-posix-dwarf-rt_v5-rev0\`
2. Open `cmd` with admin privileges and run:

    ```cmd
    setx /m PATH "C:\mingw-w64\i686-7.3.0-posix-dwarf-rt_v5-rev0\mingw32\bin;%PATH%
    set PATH=C:\mingw-w64\i686-7.3.0-posix-dwarf-rt_v5-rev0\mingw32\bin;%PATH%"
    ```

3. Extract the downloaded .zip file to `C:\`
4. Now run on `cmd`:

    ```cmd
    cd "C:\cryptopp-CRYPTOPP_8_2_0"
    mingw32-make
    md "C:\mingw-w64\i686-7.3.0-posix-dwarf-rt_v5-rev0\mingw32\lib\gcc\i686-w64-mingw32\7.3.0\include\c++\cryptopp"
    copy *.h "C:\mingw-w64\i686-7.3.0-posix-dwarf-rt_v5-rev0\mingw32\lib\gcc\i686-w64-mingw32\7.3.0\include\c++\cryptopp"
    copy /b *.a "C:\mingw-w64\i686-7.3.0-posix-dwarf-rt_v5-rev0\mingw32\lib\gcc\i686-w64-mingw32\7.3.0"
    ```

5. You're now ready to go!

## How to Build

Open CMD on the cloned directory and run `make`\
Ensure that `g++` is added to system `PATH` variable;\
you can check this by running `g++ --version` on a freshly opened CMD shell.

## Known Issues

The software will not compile on `g++ 8.x` because of a bug in the compiler which prevents the use of `filesystem` library.
If you are compiling this on `g++ 9.x` or above, you first need to change line `23-27` of `constants.h` with this:

```cpp
#ifndef _GCC_VERSION_MORE_THAN_8_
#define _GCC_VERSION_MORE_THAN_8_
#endif
```

and also line 5 of `generator.cpp` with

```cpp
#define _GCC_VERSION_MORE_THAN_8_
```

## Developer Support

The settings for C++ IntelliSense Extension for Visual Studio Code (`ms-vscode.cpptools`) are present under `.vscode > c_cpp_properties.json`. You just need to change the `compilerPath` and `includePath` settings there.

## Third Party Libraries

* Crypto\+\+ by Wei Dai (@github/weidai11) used under the Boost Software License, Version 1.0, August 17th, 2003 ((c) 2019).
* CSPRNG by Michael Thomas Greer (@github/Duthomhas) used under the Boost Software License, Version 1.0, August 17th, 2003 ((c) 2017).
* rlutil.h by Tapio Vierros (@github/tapio) used under the WTFPL, Version 2, December 2004 ((c) 2010).
