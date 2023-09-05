
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

     //cout<<"seller in  insert: "<<flower.client_orderID<<endl;


    // Sort the vector based on price and orderID
    sort(flowers.begin(), flowers.end(), [](const Flower& a, const Flower& b) {
        // Sort in ascending order based on price
        if (a.side == 2 && b.side == 2) { // Both are sellers, sort by price and then orderID
            if (a.price == b.price) {
                return a.orderID < b.orderID;
            }
            return a.price < b.price;
        } else if (a.side == 1 && b.side == 1) { // Both are buyers, sort by price (descending) and then orderID
            if (a.price == b.price) {
                return a.orderID < b.orderID;
            }
            return a.price > b.price;
        } else if (a.side == 1 && b.side == 2) { // Buyer comes before seller
            return true;
        } else { // Seller comes after buyer
            return false;
        }
    });

    // Check if client_orderID already exists in the list

    // If client_orderID doesn't exist, update ExecStatus to "New"
    flower.ExecStatus = "New  ";




}


void VectorList::display() const {
    for (const Flower& flower : flowers) {
        string side;

        if (flower.side == 1) {
            side = "Buy  1";
        } else if (flower.side == 2) {
            side = "Sell 2";
        }

        cout << "   " << flower.orderID << "   " << flower.client_orderID
             << "   " << flower.instrument << "   " << side
             << "   " << flower.ExecStatus << "   " << flower.TR_quantity
             << "   " << flower.TR_price << endl;
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
        std::string side = (flower.side == 1) ? "Buy " : "Sell";
        file <<"ord" + std::to_string(flower.orderID)  << "," << flower.client_orderID << "," << flower.instrument
             << "," << side << "," << flower.ExecStatus << "," << flower.TR_quantity
             << "," << flower.TR_price << "," << flower.Reason << std::endl;
    }

    file.close();
}

void VectorList::processBuyer(Flower& buyer, VectorList& sellerList, VectorList& buyerList, VectorList& Outlist) {
    // Initialize lastBuyer to false
    bool lastSeller = false;

    if (sellerList.flowers.empty()) {
        // If seller list is empty, add buyer to buyer list with ExecStatus "New"
        buyer.ExecStatus = "New  ";
        buyer.TR_quantity = buyer.quantity;
        buyer.TR_price = buyer.price;

        buyerList.insert(buyer);
        Outlist.Normal_insert(buyer);
    } else {
        // Iterate through sellers and process buyers accordingly
        for (Flower& seller : sellerList.flowers) {
            if (buyer.quantity > 0 && seller.price <= buyer.price) {
                    //cout<<seller.client_orderID<<endl;
                sellerList.selling(seller, buyer, sellerList, buyerList, Outlist);
                if (lastSeller) {
                    break;
                }
            }
        }

        // If buyer's quantity is still greater than 0 and lastBuyer is false, add it to the buyer list
        if (buyer.quantity > 0 && !lastBuyer) {
            buyerList.insert(buyer);
        }
    }
}

void VectorList::processSeller(Flower& seller, VectorList& sellerList, VectorList& buyerList, VectorList& Outlist) {
    lastBuyer=false;
    if (buyerList.flowers.empty()) {
        // If buyer list is empty, add seller to seller list with ExecStatus "New"
        seller.ExecStatus = "New  ";
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
                        //cout<<lastBuyer<<endl;
                    break;
                }
            }
        }

        // If seller's quantity is still greater than 0 after the iteration, add it to the seller list
        if (seller.quantity > 0) {
            sellerList.insert(seller);
        }
    }
}

void VectorList::Normal_insert(Flower& flower) {
    flowers.push_back(flower);

}

void VectorList::removeFirst() {
    if (!flowers.empty()) {
        // Check if there are at least two elements
        if (flowers.size() >= 2) {
            // Copy the details of the second element into the first element
            flowers[0] = flowers[1];
        }
        // Remove the second element (if there are only two elements, it will become empty)
        flowers.erase(flowers.begin() + 1);


    }
}


void VectorList::selling(Flower& seller, Flower& buyer, VectorList& sellerList, VectorList& buyerList, VectorList& Outlist) {
    //cout<<"seller in  selling: "<<seller.client_orderID<<endl;
   // cout<<"buyer in selling: "<<buyer.client_orderID<<endl;
    if (seller.quantity > buyer.quantity) {
        seller.quantity -= buyer.quantity;
        seller.TR_quantity = buyer.quantity;
        buyer.TR_quantity = buyer.quantity;

        seller.ExecStatus = "pfill";
        buyer.ExecStatus = "fill ";

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
               // cout<<"buyerlist is deleted"<<endl;
            buyerList.clear();
            lastBuyer=true;
        } else {
            buyerList.removeFirst();
           // cout<<lastBuyer<<endl;
        //cout<<"just removed the top buyer"<<endl;
        }
    } else if (seller.quantity < buyer.quantity) {
        buyer.quantity -= seller.quantity;
        seller.TR_quantity = seller.quantity;
        buyer.TR_quantity = seller.quantity;
        buyer.TR_price = buyer.price;
        seller.TR_price = buyer.price;
        buyer.ExecStatus = "pfill";
        seller.ExecStatus = "fill ";

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
           // cout<<"sellerlist is deleted"<<endl;
            lastSeller=true;
        } else {
            sellerList.removeFirst();
            //cout<<"top seller is deleted"<<endl;
        }
    } else {
        seller.TR_quantity = seller.quantity;
        buyer.TR_quantity = seller.quantity;
        buyer.TR_price = buyer.price;
        seller.TR_price = buyer.price;
        buyer.ExecStatus = "fill ";
        seller.ExecStatus = "fill ";

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
           // cout<<"seller list is deleted"<<endl;
            lastSeller=true;
        } else {
            sellerList.removeFirst();
           // cout<<"top seller is deleted"<<endl;
        }

        if (buyerList.flowers.size() == 1) {
            buyerList.clear();
           // cout<<"buyerlist is deleted"<<endl;
            lastBuyer=true;
        } else {
            buyerList.removeFirst();
           // cout<<"top buyer is deleted"<<endl;
        }
    }
}


void VectorList::remove(const Flower& flower) {
    auto it = std::remove(flowers.begin(), flowers.end(), flower);
    flowers.erase(it, flowers.end());
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

void VectorList::clear() {
    flowers.clear();
    lastBuyer = false;
    lastSeller = false;
}

