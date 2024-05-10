#ifndef ROTMAT_H
#define ROTMAT_H
#include "matrix.h"
#include <cmath>

//Nedarvning fra Matrix klassen:
class RotMat2D : public Matrix{

//Oprettelse af privat variabel:
private:
    double _angle;

//Oprettelse af public memberfunktionerne (metoderne):
public:

    //Default constructer, der kalder super-klassens contructor og er initialiseret som en 2x2 identitetsmatrice med en vinkel på 0 radianer:
    RotMat2D() : Matrix(2, 2), _angle(0){
        Matrix::set(0,0,1);
        Matrix::set(1,1,1);
    };

    //Contructor, som initialiserer rotations matrix ud fra input vinklen/angle:
    RotMat2D(double angle) : Matrix(3,3), _angle(angle){
        Matrix::set(0,0, cos(angle));
        Matrix::set(0,1, -sin(angle));
        Matrix::set(0,2, 0);
        Matrix::set(1,0, sin(angle));
        Matrix::set(1,1, cos(angle));
        Matrix::set(1,2, 0);
        Matrix::set(2,0, 0);
        Matrix::set(2,1, 0);
        Matrix::set(2,2, 1);

    };

    //Print metode, der overskriver print() i super-klassen:
    virtual void print() override{

        double angledegree = _angle*(180/M_PI); //Fra vinkel i radianer til vinkel i grader.

        std::cout << "Rotation angle: " << angledegree << " degrees" << std::endl; //Printer vinklen som metoden repræsenterer.
        Matrix::print(); //Benytter super-klassens print() metode.

    }

    //Transpose metode, der overskriver transpose() i super-klassen:
    virtual void transpose() override{

        _angle*=-1; //Ændrer _angle til at have omvendt fortegn.

        Matrix::transpose(); //Benytter/kalder super-klassens transpose() metode.


    }





};

#endif // ROTMAT_H
