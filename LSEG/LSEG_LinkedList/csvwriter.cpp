#include "csvwriter.h"

CSVWriter::CSVWriter(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    } else {
        // Write the CSV header
        file << "Order ID,Cl. Ord. ID,Instrument,Side,Exec Status,Quantity,Price,Reason" << std::endl;
    }
}

CSVWriter::~CSVWriter() {
    if (file.is_open()) {
        file.close();
    }
}

void CSVWriter::writeFlowerToCSV(const Flower& flower) {
    if (file.is_open()) {
        file << flower.orderID << ","
             << flower.client_orderID << ","
             << flower.instrument << ","
             << (flower.side == 1 ? "Buy" : "Sell") << ","
             << flower.ExecStatus << ","
             << flower.quantity << ","
             << flower.price << ","
             << flower.Reason << std::endl;
    } else {
        std::cerr << "Error: File is not open for writing." << std::endl;
    }
}

void CSVWriter::writeFlowerListToCSV(const std::vector<Flower>& flowers) {
    for (const Flower& flower : flowers) {
        writeFlowerToCSV(flower);
    }
}
