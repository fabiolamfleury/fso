#include <stdio.h>
#include "new_types.h"
#include "quadrilateral_calcs.h"

Quadrilateral read_coordinates(){
  Quadrilateral quadrilateral;
  int number = 0;
  while(number < 4){
    scanf("%lf",&quadrilateral.vertice[number].x);
    scanf("%lf",&quadrilateral.vertice[number].y);
    number++;
  }
  return quadrilateral;
}

void print_area(Quadrilateral quadrilateral){
  printf("Area: %.lf.\n",area(quadrilateral));
}

void out_is_convex(Quadrilateral quadrilateral){
  int result;
  result = is_convex(quadrilateral);
  if(result == 0){
    printf("Quadrilatero convexo.\n");
    print_area(quadrilateral);
  }
  else{
    printf("Quadrilatero nao convexo.\n");
  }
}
