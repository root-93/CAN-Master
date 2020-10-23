#pragma once
#include <vector>
#include <string>
#include <stdlib.h> //std::exit()

struct MenuContent{
    std::string mainMenuName {"Menu Główne"};

    MenuCells mainMenuList{
        MenuCell(1, "Can Utils", true),
        MenuCell(2, "Something else", true),
        MenuCell(3, "Nothing"),
        MenuCell(9, "Exit", false, [](){std::exit(EXIT_SUCCESS);})
    };
    
    std::vector<MenuCells*> pMenuList{
        &canUtils,
        &somethingElse,
            &thirdLevel
    };
    
    MenuCells canUtils {
        MenuCell(1, "Candump"),
        MenuCell(2, "Cangen"),
        MenuCell(3, "Canplayer"),
        MenuCell(4, "Cansend"),
        MenuCell(5, "Cansniffer", false),
        MenuCell(9, "Back")
    };

    MenuCells somethingElse {
        MenuCell(1, "cell 1"),
        MenuCell(2, "Third Level", true),
        MenuCell(3, "cell 3"),
        MenuCell(4, "cell 4"),
        MenuCell(5, "cell 5"),
        MenuCell(9, "Back")
    };
    
    MenuCells thirdLevel {
        MenuCell(1, "cell 1"),
        MenuCell(2, "cell 2"),
        MenuCell(9, "Back")
    };
};
