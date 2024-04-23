#include "DBfetch.h"
#include "gui.h"
#include <iostream>
#include <modbus.h>
#include <vector>
#include <chrono>
#include <thread>
#include "PicknPlace.h"

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

    std::vector<std::vector<int>> wordCoords = returnWordVec();     // Saves coords of choosen word

    // Variables to store positions for PLACING LEGOs
    uint16_t x_pos_place;
    uint16_t y_pos_place;

    // Variables to store positions for PICKING LEGOs
    uint16_t x_pos_pick;
    uint16_t y_pos_pick;

    // Variables to store z-coordinates for pick and place
    uint16_t z_pos_down = 1;
    uint16_t z_pos_up = 10;

    // Variables to store rotations
    uint16_t x_rot = 314;
    uint16_t y_rot = 314;
    uint16_t z_rot = 314;

    std::vector<std::vector<int>> legoPos = legoPosFunc();


    uint16_t controlBit[1];
    mb.modbus_read_holding_registers(128, 1, controlBit);

    mb.modbus_write_register(128, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));      // Wait

    int i_pick = 0;
    int j_pick = 0;

    for (int i = 0; i < wordCoords.size(); i++) {                   // Iterates through vector of coords to print all x, and y for each letter in the chosen word
        std::cout << "Letter " << i+1 << ":" << std::endl;
        for (int j = 0; j < wordCoords[i].size(); j+=2) {
            bool run = true;    // Resets "run" bool

            /* PICKING MOTION */
            x_pos_pick = legoPos[i_pick][j_pick];
            y_pos_pick = legoPos[i_pick][j_pick+1];
            j_pick = 0;
            i_pick++;

            // PICK - Above LEGO piece WO. LEGO piece
            run = true;     // Resets "run" bool
            while(run) {    // While-loop runs until robot has finished current task

                /* Writing positions to robot registers */
                mb.modbus_read_holding_registers(128, 1, controlBit);
                while(controlBit[0] == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos ready for sending, controlBit = " << controlBit[0] << std::endl;

                    mb.modbus_write_register(130, x_pos_pick);
                    mb.modbus_write_register(131, y_pos_pick);
                    mb.modbus_write_register(132, z_pos_up);
                    mb.modbus_write_register(133, x_rot);
                    mb.modbus_write_register(134, y_rot);
                    mb.modbus_write_register(135, z_rot);
                    mb.modbus_write_register(128, 1);

                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;

                    run = false;    // Set "run" bool for next pos to be calculated
                }
            }

            // PICK - Grap LEGO piece
            run = true;     // Resets "run" bool
            while(run) {    // While-loop runs until robot has finished current task

                /* Writing positions to robot registers */
                mb.modbus_read_holding_registers(128, 1, controlBit);
                while(controlBit[0] == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos ready for sending, controlBit = " << controlBit[0] << std::endl;

                    mb.modbus_write_register(130, x_pos_pick);
                    mb.modbus_write_register(131, y_pos_pick);
                    mb.modbus_write_register(132, z_pos_down);
                    mb.modbus_write_register(133, x_rot);
                    mb.modbus_write_register(134, y_rot);
                    mb.modbus_write_register(135, z_rot);
                    mb.modbus_write_register(128, 1);

                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;

                    run = false;    // Set "run" bool for next pos to be calculated
                }
            }

            // PICK - Above W. LEGO piece
            run = true;     // Resets "run" bool
            while(run) {    // While-loop runs until robot has finished current task

                /* Writing positions to robot registers */
                mb.modbus_read_holding_registers(128, 1, controlBit);
                while(controlBit[0] == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos ready for sending, controlBit = " << controlBit[0] << std::endl;

                    mb.modbus_write_register(130, x_pos_pick);
                    mb.modbus_write_register(131, y_pos_pick);
                    mb.modbus_write_register(132, z_pos_up);
                    mb.modbus_write_register(133, x_rot);
                    mb.modbus_write_register(134, y_rot);
                    mb.modbus_write_register(135, z_rot);
                    mb.modbus_write_register(128, 1);

                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;

                    run = false;    // Set "run" bool for next pos to be calculated
                }
            }

            /* PLACING MOTION */
            // x-coord
            x_pos_place = wordCoords[i][j];
            std::cout << "x(" << x_pos_place << ")" << " ";

            // y-coord
            y_pos_place = wordCoords[i][j+1];
            std::cout << "y(" << y_pos_place << ")" << std::endl;

            // PLACE - Above workspace W. LEGO piece
            run = true;
            while(run) {        // While-loop runs until robot has finished current task

                /* Writing positions to robot registers */
                mb.modbus_read_holding_registers(128, 1, controlBit);
                while(controlBit[0] == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos ready for sending, controlBit = " << controlBit[0] << std::endl;

                    mb.modbus_write_register(130, x_pos_place);
                    mb.modbus_write_register(131, y_pos_place);
                    mb.modbus_write_register(132, z_pos_up);
                    mb.modbus_write_register(133, x_rot);
                    mb.modbus_write_register(134, y_rot);
                    mb.modbus_write_register(135, z_rot);
                    mb.modbus_write_register(128, 1);

                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;

                    run = false;    // Set "run" bool for next pos to be calculated
                }
            }

            // PLACE - Placing LEGO piece
            run = true;
            while(run) {        // While-loop runs until robot has finished current task

                /* Writing positions to robot registers */
                mb.modbus_read_holding_registers(128, 1, controlBit);
                while(controlBit[0] == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos ready for sending, controlBit = " << controlBit[0] << std::endl;

                    mb.modbus_write_register(130, x_pos_place);
                    mb.modbus_write_register(131, y_pos_place);
                    mb.modbus_write_register(132, z_pos_down);
                    mb.modbus_write_register(133, x_rot);
                    mb.modbus_write_register(134, y_rot);
                    mb.modbus_write_register(135, z_rot);
                    mb.modbus_write_register(128, 1);

                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;

                    run = false;    // Set "run" bool for next pos to be calculated
                }
            }

            // PLACE - Above workpiece WO. LEGO piece
            run = true;
            while(run) {        // While-loop runs until robot has finished current task

                /* Writing positions to robot registers */
                mb.modbus_read_holding_registers(128, 1, controlBit);
                while(controlBit[0] == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos ready for sending, controlBit = " << controlBit[0] << std::endl;

                    mb.modbus_write_register(130, x_pos_place);
                    mb.modbus_write_register(131, y_pos_place);
                    mb.modbus_write_register(132, z_pos_up);
                    mb.modbus_write_register(133, x_rot);
                    mb.modbus_write_register(134, y_rot);
                    mb.modbus_write_register(135, z_rot);
                    mb.modbus_write_register(128, 1);

                    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                    mb.modbus_read_holding_registers(128, 1, controlBit);
                    std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;

                    run = false;    // Set "run" bool for next pos to be calculated
                }
            }
        }

        std::cout << std::endl;
    }

    // close connection and free the memory
    mb.modbus_close();

    return 0;
}
