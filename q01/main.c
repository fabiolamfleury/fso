#include <stdio.h>
#include "new_types.h"
#include "io_functions.h"
#include "io_functions.c"

int main(int argc, char const *argv[]) {
  Quadrilateral quadrilateral;
  quadrilateral = read_coordinates();
  out_is_convex(quadrilateral);
  return 0;
}
