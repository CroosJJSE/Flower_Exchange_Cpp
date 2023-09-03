#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "flower.h"
#include <fstream>

class LinkedList {
private:
    struct Node {
        Flower data;
        Node* next;
    };

    Node* head;
    bool lastBuyer;
    bool lastSeller;

public:
    LinkedList();
    ~LinkedList();

    void insert(Flower flower);
    void processBuyer(Flower& buyer, LinkedList& sellerList, LinkedList& buyerList, LinkedList& Outlist);
    void processSeller(Flower& seller, LinkedList& sellerList, LinkedList& buyerList, LinkedList& Outlist);
    void Normal_insert(Flower& flower);
    void selling(Flower& seller, Flower& buyer, LinkedList& sellerList, LinkedList& buyerList, LinkedList& Outlist);
    void remove(const Flower& flower);
    void clear();
    void removeFirst();
    void Flowerdisplay(Flower& flower);
    void display() const;
    void writeOutputToCSV(const std::string& filename) const;
};

#endif
