#ifndef PICKNPLACE_H
#define PICKNPLACE_H
#include <iostream>
#include <vector>

std::vector<std::vector<int>> legoPosFunc() {

    std::vector<std::vector<int>> legoPos;

    for(int i=0; i<7; i++) {
        for(int j=0; j<17; j++) {
            legoPos.push_back(std::vector<int> {i+1,j+1});
        }
    }
    return legoPos;
}

#endif // PICKNPLACE_H
