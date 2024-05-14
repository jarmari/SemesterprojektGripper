#include <libserial/SerialPort.h>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace LibSerial;

class Serial{
    private:
        const char* device;
        SerialPort serialPort;
        std::vector <int> gripper_close_state = {0, 0, 0, 0};
        std::vector <int> gripper_rotate_state = {0, 0, 0, 0};

    public:
        Serial(const char* dev = "/dev/ttyUSB0") : device(dev) {}

        ~Serial() {
            disconnect();
        }

        void connect(){
            serialPort.Open(device);
            serialPort.SetBaudRate(BaudRate::BAUD_9600);
            serialPort.SetCharacterSize(CharacterSize::CHAR_SIZE_DEFAULT);
            serialPort.SetParity(Parity::PARITY_NONE);
            serialPort.SetStopBits(StopBits::STOP_BITS_1);
            serialPort.SetFlowControl(FlowControl::FLOW_CONTROL_HARDWARE);
        }

        //returns command when inputting grip. no., rot. state and close state
        uint8_t gripper_command(int gripper_number, bool rotate, bool close){
            uint8_t fail = 0x00;
            uint8_t command1[] = {0xD1, 0xB1, 0x91, 0xF1};
            uint8_t command2[] = {0xC1, 0xA1, 0x81, 0xE1};
            uint8_t command3[] = {0xD9, 0xB9, 0x99, 0xF9};
            uint8_t command4[] = {0xC9, 0xA9, 0x89, 0xE9};

            if(gripper_number < 1 || gripper_number > 4){
                return fail;
            }
            if(rotate && close){
                return command1[gripper_number-1];
            }
            if(!rotate && close){
                return command2[gripper_number-1];
            }
            if(rotate && !close){
                return command3[gripper_number-1];
            }
            if(!rotate && !close){
                return command4[gripper_number-1];
            }
            return fail;
        }

        //sends input command to the MCU e.g.: 0x91
        void execute_command(uint8_t command){

            bool writeSuccess = false;
            connect();
            //make 3 attempts to send command
            for (int attempts = 0; attempts < 3 && !writeSuccess; attempts++) {
                try {
                    if (!serialPort.IsOpen()) connect();
                    serialPort.WriteByte(command);
                    writeSuccess = true;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Failed to write byte: " << e.what() << ". Retrying..." << std::endl;
                    sleep(1); // Delay before retry
                    disconnect();
                }
            }
            if (!writeSuccess) {
                throw std::runtime_error("Failed to write after several attempts.");
            }
            disconnect();
        }

        void disconnect() {
            if (serialPort.IsOpen()) {
                serialPort.Close();
            }
        }

        //fetch the current state of gripper e.g.: "Gripper is: not rotated and open"
        std::string fetch_state(int gripper_number){
            std::string rotate, close;
            int rotate_state = gripper_rotate_state[gripper_number-1];
            int close_state = gripper_close_state[gripper_number-1];
            if(rotate_state == 1){
                rotate = "rotated";
            }
            if(rotate_state == 0){
                rotate = "not rotated";
            }
            if(close_state == 1){
                close = "closed";
            }
            if(close_state == 0){
                close = "open";
            }
            return "Gripper is: " + rotate + " and " + close;
        }

        //fetch the rotate state of gripper e.g. 1: rotated, 0: not rotated
        int fetch_rotate_state(int gripper_number){
            return gripper_rotate_state[gripper_number-1];
        }
        //fetch the close state of gripper e.g. 1: closed, 0: open
        int fetch_close_state(int gripper_number){
            return gripper_close_state[gripper_number-1];
        }

        //commands for move_robot.h -------------------------------------------------
        void gripper_open(int gripper_number){
            if(gripper_rotate_state[gripper_number-1]){
                execute_command(gripper_command(gripper_number, 1, 0));
            }
            if(!gripper_rotate_state[gripper_number-1]){
                execute_command(gripper_command(gripper_number, 0, 0));
            }
            gripper_close_state[gripper_number-1] = 0;
            //std::cout << "Gripper " + gripper_number + " has opened" << std::endl;
        }

        void gripper_close(int gripper_number){
            if(gripper_rotate_state[gripper_number-1]){
                execute_command(gripper_command(gripper_number, 1, 1));
            }
            if(!gripper_rotate_state[gripper_number-1]){
                execute_command(gripper_command(gripper_number, 0, 1));
            }
            gripper_close_state[gripper_number-1] = 1;
            //std::cout << "Gripper " + gripper_number + " has closed" << std::endl;
        }

        void gripper_rotate(int gripper_number){
            if(gripper_close_state[gripper_number-1]){
                execute_command(gripper_command(gripper_number, 1, 1));
            }
            if(!gripper_close_state[gripper_number-1]){
                execute_command(gripper_command(gripper_number, 1, 0));
            }
            gripper_rotate_state[gripper_number-1] = 1;
            //std::cout << "Gripper " + gripper_number + " has rotated" << std::endl;
        }

        void gripper_rotate_back(int gripper_number){
            if(gripper_close_state[gripper_number-1]){
                execute_command(gripper_command(gripper_number, 0, 1));
            }
            if(!gripper_close_state[gripper_number-1]){
                execute_command(gripper_command(gripper_number, 1, 0));
            }
            gripper_rotate_state[gripper_number-1] = 0;
            //std::cout << "Gripper " + gripper_number + " has rotated back" << std::endl;
        }

};


