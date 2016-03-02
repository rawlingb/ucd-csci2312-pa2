//
// Created on 2/7/2016.
//

#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "Point.h"

namespace Clustering {
    unsigned int Point::__idGen = 0;

    Point::Point(int dim) : __dim(dim), __values(new double[dim]) {
        for(int count = 0; count < __dim; count++)
            __values[count] = 0;
        __id = __idGen++;
    }

    Point::Point(int dim, double *values) : __dim(dim), __values(values){
        for(int count = 0; count < __dim; count++)
            __values[count] = 0;
        __id = __idGen++;
    }

    //Copy Constructor
    Point::Point(const Point &point) {
		//if (&point == nullptr)
			//return;
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
        if(*this == rhs)
            return *this;
        this->~Point();
        Point* lhs = new Point(rhs);
        return *lhs;
    }

    double Point::distanceTo(const Point &point) const {
        double answer = 0;
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

    Point &operator+=(Point &lhs, const Point &rhs) {
        for (int count = 0; count < lhs.__dim; count++)
            lhs[count] += rhs.__values[count];
        return lhs;
    }

    Point &operator-=(Point &point, const Point &point1) {
        for (int count = 0; count < point.__dim; count++)
            point[count] -= point1.__values[count];
        return point;
    }

    const Point operator+(const Point &lhs, const Point &rhs) {
        Point p(lhs.__dim);
        p+=lhs;
        p+=rhs;
        return p;
    }

    const Point operator-(const Point &lhs, const Point &rhs) {
        Point p(lhs.__dim);
        p+=lhs;
        p-=rhs;
        return p;
    }

    bool operator==(const Point &lhs, const Point &rhs) {
        if(lhs.__id != rhs.__id)
            return false;
        for (int count = 0; count < lhs.__dim; count++) {
            if(lhs.__values[count] != rhs.__values[count])
                return false;
        }
        return true;
    }

    bool operator!=(const Point &lhs, const Point &rhs) {
        return !(lhs == rhs);
    }

    bool operator<(const Point &lhs, const Point &rhs) {
        for (int count = 0; count < lhs.__dim; count++) {
			if (lhs.__values[count] < rhs.__values[count]) {
				return true;
			} else if (lhs.__values[count] > rhs.__values[count]) {
				//If this lhs coordinate is more than the rhs coordinate, it doesn't matter what coordinates are on the right
				//However, it still has to continue if they are equal.
				return false;
			}
        }
        return false;
    }

    bool operator>(const Point &lhs, const Point &rhs) {
        for (int count = 0; count < lhs.__dim; count++) {
            if(lhs.__values[count] > rhs.__values[count]) {
                return true;
			}
			else if (lhs.__values[count] < rhs.__values[count]) {
				//If this lhs coordinate is less than the rhs coordinate, it doesn't matter what coordinates are on the right
				//However, it still has to continue if they are equal.
				return false;
			}
        }
        return false;
    }

    bool operator<=(const Point &lhs, const Point &rhs) {
        return !(lhs > rhs);
    }

    bool operator>=(const Point &lhs, const Point &rhs) {
        return !(lhs < rhs);
    }

    std::ostream &operator<<(std::ostream &ostream, const Point &point) {
        for (int count = 0; count < point.__dim - 1; count++)
            ostream << point.__values[count] << ",";
        ostream << point.__values[point.__dim - 1];
        return ostream;
    }

    std::istream &operator>>(std::istream &istream, Point &point) {
		std::string str;
		istream >> str;
		std::stringstream sstream(str);
		for (int count = 0; count < point.__dim; count++)
		{
			std::string temp;
			getline(sstream, temp, ',');
			point.__values[count] = atof(temp.c_str());
		}
        return istream;
    }
}



