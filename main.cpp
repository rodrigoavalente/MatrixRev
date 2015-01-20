#include <iostream>
#include <typeinfo>
#include "include/matrix.h"

using namespace std;

template<typename t1, typename t2>
t2 add (t1 a, t2 b)
{
    return a + b;
}

int main()
{
//    LinAlg::Matrix<double> A, B, C;
//
//    A = "1,2,3;4,5,6";
//    B = "7,8,9;10,11,12";
//
//    C = LinAlg::Zeros<double>(2, 2);
//
//    A += 2;
//
//    C = A + B;
//
//    LinAlg::Print(C);
//
//    return 0;

    int a = 2;
    double b = 2;

    std::cout << typeid(add(a,b)).name() << std::endl;
}
