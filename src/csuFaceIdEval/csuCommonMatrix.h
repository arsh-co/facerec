/*
Copyright (c) 2003 Colorado State University

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

/*
Changes Under License Permision By Zeeshan Ejaz Bhatti
Center for Advanced Studies in Engineering, Islamabad, Pakistan.
Implementation of Laplacianfaces Algorithm for Face Recognition
November 2007...

Changes in this file:
Added a new function to subtract a scalar value from a matrix
*/

#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

#include <csuCommon.h>

typedef struct {
    int row_dim;  /* Number of rows    */
    int col_dim;  /* Number of columns */
    double *data;    /* Data stored in standard form: column major */
    double **cols;
}
matrix;

typedef matrix* Matrix;

Matrix makeMatrix(int row_dim, int col_dim);        /* creates and allocates memory for a matrix */
void freeMatrix(Matrix A);                        /* frees the area allocated to a matrix      */
Matrix valueMatrix(int row_dim, int col_dim, double value);
Matrix makeZeroMatrix(int row_dim, int col_dim);       /* creates, allocates, and initailizes memory for a matrix */
Matrix makeIdentityMatrix(int dim);           /* creates and allocates memory for an identity matrix */

/* ME (Matrix Element) is used to access a matrix element:
*     implements dope vector expansion
*     Remember that a matrix is stored by columns.
*
*  There are two versions of ME avaible and they are toggled with the
*  range check definition below (MATRIX_RANGE_CHECK).  When MATRIX_RANGE_CHECK
*  is enabled it will cause a function to be called that will check that the
*  element to be accessed is in the correct range (determined by ->row_dim
*  and ->col_dim) if it is not a nice error message will be printed indicating
*  file, function and line number where the error occurred and the program will
*  exit.  Range checking is great for debugging however it is also rather expensive
*  (function call and compares) especially within the nested loops of a matrix multiply.
*
*     Matrix A; index i,j
*/

/* #define MATRIX_RANGE_CHECK */
#ifdef MATRIX_RANGE_CHECK
#define  ME( mat , i , j )  ( ( rangeCheck(mat,i,j,__FILE__,__FUNCTION__,__LINE__,#mat))->cols[j][i] )
#else
#define  ME( mat , i , j )  ( (mat)->cols[j][i] )
#endif

Matrix rangeCheck(Matrix mat, int i, int j, const char* file_name, const char* func_name, int line_num, const char* mat_name);

/* creates a new matrix that is the product of A and B */
Matrix multiplyMatrix (const Matrix A, const Matrix B);
/* creates a new matrix that is the product of (A transpose) and B */
Matrix transposeMultiplyMatrixL (const Matrix A, const Matrix B);
/* creates a new matrix that is the product of A and (B transpose) */
Matrix transposeMultiplyMatrixR (const Matrix A, const Matrix B);

/*START: Changed by Zeeshan for LPP*/
/* A - n */
void subtractScalarFromMatrix (Matrix A, const int n);
/*END: Changed by Zeeshan for LPP*/

/* A - B */
Matrix subtractMatrix (const Matrix A, const Matrix B);
/* A + B */
Matrix addMatrix (const Matrix A, const Matrix B);
/* A += B */
void addMatrixEquals ( Matrix A, const Matrix B);

/* creates a new matrix that is the transpose of A     */
Matrix transposeMatrix(const Matrix A);

/* invert a matrix */
Matrix invertRREF(Matrix);

/* solve a least squares problem - This function returns the solution vector a */
Matrix leastSquares(Matrix A, Matrix b);
Matrix weightedLeastSquares(Matrix A, Matrix b, Matrix W);

/* creates a matrix of consisting of columns col1 to col2 of matrix mat */
Matrix matrixCols(const Matrix mat, int col1, int col2);

/* creates a matrix of consisting of rows row1 to row2 of matrix mat */
Matrix matrixRows( const Matrix mat, int row1, int row2);

/* alocates and fills a duplicate matrix */
Matrix duplicateMatrix(const Matrix mat);

typedef enum {
    octaveFormat = 0x00,
    matlabFormat = 0x01,
    appendToFile = 0x02,

    formatMask   = 0x01
} MatrixSaveMode;

extern MatrixSaveMode asciiFormat;  /* set to zero for octive format otherwize use matlab */
#define  SAVE_MATRIX( mat )  saveMatrixAscii(NULL, #mat, mat, asciiFormat) 
/* saves a matrix to an octive file */
void saveMatrixAscii(const char *fname, const char* label, const Matrix m, MatrixSaveMode format);

/* return a matrix of random elements (from 0.0 to 1.0) */
Matrix makeRandomMatrix (int row_dim, int col_dim);

/* return the sum of the squares of the matrix elements */
double matrixSumOfSquares (Matrix mat);

void printMatrix(const char* label, Matrix m);

/*START: Changed by Zeeshan: for LPP*/
void multiplyMatrixScalar(Matrix M, double scale);

Matrix orderColumns(Matrix M, int order[]);

Matrix orderRows(Matrix M, int order[]);

Matrix reshapeMatrix (Matrix M, int row, int col);

Matrix ACOSMatrix (Matrix M);

Matrix sqrtElem (Matrix M);

Matrix sqrtMatrix (Matrix M);

void each_mean_subtract_column (Matrix images, Matrix mean);

Matrix get_mean_each_column (Matrix images);

Matrix computeCovariance(Matrix A);

void initializeMatrix(Matrix X, int value);

Matrix calculateMean(Matrix ims);

Matrix calculateStandardDeviation(Matrix ims);

Matrix choleskyDecomposition (Matrix B);
/*used by cholesky decomposition, computes sum 
upto a specified row and specified column*/
double computeDigonalSum (Matrix LP, int i, int j);
/*END: Changed by Zeeshan: for LPP*/

#endif
