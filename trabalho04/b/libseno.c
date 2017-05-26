#include <math.h>
/*calcula o seno com a aproxima da serie sen(x)=x - x³/3! + x⁵/5! - x⁷/7!*/
double seno(double angulo){
  double elemento2 = (pow (angulo, 3) / 6); /* angulo^3 / 3!*/
  double elemento3 = (pow (angulo, 5) / 120); /*angulo^5 / 5!*/
  double elemento4 = (pow (angulo, 7) / 5040); /*angulo^7 / 7!*/

  double seno = angulo - elemento2 + elemento3 - elemento4;
  return seno;
}

double arc_seno(double seno){
  double elemento2 = (pow (seno, 3) / 6); /* angulo^3 / 6*/
  double elemento3 = 3 * (pow (seno, 5) / 40); /*angulo^5 / 40*/
  double elemento4 = 5 * (pow (seno, 7) / 15);

  double arcseno = seno + elemento2 + elemento3 + elemento4;
  return arcseno;
}
