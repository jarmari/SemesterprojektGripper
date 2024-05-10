#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include <iostream>
#include <vector>
#include "matrix.h"
#include "rotmat.h"


class Transformation {
private:
    double _xPos;
    double _yPos;

public:

    Transformation(double xPos, double yPos) : _xPos(xPos), _yPos(yPos){}

    Matrix BaseToTarget(double xCoord, double yCoord, double zCoord, double rotAngle, double space) { //all grippers -> rotAngle is the angle between the x-axes (WS(vector) to base(vector))
        Matrix Transformation(4,4);
        Matrix translation(3,1);
        translation.set(0,0, xCoord); //divider m. 10 i URscript
        translation.set(1,0, yCoord);
        translation.set(2,0, zCoord);

        RotMat2D rotation(-rotAngle); //Negative because of rotation around z-axis

        Matrix shsc(1,4);
        shsc.set(0,3,1);

        for(int i = 0; i<3; i++){

            for(int j = 0; j<3; j++){
                Transformation.set(i,j, rotation.read(i,j));
            }

            Transformation.set(i,3, translation(i, 0));
        }
        for(int k = 0; k<4; k++){
            Transformation.set(3,k,shsc.read(0,k));
        }



        Matrix WS_P(4,1);
        WS_P.set(0,0, _xPos*space); //ganger med 8 mm, da 2x2 legoklods bredde er 16.00 mm
        WS_P.set(1,0, _yPos*space);
        WS_P.set(2,0, 0); //z er altid samme værdi??
        WS_P.set(3,0, 1);

        return Transformation*(WS_P);

    }

};

#endif // TRANSFORMATIONS_H
