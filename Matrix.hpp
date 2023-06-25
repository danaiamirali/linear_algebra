#ifndef MATRIX_H
#define MATRIX_H

/* Matrix.h
 * Class containing definition of a matrix
 * Maximimum size of 20 rows and 20 columns
 * Matrices are dynamically allocated and have immutable dimensions
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Fraction.hpp"

using std::cout, std::endl;

const int MAX_DIM = 20;

class DIM_ERROR {
    public:
        DIM_ERROR() {
            cout << "Error: Invalid dimensions" << endl;
        }
};

class MULTIPLY_ERROR {
    public:
        MULTIPLY_ERROR() {
            cout << "Error: Cannot multiply matrices" << endl;
        }
};

class Matrix {
    /*
    INVARIANTS:
    m and n must be positive integers
    m and n must be less than MAX_DIM
    m and n cannot be changed after initialization
    */
    protected:
    friend class SquareMatrix;

    // Immutable dimensions
    const int m, n;
    int **const matrix; // Immutable pointer - root of matrix
    

    public:


        /*
         * ========================
         *       CONSTRUCTORS
         * ========================
        */

        // Default constructor
        // Creates 2x2 matrix
        Matrix() : m(2), n(2), matrix(new int*[m]) {}


        // Constructor with specified dimensions
        // Dynamically allocates memory for matrix
        // Throws DIM_ERROR if dimensions are invalid
        Matrix(int m_in, int n_in):
        m (m_in), n(n_in), matrix(new int*[m]) {

            if (m <= 0 || n <= 0 || m > MAX_DIM || n > MAX_DIM) {
                throw DIM_ERROR();
            }

            for (int i = 0; i < m; i++) {
                matrix[i] = new int[n];
            }

            cout << m << " x " << n << " matrix initialized." << endl;

        }

        
        // Copy constructor
        // Deep Copy
        Matrix(const Matrix& matrix) 
        : m(matrix.m), n(matrix.n), matrix(new int*[m]) {
            copyAll(matrix);
        }


        ~Matrix() {
            deleteMatrix();
        }


        /*
         * ========================
         *      PUBLIC METHODS
         * ========================
        */


        std::pair<int, int> getDimensions() const {
            return std::pair<int, int> (m, n);
        }


        // Fills matrix with random integers from 0 to 9
        Matrix *load() {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    matrix[i][j] = rand() % 10;
                }
            }

            cout << "Successfully loaded matrix with random integers." << endl;

            return this;
        }


        // Fills matrix with integers from string
        // Integers must be separated by spaces
        Matrix *load(std::string nums) {
            std::vector<int> numbers;
            std::stringstream ss(nums);
            std::string token;

            while (ss >> token) {
                try {
                    int num = std::stoi(token);
                    numbers.push_back(num);
                } catch (const std::exception& e) {

                }

            }

            int numbersCount = numbers.size();
            for (int i = 0; i < m * n && i < numbersCount; i++) {
                std::pair<int, int> ind = index(i);
                matrix[ind.first][ind.second] = numbers[i];
            }

            cout << "Successfully loaded matrix from string." << endl;
    
            return this;
        }


        /*
         * ========================
         *         OPERATORS
         * ========================
        */


        // Overloaded bracket operator
        // Returns pointer to row
        int* operator[](int i) const {
            return matrix[i];
        }
        

        // Overloaded extraction operator  
        friend std::ostream& operator<<(std::ostream &os, const Matrix& matrix) {
            for (int i = 0; i < matrix.m; i++) {
                os << "| ";
                for (int j = 0; j < matrix.n; j++) {
                    os << matrix[i][j] << " ";
                }
                os << "|" << endl;
            }

            return os;
        }


        /*
         * ========================
         *     MATRIX OPERATIONS
         * ========================
        */

        // Multiplies two matrices
        // Returns new matrix
        Matrix operator*(const Matrix &other) const;

        // Scalar multiplication
        Matrix operator*(int c) const;

        // Matrix reduced echelon form
        // Returns new matrix
        Matrix ref() const;
        void refHelper(int m, int n);
        

    private:
        /*
         * ========================
         *     PRIVATE HELPERS
         * ========================
        */ 

       bool isZeroCol(int col) const {
            for (int i = 0; i < m; i++) {
                if (matrix[i][col] != 0) {
                        return false;
                }
            }

            return true;
       }

        // Converts 1D Index to 2D Index
        std::pair<int, int> index(int i) const {
            return std::pair<int, int> (i / n, i % n);
        }


        int* getRow(int row) const {
            return matrix[row];
        }

        // Performs deep copy from argument matrix to this matrix
        Matrix *copyAll(const Matrix &matrix) {
            for (int i = 0; i < m; i++) {
                this->matrix[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    this->matrix[i][j] = matrix[i][j];
                }
            }

            return this;
        }        


        void deleteMatrix() {
                for (int i = 0; i < m; i++) {
                    delete[] matrix[i];
                }
                delete[] matrix;
        }


};



#endif // Matrix
