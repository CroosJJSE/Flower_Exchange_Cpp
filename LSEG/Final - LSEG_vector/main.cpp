#include <iostream>
#include <fstream>
#include <vector>
#include "flower.h"
#include "struct.h"
#include "VectorList.h"

using namespace std;

// Function to write the vector of Flower structs to a CSV file iteratively


int main() {
    vector<Flower> flowers;
    VectorList rose1, rose2, lavender1, lavender2, lotus1, lotus2, tulip1, tulip2, orchid1, orchid2, Outlist;

    ifstream file("ex9.csv");
    string line;

    // Skip the first line (headers)
    getline(file, line);
    int orderID = 0;

    while (getline(file, line)) {
        orderID++;
        Flower flower = parseFlowerData(line);

        flower.orderID = orderID;
        flower.TR_price = flower.price;
        flower.TR_quantity = flower.quantity;


        // Validate the flower object
        //bool isValid = true; // Assume the flower is valid by default

        // Check conditions and update ExecStatus and Reason accordingly
        if (flower.client_orderID.empty() ||
            flower.price <= 0 ||
            (flower.quantity % 10 != 0) ||
            flower.quantity < 10 || flower.quantity > 1000) {
            flower.ExecStatus = "Rejected";
            if (flower.client_orderID.empty()) {
                flower.Reason = "Missing client_orderID";
            } else if (flower.price <= 0) {
                flower.Reason = "Price is not greater than 0";
            } else if (flower.quantity % 10 != 0) {
                flower.Reason = "Quantity is not a multiple of 10";
            } else if (flower.quantity < 10 || flower.quantity > 1000) {
                flower.Reason = "Quantity is outside the range (min = 10 max = 1000)";
            }
            flower.TR_price = flower.price;
            flower.TR_quantity = flower.quantity;
            Outlist.Normal_insert(flower);
        } else {
            // Process the flower based on your other logic
            if (flower.instrument == "Rose") {
                if (flower.side == 1) { // Buyer
                    // Process the buyer logic for Rose
                   rose1.processBuyer(flower, rose2, rose1, Outlist);

                } else if (flower.side == 2) { // Seller
                    // Process the seller logic for Rose
                rose2.processSeller(flower, rose2, rose1, Outlist);
                } else {
                    // Invalid side

                    flower.Reason = "Invalid side";
                    flower.ExecStatus = "Rejected";
                    Outlist.Normal_insert(flower);
                }
            } else if (flower.instrument == "Lavender") {
                if (flower.side == 1) { // Buyer
                    // Process the buyer logic for Lavender
                    lavender1.processBuyer(flower, lavender2, lavender1, Outlist);
                } else if (flower.side == 2) { // Seller
                    // Process the seller logic for Lavender
                    lavender2.processSeller(flower, lavender2, lavender1, Outlist);
                } else {
                    // Invalid side
                    flower.Reason = "Invalid side";
                    flower.ExecStatus = "Rejected";
                    Outlist.Normal_insert(flower);
                }
                // Process Lavender
            } else if (flower.instrument == "Lotus") {
                if (flower.side == 1) { // Buyer
                    // Process the buyer logic for Lotus
                    lotus1.processBuyer(flower, lotus2, lotus1, Outlist);
                } else if (flower.side == 2) { // Seller
                    // Process the seller logic for Lotus
                    lotus2.processSeller(flower, lotus2, lotus1, Outlist);
                } else {
                    // Invalid side
                    flower.Reason = "Invalid side";
                    flower.ExecStatus = "Rejected";
                    Outlist.Normal_insert(flower);
                }
                // Process Lotus
            } else if (flower.instrument == "Tulip") {
                if (flower.side == 1) { // Buyer
                    // Process the buyer logic for Tulip
                    tulip1.processBuyer(flower, tulip2, tulip1, Outlist);
                } else if (flower.side == 2) { // Seller
                    // Process the seller logic for Tulip
                    tulip2.processSeller(flower, tulip2, tulip1, Outlist);
                } else {
                    // Invalid side
                    flower.Reason = "Invalid side";
                    flower.ExecStatus = "Rejected";
                    Outlist.Normal_insert(flower);
                }
                // Process Tulip
            } else if (flower.instrument == "Orchid") {
                if (flower.side == 1) { // Buyer
                    // Process the buyer logic for Orchid
                    orchid1.processBuyer(flower, orchid2, orchid1, Outlist);
                } else if (flower.side == 2) { // Seller
                    // Process the seller logic for Orchid
                    orchid2.processSeller(flower, orchid2, orchid1, Outlist);
                } else {
                    // Invalid side
                    flower.Reason = "Invalid side";
                    flower.ExecStatus = "Rejected";
                    Outlist.Normal_insert(flower);
                }
                // Process Orchid
            } else {
                // Invalid instrument
                flower.Reason = "Invalid instrument";
                flower.ExecStatus = "Rejected";
                flowers.push_back(flower);
            }

            // Set rejection reason based on which condition failed
        }
    }

    // Output or further processing
    // ...

    // Write the output to CSV
    //Outlist.display();
    Outlist.writeOutputToCSV("output.csv");
    cout << "It is finished :)" << endl;

    return 0;
}
