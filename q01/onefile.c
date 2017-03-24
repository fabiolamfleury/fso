#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct coordinate{
  double x;
  double y;
}Cordinate;

typedef struct quadrilateral{
  Cordinate vertice[5];
}Quadrilateral;

double length(Cordinate cordinate_1, Cordinate cordinate_2);
int is_convex(Quadrilateral quadrilateral);
double area(Quadrilateral quadrilateral);
Quadrilateral read_coordinates();
void out_is_convex(Quadrilateral quadrilateral);


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

double line_orientation(const Cordinate P, const Cordinate Q, const Cordinate R){
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
    printf("\n D[%d]: %d\n",i, d);
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

int main(int argc, char const *argv[]) {
  Quadrilateral quadrilateral;
  quadrilateral = read_coordinates();
  out_is_convex(quadrilateral);
  return 0;
}
