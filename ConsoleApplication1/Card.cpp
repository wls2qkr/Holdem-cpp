#include <iostream>
#include "Card.h"

void Card::SetNum(cnum num) {
	this->num = num;
}
cnum Card::GetNum() {
	return this->num;
}
void Card::SetShape(cshape shape) {
	this->shape = shape;
}
cshape Card::GetShape() {
	return this->shape;
}