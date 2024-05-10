#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>
#include <memory>

class Matrix{

//Oprettelse af de private variabler:
private:
    std::vector<double> _data;
    int _rows;
    int _cols;

//Oprettelse af public memberfunktionerne (metoderne):
public:

    //Contructor som initialiserer matricen med val i hvert index (default er 0) og initialisere feltvariablerne rows og cols:
    Matrix(int rows, int cols, double val = 0){
        _rows = rows;
        _cols = cols;

        for(int i=0; i<_rows; i++){
            for(int j=0; j<_cols; j++){

                _data.push_back(val); //Indsætter værdien af val i vektoren, der har størrelsen rows*cols.
                //Starter på først række i matricen (benytter 0-indeksering) og indsætter værdien val i hver søjle i den række. Derefter indsættes værdierne i næste rækkes søjler osv.
            }
        }
    }

    //Getter metoder:
    int getRows(){
        return _rows;
    }

    int getCols(){
        return _cols;
    }

    //Printer matricen i terminalen:
    virtual void print(){
        for(int i=0; i<_rows; i++){
            for(int j=0; j<_cols; j++){
                std::cout << _data[_cols*i+j] << " " ; //(_cols*i+j) er omregningen fra matrix til vector. Igen benyttes 0-indeksering.
            }
            std::cout << std::endl;
        }
    }

    //Returnerer værdien af et enkelt entry i matricen:
    double read(int r, int c){
        int idx = _cols*r+c;
        return _data[idx];
    }

    //Sætter index (r,c) til at have værdien val:
    void set(int r, int c, double val){
        int idx = _cols*r+c; //Bestemmer placeringen for den nye værdi val i vektoren.

        _data.insert(_data.begin()+idx, val); //Indsætter værdien val på positionen idx i vektoren.
    }

    //Returnerer en reference til et enkelt entry i matricen:
    double& at(int r, int c){
        int idx = _cols*r+c;
        return _data[idx];
    }

    //Returnerer matricen, som er resultatet af additionen mellem to matricer:
    Matrix add(Matrix& matrix){ 
        Matrix newMatrix(_rows, _cols); //Laver den nye matrice("resultat-matricen"), der har samme størrelse, som de to matricer, der adderes.
        Matrix errorMatrix(0,0); //Laver "fejl-matricen" uden rækker eller søjler til, hvis de to matricer, der skal adderes ikke har samme størrelse.

        //Tjekker om de to matricer, der skal adderes har samme størrelse:
        if((matrix.getCols()==_cols) & (matrix.getRows()==_rows)){
            for(int i=0; i<_rows; i++){
                for(int j=0; j<_cols; j++){
                   newMatrix.set(i, j, (matrix.read(i,j) + read(i,j)));
                } //Elementvis addition.
            }
            return newMatrix;
        }
        return errorMatrix;
    }

    //Returnerer matrix produktet mellem den matrice, som funktionen bliver kaldt på og input matricen.
    Matrix multiply(Matrix& matrix){

        double allmult = 0;
        Matrix newMatrix(_rows,matrix.getCols(), allmult); //"resultat-matricen" har samme antal rækker, som matricen funtionen kalder på og har samme antal søljer, som input matricen.
        Matrix errorMatrix(0,0);

        //Tjekker om matricen funktionen bliver kaldt på har samme antal søjler, som input matricen har antal rækker:
        if(_cols==matrix.getRows()){

            for(int i=0; i<_rows; i++){
                for(int j=0; j<matrix.getCols(); j++){

                    int idx = matrix.getCols()*i+j;


                    //Beregningen for multiplikationen:
                    for(int m=0; m<matrix.getRows(); m++){
                        double mult = read(i,m)*matrix.read(m,j);
                        allmult += mult;
                        newMatrix._data[idx]=allmult; //Sætter de enkelte elementer i "resultat-matricen" lig med den beregnede allmult værdi.

                    }
                    allmult=0; //Næste element starter med en værdi på nul igen, så der ikke køres videre fra sidste multiplikation.
                }
            }
            return newMatrix;
        }
        return errorMatrix;
    }

    //Transponerer matricen:
    virtual void transpose(){

        std::vector<double> trans;


        for(int j=0; j<_cols; j++){
             for(int i=0; i<_rows; i++){

                 trans.push_back(_data[_cols*i+j]); //Lægger hvert element fra _data vektoren ind i trans vektoren, hvor der her byttes om på rækker og søjler.
            }

        }

        int rows = _rows; //Gemmer antal af rækker for matrix i en variabel rows.
        int cols = _cols; //Gemmer antal af søjler for matrix i en variabel cols.

        //Antal rækker i matricen bliver til antal søjler og omvendt:
        _rows = cols;
        _cols = rows;

        _data = trans; //_data vektoren sættes lig med trans vektoren.
    }

    //Magen til add() metoden, men med benyttelse af smart pointers:
    std::shared_ptr<Matrix> add(std::shared_ptr<Matrix> matrix){

        std::shared_ptr<Matrix> newMatrix = std::make_shared<Matrix>(_rows, _cols);

        if((matrix->getCols()==_cols) & (matrix->getRows()==_rows)){
            for(int i=0; i<_rows; i++){
                for(int j=0; j<_cols; j++){
                   newMatrix->set(i, j, (matrix->at(i,j) + at(i,j)));
                }
            }
            return newMatrix;
        }
        return std::shared_ptr<Matrix>(nullptr);
    }

    //Magen til multiply() metoden, men med benyttelse af smart pointers:
    std::shared_ptr<Matrix> multiply(std::shared_ptr<Matrix> matrix){
        double allmult = 0;
        std::shared_ptr<Matrix> newMatrix = std::make_shared<Matrix>(_rows,matrix->getCols(), allmult);

        if(_cols==matrix->getRows()){

            for(int i=0; i<_rows; i++){
                for(int j=0; j<matrix->getCols(); j++){

                    int idx = matrix->getCols()*i+j;
                    newMatrix->_data[idx]=allmult;


                    for(int m=0; m<matrix->getRows(); m++){
                        double mult = read(i,m)*matrix->read(m,j);
                        allmult += mult;
                        newMatrix->_data[idx]=allmult;
                    }
                    allmult=0;
                }
            }
            return newMatrix;
        }
        return std::shared_ptr<Matrix>(nullptr);
    }

    //Overloader parentes operatoren, så den kalder at() metoden:
    double& operator()(int r, int c){
        return at(r,c);
    }

    //Overloader plus operatoren, så den kalder add() metoden:
    Matrix operator+(Matrix m){
        return add(m);
    }

    //Overloader gange operatoren, så den kalder multiply() metoden:
    Matrix operator* (Matrix m){
        return multiply(m);
    }
};

#endif // MATRIX_H
