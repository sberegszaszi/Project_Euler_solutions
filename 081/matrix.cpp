#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "matrix.hpp"

Matrix::Matrix(std::string filename)
{
    std::ifstream inFile;
    inFile.open(filename);
    if(!inFile.is_open()){
        throw(std::ios_base::failure("Unable to open file."));
    }
    std::string line;
    std::string number;
    while(inFile.good()){
        while(std::getline(inFile, line)){
            std::stringstream sline(line);
            ++rows;
            while(std::getline(sline, number, ',')){
                elements.push_back(stoi(number));
            }
        }
    }
    columns = elements.size()/rows;
    inFile.close();
}

int & Matrix::operator()(const int r, const int c)
{
    return elements.at(elements.size()/rows * r + c);
}

std::ostream & operator<<(std::ostream & os, const Matrix & m)
{
    os << m.rows << " x " << m.columns << "\n";
    os << "|";
    for(auto i = 0; i < (m.rows * m.columns); ++i){
        if(i != 0 && i % m.columns == 0){
            os << "|\n|";
        }
        os << std::setfill(' ') << std::setw(4) << m.elements.at(i) << " ";
    }
    os << "|\n";
    return os;
}