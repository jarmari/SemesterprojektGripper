#ifndef MOVE_ROBOT_H
#define MOVE_ROBOT_H

//define regs: 
#define REG_X 130
#define REG_Y 131
#define REG_Z 132
#define REG_ROT_X 133
#define REG_ROT_Y 134
#define REG_ROT_Z 135
#define REG_CONTROL 128
#define REG_FLANGE 129

//Includes: 
#include "DBfetch.h"
#include "gui.h"
#include <iostream>
#include <modbus.h>
#include <vector>
#include <chrono>
#include <thread>
#include "transformations.h"
#include "rotmat.h"
#include "matrix.h"


class Robot_control{
    private: 
        std::vector<std::vector<int>> wordCoords; 
        std::vector<std::vector<int>> legoPos;
        modbus _mb;
        uint16_t controlBit[1];
        uint16_t xcontrolBit[1];
        uint16_t ycontrolBit[1];
        uint16_t zcontrolBit[1];
        uint16_t x_pos_place, y_pos_place;
        uint16_t flangeBit[1];

        // Variables to store positions for PICKING LEGOs
        uint16_t x_pos_pick, y_pos_pick;
        std::vector <double> z_pos_down_LS = {-10.8, 82.8, 176.7, 85.0};
        std::vector <double> z_pos_down_WS = {-9.6, 84.3, 178.1, 84.7};
        std::vector <double> z_pos_up = {187.0, 279.3, 373.2, 271.7};
        double x_rot;
        double y_rot;
        double z_rot;

        std::vector <double> x_rot_vec = {1.16, 1.57, 0.05, 0.63};
        std::vector <double> y_rot_vec = {-2.92, -4.45, 0.02, -1.44};
        std::vector <double> z_rot_vec = {0.14, 0.18, -0.01, 0.11};

        std::vector<std::vector<double>> LS_TCP = {{311.8, -305.1, 2.74}, {400.0, -274.5, 2.70}, {313.9,-310.5, 2.77}, {229.7,-344.2, 2.75}};
        std::vector<std::vector<double>> WS_TCP = {{432.3, -466.1, 2.75}, {520.3, -433.0, 2.76}, {431.3,-462.9, 2.75}, {349.0, -505.2, 2.75}};
        double LS_Gap = 16.25; //mm
        double WS_Gap = 8; //mm

        // Variables to check for-loops in pickNplace
        int check = 1;
        float rest = 1.0;

        int i_pick = 0;
        int j_pick = 0;

        double x_Coord, y_Coord;
        double z_Coord_down, z_Coord_up;
        double rotAngle;
        bool run = true;

        int counter = 1;

    public: 
        Robot_control(modbus mb) : _mb(mb){
            wordCoords = returnWordVec();
            legoPos = legoPosFunc();
            open_modbus_com();
        }

        ~Robot_control(){
            _mb.modbus_close();
        }

        
        void open_modbus_com(){ //"192.168.1.54"
            _mb.modbus_set_slave_id(1);
            _mb.modbus_connect();    // Connects to robot via Modbus TCP/IP through IP-adress and Port
            //control_sleep();
        }

        void control_sleep (){
            _mb.modbus_read_holding_registers(REG_CONTROL, 1, controlBit);
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1));  
            
            _mb.modbus_write_register(REG_CONTROL, 0);
            std::this_thread::sleep_for(std::chrono::seconds(5));

            _mb.modbus_write_register(REG_CONTROL, 1);
            std::this_thread::sleep_for(std::chrono::seconds(1));      // Wait

            _mb.modbus_write_register(REG_CONTROL, 0);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::vector<std::vector<int>> legoPosFunc() {

                for(int i=0; i<7; i++) {
                    for(int j=0; j<17; j++) {
                        legoPos.push_back(std::vector<int> {j,i});
                    }
                }
            return legoPos;
        }

        void main_loop(){
            for (int i = 0; i < wordCoords.size(); i++) {     // Iterates through vector of coords to print all x, and y for each letter in the chosen word
                std::cout << "Letter " << i+1 << ":" << std::endl;

                float length1 = wordCoords[i].size()/8; // 8, because fetch 2 coordinates at a time
                int length2 = length1;

                    for (int j = 0; j < wordCoords[i].size(); j+=8) { // j+=4, because gets 4 Lego at a time

                        bool run = true;    // Resets "run" bool

                        if(check > length1){ // Checks if next for-loops shouldn't be 4 but less if there isn't 4 legos left in the letter.
                            rest = length1 - length2;
                        }
                        loop2_pickup(i, j);
                        loop3_drop(i, j);                        
                        check++;
                     }
            std::cout << std::endl;
            } 
        }

        void loop2_pickup(int i, int j){
            _mb.modbus_write_register(REG_FLANGE, 0);

            for(int k = 0; k < 4*rest; k++){ // rest = 1, but if only needs to fetch 2 legos it stops the loop after 2 because then rest = 0.5
                /* PICKING MOTION */

                x_pos_place = legoPos[i_pick][j_pick];
                y_pos_place = legoPos[i_pick][j_pick+1];
                j_pick = 0;
                i_pick++;
                x_Coord = LS_TCP[k][0];
                y_Coord = LS_TCP[k][1];
                z_Coord_down = z_pos_down_LS[k];
                z_Coord_up = z_pos_up[k];
                rotAngle = LS_TCP[k][2];
                x_rot = x_rot_vec[k];
                y_rot = y_rot_vec[k];
                z_rot = z_rot_vec[k];

                move(LS_Gap, z_Coord_up);
                move(LS_Gap, z_Coord_down);
                move(LS_Gap, z_Coord_up);
                _mb.modbus_write_register(REG_FLANGE, 1);
             }
        }

        void loop3_drop(int i, int j){
            int k = 0;
            _mb.modbus_write_register(REG_FLANGE, 0);

            for(int l = 0; l < 8*rest; l+=2){ // rest = 1, but if only needs to fetch 2 legos it stops the loop after 2 because then rest = 0.5
                /* PICKING MOTION */
                x_pos_place = wordCoords[i][j+l]; // Ikke rigtigt??
                std::cout << "x(" << x_pos_place << ")" << " ";

                // y-coord
                y_pos_place = wordCoords[i][j+l+1]; //Ikke rigtigt??
                std::cout << "y(" << y_pos_place << ")" << std::endl;

                x_Coord = WS_TCP[k][0];
                y_Coord = WS_TCP[k][1];
                z_Coord_down = z_pos_down_WS[k];
                z_Coord_up = z_pos_up[k];
                rotAngle = WS_TCP[k][2]; //eller bare 2 istedet for two?
                x_rot = x_rot_vec[k];
                y_rot = y_rot_vec[k];
                z_rot = z_rot_vec[k];

                move(WS_Gap, z_Coord_up);
                //open
                move(WS_Gap, z_Coord_down);
                //close
                move(WS_Gap, z_Coord_up);
                _mb.modbus_write_register(REG_FLANGE, 1);

                k++;
            } 
        }

        //EN MASSE WHILE 

        void move(double GAP, double z_Coord){ //WS_Gap or LS_gap --- z_Coord_up or z_Coord_down 
            run = true;
                while(run) {        // While-loop runs until robot has finished current task

                    Transformation TransPlace(x_pos_place, y_pos_place);
                    Matrix position = TransPlace.BaseToTarget(x_Coord, y_Coord, z_Coord_down, rotAngle, GAP);

                    /* Writing positions to robot registers */
                    _mb.modbus_read_holding_registers(REG_CONTROL, 1, controlBit);
                    std::this_thread::sleep_for(std::chrono::seconds(1));

                    while(controlBit[0] == 0) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                        _mb.modbus_read_holding_registers(REG_CONTROL, 1, controlBit);
                        std::cout << "Pos ready for sending, controlBit = " << controlBit[0] << std::endl;

                        _mb.modbus_write_register(REG_X, position(0,0)*10);
                        _mb.modbus_write_register(REG_Y, position(1,0)*10);
                        _mb.modbus_write_register(REG_Z, z_Coord*10); //Ændre z-pos til over
                        _mb.modbus_write_register(REG_ROT_X, x_rot*100);
                        _mb.modbus_write_register(REG_ROT_Y, y_rot*100);
                        _mb.modbus_write_register(REG_ROT_Z, z_rot*100);
                        _mb.modbus_write_register(REG_CONTROL, 1);

                        std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

                        _mb.modbus_read_holding_registers(REG_CONTROL, 1, controlBit);
                        std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;

                        debug(position, z_Coord);

                        run = false;    // Set "run" bool for next pos to be calculated
                    }
                }
        }

        void debug(Matrix testPos, double z_Coord_test){
            std::cout << "---------------------  "<< counter <<"  -----------------------------" << std::endl;
            testPos.print();
            _mb.modbus_read_holding_registers(130, 1, xcontrolBit);
            _mb.modbus_read_holding_registers(131, 1, ycontrolBit);
            _mb.modbus_read_holding_registers(132, 1, zcontrolBit);

            std::this_thread::sleep_for(std::chrono::seconds(1));       // Wait
            std::cout << "Xregister = " << xcontrolBit[0] << std::endl;
            std::cout << "Yregister = " << ycontrolBit[0] << std::endl;
            std::cout << "Zregister = " << zcontrolBit[0] << std::endl;

            std::cout << "x_pos: " <<  testPos(0,0)*10 << std::endl;
            std::cout << "y_pos: " <<  testPos(1,0)*10 << std::endl;
            std::cout << "z_pos: " <<  z_Coord_up*10 << std::endl;
            std::cout << "xrot: " << x_rot << std::endl;
            std::cout << "yrot: " << y_rot << std::endl;
            std::cout << "zrot: " << z_rot << std::endl;

            _mb.modbus_read_holding_registers(REG_CONTROL, 1, controlBit);
            std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;
            std::cout << "---------------------------------------------------------" << std::endl;
            counter++;

        }


};


#endif
