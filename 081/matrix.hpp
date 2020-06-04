#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix
{
private:
    int rows{0};
    int columns{0};
    std::vector<int> elements{};
public:
    Matrix() = delete;
    Matrix(int r, int c): rows{r}, columns{c}, elements(r * c) {};
    Matrix(int r, int c, int initValue): rows{r}, columns{c}, elements(r * c, initValue) {};
    Matrix(std::string filename);
    Matrix(const Matrix&) = default;
    Matrix& operator=(const Matrix&) = default;
    Matrix(Matrix&&) = default;
    Matrix& operator=(Matrix&&) = default;
    ~Matrix() = default;
    int Rows() const { return rows; }
    int Columns() const { return columns; }
    int& operator()(const int r, const int c);
    friend std::ostream & operator<<(std::ostream & os, const Matrix & m);
};

#endif //MATRIX_H