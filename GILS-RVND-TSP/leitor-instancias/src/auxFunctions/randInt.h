#pragma once
#include <cstdlib>

inline int randInt(int start__, int end__) {
  return (rand() % (end__ - start__)) + start__;
}