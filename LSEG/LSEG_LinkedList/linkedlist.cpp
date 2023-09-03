#include "linkedlist.h"
#include <iostream>
#include <fstream>

using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    lastBuyer = false;
    lastSeller = false;
}

LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::insert(Flower flower) {
    Node* newNode = new Node{flower, nullptr};

    if (!head) {
        head = newNode;
        return;
    }

    if (flower.side == 2) { // Increasing order
        if (flower.price < head->data.price || (flower.price == head->data.price && flower.orderID < head->data.orderID)) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && (current->next->data.price < flower.price || (current->next->data.price == flower.price && current->next->data.orderID < flower.orderID))) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    } else if (flower.side == 1) { // Decreasing order
        if (flower.price >= head->data.price || (flower.price == head->data.price && flower.orderID <= head->data.orderID)) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && (current->next->data.price > flower.price || (current->next->data.price == flower.price && current->next->data.orderID > flower.orderID))) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // Check if client_orderID already exists in the list
    Node* current2 = head;
    while (current2) {
        if (current2->data.client_orderID == flower.client_orderID) {
            flower.ExecStatus = "Pfully";
            return;
        }
        current2 = current2->next;
    }

    // If client_orderID doesn't exist, update ExecStatus to "New"
    flower.ExecStatus = "New";
}


void LinkedList::display() const {
    Node* current = head;

    while (current) {
        string side;

        if (current->data.side == 1) {
            side = "Buy  1";
        } else if (current->data.side == 2) {
            side = "Sell 2";
        }

        cout << "Order ID: " << current->data.orderID << ", Client Order ID: " << current->data.client_orderID
             << ", Instrument: " << current->data.instrument << ", Side: " << side
             << ", Exec Status: " << current->data.ExecStatus << ", Quantity: " << current->data.quantity
             << ", Price: " << current->data.price << ", Reason: " << current->data.Reason << endl;

        current = current->next;
    }
}
void LinkedList::writeOutputToCSV(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << " for writing." << std::endl;
        return;
    }

    file << "Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price,Reason" << std::endl;

    Node* current = head;
    while (current) {
        std::string side = (current->data.side == 1) ? "Buy" : "Sell";
        file << current->data.orderID << "," << current->data.client_orderID << "," << current->data.instrument
             << "," << side << "," << current->data.ExecStatus << "," << current->data.TR_quantity
             << "," << current->data.TR_price << "," << current->data.Reason << std::endl;
        current = current->next;
    }

    file.close();
}


void LinkedList::processBuyer(Flower& buyer, LinkedList& sellerList, LinkedList& buyerList, LinkedList& Outlist) {
    // Initialize lastBuyer to false
    lastBuyer = false;

    if (!sellerList.head) {
        // If seller list is empty, add buyer to buyer list with ExecStatus "New"
        buyer.ExecStatus = "New";
        buyer.TR_quantity = buyer.quantity;
        buyer.TR_price = buyer.price;

        buyerList.insert(buyer);
        Outlist.Normal_insert(buyer);
    } else {
        // Iterate through sellers and process buyers accordingly
        Node* currentSeller = sellerList.head;
        while (currentSeller && buyer.quantity > 0 && sellerList.head->data.price <= buyer.price) {
            selling(sellerList.head->data, buyer, sellerList, buyerList, Outlist);
            if (lastSeller) {
                break;
            }
        }

        // If buyer's quantity is still greater than 0 and lastBuyer is false, add it to the buyer list
        if (buyer.quantity > 0 && !lastBuyer) {
            buyer.ExecStatus = "New";
            buyerList.insert(buyer);
        }
    }
}

void LinkedList::remove(const Flower& flower) {
    Node* current = head;
    Node* previous = nullptr;

    while (current) {
        if (current->data == flower) {
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            return;
        }

        previous = current;
        current = current->next;
    }
}

void LinkedList::Normal_insert(Flower& flower) {
    Node* newNode = new Node{flower, nullptr};

    if (!head) {
        head = newNode;
    } else {
        Node* current = head;

        while (current->next) {
            current = current->next;
        }

        current->next = newNode;
    }
}

void LinkedList::selling(Flower& seller, Flower& buyer, LinkedList& sellerList, LinkedList& buyerList, LinkedList& Outlist) {
    Node* currentSeller = sellerList.head;
    Node* currentBuyer = buyerList.head;

    if (seller.quantity > buyer.quantity) {
        seller.quantity -= buyer.quantity;
        seller.TR_quantity = buyer.quantity;
        buyer.TR_quantity = buyer.quantity;

        seller.ExecStatus = "pfill";
        buyer.ExecStatus = "fill";

        if (seller.orderID > buyer.orderID) {
            buyer.TR_price = buyer.price;
            seller.TR_price = buyer.price;
            Outlist.Normal_insert(seller);
            Outlist.Normal_insert(buyer);
        } else {
            buyer.TR_price = seller.price;
            seller.TR_price = seller.price;
            Outlist.Normal_insert(buyer);
            Outlist.Normal_insert(seller);
        }

        if (currentBuyer && !currentBuyer->next) {
            buyerList.clear();
            lastBuyer = true;
        } else if (currentBuyer && currentBuyer->next) {
            buyerList.removeFirst();
        }
    } else if (seller.quantity < buyer.quantity) {
        buyer.quantity -= seller.quantity;
        seller.TR_quantity = seller.quantity;
        buyer.TR_quantity = seller.quantity;
        buyer.TR_price = buyer.price;
        seller.TR_price = buyer.price;
        buyer.ExecStatus = "pfill";
        seller.ExecStatus = "fill";

        if (seller.orderID > buyer.orderID) {
            buyer.TR_price = buyer.price;
            seller.TR_price = buyer.price;
            Outlist.Normal_insert(seller);
            Outlist.Normal_insert(buyer);
        } else {
            buyer.TR_price = seller.price;
            seller.TR_price = seller.price;
            Outlist.Normal_insert(buyer);
            Outlist.Normal_insert(seller);
        }

        if (currentSeller && !currentSeller->next) {
            sellerList.clear();
            lastBuyer = true;
        } else if (currentSeller) {
            sellerList.removeFirst();
        }
    } else {
        seller.TR_quantity = seller.quantity;
        buyer.TR_quantity = seller.quantity;
        buyer.TR_price = buyer.price;
        seller.TR_price = buyer.price;
        buyer.ExecStatus = "fill";
        seller.ExecStatus = "fill";

        if (seller.orderID > buyer.orderID) {
            buyer.TR_price = buyer.price;
            seller.TR_price = buyer.price;
            Outlist.Normal_insert(seller);
            Outlist.Normal_insert(buyer);
        } else {
            buyer.TR_price = seller.price;
            seller.TR_price = seller.price;
            Outlist.Normal_insert(buyer);
            Outlist.Normal_insert(seller);
        }

        if (currentSeller && !currentSeller->next) {
            sellerList.clear();
            lastSeller = true;
        } else if (currentSeller) {
            sellerList.removeFirst();
        }

        if (currentBuyer && !currentBuyer->next) {
            buyerList.clear();
            lastBuyer = true;
        } else if (currentBuyer && currentBuyer->next) {
            buyerList.removeFirst();
        }
    }
}

void LinkedList::processSeller(Flower& seller, LinkedList& sellerList, LinkedList& buyerList, LinkedList& Outlist) {
    if (!buyerList.head) {
        // If buyer list is empty, add seller to seller list with ExecStatus "New"
        seller.ExecStatus = "New";
        seller.TR_quantity = seller.quantity;
        seller.TR_price = seller.price;
        Outlist.Normal_insert(seller);
        sellerList.insert(seller);
    } else {
        // Iterate through buyers and process sellers accordingly
        Node* currentBuyer = buyerList.head;

        while (currentBuyer && seller.quantity > 0 && buyerList.head->data.price >= seller.price) {
            selling(seller, buyerList.head->data, sellerList, buyerList, Outlist);
            if (lastBuyer) {
                break;
            }
        }

        // If seller's quantity is still greater than 0 after the iteration, add it to the seller list
        if (seller.quantity > 0) {
            seller.ExecStatus = "New";
            sellerList.insert(seller);
        }
    }
}

void LinkedList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    lastBuyer = false;
    lastSeller = false;
}

void LinkedList::removeFirst() {
    if (head == nullptr) {
        return;
    }

    Node* oldHead = head;
    head = head->next;
    delete oldHead;
}

void LinkedList::Flowerdisplay(Flower& flower) {
    std::string side;

    if (flower.side == 1) {
        side = "Buy  1";
    } else if (flower.side == 2) {
        side = "Sell 2";
    }

    cout << "Order ID: " << flower.orderID << ", Client Order ID: " << flower.client_orderID
         << ", Instrument: " << flower.instrument << ", Side: " << side
         << ", Exec Status: " << flower.ExecStatus << ", Quantity: " << flower.quantity << " quantity: " << flower.TR_quantity
         << ", Price: " << flower.price << endl;
}

