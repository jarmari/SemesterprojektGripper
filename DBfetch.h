#ifndef DBFETCH_H
#define DBFETCH_H

#include <iostream>
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <string>
#include <vector>

void fetchCoordinates(QString letter, int offset){
    QSqlQuery query;

    query.prepare("SELECT letter, x, y, rotation FROM letter INNER JOIN coordinate ON letter.letter_id=coordinate.letter_id WHERE letter.letter=? ORDER BY coordinate_id");
    query.addBindValue(letter);
    query.exec();

    while (query.next()){

        int yoffset = 0;
        int x = query.value(1).toInt() + offset;
        int y = query.value(2).toInt() + yoffset; //for at få den på midten af pladen

        if(query.value(3) == 1){
        //LAV EN TRANSFORMATION
        //LAV EN TRANSFORMATION
        }

        std::vector<int> coordinate;

        coordinate.push_back(x);
        coordinate.push_back(y);

        qDebug() << query.value(0).toString() << coordinate[0] << coordinate[1] << query.value(3).toInt();
        }
}

int calculateOffset(QString letter){
    QSqlQuery query;

    query.prepare("SELECT width FROM letter WHERE letter.letter=?");
    query.addBindValue(letter);
    query.exec();

    int offset = 0;
    int extraSpace = 4;
    while (query.next()){
    offset = query.value(0).toInt() + extraSpace;
    }
    return offset;
}
void coordinatesOfWord(int word_id_number){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("letters");
    db.setUserName("sarah");  // Change to username
    db.setPassword("0111");  // Change to password
    db.open();


    if(word_id_number == 0){
        int offset = 0;
        fetchCoordinates("O", 0);
        offset = calculateOffset("O");
        fetchCoordinates("R", offset);
        offset += calculateOffset("R");
        fetchCoordinates("A",offset);
        offset += calculateOffset("A");
        fetchCoordinates("N", offset);
        offset += calculateOffset("N");
        fetchCoordinates("G", offset);
        offset += calculateOffset("G");
        fetchCoordinates("E", offset);

    }
    if(word_id_number == 1){
        int offset = 0;
        fetchCoordinates("G", 0);
        offset += calculateOffset("G");
        fetchCoordinates("R",offset);
        offset += calculateOffset("R");
        fetchCoordinates("A",offset);
        offset += calculateOffset("A");
        fetchCoordinates("P",offset);
        offset += calculateOffset("P");
        fetchCoordinates("E",offset);
    }
    if(word_id_number == 2){
        int offset = 0;
        fetchCoordinates("A", 0);
        offset += calculateOffset("A");
        fetchCoordinates("P", offset);
        offset += calculateOffset("P");
        fetchCoordinates("P", offset);
        offset += calculateOffset("P");
        fetchCoordinates("L", offset);
        offset += calculateOffset("L");
        fetchCoordinates("E", offset);
    }
    if(word_id_number == 3){
        int offset = 0;
        fetchCoordinates("H", 0);
        offset += calculateOffset("H");
        fetchCoordinates("A", offset);
        offset += calculateOffset("A");
        fetchCoordinates("T", offset);
    }
    if(word_id_number == 4){
        int offset = 0;
        fetchCoordinates("S", 0);
        offset += calculateOffset("S");
        fetchCoordinates("H", offset);
        offset += calculateOffset("H");
        fetchCoordinates("I", offset);
        offset += calculateOffset("I");
        fetchCoordinates("R", offset);
        offset += calculateOffset("R");
        fetchCoordinates("T", offset);
    }
    if(word_id_number == 5){
        int offset = 0;
        fetchCoordinates("P", 0);
        offset += calculateOffset("P");
        fetchCoordinates("A", offset);
        offset += calculateOffset("A");
        fetchCoordinates("N", offset);
        offset += calculateOffset("N");
        fetchCoordinates("T", offset);
        offset += calculateOffset("T");
        fetchCoordinates("S", offset);
    }
    if(word_id_number == 6){
        int offset = 0;
        fetchCoordinates("D", 0);
        offset += calculateOffset("D");
        fetchCoordinates("O", offset);
        offset += calculateOffset("O");
        fetchCoordinates("G", offset);
    }
    if(word_id_number == 7){
        int offset = 0;
        fetchCoordinates("C", 0);
        offset += calculateOffset("C");
        fetchCoordinates("O", offset);
        offset += calculateOffset("O");
        fetchCoordinates("W", offset);
    }
    if(word_id_number == 8){
        int offset = 0;
        fetchCoordinates("B", 0);
        offset += calculateOffset("B");
        fetchCoordinates("E", offset);
        offset += calculateOffset("E");
        fetchCoordinates("E", offset);
    }
}

#endif // DBFETCH_H
