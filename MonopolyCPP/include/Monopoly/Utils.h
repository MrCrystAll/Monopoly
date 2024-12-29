#pragma once

#include <iostream>
#include <random>
#include <stdlib.h>
#define LOG(content) std::cout << content << '\n'
#define WARN(content) std::cout << "[WARN] - " << content << '\n'
#define ERR(content) std::cerr << "[ERROR] - " << content << '\n'; \
exit(EXIT_FAILURE);


int Random(int lowBound, int highBound);
