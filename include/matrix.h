#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <iomanip>
#include <iostream>

namespace LinAlg {
    template<typename Type>
    class Matrix
    {
        public:
            Matrix ();
            Matrix (unsigned lin, unsigned col);
            Matrix (const LinAlg::Matrix<Type>& otherMatrix);
            virtual ~Matrix ();

            unsigned getNumberOfLines ();
            unsigned getNumberOfColumns ();

            Type operator() (unsigned line, unsigned column);
            void operator() (unsigned line, unsigned column, Type number);

            void operator= (std::string Mat);
            void operator= (LinAlg::Matrix<Type>& Mat);

            LinAlg::Matrix<Type> operator+= (LinAlg::Matrix<Type>& Mat);
        private:
            void Init (std::string Mat);
            void Init (unsigned lin, unsigned col);

            void Add (unsigned lin, unsigned col);

            unsigned lines, columns;
            Type** mat;
    };

    template<typename Type>
    void Zeros (Matrix<Type>& Mat);

    template<typename Type>
    LinAlg::Matrix<Type> Zeros (unsigned lines, unsigned columns);

    template<typename Type>
    LinAlg::Matrix<Type> Eye (unsigned dimension);

    template<typename Type>
    LinAlg::Matrix<Type> operator+ (LinAlg::Matrix<Type> Mat1, LinAlg::Matrix<Type> Mat2);

    template<typename Type>
    void Print (Matrix<Type>& Mat);
};

#endif // MATRIX_H
