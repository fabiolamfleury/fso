
#include "quadrilateral_calcs.h"
#include <stdio.h>

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

void out_is_convex(Quadrilateral quadrilateral){
  int result;
  result = is_convex(quadrilateral);
  if(result == 0){
    printf("Quadrilatero convexo");
  }
  else{
    printf("Quadrilatero nao convexo");
  }
}
