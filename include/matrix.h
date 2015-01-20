#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <iomanip>
#include <cstdlib>
#include <iostream>

namespace LinAlg {
    template<typename Type>
    class Matrix
    {
        public:
            Matrix (std::string Mat);
            Matrix (unsigned row, unsigned column);
            Matrix (): rows(0), columns(0), mat(NULL){};
            Matrix (const LinAlg::Matrix<Type>& otherMatrix);
            virtual ~Matrix ();

            unsigned getNumberOfRows () const;
            unsigned getNumberOfColumns () const;

            Type& operator() (unsigned row, unsigned column);
            Type operator() (unsigned  row, unsigned column) const;
            void operator() (unsigned row, unsigned column, Type number);

            void operator= (std::string rhs);
            LinAlg::Matrix<Type>& operator= (const LinAlg::Matrix<Type>& otherMatrix);

            LinAlg::Matrix<Type> operator- () const;

            LinAlg::Matrix<Type>& operator+= (const Type& rhs /*scalar*/);

            LinAlg::Matrix<Type>& operator+= (const LinAlg::Matrix<Type>& rhs);

            LinAlg::Matrix<Type>& operator-= (const Type& rhs /*scalar*/);
            friend LinAlg::Matrix<Type> operator- (LinAlg::Matrix<Type> lhs, const Type& rhs) {return lhs -= rhs;}
            friend LinAlg::Matrix<Type> operator- (const Type& lhs, LinAlg::Matrix<Type> rhs) {return rhs -= lhs;}

            LinAlg::Matrix<Type>& operator-= (const LinAlg::Matrix<Type>& rhs);
            friend LinAlg::Matrix<Type> operator- (LinAlg::Matrix<Type> lhs, const LinAlg::Matrix<Type>& rhs) {return lhs -= rhs;};

            LinAlg::Matrix<Type>& operator*= (const Type& rhs /*scalar*/);
            friend LinAlg::Matrix<Type> operator* (LinAlg::Matrix<Type> lhs, const Type& rhs) {return lhs *= rhs;};
            friend LinAlg::Matrix<Type> operator* (const Type& lhs, LinAlg::Matrix<Type> rhs) {return rhs *= lhs;}

            LinAlg::Matrix<Type>& operator*= (const LinAlg::Matrix<Type>& rhs);
            friend LinAlg::Matrix<Type> operator* (LinAlg::Matrix<Type> lhs, const LinAlg::Matrix<Type>& rhs) {return lhs *= rhs;};

            LinAlg::Matrix<Type>& operator/= (const Type& rhs);
            friend LinAlg::Matrix<Type> operator/ (LinAlg::Matrix<Type> lhs, const Type& rhs) {return lhs /= rhs;};

            //LinAlg::Matrix<Type>& operator/= (const LinAlg::Matrix<Type>& rhs);
            //friend LinAlg::Matrix<Type> operator/ (const LinAlg::Matrix<Type> lhs, const LinAlg::Matrix<Type>& rhs) {return lhs /= rhs};

            void swap (const LinAlg::Matrix<Type>& otherMatrix);
            friend void swap (LinAlg::Matrix<Type>& lhs, LinAlg::Matrix<Type>& rhs) {lhs.swap(rhs);};

        private:
            void Init (std::string Mat);
            void Init (unsigned row, unsigned column);

            void ReInit (unsigned row, unsigned column);

            void Add (unsigned& row, unsigned& column, Type& number);

            bool CheckDimensions(const LinAlg::Matrix<Type>& rhs, unsigned operation);

            unsigned rows, columns;
            Type** mat;
    };

    template<typename MatrixType, typename ScalarType>
    LinAlg::Matrix<MatrixType> operator+ (LinAlg::Matrix<MatrixType> lhs, const ScalarType& rhs) {return lhs += rhs;}

    template<typename Type>
    LinAlg::Matrix<Type> operator+ (LinAlg::Matrix<Type> lhs, const LinAlg::Matrix<Type>& rhs) {return lhs += rhs;};

//    template<typename Type>
//    LinAlg::Matrix<Type> operator+ (const Type& lhs, LinAlg::Matrix<Type> rhs) {return rhs += lhs;}

    template<typename Type>
    void Zeros (LinAlg::Matrix<Type>& Mat);

    template<typename Type>
    LinAlg::Matrix<Type> Zeros (unsigned rows, unsigned columns);

    template<typename Type>
    LinAlg::Matrix<Type> Eye (unsigned dimension);

    template<typename Type>
    void Print (const LinAlg::Matrix<Type>& Mat);
};

#endif // MATRIX_H
