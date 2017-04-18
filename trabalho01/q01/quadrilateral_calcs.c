#include <math.h>
#include <stdlib.h>
#include "new_types.h"

double length(Cordinate cordinate_1, Cordinate cordinate_2){
  double result = 0;
  double result_x = 0;
  double result_y = 0;
  result_x = (cordinate_1.x - cordinate_2.x)*(cordinate_1.x - cordinate_2.x);
  result_y = (cordinate_1.y - cordinate_2.y)*(cordinate_1.y - cordinate_2.y);
  result = result_x + result_y;
  result = pow(result,(1/2));
  return result;
}
double line_orientation(Cordinate P, Cordinate Q, Cordinate R){
    return (P.x * Q.y + P.y * R.x + Q.x * R.y) - (R.x * Q.y + R.y * P.x + Q.x * P.y);
}

int is_convex(Quadrilateral quadrilateral){
  quadrilateral.vertice[4] = quadrilateral.vertice[0];

  int result = 0;
  int orientation = 0, i = 0;
  for (i = 0; i < 4; ++i){
    int d = line_orientation(quadrilateral.vertice[i], quadrilateral.vertice[i + 1], quadrilateral.vertice[i + 2]);
    if (d == 0)
      continue;

    orientation = d;
    break;
  }

  for (i = 0; i < 4; ++i) {
    int d = line_orientation(quadrilateral.vertice[i], quadrilateral.vertice[i + 1], quadrilateral.vertice[i + 2]);
    if (d == -orientation)
      return -1;
  }
  if(orientation != 0)
    return 0;
}

double area(Quadrilateral quadrilateral){
  double area = 0;
  int i;

  for (i = 0; i < 4; ++i) {
      area += quadrilateral.vertice[i].x * quadrilateral.vertice[i+1].y;
      area -= quadrilateral.vertice[i+1].x * quadrilateral.vertice[i].y;
  }

  area = 0.5 * fabs(area);
  return area;
}
