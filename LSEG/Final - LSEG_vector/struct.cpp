#include "struct.h"
#include <sstream>

Flower parseFlowerData(const std::string& data) {
    std::istringstream ss(data);
    Flower flower;

    // Assuming your CSV format is: client_orderID,instrument,side,quantity,price
    getline(ss, flower.client_orderID, ',');
    getline(ss, flower.instrument, ',');
    ss >> flower.side;
    ss.ignore(); // Ignore the comma
    ss >> flower.quantity;
    ss.ignore(); // Ignore the comma
    ss >> flower.price;

    return flower;
}

