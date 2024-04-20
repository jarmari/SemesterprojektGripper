#include "DBfetch.h"
#include "gui.h"
#include <iostream>
#include <modbus.h>
#include <vector>
#include <chrono>
#include <thread>

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
    modbus mb = modbus("192.168.1.54", 502); mb.modbus_set_slave_id(1); mb.modbus_connect();    // Connects to robot via Modbus TCP/IP through IP-adress and Port

    // Variables to store robot positions
    uint16_t x_pos;
    uint16_t y_pos;
    uint16_t z_pos;
    uint16_t x_rot;
    uint16_t y_rot;
    uint16_t z_rot;


//    uint16_t controlBit[1];
//    mb.modbus_read_holding_registers(128, 1, controlBit);

//    mb.modbus_write_register(128, 0);
//    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

//    while(1) {
//        mb.modbus_read_holding_registers(128, 1, controlBit);
//        while(controlBit[0] == 0) {
//            std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

//            mb.modbus_read_holding_registers(128, 1, controlBit);
//            std::cout << "Pos ready for sending, controlBit = " << controlBit[0] << std::endl;

//            mb.modbus_write_register(130, x_pos);
//            mb.modbus_write_register(131, y_pos);
//            mb.modbus_write_register(132, z_pos);
//            mb.modbus_write_register(133, x_rot);
//            mb.modbus_write_register(134, y_rot);
//            mb.modbus_write_register(135, z_rot);
//            mb.modbus_write_register(128, 1);

//            std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

//            mb.modbus_read_holding_registers(128, 1, controlBit);
//            std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;
//        }
//    }

    // close connection and free the memory
    mb.modbus_close();

    return 0;
}
