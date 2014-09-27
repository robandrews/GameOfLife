#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
using namespace std;

string collectFile(){
    cout << "Welcome to the CS 106B Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl;
    cout << "\n" << endl;

    string fileName;
    cout << "Grid input file name? ";
    cin >> fileName;
    return fileName;
}

void printGrid(Grid<char> &grid){
    clearConsole();
    for(int i = 0; i< grid.numRows(); i++){
        for(int j = 0; j < grid.numCols(); j++){
            cout << grid[i][j];
        }
        cout << endl;
    }
}

char life(int xCoord, int yCoord, Grid<char> &grid){
//    Build offset array
    Grid<int> offsets(8,2);
    int counter = 0;
    for(int i=-1; i < 2; i++){
        for(int j=-1; j < 2; j++){
            if(!(i==0 && j==0)){
                offsets.set(counter, 0, i);
                offsets.set(counter, 1, j);
                counter++;
            }
        }
    }

    int neighbors = 0;
    for(int i=0; i < offsets.numRows(); i++){
        int x = xCoord + offsets[i][0];
        int y = yCoord + offsets[i][1];
        if(grid.inBounds(x, y) && grid[x][y] == 'X'){
            neighbors++;
        }
    }

    if(neighbors < 1){return '-';}
    else if(neighbors == 3){return 'X';}
    else if(neighbors == 2 && grid[xCoord][yCoord] == 'X'){return 'X';}
    else{return '-';};
}

void stepGrid(Grid<char> &grid){
    for(int i = 0; i< grid.numRows(); i++){
        for(int j = 0; j < grid.numCols(); j++){
            grid.set(i, j, life(i, j, grid));
        }
    }
}

int main() {

    int numRows, numCols;
    string tempLine;
    ifstream inputFile;

//    Get board size
    openFile(inputFile, collectFile());
    getline(inputFile, tempLine);
    numRows = stringToInteger(tempLine);
    getline(inputFile, tempLine);
    numCols = stringToInteger(tempLine);

//    Build grid
    Grid<char> lifeGrid;
    lifeGrid.resize(numRows, numCols);
    for(int i=0; i < numRows; i++){
        getline(inputFile, tempLine);
        for(int j = 0; j < numCols; j++){
            lifeGrid.set(i, j, tempLine.at(j));
        }
    }

    printGrid(lifeGrid);

    for(int i = 0; i<500; i++){
        clearConsole();
        printGrid(lifeGrid);
        stepGrid(lifeGrid);
        pause(50);
    }

    return 0;
}
