// Problem 81 - Path sum: two ways
// In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by only moving to the right and down, is indicated in bold red and is equal to 2427.
// | 131 673 234 103  18 |
// | 201  96 342 965 150 |
// | 630 803 746 422 111 |
// | 537 699 497 121 956 |
// | 805 732 524  37 331 |
// 131 >> 201 >> 96 >> 342 >> 746 >> 422 >> 121 >> 37 >> 331 >> SUM = 2427
// Find the minimal path sum, in matrix.txt (right click and "Save Link/Target As..."), a 31K text file containing a 80 by 80 matrix, from the top left to the bottom right by only moving right and down.

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "matrix.hpp"

int SearchForMinPath(Matrix & matrix);

int main()
{
    try{
        std::string file = "test.txt";
        Matrix testM(file);
        std::cout << testM << "\n";
        std::cout << "Minimum path sum for test matrix: " << SearchForMinPath(testM) << "\n\n";
        file = "p081_matrix.txt";
        Matrix M(file);
        std::cout << "Minimum path sum for matrix: " << SearchForMinPath(M) << "\n";
    }
    catch(const std::ios_base::failure & e){
        std::cout << e.what() << std::endl;
    }
    catch(...){
        std::cout << "Unexpected error!" << std::endl;
    }
    return 0;
}

int SearchForMinPath(Matrix & matrix)
{
    Matrix m(matrix.Rows(), matrix.Columns());
    m(0,0) = matrix(0,0);
    for(auto r = 0; r < m.Rows(); ++r){
        for(auto c = 0; c < m.Columns(); ++c){
            if(!(r == 0 && c == 0)){
                if(r < 1){
                    m(r,c) = matrix(r,c) + m(r,c-1);
                } else if(c < 1){
                    m(r,c) = matrix(r,c) + m(r-1,c);
                } else {
                    if(m(r-1,c) < m(r,c-1)){
                        m(r,c) = matrix(r,c) + m(r-1,c);
                    } else {
                        m(r,c) = matrix(r,c) + m(r,c-1);
                    }
                }
            }
        }
    }
    return m(m.Rows()-1,m.Columns()-1);
}
