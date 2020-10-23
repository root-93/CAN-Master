#pragma once
#include <string>

struct ViewActionData{
    ViewActionData(std::string cellName): cellName{cellName}{}
    ~ViewActionData(){};
    
    std::string cellName;
};