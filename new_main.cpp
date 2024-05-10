#include "DBfetch.h"
#include "gui.h"
#include <iostream>
#include <modbus.h>
#include "move_robot.h"

int main(int argc, char** argv){

    QCoreApplication a(argc, argv);

    loadStuff();
    resizeStuff();
    createButtons();
    insertButtons();
    loadSounds();

    category.play();

    imgtext = "Our GUI";
    cv::namedWindow(imgtext);
    cv::setMouseCallback(imgtext, callBackFunc);

    cv::imshow(imgtext, imggui_resized);

    cv::waitKey(0);

    /* MODBUS COMMUNICATION */
    modbus mb = modbus("192.168.1.54", 502);
    Robot_control UR(mb);

    UR.main_loop();

    return 0;

}
