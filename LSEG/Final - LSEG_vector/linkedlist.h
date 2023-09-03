
#ifndef VectorList_H
#define VectorList_H

#include "flower.h"
#include <vector>

class VectorList {
private:
    std::vector<Flower> flowers; // Use a vector to store Flower objects

public:
    VectorList();

    void insert(Flower flower);
    void processBuyer(Flower& buyer, VectorList& sellerList, VectorList& buyerList, VectorList& Outlist);
    void processSeller(Flower& seller, VectorList& sellerList, VectorList& buyerList, VectorList& Outlist);
    void Normal_insert(Flower& flower);
    void selling(Flower& seller, Flower& buyer, VectorList& sellerList, VectorList& buyerList, VectorList& Outlist);
    void remove(const Flower& flower);
    void clear();
    void removeFirst();
    void Flowerdisplay(Flower& flower);
    void display() const;
    void writeOutputToCSV(const std::string& filename) const;
};

#endif
