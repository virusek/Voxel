#ifndef STATE_H
#define STATE_H

#include "gfx/window.h"

struct State {
  struct Window *window;
};

extern struct State state;

#endif // !STATE_H
