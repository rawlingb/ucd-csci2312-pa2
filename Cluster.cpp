//
// Created by Brian on 2/16/2016.
//

#include "Point.h"
#include "Cluster.h"

Clustering::LNode::LNode(const Clustering::Point &p, Clustering::LNodePtr n) :
        point(p), next(n){ }

Clustering::Cluster::Cluster() : __points (nullptr), __size(0){ }

int Clustering::Cluster::getSize() const {
    return __size;
}

void Clustering::Cluster::add(const Clustering::Point &point) {
    if(__size == 0){ //C0py point and point the beginning to a node containing it
        Point p(point);
        __points = new LNode(p, nullptr);
    }
    else if(__size == 1){
        if(point >= __points->point){//If the new point is more than or equal to the current
            Point p(point);//Copy it and make the 1st Node point to a node containing it
            __points->next = new LNode(p, nullptr);
        }
        else { //Otherwise if the new point is smaller
            Point p(point);//Copy the point, make new point to first, then make beginning point to new
            LNode *newNode = new LNode(p, __points);
            __points = newNode;
        }
    }
    else if(__size > 1){
        int count = 0;
        bool placed = false;
        while(count < __size && !placed) {
            if(point <= __points[count].point){
                //If this point is less than or equal to this point, make it point to that point, and take whatever was
                //pointing to that and point it to this new one
                Point p(point);
                LNode *newNode;
                if(count == 0) {
                    newNode = new LNode(p, __points);
                    __points = newNode;
                } else {
                    newNode = new LNode(p, __points[count - 1].next);
                    __points[count - 1].next = newNode;
                }
                placed = true;
            }
            count++;
        }

    }
    __size++;
}

const Clustering::Point &Clustering::Cluster::remove(const Clustering::Point &point) {
    if(__size == 0){ //Nothing to remove
        return nullptr;//TODO Implement contains and consider CAssert
    }
    else if(__size == 1){
        if(point == __points->point){//If the new point is more than or equal to the current
            Point p(point);//Copy it and make the 1st Node point to a node containing it
            delete __points;
            return p;
        }
        return nullptr;
    }
    else if(__size > 1){
        int count = 0;
        bool placed = false;
        while(count < __size && !placed) {
            if(point == __points[count].point){
                //If these points are equal, make the previous point point to whatever
                //this point was pointing to and delete the current one
            }
            count++;
        }

    }
    __size++;
}
