// Problem 5 - Smallest multiple
// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

#include <vector>
#include <iostream>
#include <numeric>

long long int MultipOfPrimesUntil(int N);
bool TestDivisors(const std::vector<int> & divisors, long long int & Multiple);
long long int LeastCommonMultiple(int N);

int main()
{
    int N = 20;
    std::cout << "Least Common Multiple of numbers until " << N << ": " << LeastCommonMultiple(N) << "\n";
    return 0;
}

long long int MultipOfPrimesUntil(int N)
{
    long long int MultipOfPrimes = 1;
    for(int num = 2; num < (N + 1); ++num){
        bool isPrime = true;
        for(int divisor = 2; divisor < num; ++divisor){
            if(num % divisor == 0){
                isPrime = false;
                break;
            }
        }
        if(isPrime == true){
            MultipOfPrimes *= num;
        }
    }
    return MultipOfPrimes;
}

bool TestDivisors(const std::vector<int> & divisors, long long int & Multiple)
{
    for(auto & d : divisors){
        if(Multiple % d != 0){
            return false;
        }
    }
    return true;
}

long long int LeastCommonMultiple(int N)
{
    std::vector<int> numsToN(N);
    std::iota(numsToN.begin(), numsToN.end(), 1);
    // result can't be lower than the multiple of prime numbers until N
    long long int lcm = MultipOfPrimesUntil(N);
    int n = 2;
    while(true){
        lcm *= n;
        if(TestDivisors(numsToN, lcm)){
            break;
        } else {
            lcm /= n;
            ++n;
        }
    }
    return lcm;
}
