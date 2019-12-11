#pragma once

#include <bits/stdc++.h>
#include "constants.h"
#include "credentials.h"
#include "loaders.h"
#include "rlutil.h"
#include "criminals.h"
#include "admin.h"

using namespace std::literals::chrono_literals;

credentials caller1(bool existing_user = true, bool modify = false);
void caller2(bool, bool);
extern bool AdminChoiceProcessor();
bool caller3(bool);
