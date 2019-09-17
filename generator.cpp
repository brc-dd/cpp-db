#include <bits/stdc++.h>

#include <duthomhas/csprng.hpp>

#define _GCC_VERSION_LESS_THAN_8_   //temp line for mingw-w64\\i686-7.3.0-posix-dwarf-rt_v5-rev0 added due to a bug in some gcc versions

#ifdef _GCC_VERSION_LESS_THAN_8_
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#elif _GCC_VERSION_MORE_THAN_8_
    #include <filesystem>
    namespace fs = std::filesystem;
#endif

fs::path cp=fs::current_path();

int main()
{
    duthomhas::csprng rng;
    std::string _key_, _iv_;
    char ch;
    for(int i=0; i<16; )
    {
        ch = rng();
        if(('0'<=ch and ch<='9') or ('a'<=ch and ch<='z'))
        {
            _key_.append(1, ch);    ++i;
        }
    }
    for(int i=0; i<16; )
    {
        ch = rng();
        if(('0'<=ch and ch<='9') or ('a'<=ch and ch<='z'))
        {
            _iv_.append(1, ch);    ++i;
        }
    }
    
    #ifdef _GCC_VERSION_LESS_THAN_8_
        std::ofstream ofile((cp/"constants.h").string(), std::ios::app);
    #elif _GCC_VERSION_MORE_THAN_8_
        std::ofstream ofile(cp/"constants.h", std::ios::app);
    #endif
    
    ofile<<"\nstd::string _key_ = \""<<_key_<<"\";"
         <<"\nstd::string _iv_ = \""<<_iv_<<"\";";
    ofile.close();
    return 0;
}
