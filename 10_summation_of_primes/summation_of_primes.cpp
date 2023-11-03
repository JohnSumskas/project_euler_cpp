
#include <iostream>
#include <string>
#include <vector>

bool isPrime(int number)
{
    int upperLimit = number;
    for (int i = 2; i<upperLimit; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
        upperLimit = number/i + 1;
    }
    return true;
}


long findSummationOfPrimes(int number)
{

    long sum = 0;
    for (int i = 2; i < number; i++)
    {
        if (isPrime(i))
        {
            std::cout << i << std::endl;
            sum += i;
            std::cout <<sum << std::endl;
        }
    }
    return sum;
}

int main()
{
    int number=2000000;

    std::cout << "Sum of Primes: " << findSummationOfPrimes(number) << std::endl;
    return 0;
}