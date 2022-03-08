#ifndef __CARD_H__
#define __CARD_H__
#include "var.h"
#pragma once

class Card {
private:
	cnum num;
	cshape shape;
public:
	Card() {}
	Card(cnum n, cshape s) {
		num = n;
		shape = s;
	}
	void SetNum(cnum num);
	cnum GetNum();
	void SetShape(cshape num);
	cshape GetShape();
};

#endif

