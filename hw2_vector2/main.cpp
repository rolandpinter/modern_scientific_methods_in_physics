#include "vector2.hpp"

int main()
{
    // Check 1: create vector2 with given values and output operator for vector2
    vector2<int> a = {10, 2};
    vector2<int> b = {3, 4};
    std::cout << "Initially a vector: " << a << std::endl;
    std::cout << "Initially b vector: " << b << std::endl;

    // Check 2: Addition in place
    a+=b;
    std::cout << "a+=b: " << a << std::endl;

    // Check 3: Substraction in place
    a-=b;
    std::cout << "a-=b: " << a << std::endl;

    // Check 4: Multiplication with scalar in place
    a*=2;
    std::cout << "a*=2: " << a << std::endl;

    // Check 5: Division with scalar in place
    a/=2;
    std::cout << "a/=2: " << a << std::endl;

    // Check 6: Addition of two vectors and returning with result
    auto sum = a + b;
    std::cout << "sum = a + b: " << sum << std::endl;

    // Check 7: Substraction of two vectors and returning with result
    auto diff = a - b;
    std::cout << "diff = a + b: " << diff << std::endl;

    // Check 8: Multiplication of a vector with a scalar value from right and returning with result
    auto multRight = a * 2;
    std::cout << "multRight = a * 2: " << multRight << std::endl;

    // Check 8: Multiplication of a vector with a scalar value from right and returning with result
    auto multLeft = 2 * a;
    std::cout << "multLeft = 2 * a: " << multLeft << std::endl;

    // Check 9: Division of a vector with a scalar value and returning with result
    auto div = a / 2;
    std::cout << "div = a / 2: " << div << std::endl;

    // Check 10: Length of a given vector
    double l = length(a);
    std::cout << "l = length(a): " << l << std::endl;

    // Check 11: Square of the length of a given vector
    double ll = sqlength(a);
    std::cout << "ll = sqlength(a): " << ll << std::endl;

    // Check 12: Dot product of two vectors and returning with result
    auto dotP = dot(a,b);
    std::cout << "dotP = dot(a,b): " << dotP << std::endl;

    // Check 13: Normalise a vector and returning with result
    auto norm = normalise(a);
    std::cout << "norm = normalise(a): " << norm << std::endl;

    // Check 14: Read vector components from standard input
    vector2<int> inputVec;
    std::cout << "Enter the two components of a two dimensional vector:" << std::endl;
    std::cin >> inputVec;
    std::cout << "inputVec: " << inputVec << std::endl;
    
    return 0;
}