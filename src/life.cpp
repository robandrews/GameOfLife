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

void buildGrid(Grid<char> &grid){

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

bool stayAlive(int xCoord, int yCoord, Grid<char> &grid){

}

void stepGrid(Grid<char> &grid){
    for(int i = 0; i< grid.numRows(); i++){
        for(int j = 0; j < grid.numCols(); j++){
            if(stayAlive(i, j, grid)){
                grid.set(i, j, '0');
            }
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

//    Build game
    Grid<char> lifeGrid;
    lifeGrid.resize(numRows, numCols);
    for(int i=0; i < numRows; i++){
        getline(inputFile, tempLine);
        for(int j = 0; j < numCols; j++){
            lifeGrid.set(i, j, tempLine.at(j));
        }
    }

    printGrid(lifeGrid);
    stepGrid(lifeGrid);
    pause(500);
    printGrid(lifeGrid);

    return 0;
}
