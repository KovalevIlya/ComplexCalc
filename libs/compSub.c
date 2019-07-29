#include "complexNum.h"

const char name[12] = "Subtraction";

void Subtraction(struct complexNum * num, struct complexNum * one, struct complexNum * two)
{
  num->real = one->real - two->real;
  num->img = one->img - two->img;
}
