// Problem 108 - Diophantine reciprocals I
// In the following equation x, y, and n are positive integers.
// 1/x + 1/y = 1/n
// For n = 4 there are exactly three distinct solutions:
// 1/5 + 1/20 = 1/4
// 1/6 + 1/12  =1/4
// 1/8 + 1/8 = 1/4
// What is the least value of n for which the number of distinct solutions exceeds one-thousand?

#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

std::vector<int>& ExpandPrimesUntilN(std::vector<int>& primes, int N);
unsigned int NumOfDivsWithPrimeFacts(unsigned long long int n);
unsigned long long int SearchForN_1(unsigned int NumOfSolutions, unsigned int startSearchFrom);
unsigned long long int SearchForN_2(unsigned int NumOfSolutions,unsigned int searchStartsFrom);

int main()
{
    unsigned int searchStartsFrom = 100'000;
    unsigned int numOfSolutions = 1000;

    std::cout << "Solution #1 result = ";
    auto start = std::chrono::high_resolution_clock::now();
    auto n = SearchForN_1(numOfSolutions, searchStartsFrom);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << n << "\n";
    std::chrono::duration<float> duration = end - start;
    std::cout << "Solution #1 runtime: " << std::fixed << duration.count() << " s\n\n";

    std::cout << "Solution #2 result = ";
    start = std::chrono::high_resolution_clock::now();
    n = SearchForN_2(numOfSolutions, searchStartsFrom);
    end = std::chrono::high_resolution_clock::now();
    std::cout << n << "\n";
    duration = end - start;
    std::cout << "Solution #2 runtime: " << std::fixed << duration.count() << " s\n";

    return 0;
}

std::vector<int>& ExpandPrimesUntilN(std::vector<int>& primes, int N)
{
    bool isprime = true;
    for(auto i = primes.back()+1; i < N; ++i){
        for(auto j = 2; j < sqrt(i)+1; ++j){
            if((i % j) == 0){
                isprime = false;
                break;
            }
        }
        if(isprime == true){
            primes.push_back(i);
        }
        isprime = true;
    }
    return primes;
}

unsigned int NumOfDivsWithPrimeFacts(unsigned long long int n)
{
    // since we are looking for the lowest number with the most divisors, the divisors will be multiplicates of the lower prime numbers so primes until 100 are sufficient in this case
    // ExpandPrimesUntilN() function could be used to extend the primes vector when needed but those cases will not give the final answer so we just ingnore them to increase execution time
    std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 , 73, 79, 83, 89, 97};
    std::vector<int> exponents(primes.size());
    auto ei = exponents.begin();
    for(auto pi = primes.begin(); pi != primes.end(); ++pi){
        while(n % *pi == 0){
                ++(*ei);
                n /= *pi;
        }
        ++ei;
    }
    int numOfDivisors = 1;
    for(auto ei = exponents.begin(); ei != exponents.end(); ++ei){
        numOfDivisors = numOfDivisors * (*ei + 1);
    }
    return numOfDivisors;
}

// #1 Solution
// the divisors of n^2 must exceed 2000
unsigned long long int SearchForN_1(unsigned int NumOfSolutions, unsigned int startSearchFrom)
{
    unsigned long long int n = startSearchFrom;
    unsigned long long int squareN = n * n;
    unsigned int numOfDivs = NumOfDivsWithPrimeFacts(squareN);
    NumOfSolutions = 2 * NumOfSolutions;
    while(numOfDivs <= NumOfSolutions){
        ++n;
        squareN = n * n;
        numOfDivs = NumOfDivsWithPrimeFacts(squareN);
    }
    return n;
}

// #2 Solution
// n < x < 2n, y = (x * n) / (x - n)
// correct soltuion if...
// (x * n) + (y * n) == (x * y)
unsigned long long int SearchForN_2(unsigned int NumOfSolutions,unsigned int searchStartsFrom)
{
    unsigned long long int n = searchStartsFrom;
    unsigned long long int x = 0, y = 0;
    unsigned int count = 0;
    while(count < NumOfSolutions){
        ++n;
        count = 0;
        for(x = (n + 1); x < (2 * n); ++x){
            y = (x * n) / (x - n);
            if((x * n) + (y * n) == (x * y)){
                ++count;
            }
        }
    }
    return n;
}