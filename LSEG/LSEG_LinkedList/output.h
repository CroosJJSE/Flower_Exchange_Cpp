#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>

struct Output {
    std::string orderID;
    std::string client_orderID;
    std::string instrument;
    int side;
    std::string ExecStatus;
    int quantity;
    double price;
};

#endif


