#include <iostream>
#include <modbus.h>
#include <vector>
#include <chrono>
#include <thread>

int main() {
    modbus mb = modbus("192.168.1.54", 502); mb.modbus_set_slave_id(1); mb.modbus_connect();

    uint16_t controlBit[1];
    mb.modbus_read_holding_registers(128, 1, controlBit);

    mb.modbus_write_register(128, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

    while(1) {
        mb.modbus_read_holding_registers(128, 1, controlBit);
        while(controlBit[0] == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

            mb.modbus_read_holding_registers(128, 1, controlBit);
            std::cout << "Pos ready for sending, controlBit = " << controlBit[0] << std::endl;

            mb.modbus_write_register(130, 900);
            mb.modbus_write_register(131, 6284);
            mb.modbus_write_register(132, 5827);
            mb.modbus_write_register(133, 2275);
            mb.modbus_write_register(134, 368);
            mb.modbus_write_register(135, 2117);
            mb.modbus_write_register(128, 1);

            std::this_thread::sleep_for(std::chrono::milliseconds(1));       // Wait

            mb.modbus_read_holding_registers(128, 1, controlBit);
            std::cout << "Pos sendt, controlBit = " << controlBit[0] << std::endl;
        }
    }




    /*
    uint16_t x = -1562;
    uint16_t y = -1292;
    uint16_t z = 5208;
    uint16_t rx = 210;
    uint16_t ry = -1653;
    uint16_t rz = 352;

    std::vector<uint16_t> pos = {x, y, z, rx, ry, rx};

    for(int i=0; i<6; i++) {
        if(pos[i]<0) {
            pos[i] = 65536pos[i];
        }
    }

    x = pos[0];
    y = pos[1];
    z = pos[2];
    rx = pos[3];
    ry = pos[4];
    rz = pos[5];

    mb.modbus_write_register(130, x);
    mb.modbus_write_register(131, y);
    mb.modbus_write_register(132, z);
    mb.modbus_write_register(133, rx);
    mb.modbus_write_register(134, ry);
    mb.modbus_write_register(135, rz);
*/
    //uint16_t read_holding_regs[1];

    //mb.modbus_read_holding_registers(1, 1, read_holding_regs);

    //std::cout << read_holding_regs[0] << std::endl;

    // close connection and free the memory
    mb.modbus_close();
    return 0;
}
