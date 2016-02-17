//
// Created on 2/7/2016.
//

#include <cmath>
#include "Point.h"

double computeArea(const Point &a, const Point &b, const Point &c) {
    //Side lengths are the distance between two points
    double sideA = a.distanceTo(b);
    double sideB = b.distanceTo(c);
    double sideC = c.distanceTo(a);

    double s = (sideA + sideB + sideC)/2;

    return sqrt(s * (s - sideA) * (s-sideB) * (s-sideC));
}

