//
// Created on 2/7/2016.
//

#include <gdiplus/gdiplustypes.h>
#include <cmath>
#include "Point.h"

namespace Clustering {
    unsigned int Point::__idGen = 0;

    Point::Point(int dim) : __dim(dim), __values(new double[dim]) {
        __id = __idGen++;
    }

    Point::Point(int dim, double *values) : __dim(dim), __values(values){
        __id = __idGen++;
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

    //Assignment Operator
    Point &Point::operator=(const Point &rhs) {
        if(this == &rhs)
            return *this;
        Point lhs(rhs);
        return lhs;
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

    Point &Point::operator*=(double rhs) {
        for (int count = 0; count < __dim; count++)
            __values[count] *= rhs;
        return *this;
    }

    Point &Point::operator/=(double rhs) {
        for (int count = 0; count < __dim; count++)
            __values[count] /= rhs;
        return *this;
    }

    const Point Point::operator*(double rhs) const {
        Point p(*this);
        return p*= rhs;
    }

    const Point Point::operator/(double rhs) const {
        Point lhs(*this);
        return lhs /= rhs;
    }

    Point &Clustering::operator+=(Point &lhs, const Point &rhs) {
        for (int count = 0; count < lhs.__dim; count++)
            lhs[count] += rhs.__values[count];
        return lhs;
    }

    Point &Clustering::operator-=(Point &point, const Point &point1) {
        for (int count = 0; count < point.__dim; count++)
            point[count] -= point1.__values[count];
        return point;
    }

    const Point Clustering::operator+(const Point &lhs, const Point &rhs) {
        Point p(lhs.__dim);
        p+=lhs;
        p+=rhs;
        return p;
    }

    const Point Clustering::operator-(const Point &lhs, const Point &rhs) {
        Point p(lhs.__dim);
        p+=lhs;
        p-=rhs;
        return p;
    }

    bool Clustering::operator==(const Point &lhs, const Point &rhs) {
        if(lhs.__id != rhs.__id)
            return false;
        for (int count = 0; count < lhs.__dim; count++) {
            if(lhs.__values[count] != rhs.__values[count])
                return false;
        }
        return true;
    }

    bool Clustering::operator!=(const Point &lhs, const Point &rhs) {
        return !(lhs == rhs);
    }

    bool Clustering::operator<(const Point &lhs, const Point &rhs) {
        for (int count = 0; count < lhs.__dim; count++) {
            if(lhs.__values[count] < rhs.__values[count])
                return true;
        }
        return false;
    }

    bool Clustering::operator>(const Point &lhs, const Point &rhs) {
        for (int count = 0; count < lhs.__dim; count++) {
            if(lhs.__values[count] > rhs.__values[count])
                return true;
        }
        return false;
    }

    bool Clustering::operator<=(const Point &lhs, const Point &rhs) {
        return !(lhs > rhs);
    }

    bool Clustering::operator>=(const Point &lhs, const Point &rhs) {
        return !(lhs < rhs);
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



