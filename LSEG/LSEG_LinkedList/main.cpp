#include <iostream>
#include <fstream>
#include "linkedlist.h"
#include "struct.h"
#include <iostream>
#include <fstream>
#include <string>
#include "flower.h"
#include "struct.h"
#include "linkedlist.h"



using namespace std;



// Function to write the linked list of Flower structs to a CSV file iteratively

int main() {
    LinkedList rose1, rose2, lavender1, lavender2, lotus1, lotus2, tulip1, tulip2, orchid1, orchid2, Outlist;

    ifstream file("ex9.csv");
    string line;

    // Skip the first line (headers)
    getline(file, line);
    int orderID = 0;

    while (getline(file, line)) {
        orderID++;
        Flower flower = parseFlowerData(line);

        flower.orderID = orderID;
        flower.TR_price=flower.price;
        flower.TR_quantity=flower.quantity;

        // Validate the flower object
        bool isValid = true; // Assume the flower is valid by default

        // Check conditions and update ExecStatus and Reason accordingly
        if (flower.client_orderID.empty()||
            flower.price < 0 ||
            (flower.quantity % 10 != 0) ||
            flower.quantity < 10 || flower.quantity > 1000) {
            isValid = false;
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
                flower.TR_price=flower.price;
                flower.TR_quantity=flower.quantity;
                Outlist.Normal_insert(flower);
     } else {
            if (flower.instrument == "Rose") {
            if (flower.side == 1) { // Buyer
                rose2.processBuyer(flower, rose2, rose1, Outlist);
            } else if (flower.side == 2) { // Seller
                rose2.processSeller(flower, rose2, rose1, Outlist);
            } else {
                // Invalid side
                isValid = false;
                flower.Reason = "Invalid side";
                flower.ExecStatus = "Rejected";
                Outlist.Normal_insert(flower);

            }
        } else if (flower.instrument == "Lavender") {
            if (flower.side == 1) { // Buyer
                lavender2.processBuyer(flower, lavender2, lavender1, Outlist);
            } else if (flower.side == 2) { // Seller
                lavender2.processSeller(flower, lavender2, lavender1, Outlist);
            } else {
                // Invalid side
                isValid = false;
                flower.Reason = "Invalid side";
                flower.ExecStatus = "Rejected";
                Outlist.Normal_insert(flower);
            }
        } else if (flower.instrument == "Lotus") {
            if (flower.side == 1) { // Buyer
                lotus2.processBuyer(flower, lotus2, lotus1, Outlist);
            } else if (flower.side == 2) { // Seller
                lotus2.processSeller(flower, lotus2, lotus1, Outlist);
            } else {
                // Invalid side
                isValid = false;
                flower.Reason = "Invalid side";
                flower.ExecStatus = "Rejected";
                Outlist.Normal_insert(flower);
            }
        } else if (flower.instrument == "Tulip") {
            if (flower.side == 1) { // Buyer
                tulip2.processBuyer(flower, tulip2, tulip1, Outlist);
            } else if (flower.side == 2) { // Seller
                tulip2.processSeller(flower, tulip2, tulip1, Outlist);
            } else {
                // Invalid side
                isValid = false;
                flower.Reason = "Invalid side";
                flower.ExecStatus = "Rejected";
                Outlist.Normal_insert(flower);
            }
        } else if (flower.instrument == "Orchid") {
            if (flower.side == 1) { // Buyer
                orchid2.processBuyer(flower, orchid2, orchid1, Outlist);
            } else if (flower.side == 2) { // Seller
                orchid2.processSeller(flower, orchid2, orchid1, Outlist);
            } else {
                // Invalid side
                isValid = false;
                flower.Reason = "Invalid side";
                flower.ExecStatus = "Rejected";
                Outlist.Normal_insert(flower);
            }
        } else {
            // Invalid instrument
            isValid = false;
            flower.Reason = "Invalid instrument";
            flower.ExecStatus = "Rejected";
            Outlist.Normal_insert(flower);
        }

        // Insert the flower into the respective lists based on your other logic
        // ...


            // Set rejection reason based on which condition failed



        }

        // Process the flower based on its instrument and side
       }

    // Output or further processing
    // ...
     Outlist.writeOutputToCSV("output.csv");
     //rose2.display();
     cout<<"it is finished :) "<<endl;
    return 0;

}
