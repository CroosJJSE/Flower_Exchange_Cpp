#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "flower.h"

class CSVWriter {
public:
    CSVWriter(const std::string& filename);
    ~CSVWriter();

    void writeFlowerToCSV(const Flower& flower);
    void writeFlowerListToCSV(const std::vector<Flower>& flowers);

private:
    std::ofstream file;
};

#endif // CSVWRITER_H
