#pragma once

#ifndef iterateOver
#define iterateOver 1
#endif

#ifndef console_width
#define console_width 80
#endif

#ifndef console_height
#define console_height 20
#endif

#ifndef padding_horizontal
#define padding_horizontal 13
#endif

#ifndef padding_vertical
#define padding_vertical 9
#endif

#ifndef maxlen
#define maxlen 256
#endif

/* Temporary Code Block Begin */
#ifndef _GCC_VERSION_LESS_THAN_8_
#define _GCC_VERSION_LESS_THAN_8_
#endif
/* Temporary Code Block End */

#include <bits/stdc++.h>

#ifdef _GCC_VERSION_LESS_THAN_8_
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#elif _GCC_VERSION_MORE_THAN_8_
    #include <filesystem>
    namespace fs = std::filesystem;
#endif
