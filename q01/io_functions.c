Quadrilateral read_coordinates(){
  Quadrilateral quadrilateral = NULL;
  int number = 0;
  while(number < 4){
    scanf("%d",&quadrilateral.vertice[number].x);
    scanf("%d",&quadrilateral.vertice[number].y);
    number++;
  }
  return quadrilateral;
}

void out_is_convex(Quadrilateral quadrilateral){
  int result;
  result = is_convex(Quadrilateral quadrilateral);
  if(result == 0){
    printf("É convexo");
  }
  else{
    printf("Não é convexo");
  }
}
