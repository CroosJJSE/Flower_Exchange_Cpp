
#ifndef FLOWER_H
#define FLOWER_H
using namespace std;

#include <string>

struct Flower {
    int orderID;
    std::string client_orderID;
    std::string instrument;
    int side;
    std::string ExecStatus;
    int quantity;
    int TR_quantity;
    double price;
    double TR_price;
    std::string Reason;

    // Correct definition of the equality operator
    bool operator==(const Flower& rhs) const {
        return client_orderID == rhs.client_orderID &&
               instrument == rhs.instrument &&
               side == rhs.side &&
               quantity == rhs.quantity &&
               price == rhs.price;
    }


    // Function to extract an integer from an order ID

};

#endif
