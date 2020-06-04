// Problem 89 - Roman numerals
// For a number written in Roman numerals to be considered valid there are basic rules which must be followed. Even though the rules allow some numbers to be expressed in more than one way there is always a "best" way of writing a particular number.
// For example, it would appear that there are at least six ways of writing the number sixteen:
// IIIIIIIIIIIIIIII
// VIIIIIIIIIII
// VVIIIIII
// XIIIIII
// VVVI
// XVI
// However, according to the rules only XIIIIII and XVI are valid, and the last example is considered to be the most efficient, as it uses the least number of numerals.
// The 11K text file, roman.txt (right click and 'Save Link/Target As...'), contains one thousand numbers written in valid, but not necessarily minimal, Roman numerals; see About... Roman Numerals for the definitive rules for this problem.
// Find the number of characters saved by writing each of these in their minimal form.
// Note: You can assume that all the Roman numerals in the file contain no more than four consecutive identical units.

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

struct romanNumber
{
    std::string Ones{};
    std::string Tens{};
    std::string Hundreds{};
    std::string Thousands{};
    romanNumber() = default;
};

romanNumber ParseRomanNumber(std::string romanNumStr);
int CheckRomanNumber(std::string romanNumStr);

int main(){
    int numOfSavedChars = 0;
    const char * fileName = "p089_roman.txt";
    std::ifstream inFile;
    inFile.open(fileName);
    if(inFile.is_open()){
        std::string romanNumber;
        while(inFile.good()){
            while(std::getline(inFile, romanNumber)){
                // ParseRomanNumber(romanNumber);
                numOfSavedChars += CheckRomanNumber(romanNumber);
            }
        }
    }
    inFile.close();
    std::cout << "Number of saved characters: " << numOfSavedChars << "\n";
    return 0;
}

romanNumber ParseRomanNumber(std::string romanNumStr)
{
    romanNumber romNum;
    int romNumLength = romanNumStr.length();
    std::cout << romanNumStr  << " = ";
    std::smatch match;
    std::regex digitPattern ("(^M{1,4})");
    if(std::regex_search(romanNumStr, match, digitPattern)){
        romNum.Thousands = match.str();
        romanNumStr = match.suffix().str();
    }
    digitPattern.assign("((CM)|(D?C{0,4}D?))");
    if(std::regex_search(romanNumStr, match, digitPattern)){
        romNum.Hundreds = match.str();
        romanNumStr = match.suffix().str();
    }
    digitPattern.assign("((XC)|(L?X{0,4}L?))");
    if(std::regex_search(romanNumStr, match, digitPattern)){
        romNum.Tens = match.str();
        romanNumStr = match.suffix().str();
    }
    digitPattern.assign("((IX)|(V?I{0,4}V?))");
    if(std::regex_search(romanNumStr, match, digitPattern)){
        romNum.Ones = match.str();
    }
    int romanNumberLength = romNum.Thousands.length() + romNum.Hundreds.length() + romNum.Tens.length() + romNum.Ones.length();
    std::cout << romNum.Thousands << " | " << romNum.Hundreds << " | " << romNum.Tens << " | " << romNum.Ones << "\n";
    if(romNumLength != romanNumberLength){
        std::cout << "ERROR\n\n";
    }
    return romNum;
}

int CheckRomanNumber(std::string romanNumStr)
{
    int savedChars = 0;
    std::smatch match;
    // the thousands will always be correct because MMMM is correct for 4000
    std::regex correctPattern ("(^M{1,4})");
    if(std::regex_search(romanNumStr, match, correctPattern)){
        romanNumStr = match.suffix().str();
    }
    // each digit will be incorrect if it has four of the same charcters in a row
    // DCCCC >> CM, saves 3 characters
    // CCCC >> CD, saves 2 characters
    correctPattern.assign("((CM)|(D?C{0,3}D?))");
    std::regex incorrectPattern ("(D?C{4})");
    if(std::regex_search(romanNumStr, match, incorrectPattern)){
        if(romanNumStr.front() == 'D'){
            savedChars += 3;
        } else {
            savedChars += 2;
        }
        romanNumStr = match.suffix().str();
    } else {
        std::regex_search(romanNumStr, match, correctPattern);
        romanNumStr = match.suffix().str();
    }
    correctPattern.assign("((XC)|(L?X{0,3}L?))");
    incorrectPattern.assign("(L?X{4})");
    if(std::regex_search(romanNumStr, match, incorrectPattern)){
        if(romanNumStr.front() == 'L'){
            savedChars += 3;
        } else {
            savedChars += 2;
        }
        romanNumStr = match.suffix().str();
    } else {
        std::regex_search(romanNumStr, match, correctPattern);
        romanNumStr = match.suffix().str();
    }
    correctPattern.assign("((IX)|(V?I{0,3}V?))");
    incorrectPattern.assign("(V?I{4})");
    if(std::regex_search(romanNumStr, match, incorrectPattern)){
        if(romanNumStr.front() == 'V'){
            savedChars += 3;
        } else {
            savedChars += 2;
        }
        romanNumStr = match.suffix().str();
    } else {
        std::regex_search(romanNumStr, match, correctPattern);
        romanNumStr = match.suffix().str();
    }
    return savedChars;
}