#include "matrix.h"
#include <assert.h>
#include <cmath>

// Constructor ----
Matrix::Matrix(int nr, int nc, float value)
{
    row = nr;
    col = nc;
    Mat = new float*[row];

    assert(Mat);

    for (int i = 0; i < row; ++i) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            Mat[i][j]= value;
        }
    }
}

Matrix::Matrix(float nr, float nc, float **m){
    row = nr;
    col = nc;
    Mat = new float*[row];

    assert(Mat);

    for (int i = 0; i < row; ++i) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            Mat[i][j]= m[i][j];
        }
    }
}

Matrix::Matrix(Matrix &m){
    this->row = m.rowCount();
    this->col = m.columnCount();
    this->Mat = new float *[row];

    assert(Mat);

    for ( int i = 0 ; i < row ; ++i ) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }
    for ( int i = 0 ; i < row ; ++i ) {
        for ( int j = 0 ; j < col ; ++j ) {
            Mat[i][j]= m.get(i,j);
        }
    }
}

Matrix::~Matrix(){
    for (int i = 0; i < row; ++i) {
        delete [] Mat[i];
    }

    delete[]Mat;
}

// Methods ----

void Matrix::initialize(int R, int C)
{
    row = R;
    col = C;
    Mat = new float*[row];

    for (int i = 0; i < row; ++i) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            Mat[i][j]= 0;
        }
    }
}

Matrix &Matrix::operator *(const Matrix &m)
{
    Matrix *result = new Matrix(row, col, 0);
    assert(result);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            for (int k = 0; k < col; ++k) {
                result->Mat[i][j] += Mat[i][k] * m.Mat[k][j];
            }
        }
    }
    return *result;
}

Matrix &Matrix::assign(Matrix m)
{
    for(int i=0; i < m.rowCount(); i++)
        for(int j=0; j < m.columnCount(); j++)
            Mat[i][j] = m.get(i,j);

    return *this;
}

Matrix &Matrix::identity()
{
    for(int i=0; i < row; i++)
        for(int j=0; j < col; j++)
            if(i == j)
                this->Mat[i][i] = 1;
            else
                Mat[i][j] = 0;

    return *this;
}

// --------

Matrix &Matrix::operator *=(Matrix &m)
{
    Matrix aux;
    aux.initialize(row,col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < m.columnCount(); j++) {
            float sum = 0;
            for (int k = 0; k < col; ++k) {
                sum += floor(Mat[i][k] * m.get(k, j) + 0.5);
                aux.set(i, j, sum);
            }
        }
    }

    assign(aux);

    return *this;
}

Matrix &Matrix::operator =(Matrix &m)
{
    for (int i = 0; i < row; ++i) {
        delete []Mat[i];
    }
    delete []Mat;

    this->row = m.rowCount();
    this->col = m.columnCount();
    this->Mat = new float *[row];

    assert(Mat);

    for (int i = 0; i < row; ++i) {
        Mat[i] = new float [col];
        assert(Mat[i]);
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            Mat[i][j]= m.get(i,j);
        }
    }
    return *this;
}

Matrix Matrix::operator*(float val){
    Matrix aux;
    aux.initialize(row, col);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            aux.set(i, j, Mat[i][j] * val);
        }
    }
    return aux;
}

// --------

Matrix &Matrix::translation(Matrix f, Matrix id, int tx, int ty)
{
    id.identity();

    id.set(2, 0, tx);
    id.set(2, 1, ty);

    f *= id;

    this->assign(f);

    return *this;
}

Matrix &Matrix::escalation(Matrix fig, Matrix id, float sY, float sX)
{
    id.identity();
    id.set(0, 0, sX);
    id.set(1, 1, sY);

    fig *= id;

    this->assign(fig);

    return *this;
}

Matrix &Matrix::fixedEscalation(Matrix fig, Matrix id, double sx, double sy, double pFx, double pFy)
{
    id.identity();

    double escPfx = pFx * (1 - sx);
    double escPfy = pFy * (1 - sy);

    id.set(0, 0, sx);
    id.set(1, 1, sy);
    id.set(2, 0, escPfx);
    id.set(2, 1, escPfy);

    fig *= id;

    this->assign(fig);

    return *this;
}

Matrix &Matrix::rotation(Matrix fig, Matrix id, double radians)
{
    id.identity();

    double degrees = radians * M_PI / 180.0;

    id.set(0, 0, cos(degrees));
    id.set(0, 1, sin(degrees));
    id.set(1, 0, -sin(degrees));
    id.set(1, 1, cos(degrees));

    fig *= id;
    this->assign(fig);

    return *this;
}

Matrix &Matrix::fixedRotation(Matrix fig, Matrix id, double radians, double pFx, double pFy)
{
    id.identity();
    double degrees = radians * M_PI / 180.0;

    double ren2_0 = pFx * (1 - cos(degrees)) + pFy * sin(degrees);
    double ren2_1 = pFy * (1 - cos(degrees)) - pFx * sin(degrees);

    id.set(0, 0, cos(degrees));
    id.set(0, 1, sin(degrees));
    id.set(1, 0, -sin(degrees));
    id.set(1, 1, cos(degrees));
    id.set(2, 0, ren2_0);
    id.set(2, 1, ren2_1);

    fig *= id;
    this->assign(fig);

    return *this;
}











