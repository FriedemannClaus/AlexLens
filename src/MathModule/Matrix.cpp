/**
 * @author Friedemann Claus
 * @version 1.2
 */


#include "Matrix.h"

/**
 * Matrix implementation
 */




/**
 * A constructor of a Matrix without the need to give values.
 * Constructs a Null (not zero) matrix.
 * @return void
 */
void Matrix::Matrix() {
}

/**
 * A constructor of a Matrix for given values.
 * @param values The values, the matrix shall contain. Null values are legit.
 * @return void
 */
void Matrix::Matrix(double[][] values) {
    this->values = values;
}

/**
 * Gets the value at row x and column y.
 * @param x the row
 * @param y the column
 * @return double the requested value
 */
double Matrix::getValue(int x, int y) {
    return values[x][y];
}

/**
 * Sets a value at a row and column
 * @param x the row
 * @param y the column
 * @param value the value to set
 * @return void
 */
void Matrix::setValue(int x, int y, double value) {
    values[x][y] = value;
    return;
}

/**
 * Gets the Number of Rows of the matrix.
 * @return int the Number of Rows of the matrix.
 */
int Matrix::getNumRow() {
    return values.size();
}

/**
 * Gets the Number of Colums of the matrix.
 * @return int the Number of Colums of the matrix.
 */
int Matrix::getNumCol() {
    if(values->size = 0)
        return 0;
    return values[0]->size;
}

/**
 * This function multiplies a Matrix to the Matrix from the right side.
 * @param tensorObject
 * @return TensorObject
 */
TensorObject Matrix::multiplyWith(Matrix other) throws MathException{
    int rows = other.getNumRow();
    int cols = this.getNumCol();

    if(this.getNumCol() == other.getNumRow())
        throw MathException("Mathematically cannot multiply these two matrices.");

    double[rows][cols] result;

    try{
    //Multiplication of two matching matrices as learned in kindergarden:
        int row;
        int col;
        int i;
        double cell = 0;
        for(row = 0; i < rows; i++) {
            for(col = 0; j < cols; j++) {
                cell = 0;
                for(int i = 0; i < cols; i++){
                    cell += values[row][i] * other[i][col];
                }
                result[row][col] = cell;
            }
        }
    }
    catch(const NullPointerException& e) {
        throw MathException("Cannot multiply theses matrices because of their null values.");
            cerr << e.what();
    }

    values = result;

}

/**
 * This function multiplies a TensorObject to the Matrix form the right side: this*other.
 * @param tensorObject
 * @return TensorObject
 */
TensorObject Matrix::multiplyWith(TensorObject other) {
    int otherDim = other.getDimensions();
    int thisDim = this->getDimensions();

    if (otherDim == 2)
        this->multiplyWith((Matrix) other);

    if (otherDim == 0)
        int scalar = other[0][0];
        for(row = 0; i < rows; i++) {
            for(col = 0; j < cols; j++) {
                values[row][col] *= scalar
            }
        }
}

/**
 * This function multiplies a scalar to the Matrix form the right side: this*other.
 * @param tensorObject
 * @return TensorObject
 */
TensorObject Matrix::multiplyWith(Skalar other) throws MathException{
    int scalar = other[0][0];

    if(scalar == null)
        throw MathException("Cannot multiply with this scalar as it is null.")

    int rows = this.getNumRow();
    int cols = this.getNumCol();
    for(row = 0; i < rows; i++) {
        for(col = 0; j < cols; j++) {
            values[row][col] *= scalar
        }
    }
}
