#include "viewtext.h"
#include <iostream>
#include <fstream>
#include <string>

viewText::viewText() {
}

viewText::~viewText() {
}

void viewText::printcontent() { 
    std::ifstream file("text.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } 
    else {
        std::cerr << "Unable to open file: text.txt" << std::endl;  
    }
}
