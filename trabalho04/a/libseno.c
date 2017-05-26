/*calcula o seno com a aproxima da serie sen(x)=x - x³/3! + x⁵/5! - x⁷/7!*/
double seno(double angulo){
  double elemento2 = (angulo * angulo * angulo) / 6); /* angulo^3 / 3!*/
  double elemento3 = (angulo * angulo * angulo * angulo * angulo / 120); /*angulo^5 / 5!*/
  double elemento4 = (angulo * angulo * angulo * angulo * angulo * angulo * angulo/ 5040); /*angulo^7 / 7!*/

  double seno = angulo - elemento2 + elemento3 - elemento4;
  return seno;
}

double arc_seno(double seno){
  double elemento2 = (angulo * angulo * angulo) / 6); /* angulo^3 / 3!*/
  double elemento3 = (angulo * angulo * angulo * angulo * angulo / 120); /*angulo^5 / 5!*/
  double elemento4 = (angulo * angulo * angulo * angulo * angulo * angulo * angulo/ 5040); /*angulo^7 / 7!*/

  double arcseno = seno + elemento2 + elemento3 + elemento4;
  return arcseno;
}
