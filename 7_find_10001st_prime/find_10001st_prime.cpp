
#include <iostream>

bool isPrime(int number)
{
    for (int i = 2; i<number; i++)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}

int findPrime(int number)
{
    int primesFound = 0;

    int currentNumber = 2;

    while (primesFound < number)
    {
        if (isPrime(currentNumber))
        {
            // std::cout << currentNumber << std::endl;
            primesFound++;
        }
        currentNumber++;
    }
    return --currentNumber;
}

int main()
{
    int number = 10001;

    std::cout << "10001st Prime is" << findPrime(number) << "." << std::endl;
    return 0;
}