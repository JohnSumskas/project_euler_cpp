
#include <iostream>

int findDifferenceOfSumOfSquares(int number)
{
    int sumOfSquares = 0;

    int squareOfSum = 0;

    for (int i = 1; i<=number; i++)
    {
        sumOfSquares += i*i;

        squareOfSum += i;
    }

    squareOfSum = squareOfSum*squareOfSum;

    return squareOfSum - sumOfSquares;
}

int main()
{
    int number = 100;

    std::cout << "Difference of Sum of Square of " << number << " is " << findDifferenceOfSumOfSquares(number) << "." << std::endl;
    return 0;
}