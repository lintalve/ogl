#ifndef LINEAR_H
#define LINEAR_H
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <format>

#include <GL/gl.h>
#define ALGO 1
static const int size = 9;

class Vector3{
    static const int size = 3;
    double vector[size] {};
public:
    Vector3(float x, float y, float z) {
        std::cout << "initialising vector" << std::endl;
        vector[0] = static_cast<double>(x);
        vector[1] = static_cast<double>(y);
        vector[2] = static_cast<double>(z);
    }
    Vector3(double x, double y, double z) {
        std::cout << "initialising vector from doubles" << std::endl;
        vector[0] = x;
        vector[1] = y;
        vector[2] = z;
    }
    Vector3(const Vector3& v) {
        std::cout << "copying vector " << std::endl;
        vector[0] = v.vector[0];   //it is interresting that you can
        vector[1] = v.vector[1];   //access private variables of other object
        vector[2] = v.vector[2];   //from a member function
    }
    double getX() const { return vector[0]; }
    double getY() const { return vector[1]; }
    double getZ() const { return vector[2]; }
    double getGLx() const { return (GLfloat)vector[0]; }
    double getGLy() const { return (GLfloat)vector[1]; }
    double getGLz() const { return (GLfloat)vector[2]; }
    void setX(double x) { vector[0] =x; }
    void setY(double y) { vector[1] =y; }
    void setZ(double z) { vector[2] =z; }
    //---Operator Overloading---//
    Vector3 operator+(const Vector3& rv) {
        std::cout << "left vector + " << std::endl;
        vector[0] += rv.vector[0];
        vector[1] += rv.vector[1];
        vector[2] += rv.vector[2];
        return *this;
    }
    Vector3 operator-(const Vector3& rv) {
        vector[0] += -(rv.vector[0]);
        vector[1] += -(rv.vector[1]);
        vector[2] += -(rv.vector[2]);
        return *this;
    }
    Vector3 operator*(const int& rvint) {
        vector[0] *= rvint;
        vector[1] *= rvint;
        vector[2] *= rvint;
        return *this;
    }
    Vector3 operator*(const float& rvfloat) {
        vector[0] *= rvfloat;
        vector[1] *= rvfloat;
        vector[2] *= rvfloat;
        return *this;
    }
    Vector3 operator*(const double& rvdouble) {
        vector[0] *= rvdouble;
        vector[1] *= rvdouble;
        vector[2] *= rvdouble;
        return *this;
    }
    Vector3 operator*=(const int& rvint) {
        vector[0] *= rvint;
        vector[1] *= rvint;
        vector[2] *= rvint;
        return *this;
    }
    double magnitude(){
        return sqrt(vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2]);
    }
    /*
    double magnitude(const Vector3& v){
        return sqrt(v.getX()*v.getX() + v.getY()*v.getY() + v.getZ()*v.getZ(), 2);
    }
     */
    double dot(const Vector3& v){
        return vector[0]*v.getX() + vector[1]*v.getY() + vector[2]*v.getZ();
    }
    Vector3 cross(const Vector3& v){
        return Vector3(vector[1]*v.getZ() - vector[2]*v.getY(),
                      vector[2]*v.getX() - vector[0]*v.getZ(),
                      vector[0]*v.getY() - vector[1]*v.getX());
    }
    /*
    bool operator<(const Vector3& v) const {
        return magnitude() < v.magnitude() ? true : false;
    }
     */
    //FRIEND fucking functions!!!! as in Python or in vex len()
    //it's a stand alone fucntion but it has access to the
    //internals of the objects of the certain class!!
    //I'm smart, I'm smart!
    friend double length(const Vector3& v);
    ~Vector3() {
        std::cout << "destructing vector" << std::endl;
    }
};

//------GLOBAL VECTOR FUNCTIONS-------//
double length(const Vector3& v){
    return static_cast<int>(sizeof(v.vector)/sizeof(*v.vector));
}


//-------MATRIX-------//
class Matrix3{
    static const int size = 9;
    double matrix[size];
public:
    Matrix3(){
        for(int i=0; i<size; i++){
            if(i%4){
                matrix[i] = 1.0;
            } else {
                matrix[i] = 0.0;
            }
        }
    }
    ~Matrix3(){
        std::cout << "destructing a matrix" << std::endl;
    }
    Matrix3(float a, float b, float c,
            float d, float e, float f,
            float g, float h, float i) {
        matrix[0] = a; matrix[1] = b; matrix[2] = c;
        matrix[3] = d; matrix[4] = e; matrix[5] = f;
        matrix[6] = g; matrix[7] = h; matrix[8] = i;
    }
    Matrix3(double a, double b, double c,
            double d, double e, double f,
            double g, double h, double i) {
        matrix[0] = a; matrix[1] = b; matrix[2] = c;
        matrix[3] = d; matrix[4] = e; matrix[5] = f;
        matrix[6] = g; matrix[7] = h; matrix[8] = i;
    }
    Matrix3(const Vector3& vec1, const Vector3& vec2, const Vector3& vec3){
        matrix[0] = vec1.getX(); matrix[1] = vec2.getX(); matrix[2] = vec3.getX();
        matrix[3] = vec1.getY(); matrix[4] = vec2.getY(); matrix[5] = vec3.getY();
        matrix[6] = vec1.getZ(); matrix[7] = vec2.getZ(); matrix[8] = vec3.getZ();
        
    }
    Matrix3(float* matrix_array) {
        for(int i=0; i<size; i++) {
            matrix[i] = matrix_array[i];
        }
    }
    Matrix3(double* matrix_array) {
        for(int i=0; i<size; i++) {
            matrix[i] = matrix_array[i];
        }
    }
    //Copy constructor
    Matrix3(const Matrix3& m){
        for(int i=0; i<sizeof(matrix)/sizeof(*matrix); i++) matrix[i] = m.matrix[i];
    }
    Matrix3 rref(){
        std::cout << "perfoming reduced roe echelon form algorithm" << std::endl;
        return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    void print(){
        std::string str = std::format("|{0} {1} {2}|\n|{3} {4} {5}|\n|{6} {7} {8}|\n",
                                matrix[0], matrix[1], matrix[2],
                                matrix[3], matrix[4], matrix[5],
                                matrix[6], matrix[7], matrix[8]);
        std::cout << str << std::endl;
    }
    //Since matrix scalar multiplication is not cummutative
    //we implement the following function as a friend function
    //so it can have 2 parameters in the oder from math formula
    friend const Matrix3 operator*(float f, const Matrix3& m);
    friend const Matrix3 operator*(double d, const Matrix3& m);
    friend const Vector3 operator*(const Vector3& v, const Matrix3& m);
    friend const Matrix3 operator*(const Matrix3& lm, const Matrix3& rm);
};

//------GLOBAL VECTOR FUNCTIONS-------//

const Matrix3 operator*(const float f, const Matrix3& m) {
    float local_matrix[size] {};
    for(int i=0; i<sizeof(m.matrix)/sizeof(*m.matrix); i++) {
        local_matrix[i] = m.matrix[i]*f;
    }
    return Matrix3(local_matrix);
}
const Matrix3 operator*(const double d, const Matrix3& m) {
    double local_matrix[size] {};
    for(int i=0; i<sizeof(m.matrix)/sizeof(*m.matrix); i++) {
        local_matrix[i] = m.matrix[i]*d;
    }
    return Matrix3(local_matrix);
}
const Vector3 operator*(const Vector3& v, const Matrix3& m) {
    //Since 3d vector has the same number of rows as the the 3x3 Matrix collumns
    //we can perform following operation
    double x = m.matrix[0]*v.getX() + m.matrix[1]*v.getY() + m.matrix[2]*v.getZ();
    double y = m.matrix[3]*v.getX() + m.matrix[4]*v.getY() + m.matrix[5]*v.getZ();
    double z = m.matrix[6]*v.getX() + m.matrix[7]*v.getY() + m.matrix[8]*v.getZ();
    return Vector3(x, y, z);
}
#if ALGO == 0
const Matrix3 operator*(const Matrix3& lm, const Matrix3& rm) {
    double a = lm.matrix[0]*rm.matrix[0] + lm.matrix[1]*rm.matrix[3] + lm.matrix[2]*rm.matrix[6];
    double b = lm.matrix[0]*rm.matrix[1] + lm.matrix[1]*rm.matrix[4] + lm.matrix[2]*rm.matrix[7];
    double c = lm.matrix[0]*rm.matrix[2] + lm.matrix[1]*rm.matrix[5] + lm.matrix[2]*rm.matrix[8];
    double d = lm.matrix[3]*rm.matrix[0] + lm.matrix[4]*rm.matrix[3] + lm.matrix[5]*rm.matrix[6];
    double e = lm.matrix[3]*rm.matrix[1] + lm.matrix[4]*rm.matrix[4] + lm.matrix[5]*rm.matrix[7];
    double f = lm.matrix[3]*rm.matrix[2] + lm.matrix[4]*rm.matrix[5] + lm.matrix[5]*rm.matrix[8];
    double g = lm.matrix[6]*rm.matrix[0] + lm.matrix[7]*rm.matrix[3] + lm.matrix[8]*rm.matrix[6];
    double h = lm.matrix[6]*rm.matrix[1] + lm.matrix[7]*rm.matrix[4] + lm.matrix[8]*rm.matrix[7];
    double i = lm.matrix[6]*rm.matrix[2] + lm.matrix[7]*rm.matrix[5] + lm.matrix[8]*rm.matrix[8];
    return Matrix3(a, b, c, d, e, f, g, h, i);
}
#elif ALGO == 1

const Matrix3 operator*(const Matrix3& lm, const Matrix3& rm) {
    double matrix[size] = {};
    for(int i=0; i<sizeof(lm.matrix)/sizeof(*lm.matrix); i++){
        for(int j=0; j<sqrt(sizeof(matrix)/sizeof(*matrix)); j++){
            matrix[i] += lm.matrix[i/3*3+j]*rm.matrix[j*3+i%3];
        }
    }
    return Matrix3(matrix);
}
#endif //ALGO

//print()
#endif// LINEAR_H
