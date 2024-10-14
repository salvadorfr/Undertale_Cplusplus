#ifndef MATRIX_H
#define MATRIX_H

/*
 * This class works giving us a few methods of basic linear algebra
 * operations, which ones we will be using in the different methods
 * that will be modifying our sprites painted in the screen, such as:
 *      - Translation
 *      - Escalation
 *      - Rotation
*/

class Matrix
{
    int col, row;
    float **Mat;
public:
    // Default constructor
    Matrix(int nr = 4, int nc = 4, float value = 0);
    //Constructor
    Matrix(float nr, float nc, float **m);
    //Constructor copy
    Matrix (Matrix &);
    //Destructor
    ~Matrix();

    // Methods --------
    void set(int r, int c, float val){
        Mat[r][c]=val;
    }

    float get(int r, int c){
        return Mat[r][c];
    }

    int columnCount()   {return col;}
    int rowCount()      {return row;}
    void initialize(int, int);

    // Operators overloading
    Matrix &operator *(const Matrix  &);
    Matrix &operator *=(Matrix  &);
    Matrix &operator =(Matrix  &);
    Matrix operator *(float); // Multiply with an scalar
    Matrix &assign(Matrix);
    Matrix &identity(); // Permite inicializar la matriz base

    // Transfromations
    Matrix &translation(Matrix, Matrix, int, int);
    Matrix &escalation(Matrix, Matrix, float, float);
    Matrix &fixedEscalation(Matrix fig, Matrix id, double sx,double sy,double pFx,double pFy);
    Matrix &rotation(Matrix fig, Matrix id, double);
    Matrix &fixedRotation(Matrix fig, Matrix id, double, double pFx, double pFy);

};

#endif // MATRIX_H
