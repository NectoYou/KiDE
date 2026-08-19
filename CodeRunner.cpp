#include "CodeRunner.hpp"
#include <fstream>
#include <cstdlib>

void CodeRunner::run(nana::textbox& box) {
    std::string code = box.text();

    if (code.find("#include") != std::string::npos || code.find("int main") != std::string::npos) {
        std::ofstream temp_file("temp.cpp");
        if (temp_file.is_open()) {
            temp_file << code;
            temp_file.close();
        }
        std::string command = "g++ temp.cpp -o temp.exe && start cmd /k \"temp.exe && pause && exit\"";
        std::system(command.c_str());
    } 
    else {
        std::ofstream temp_file("temp.py");
        if (temp_file.is_open()) {
            temp_file << code;
            temp_file.close();
        }
        std::string command = "start cmd /k \"python temp.py && pause && exit\"";
        std::system(command.c_str());
    }
}
