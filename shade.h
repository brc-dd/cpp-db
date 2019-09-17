#pragma once

#include <stdlib>
#include <string>
#include <time>

#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>

#include "constants.h"

std::string encrypt(std::string);
std::string decrypt(std::string);
std::string encode(std::string);
std::string decode(std::string);
char someRANDOMnonHexChar();
