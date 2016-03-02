//
// Created by Brian on 2/16/2016.
//
//TODO think about the usage of subscripts in the program
#include "Point.h"
#include "Cluster.h"

Clustering::LNode::LNode(const Clustering::Point &p, Clustering::LNodePtr n) :
        point(p), next(n){ }

Clustering::Cluster::Cluster() : __points (nullptr), __size(0){ }

Clustering::Cluster::Cluster(const Clustering::Cluster &cluster) {
    __size = 0;
    __points = nullptr;
    LNode* iterate = cluster.__points;
    for(int count = 0; count < cluster.__size; count++) {
        this->add(iterate->point);
        iterate = iterate->next;
    }
}

Clustering::Cluster &Clustering::Cluster::operator=(const Clustering::Cluster &cluster) {
    if(*this == cluster) {
        return *this;
    }
    this->~Cluster();
    Cluster* newCluster = new Cluster(cluster);
    return *newCluster;
}

Clustering::Cluster::~Cluster() {
	while (__size > 0) {
		remove(__points->point);
	}
}


int Clustering::Cluster::getSize() const {
    return __size;
}

void Clustering::Cluster::add(const Clustering::Point &point) {
        if (__size == 0) { //Copy point and point the beginning to a node containing it
            Point p(point);
            __points = new LNode(p, nullptr);
        }
        else if (__size == 1) {
            if (point >= __points->point) {//If the new point is more than or equal to the current
                Point p(point);//Copy it and make the 1st Node point to a node containing it
                __points->next = new LNode(p, nullptr);
            }
            else { //Otherwise if the new point is smaller
                Point p(point);//Copy the point, make new point to first, then make beginning point to new
                LNode *newNode = new LNode(p, __points);
                __points = newNode;
            }
        }
        else if (__size > 1) {
            int count = 0;
            bool placed = false;
            LNode *iterateNext = __points;
			LNode *iteratePrev = __points;
			//Size 3
			//Both point to ele 0
			//1. next to 1(2) prev to 0(1)
			//2. next to 2(nullptr) prev to 1(2)
			//3. next to nullptr prev to 2(nullptr)
            while (count < __size && !placed) {
                if (point < iterateNext->point) {
					if (iterateNext == __points) {
						Point p(point);
						LNode *newNode;
						newNode = new LNode(p, __points);
						__points = newNode;
						placed = true;
					} else {
						Point p(point);
						LNode *newNode;
						newNode = new LNode(p, iteratePrev->next);
						iteratePrev->next = newNode;
						placed = true;
					}
                }
				if(count > 0)
					iteratePrev = iteratePrev->next;
				iterateNext = iterateNext->next;
				++count;
            }
			if (!placed) {
				Point p(point);
				LNode *newNode;
				newNode = new LNode(p, iteratePrev->next);
				iteratePrev->next = newNode;
				placed = true;
			}

        }
        __size++;
}

const Clustering::Point &Clustering::Cluster::remove(const Clustering::Point &point) {
    if(__size == 1){
        if(contains(point)){
            Point* p = new Point(point);//Remove the point
            delete __points;
            __size--;
            return *p;
        }
    }
    else if(__size > 1){
        int count = 0;
        bool placed = false;
        LNode *iterateNext = __points;
        LNode *iteratePrev = __points;
        while(count < __size && !placed) {
            if(contains(point)){
				if (point == iterateNext->point) {
					if (point == __points->point) {
						Point *p = new Point(point);
						LNodePtr tempNode = __points;
						__points = __points->next;
						delete tempNode;
						__size--;
						return *p;
					} else {
						Point* p = new Point(point);
						LNodePtr tempNode = iteratePrev->next;
						iteratePrev->next = iterateNext->next;
						delete tempNode;
						__size--;
						return *p;
					}
				}
                //If these points are equal, make the previous point point to whatever
                //this point was pointing to and delete the current one
            }
            iterateNext = iterateNext->next;
            if(count > 0)
                iteratePrev = iteratePrev->next;
            count++;
        }

    }
    Point *p = nullptr;
    return *p;//TODO Implement contains and consider CAssert
}

bool Clustering::Cluster::contains(const Clustering::Point &point) {
    if(__size == 0){ //Nothing to check for
        return false;
    }
    else if(__size == 1){
        if(point == __points->point)
            return true;
        return false;
    }
    else if(__size > 1){
        LNode *iterate = __points;
        for(int count = 0; count < __size; count++) {
            if(point == iterate->point)
                return true;
            iterate = iterate->next;
        }
        return false;
    }

}

const Clustering::Point &Clustering::Cluster::operator[](unsigned int index) const {
    //TODO Cassert
    int count = 0;
    LNode *iterate = __points;
    for(count = 0; count < __size && count != index; iterate = iterate->next)
        ++count;
    return iterate->point;
}

Clustering::Cluster &Clustering::Cluster::operator+=(const Clustering::Point &point) {
    add(point);
    return *this;
}

Clustering::Cluster &Clustering::Cluster::operator-=(const Clustering::Point &point) {
    remove(point);
    return *this;
}

const Clustering::Cluster Clustering::operator+(const Clustering::Cluster &cluster, const Clustering::Point &point) {
    Cluster c(cluster);
    c += point;
    return c;
}

const Clustering::Cluster Clustering::operator-(const Clustering::Cluster &cluster, const Clustering::Point &point) {
    Cluster c(cluster);
    c -= point;
    return c;
}

Clustering::Cluster &Clustering::Cluster::operator+=(const Clustering::Cluster &cluster) {
    for(int count = 0; count < cluster.__size; count++){
        if(!contains(cluster[count]))
            add(cluster[count]);
    }
    return *this;

}

Clustering::Cluster &Clustering::Cluster::operator-=(const Clustering::Cluster &cluster) {
    for(int count = 0; count < cluster.__size; count++){
        remove(cluster[count]);
    }
    return *this;
}

const Clustering::Cluster Clustering::operator+(const Cluster &cluster, const Cluster &cluster1) {
    Cluster c(cluster);//TODO Think about implementation
    c+=cluster1;
    return c;
}

const Clustering::Cluster Clustering::operator-(const Cluster &cluster, const Cluster &cluster1) {
    Cluster c(cluster);
    c-=cluster1;
    return c;
}

bool Clustering::operator==(const Clustering::Cluster &cluster, const Clustering::Cluster &cluster1) {
    if(cluster.__size != cluster1.__size) {
        return false;
    }
    if(cluster.__size == 0 && cluster1.__size == 0) { //Nothing to check for
        return true;
    }
    else if(cluster.__size >= 1 && cluster1.__size >= 1 ){
        LNode *iterate = cluster.__points;
        LNode *iterate1 = cluster1.__points;
        for(int count = 0; count < cluster.__size; count++) {
            if (iterate->point != iterate1->point)
                return false;

        }
    }
    return true;
}

bool Clustering::operator!=(const Clustering::Cluster &cluster, const Clustering::Cluster &cluster1) {
    return !(cluster == cluster1);
}

std::ostream &Clustering::operator<<(std::ostream &ostream, const Clustering::Cluster &cluster) {
    LNode *iterate = cluster.__points;
    for(int count = 0; count < cluster.__size - 1; count++) {
        ostream << iterate->point << "." << std::endl;
        iterate = iterate->next;
    }
    ostream << iterate->point;
    return ostream;
}

std::istream &Clustering::operator>>(std::istream &istream, Clustering::Cluster &cluster) {
    LNode *iterate = cluster.__points;
    for(int count = 0; count < cluster.__size; count++)
        istream >> iterate->point;
    return istream;
}
