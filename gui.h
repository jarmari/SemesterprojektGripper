#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <QSoundEffect>
#include <QCoreApplication>
#include "DBfetch.h"

cv::String imgtext;
cv::Rect button1;
cv::Rect button2;
cv::Rect button3;

//first window
cv::Mat imggui;
cv::Mat imgfruits;
cv::Mat imgclothing;
cv::Mat imganimals;

cv::Mat imggui_resized;
cv::Mat imgfruits_resized;
cv::Mat imgclothing_resized;
cv::Mat imganimals_resized;

//second window
cv::String textfruits = "fruits";
cv::Mat newfruits;
cv::Mat newf_r;

cv::String textclothing = "clothing";
cv::Mat newclothing;
cv::Mat newc_r;

cv::String textanimals = "animals";
cv::Mat newanimals;
cv::Mat newa_r;

//fruits
cv::Mat orange;
cv::Mat grapes;
cv::Mat apple;
cv::String orangetext = "Orange";
cv::String grapestext = "Grape";
cv::String appletext = "Apple";

cv::Mat orange_r;
cv::Mat grapes_r;
cv::Mat apple_r;

//clothing
cv::Mat hat;
cv::Mat shirt;
cv::Mat pants;
cv::String hattext = "Hat";
cv::String shirttext = "Shirt";
cv::String pantstext = "Pants";

cv::Mat hat_r;
cv::Mat shirt_r;
cv::Mat pants_r;

//animals
cv::Mat dog;
cv::Mat cow;
cv::Mat bee;
cv::String dogtext = "Dog";
cv::String cowtext = "Cow";
cv::String beetext = "Bee";

cv::Mat dog_r;
cv::Mat cow_r;
cv::Mat bee_r;

std::vector <cv::Rect> buttons;
int firstClickVar = 0;
int secondClickVar = 9;

int imggui_width = 1000;
int imggui_height = 600;

int button_width = 150;
int button_height = 150;

int button1_x = 200;
int button1_y = 400;
int button2_x = 400;
int button2_y = 400;
int button3_x = 600;
int button3_y = 400;

QSoundEffect category;
QSoundEffect fruits;
QSoundEffect clothing;
QSoundEffect animals;
QSoundEffect sorange;
QSoundEffect sgrapes;
QSoundEffect sapple;
QSoundEffect shat;
QSoundEffect sshirt;
QSoundEffect spants;
QSoundEffect sdog;
QSoundEffect scow;
QSoundEffect sbee;


void loadStuff(){
    //load images
    std::string filepathAppendix = "/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/img/";
    imggui = cv::imread(filepathAppendix+"kategori2.jpg", cv::IMREAD_COLOR);
    imgfruits = cv::imread(filepathAppendix+"green/fruits2.png", cv::IMREAD_COLOR);
    imgclothing = cv::imread(filepathAppendix+"green/clothing2.png", cv::IMREAD_COLOR);
    imganimals = cv::imread(filepathAppendix+"green/animals2.png", cv::IMREAD_COLOR);
    //load new background
    newfruits = cv::imread(filepathAppendix+"fruitshop1.jpg", cv::IMREAD_COLOR);
    newclothing = cv::imread(filepathAppendix+"clothingshop1.jpg", cv::IMREAD_COLOR);
    newanimals = cv::imread(filepathAppendix+"petshop1.jpg", cv::IMREAD_COLOR);
    //load fruits, clothing and animals
    orange = cv::imread(filepathAppendix+"green/orange2.png", cv::IMREAD_COLOR);
    grapes = cv::imread(filepathAppendix+"green/grapes2.png", cv::IMREAD_COLOR);
    apple = cv::imread(filepathAppendix+"green/apple2.png", cv::IMREAD_COLOR);
    hat = cv::imread(filepathAppendix+"green/hat2.png", cv::IMREAD_COLOR);
    shirt = cv::imread(filepathAppendix+"green/shirt2.png", cv::IMREAD_COLOR);
    pants = cv::imread(filepathAppendix+"green/pants2.png", cv::IMREAD_COLOR);
    dog = cv::imread(filepathAppendix+"green/dog2.png", cv::IMREAD_COLOR);
    cow = cv::imread(filepathAppendix+"green/cow2.png", cv::IMREAD_COLOR);
    bee = cv::imread(filepathAppendix+"green/bee2.png", cv::IMREAD_COLOR);


    //check for empty matrix
    if (imggui.empty()||imgfruits.empty()||imgclothing.empty()||imganimals.empty()){
        std::cout << "Could not open or find one of the images for the first window" << std::endl;
        std::cin.get(); //wait for any key press

     }
    if (newfruits.empty()||newclothing.empty()||newanimals.empty()){
        std::cout << "Could not open or find one of the second background images" << std::endl;
        std::cin.get(); //wait for any key press

     }
    if (orange.empty()||grapes.empty()||apple.empty()){
        std::cout << "Could not open or find the image of one of the fruits" << std::endl;
        std::cin.get(); //wait for any key press

     }
    if (hat.empty()||shirt.empty()||pants.empty()){
        std::cout << "Could not open or find the image one of the clothing items" << std::endl;
        std::cin.get(); //wait for any key press

     }
    if (dog.empty()||cow.empty()||bee.empty()){
        std::cout << "Could not open or find the image one of the animals" << std::endl;
        std::cin.get(); //wait for any key press

     }
}

void resizeStuff(){
    //resize background
    cv::resize(imggui,imggui_resized, cv::Size(imggui_width, imggui_height), cv::INTER_LINEAR);
    //resize buttons first window
    cv::resize(imgfruits, imgfruits_resized, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(imgclothing, imgclothing_resized, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(imganimals, imganimals_resized, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    //resize buttons second window
    cv::resize(orange, orange_r, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(grapes, grapes_r, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(apple, apple_r, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(hat, hat_r, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(shirt, shirt_r, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(pants, pants_r, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(dog, dog_r, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(cow, cow_r, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    cv::resize(bee, bee_r, cv::Size(button_width, button_height), cv::INTER_LINEAR);
    //resize new background
    cv::resize(newfruits,newf_r, cv::Size(imggui_width, imggui_height), cv::INTER_LINEAR);
    cv::resize(newclothing,newc_r, cv::Size(imggui_width, imggui_height), cv::INTER_LINEAR);
    cv::resize(newanimals,newa_r, cv::Size(imggui_width, imggui_height), cv::INTER_LINEAR);
}
void createButtons(){
    //clickable buttons first window
    button1 = cv::Rect(button1_x, button1_y, button_width, button_height);
    buttons.push_back(button1);

    button2 = cv::Rect(button2_x, button2_y, button_width, button_height);
    buttons.push_back(button2);

    button3 = cv::Rect(button3_x, button3_y, button_width, button_height);
    buttons.push_back(button3);
}

void insertButtons(){
    //drawing button first window
    cv::Mat insertFruits(imggui_resized, button1);
    imgfruits_resized.copyTo(insertFruits);

    cv::Mat insertClothing(imggui_resized, button2);
    imgclothing_resized.copyTo(insertClothing);

    cv::Mat insertAnimals(imggui_resized, button3);
    imganimals_resized.copyTo(insertAnimals);

    //drawing clickabe buttons fruits (reusing placement of buttons)
    cv::Mat insertOrange(newf_r, button1);
    orange_r.copyTo(insertOrange);

    cv::Mat insertGrapes(newf_r, button2);
    grapes_r.copyTo(insertGrapes);

    cv::Mat insertApple(newf_r, button3);
    apple_r.copyTo(insertApple);

    //drawing clickabe buttons clothing (reusing placement of buttons)
    cv::Mat insertHat(newc_r, button1);
    hat_r.copyTo(insertHat);

    cv::Mat insertShirt(newc_r, button2);
    shirt_r.copyTo(insertShirt);

    cv::Mat insertPants(newc_r, button3);
    pants_r.copyTo(insertPants);

    //drawing clickabe buttons fruits (reusing placement of buttons)
    cv::Mat insertDog(newa_r, button1);
    dog_r.copyTo(insertDog);

    cv::Mat insertCow(newa_r, button2);
    cow_r.copyTo(insertCow);

    cv::Mat insertBee(newa_r, button3);
    bee_r.copyTo(insertBee);
}

void newWindow(cv::String text, cv::String destroy, cv::Mat img){
    cv::destroyWindow(destroy);
    cv::namedWindow(text);
    imshow(text, img);
}

void loadSounds(){

    category.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/category.wav"));
    category.setLoopCount(1);
    category.setVolume(100);

    fruits.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/fruits.wav"));
    fruits.setLoopCount(1);
    fruits.setVolume(100);

    clothing.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/clothing.wav"));
    clothing.setLoopCount(1);
    clothing.setVolume(100);

    animals.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/animals.wav"));
    animals.setLoopCount(1);
    animals.setVolume(100);

    sorange.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/orange.wav"));
    sorange.setLoopCount(1);
    sorange.setVolume(100);

    sgrapes.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/grape.wav"));
    sgrapes.setLoopCount(1);
    sgrapes.setVolume(100);

    sapple.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/apple.wav"));
    sapple.setLoopCount(1);
    sapple.setVolume(100);

    shat.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/hat.wav"));
    shat.setLoopCount(1);
    shat.setVolume(100);

    sshirt.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/shirt.wav"));
    sshirt.setLoopCount(1);
    sshirt.setVolume(100);

    spants.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/pants.wav"));
    spants.setLoopCount(1);
    spants.setVolume(100);

    sdog.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/dog.wav"));
    sdog.setLoopCount(1);
    sdog.setVolume(100);

    scow.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/cow.wav"));
    scow.setLoopCount(1);
    scow.setVolume(100);

    sbee.setSource(QUrl::fromLocalFile("/home/lucas/workspace/2. Semester/Semesterprojekt_AutonomeRobotter/mainProgram/src/sounds/bee.wav"));
    sbee.setLoopCount(1);
    sbee.setVolume(100);
}

void callBackFunc2(int event, int x, int y, int flags, void* userdata){
    if (event == cv::EVENT_LBUTTONDOWN){

        for(int i=0; i<3; i++){
            if (buttons[i].contains(cv::Point(x, y))){
                if(buttons[i]==button1){
                    if(firstClickVar == 1){
                        cv::resize(orange, orange_r, cv::Size(500, 500), cv::INTER_LINEAR);
                        newWindow(orangetext, textfruits, orange_r);

                        sorange.play();

                        secondClickVar = 0;
                        coordinatesOfWord(secondClickVar);
                    }
                    if(firstClickVar == 2){
                        cv::resize(hat, hat_r, cv::Size(500, 500), cv::INTER_LINEAR);
                        newWindow(hattext, textclothing, hat_r);

                        shat.play();

                        secondClickVar = 3;
                        coordinatesOfWord(secondClickVar);
                    }
                    if(firstClickVar == 3){
                        cv::resize(dog, dog_r, cv::Size(500, 500), cv::INTER_LINEAR);
                        newWindow(dogtext, textanimals, dog_r);

                        sdog.play();

                        secondClickVar = 6;
                        coordinatesOfWord(secondClickVar);
                    }
                }
                if(buttons[i]==button2){
                    if(firstClickVar == 1){
                        cv::resize(grapes, grapes_r, cv::Size(500, 500), cv::INTER_LINEAR);
                        newWindow(grapestext, textfruits, grapes_r);

                        sgrapes.play();

                        secondClickVar = 1;
                        coordinatesOfWord(secondClickVar);
                    }
                    if(firstClickVar == 2){
                        cv::resize(shirt, shirt_r, cv::Size(500, 500), cv::INTER_LINEAR);
                        newWindow(shirttext, textclothing, shirt_r);

                        sshirt.play();

                        secondClickVar = 4;
                        coordinatesOfWord(secondClickVar);
                    }
                    if(firstClickVar == 3){
                        cv::resize(cow, cow_r, cv::Size(500, 500), cv::INTER_LINEAR);
                        newWindow(cowtext, textanimals, cow_r);

                        scow.play();

                        secondClickVar = 7;
                        coordinatesOfWord(secondClickVar);
                    }
                }
                if(buttons[i]==button3){
                    if(firstClickVar == 1){
                        cv::resize(apple, apple_r, cv::Size(500, 500), cv::INTER_LINEAR);
                        newWindow(appletext, textfruits, apple_r);

                        sapple.play();

                        secondClickVar = 2;
                        coordinatesOfWord(secondClickVar);
                    }
                    if(firstClickVar == 2){
                        cv::resize(pants, pants_r, cv::Size(500, 500), cv::INTER_LINEAR);
                        newWindow(pantstext, textclothing, pants_r);

                        spants.play();

                        secondClickVar = 5;
                        coordinatesOfWord(secondClickVar);
                    }
                    if(firstClickVar == 3){
                        cv::resize(bee, bee_r, cv::Size(500, 500), cv::INTER_LINEAR);
                        newWindow(beetext, textanimals, bee_r);

                        sbee.play();

                        secondClickVar = 8;
                        coordinatesOfWord(secondClickVar);
                    }
                }
            }
        }
    }
}

void callBackFunc(int event, int x, int y, int flags, void* userdata){
    if (event == cv::EVENT_LBUTTONDOWN){

        for(int i=0; i<3;i++){
            if (buttons[i].contains(cv::Point(x, y))){
                if(buttons[i]==button1){
                    newWindow(textfruits, imgtext, newf_r);

                    fruits.play();

                    cv::setMouseCallback(textfruits, callBackFunc2);

                    firstClickVar = 1;
                }
                if(buttons[i]==button2){
                    newWindow(textclothing, imgtext, newc_r);

                    clothing.play();

                    cv::setMouseCallback(textclothing, callBackFunc2);

                    firstClickVar = 2;
                }
                if(buttons[i]==button3){
                    newWindow(textanimals, imgtext, newa_r);

                    animals.play();

                    cv::setMouseCallback(textanimals, callBackFunc2);

                    firstClickVar = 3;
                }
            }
        }
    }
}

#endif // GUI_H
