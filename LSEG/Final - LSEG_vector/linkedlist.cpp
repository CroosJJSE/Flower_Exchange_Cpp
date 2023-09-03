#include "VectorList.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

VectorList::VectorList() {
    flowers.clear();
}

void VectorList::insert(Flower flower) {
    // Insert the flower into the vector
    flowers.push_back(flower);

    // Sort the vector based on price and orderID
    sort(flowers.begin(), flowers.end(), [](const Flower& a, const Flower& b) {
        if (a.price == b.price) {
            return a.orderID < b.orderID;
        }
        return a.price < b.price;
    });

    // If client_orderID doesn't exist, update ExecStatus to "New"
    flower.ExecStatus = "New";
}

void VectorList::display() const {
    for (const Flower& flower : flowers) {
        string side;

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
}

void VectorList::writeOutputToCSV(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << " for writing." << std::endl;
        return;
    }

    file << "Order ID,Client Order ID,Instrument,Side,Exec Status,Quantity,Price,Reason" << std::endl;

    for (const Flower& flower : flowers) {
        std::string side = (flower.side == 1) ? "Buy" : "Sell";
        file << flower.orderID << "," << flower.client_orderID << "," << flower.instrument
             << "," << side << "," << flower.ExecStatus << "," << flower.TR_quantity
             << "," << flower.TR_price << "," << flower.Reason << std::endl;
    }

    file.close();
}

void VectorList::processBuyer(Flower& buyer, VectorList& sellerList, VectorList& buyerList, VectorList& Outlist) {
    // Initialize lastBuyer to false
    bool lastBuyer = false;

    if (sellerList.flowers.empty()) {
        // If seller list is empty, add buyer to buyer list with ExecStatus "New"
        buyer.ExecStatus = "New";
        buyer.TR_quantity = buyer.quantity;
        buyer.TR_price = buyer.price;

        buyerList.insert(buyer);
        Outlist.Normal_insert(buyer);
    } else {
        // Iterate through sellers and process buyers accordingly
        for (Flower& seller : sellerList.flowers) {
            if (buyer.quantity > 0 && seller.price <= buyer.price) {
                sellerList.selling(seller, buyer, sellerList, buyerList, Outlist);
                if (lastBuyer) {
                    break;
                }
            }
        }

        // If buyer's quantity is still greater than 0 and lastBuyer is false, add it to the buyer list
        if (buyer.quantity > 0 && !lastBuyer) {
            buyer.ExecStatus = "New";
            buyerList.insert(buyer);
        }
    }
}

void VectorList::processSeller(Flower& seller, VectorList& sellerList, VectorList& buyerList, VectorList& Outlist) {
    if (buyerList.flowers.empty()) {
        // If buyer list is empty, add seller to seller list with ExecStatus "New"
        seller.ExecStatus = "New";
        seller.TR_quantity = seller.quantity;
        seller.TR_price = seller.price;
        Outlist.Normal_insert(seller);
        sellerList.insert(seller);
    } else {
        // Iterate through buyers and process sellers accordingly
        for (Flower& buyer : buyerList.flowers) {
            if (seller.quantity > 0 && buyer.price >= seller.price) {
                sellerList.selling(seller, buyer, sellerList, buyerList, Outlist);
                if (lastBuyer) {
                    break;
                }
            }
        }

        // If seller's quantity is still greater than 0 after the iteration, add it to the seller list
        if (seller.quantity > 0) {
            seller.ExecStatus = "New";
            sellerList.insert(seller);
        }
    }
}

void VectorList::Normal_insert(Flower& flower) {
    flowers.push_back(flower);
}

void VectorList::selling(Flower& seller, Flower& buyer, VectorList& sellerList, VectorList& buyerList, VectorList& Outlist) {
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

        if (buyerList.flowers.size() == 1) {
            buyerList.clear();
            lastBuyer = true;
        } else {
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

        if (sellerList.flowers.size() == 1) {
            sellerList.clear();
            lastBuyer = true;
        } else {
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

        if (sellerList.flowers.size() == 1) {
            sellerList.clear();
            lastBuyer = true;
        } else {
            sellerList.removeFirst();
        }

        if (buyerList.flowers.size() == 1) {
            buyerList.clear();
            lastBuyer = true;
        } else {
            buyerList.removeFirst();
        }
    }
}

void VectorList::remove(const Flower& flower) {
    flowers.erase(remove(flowers.begin(), flowers.end(), flower), flowers.end());
}

void VectorList::clear() {
    flowers.clear();
    lastBuyer = false;
}

void VectorList::removeFirst() {
    if (!flowers.empty()) {
        flowers.erase(flowers.begin());
    }
}

void VectorList::Flowerdisplay(Flower& flower) {
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

