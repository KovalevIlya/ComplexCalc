#include "complexNum.h"

const char name[9] = "Division";

void Division(struct complexNum * num, struct complexNum * one, struct complexNum * two)
{
  num->real = one->real / two->real;
  num->img = one->img / two->img;
}
