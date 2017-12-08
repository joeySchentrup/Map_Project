#ifndef TESTER_H 
#define TESTER_H

#include "catch.hpp"
#include <cstdlib>

#include "../AVL.h"
#include "../BSTROOT.h"
#include "../BSTLEAF.h"
#include "../BSTRAND.h"

using namespace cop3530;

class Functions {
public:
    static bool cf(int l, int r) { return l < r; };

    static bool ef(int l, int r) { return l == r; };
};

#endif