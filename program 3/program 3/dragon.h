
#ifndef DRAGON_H_
#define DRAGON_H_

#include "Turtle.h"

class Dragon: public Turtle  // Dragon is a divide class of the Turtle class.
{
public:
    Dragon(float initX = 0.0, float initY = 0.0, float initAngle = 0.0);// constructor
    void leftCurve(int l, float d);  //draw a level-l left curve with distance d
    void rightCurve(int l, float d); //draw a level-l right curve with distance d
};
#endif /* DRAGON_H_ */
