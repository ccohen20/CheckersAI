#ifndef search_hpp
#define search_hpp

#include <stdio.h>
#include "Global.hpp"
#include "AI.hpp"

int minmax(Board b, int depth, int bot);
Move search(Board b, int depth, int bot);
Move searchJump(Board b, int depth, int x, int y);


#endif /* search_h */