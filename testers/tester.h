#ifndef TESTER_H 
#define TESTER_H

#include "catch.hpp"

#include "../AVL.h"

using namespace cop3530;

bool cf(int l, int r) { return l < r; }

bool ef(int l, int r) { return l == r; }

#endif