#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

bool isPrime(int number)
{
    std::vector<int> primes = {2,3,5,7,11,13,17,19};

    if (std::find(primes.begin(), primes.end(), number) != primes.end())
    {
        return true;
    }
    return false;
}

void findPrimeFactors(int number, std::vector<int>& primeFactors)
{
    std::vector<int> primes = {2,3,5,7,11,13,17,19};

    if (isPrime(number))
    {
        primeFactors.push_back(number);
        return;
    }

    int remainingNumber = number;
    for (auto& prime : primes)
    {
        if (prime > remainingNumber)
        {
            return;
        }
        while (remainingNumber%prime == 0)
        {
            primeFactors.push_back(prime);
            remainingNumber = remainingNumber / prime;
        }
    }
}

void combinePrimeFactors(std::vector<int> primeFactors1, std::vector<int> primeFactors2, std::vector<int>& primeFactorsCombined)
{
    primeFactorsCombined.clear();

    for (auto& primeFactor : primeFactors1)
    {
        std::vector<int>::iterator foundPrimeFactor = std::find(primeFactors2.begin(), primeFactors2.end(), primeFactor);
        primeFactorsCombined.push_back(primeFactor);
        if (foundPrimeFactor != primeFactors2.end())
        {
            primeFactors2.erase(foundPrimeFactor);
        }
    }

    primeFactorsCombined.insert(primeFactorsCombined.end(), primeFactors2.begin(), primeFactors2.end());

    return;
}

int findLCM(int number)
{
    std::vector<int> primeFactors = {};

    std::vector<int> primeFactors18 = {};

    std::vector<int> totalPrimeFactors = {};

    for (int i = 2; i<=number; i++)
    {
        std::vector<int> primeFactors = {};

        findPrimeFactors(i, primeFactors);

        combinePrimeFactors(totalPrimeFactors, primeFactors, totalPrimeFactors);
    }

    int lcm = 1;

    for (auto& primeFactor : totalPrimeFactors)
    {
        lcm *= primeFactor;
    }
    return lcm;
}

int main()
{

    int number = 20;
    std::cout << "The LCM of " << number << " is " << findLCM(number) << "." << std::endl;
    return 0;
}