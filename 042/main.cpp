// Problem 42 - Coded triangle numbers
// The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:
// 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
// By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.
// Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <sstream>
#include <vector>

int WordValue(std::string const & word);
int NthTriangleNum(int n);
void PopulateWithTriangleNums(std::vector<int> & v);
bool IsWordTriangle(std::vector<int> & triangleNums, std::string const & word);

int main()
{
    try {
        std::vector<int> triangleNums(50);
        PopulateWithTriangleNums(triangleNums);
        int numOfTriangleWords = 0;

        std::string fileName = "p042_words.txt";
        std::ifstream inFile;
        inFile.open(fileName);
        if(!inFile.is_open()){
            throw(std::ios_base::failure("Unable to open file"));
        } else {
            std::string word;
            while(inFile.good()){
                while(getline(inFile, word, ',')){
                    if(IsWordTriangle(triangleNums, word) == true){
                        ++numOfTriangleWords;
                    }
                }
            }
        }
        inFile.close();
        std::cout << "Number of triangle words: " << numOfTriangleWords << "\n";
    }
    catch(const std::ios_base::failure & e){
        std::cout << e.what() << std::endl;
    }
    catch(...) {
        std::cout << "Unexpected error!" << std::endl;
    }
    return 0;
}

int WordValue(std::string const & word)
{
    int value = 0;
    for(auto const & c : word){
        if(c != '\"'){
            value += (static_cast<int>(c) - 64);
        }
    }
    return value;
}

int NthTriangleNum(int n)
{
    return (n * (n + 1) / 2);
}

void PopulateWithTriangleNums(std::vector<int> & v)
{
    int n = 1;
    for(auto & i : v){
        i = NthTriangleNum(n);
        ++n;
    }
}

bool IsWordTriangle(std::vector<int> & triangleNums, std::string const & word)
{
    auto value = WordValue(word);
    while(value > triangleNums.back()){
        triangleNums.push_back(NthTriangleNum(triangleNums.size()+1));
    }
    return (find(triangleNums.begin(), triangleNums.end(), value) != triangleNums.end());
}