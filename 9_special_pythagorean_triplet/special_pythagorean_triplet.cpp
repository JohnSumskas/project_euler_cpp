
#include <iostream>
#include <string>
#include <vector>

int findSpecialPythagoreanTriplet(int number)
{
\
    for (int a = 1; a < 1000; a++)
    {
        for (int b = a+1; b < 1000 - a; b++)
        {
            int expectedC = 1000 - a - b;

            if (a * a + b * b == expectedC*expectedC)
            {
                std::cout << a << " " << b << " " << expectedC << std::endl;
                return a * b * expectedC;
            }
        }
    }
    return 0;
}

int main()
{
    int number=1000;

    std::cout << "Product of Special Pythagorean Triplet:   " << findSpecialPythagoreanTriplet(number) << std::endl;
    return 0;
}