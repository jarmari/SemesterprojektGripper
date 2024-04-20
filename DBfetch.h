#ifndef DBFETCH_H
#define DBFETCH_H

#include <iostream>
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <string>
#include <vector>
#include <memory>

std::vector<std::vector<int>> wordVec;

std::vector<int> fetchCoordinates(QString letter, int offset){
    QSqlQuery query;

    query.prepare("SELECT letter, x, y, rotation FROM letter INNER JOIN coordinate ON letter.letter_id=coordinate.letter_id WHERE letter.letter=? ORDER BY coordinate_id");
    query.addBindValue(letter);
    query.exec();
    //letter

    std::vector<int> coordinate;

    int i = 0;
    int j = 1;
    while (query.next()){

        int x = query.value(1).toInt()+offset;
        int y = query.value(2).toInt();

        if(query.value(3) ==1){
        //LAV EN TRANSFORMATION
        //LAV EN TRANSFORMATION
        }

        coordinate.push_back(x);
        coordinate.push_back(y);

        qDebug() << query.value(0).toString() << coordinate[i] << coordinate[j] << query.value(3).toInt();
        i+=2;
        j+=2;
    }

    return coordinate;
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
    db.setUserName("lucas");    // Change to username
    db.setPassword("password"); // Change to password
    db.open();

    if(word_id_number == 0){
        int offset = 0;
        wordVec.push_back(fetchCoordinates("O", 0));
        offset = calculateOffset("O");
        wordVec.push_back(fetchCoordinates("R", offset));
        offset += calculateOffset("R");
        wordVec.push_back(fetchCoordinates("A",offset));
        offset += calculateOffset("A");
        wordVec.push_back(fetchCoordinates("N", offset));
        offset += calculateOffset("N");
        wordVec.push_back(fetchCoordinates("G", offset));
        offset += calculateOffset("G");
        wordVec.push_back(fetchCoordinates("E", offset));
    }
    if(word_id_number == 1){
        int offset = 0;
        wordVec.push_back(fetchCoordinates("G", 0));
        offset += calculateOffset("G");
        wordVec.push_back(fetchCoordinates("R",offset));
        offset += calculateOffset("R");
        wordVec.push_back(fetchCoordinates("A",offset));
        offset += calculateOffset("A");
        wordVec.push_back(fetchCoordinates("P",offset));
        offset += calculateOffset("P");
        wordVec.push_back(fetchCoordinates("E",offset));
    }
    if(word_id_number == 2){
        int offset = 0;
        wordVec.push_back(fetchCoordinates("A", 0));
        offset += calculateOffset("A");
        wordVec.push_back(fetchCoordinates("P", offset));
        offset += calculateOffset("P");
        wordVec.push_back(fetchCoordinates("P", offset));
        offset += calculateOffset("P");
        wordVec.push_back(fetchCoordinates("L", offset));
        offset += calculateOffset("L");
        wordVec.push_back(fetchCoordinates("E", offset));
    }
    if(word_id_number == 3){
        int offset = 0;
        wordVec.push_back(fetchCoordinates("H", 0));
        offset += calculateOffset("H");
        wordVec.push_back(fetchCoordinates("A", offset));
        offset += calculateOffset("A");
        wordVec.push_back(fetchCoordinates("T", offset));
    }
    if(word_id_number == 4){
        int offset = 0;
        wordVec.push_back(fetchCoordinates("S", 0));
        offset += calculateOffset("S");
        wordVec.push_back(fetchCoordinates("H", offset));
        offset += calculateOffset("H");
        wordVec.push_back(fetchCoordinates("I", offset));
        offset += calculateOffset("I");
        wordVec.push_back(fetchCoordinates("R", offset));
        offset += calculateOffset("R");
        wordVec.push_back(fetchCoordinates("T", offset));
    }
    if(word_id_number == 5){
        int offset = 0;
        wordVec.push_back(fetchCoordinates("P", 0));
        offset += calculateOffset("P");
        wordVec.push_back(fetchCoordinates("A", offset));
        offset += calculateOffset("A");
        wordVec.push_back(fetchCoordinates("N", offset));
        offset += calculateOffset("N");
        wordVec.push_back(fetchCoordinates("T", offset));
        offset += calculateOffset("T");
        wordVec.push_back(fetchCoordinates("S", offset));
    }
    if(word_id_number == 6){
        int offset = 0;
        wordVec.push_back(fetchCoordinates("D", 0));
        offset += calculateOffset("D");
        wordVec.push_back(fetchCoordinates("O", offset));
        offset += calculateOffset("O");
        wordVec.push_back(fetchCoordinates("G", offset));
    }
    if(word_id_number == 7){
        int offset = 0;
        wordVec.push_back(fetchCoordinates("C", 0));
        offset += calculateOffset("C");
        wordVec.push_back(fetchCoordinates("O", offset));
        offset += calculateOffset("O");
        wordVec.push_back(fetchCoordinates("W", offset));
    }
    if(word_id_number == 8){
        int offset = 0;
        wordVec.push_back(fetchCoordinates("B", 0));
        offset += calculateOffset("B");
        wordVec.push_back(fetchCoordinates("E", offset));
        offset += calculateOffset("E");
        wordVec.push_back(fetchCoordinates("E", offset));
    }
}

std::vector<std::vector<int>> returnWordVec() {
    return wordVec;
}

#endif // DBFETCH_H
