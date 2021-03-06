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

Grid<int> buildOffsetArray(){
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

    return offsets;
}

char life(int xCoord, int yCoord, Grid<char> &grid){
    //    Build offset array

    Grid<int> offsets = buildOffsetArray();

    int neighbors = 0;
    for(int i=0; i < offsets.numRows(); i++){
        int x = xCoord + offsets[i][0];
        int y = yCoord + offsets[i][1];
        if(grid.inBounds(x, y) && grid[x][y] == 'X'){
            neighbors++;
        }
    }
    //    cout << "Position: " << xCoord << "," << yCoord << " Neighbors: " << neighbors << endl;

    if(neighbors <= 1){return '-';}
    else if(neighbors == 2){return grid[xCoord][yCoord];}
    else if(neighbors == 3){return 'X';}
    else{return '-';};
}

void stepGrid(Grid<char> &grid){
    Grid<char> nextGrid(grid.numRows(), grid.numCols());

    for(int i = 0; i< grid.numRows(); i++){
        for(int j = 0; j < grid.numCols(); j++){
            nextGrid.set(i, j, life(i, j, grid));
        }
    }

    grid = nextGrid;
}

Grid<char> buildGrid(int numRows, int numCols, ifstream &inputFile){

    string tempLine;
    //    Build grid
    Grid<char> lifeGrid;
    lifeGrid.resize(numRows, numCols);
    for(int i=0; i < numRows; i++){
        getline(inputFile, tempLine);
        for(int j = 0; j < numCols; j++){
            lifeGrid.set(i, j, tempLine.at(j));
        }
    }

    return lifeGrid;
}

void promptUser(int &cycles, bool &reprompt){
    cout << "a)nimate, t)ick, q)uit? ";
    string response;
    cin >> response;
    if(response ==  "a"){
        cycles = 250;
    }else if(response == "t"){
        cycles++;
        reprompt = true;
    };
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


    Grid<char> lifeGrid = buildGrid(numRows, numCols, inputFile);

    int cycles = 0;
    bool reprompt = false;
    printGrid(lifeGrid);
    promptUser(cycles, reprompt);

    for(int i = 0; i<cycles; i++){
        clearConsole();
        stepGrid(lifeGrid);
        printGrid(lifeGrid);
        pause(20);
        if(reprompt){
            promptUser(cycles, reprompt);
        }
    }

    clearConsole();
    cout << "Thanks for playing the game of life.";
    return 0;
}
