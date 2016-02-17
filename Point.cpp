//
// Created on 2/7/2016.
//

#include <cmath>
#include <gdiplus/gdiplustypes.h>
#include "Point.h"

namespace Clustering {
    unsigned int Point::__idGen = 0;

    Point::Point(int dim) : __dim(dim), __values(new double[dim]) {
        __id = __idGen;
        __idGen++;
    }

    Point::Point(int dim, double *values) : __dim(dim), __values(values){
        __id = __idGen;
        __idGen++;
    }

    //Copy Constructor
    Point::Point(const Point &point) {
        __id = point.__id;
        __dim = point.__dim;
        __values = new double[point.__dim];
        for (int count = 0; count < __dim; count++)
            __values[count] = point.__values[count];
    }

    //Destructor
    Point::~Point() {
        delete [] __values;
    }

    Point &Point::operator=(const Point &point) {
        if(this == &point)
            return *this;
        Point p(point);
        return p;
    }

    double Point::distanceTo(const Point &point) const {
        int answer = 0;
        for (int count = 0; count < __dim; count++)
            answer += pow(point.__values[count] - __values[count], 2);
        return sqrt(answer);
    }

    double &Point::operator[](int index) {
        return __values[index];
    }

    Point &Point::operator*=(double d) {
        for (int count = 0; count < __dim; count++)
            __values[count] *= d;
    }

    Point &Point::operator/=(double d) {
        for (int count = 0; count < __dim; count++)
            __values[count] /= d;
    }

    const Point Point::operator*(double d) const {
        Point p(*this);
        return p*= d;
    }

    const Point Point::operator/(double d) const {
        Point p(*this);
        return p/= d;
    }

    Point &Clustering::operator+=(Point &point, const Point &point1) {
        for (int count = 0; count < point.__dim; count++)
            point[count] += point1.__values[count];
        return point;
    }

    Point &Clustering::operator-=(Point &point, const Point &point1) {
        for (int count = 0; count < point.__dim; count++)
            point[count] -= point1.__values[count];
        return point;
    }

    const Point Clustering::operator+(const Point &point, const Point &point1) {
        Point p(point.__dim);
        p+=point;
        p+=point1;
        return p;
    }

    const Point Clustering::operator-(const Point &point, const Point &point1) {
        Point p(point.__dim);
        p+=point;
        p-=point1;
        return p;
    }

    bool Clustering::operator==(const Point &point, const Point &point1) {
        if(point.__id != point1.__id)
            return false;
        for (int count = 0; count < point.__dim; count++) {
            if(point.__values[count] != point1.__values[count])
                return false;
        }
        return true;
    }

    bool Clustering::operator!=(const Point &point, const Point &point1) {
        return !(point == point1);
    }

    bool Clustering::operator<(const Point &point, const Point &point1) {
        for (int count = 0; count < point.__dim; count++) {
            if(point.__values[count] < point1.__values[count])
                return true;
        }
        return false;
    }

    bool Clustering::operator>(const Point &point, const Point &point1) {
        for (int count = 0; count < point.__dim; count++) {
            if(point.__values[count] > point1.__values[count])
                return true;
        }
        return false;
    }

    bool Clustering::operator<=(const Point &point, const Point &point1) {
        return !(point > point1);
    }

    bool Clustering::operator>=(const Point &point, const Point &point1) {
        return !(point < point1);
    }

    std::ostream &Clustering::operator<<(std::ostream &ostream, const Point &point) {
        for (int count = 0; count < point.__dim - 1; count++)
            ostream << point.__values[count] << ",";
        ostream << point.__values[point.__dim - 1];
        return ostream;
    }

    std::istream &Clustering::operator>>(std::istream &istream, Point &point) {
        for (int count = 0; count < point.__dim; count++)
            istream >> point.__values[count];
        return istream;
    }
}



