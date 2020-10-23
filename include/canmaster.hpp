#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "menucell.hpp"

using MenuCells = std::vector<MenuCell>;

#define LOG(msg) errorLog(__FUNCTION__, msg)

inline void errorLog(const char* func, const std::string& msg){
    //printw("[%s] %s", func, msg.c_str());
    std::cerr << "[" << func << "] " << msg << std::endl;   
}