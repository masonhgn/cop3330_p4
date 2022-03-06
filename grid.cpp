#include "grid.h"
#include <cstdlib>
#include <ctime>
using namespace std;



Grid::Grid() {
    rows = 1;
    columns = 1;
    moverRow = 0;
    moverColumn = 0;
    direction = EAST;
    gridMap[0][0] = '>';
}



Grid::Grid(int r, int c) {
    if (r < 3) rows = 3;
    else if (r > 40) rows = 40;
    else rows = r;
    if (c < 3) columns = 3;
    else if (c > 40) columns = 40;
    else columns = c;

    moverRow = 0;
    moverColumn = 0;
    direction = EAST;
    for (int row=0; row < r; row++) {
        for (int column = 0; column < c; column++) {
            if (row == 0 || row == columns-1 || column == 0 || column == rows-1) {
                gridMap[row][column] = '#';
            } else gridMap[row][column] = '.';
        }
    }

    srand(time(0));
    int randomSpot = rand() % (rows) + 1; //generate random number from 1 to size
    if (randomSpot == rows-1) randomSpot--;
    else if (randomSpot == rows) randomSpot -= 2;
    int randomSide = rand() % 4; //generates random number between 0-3, used to pick a side
    if (randomSide == 0) {
        gridMap[0][randomSpot] = '.';
    } else if (randomSide == 1) {
        gridMap[rows-1][randomSpot] = '.';
    } else if (randomSide == 2) {
        gridMap[randomSpot][0] = '.';
    } else {
        gridMap[randomSpot][columns-1] = '.';
    }

    int randomMoverX = rand() % rows + 1;
    if (randomMoverX == rows-1) randomMoverX--;
    else if (randomMoverX == rows) randomMoverX -= 2;

    int randomMoverY = rand() % rows + 1;
    if (randomMoverY == rows-1) randomMoverY--;
    else if (randomMoverY == rows) randomMoverY -= 2;

    int randomMoverDirection = rand() % 4;
    if (randomMoverDirection == NORTH) gridMap[randomMoverX][randomMoverY] = '^';
    else if (randomMoverDirection == WEST) gridMap[randomMoverX][randomMoverY] = '<';
    else if (randomMoverDirection == SOUTH) gridMap[randomMoverX][randomMoverY] = 'v';
    else gridMap[randomMoverX][randomMoverY] = '>';

}




Grid::Grid(int r, int c, int mr, int mc, int d) {
    if (r < 1) rows = 1;
    else if (r > 40) rows = 40;
    else rows = r;

    if (c < 1) columns = 1;
    else if (c > 40) columns = 40;
    else columns = c;

    if (mr > r) moverRow = r;
    else if (mr < 0) moverRow = 0;
    else moverRow = mr;

    if (mc > c) moverColumn = c;
    else if (mc < 0) moverColumn = 0;
    else moverColumn = mc;

    direction = d;

    for (int row=0; row < r; row++) {
        for (int column = 0; column < c; column++) {
            if (row == 0 || row == columns-1 || column == 0 || column == rows-1) {
                gridMap[row][column] = '#';
            } else gridMap[row][column] = '.';
        }
    }
    if (direction == NORTH) gridMap[moverRow][moverColumn] = '^';
    else if (direction == WEST) gridMap[moverRow][moverColumn] = '<';
    else if (direction == SOUTH) gridMap[moverRow][moverColumn] = 'v';
    else gridMap[moverRow][moverColumn] = '>';
}

int Grid::GetNumRows() const {
    return rows;
}

int Grid::GetNumCols() const {
    return columns;
}

void Grid::Display() const {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            cout << (char) gridMap[row][column] << "  ";
        } cout << "\n";
    }
}



bool Grid::Move(int s) {
    if (direction == NORTH) {
        for (int i = moverRow; i >= moverRow-s; i--) {
            if (gridMap[i][moverColumn] == '#') { //if blocked then return false, exit loop
                return false;
            } else { //else then add to path storage for later
                pathStorage[i][0] = moverRow;
                pathStorage[i][1] = moverColumn;
            }
        } gridMap[moverRow-s][moverColumn] = '^', gridMap[moverRow][moverColumn] = '.';
        return true;
    }
    else if (direction == SOUTH) {
        for (int i = moverRow; i <= moverRow+s; i++) {
            if (gridMap[i][moverColumn] == '#') { //if blocked then return false, exit loop
                return false;
            } else { //else then add to path storage for later
                pathStorage[i][0] = moverRow;
                pathStorage[i][1] = moverColumn;
            }
        } gridMap[moverRow+s][moverColumn] = 'v', gridMap[moverRow][moverColumn] = '.';
    }
    else if (direction == EAST) {
        for (int i = moverColumn; i <= moverColumn+s; i++) {
            if (gridMap[moverRow][i] == '#') { //if blocked then return false, exit loop
                return false;
            } else { //else then add to path storage for later
                pathStorage[i][0] = moverRow;
                pathStorage[i][1] = moverColumn;
            }
        } gridMap[moverRow][moverColumn+s] = '>', gridMap[moverRow][moverColumn] = '.';
    }
    else if (direction == WEST) {
        for (int i = moverColumn; i >= moverColumn-s; i--) {
            if (gridMap[moverRow][i] == '#') { //if blocked then return false, exit loop
                return false;
            } else { //else then add to path storage for later
                pathStorage[i][0] = moverRow;
                pathStorage[i][1] = moverColumn;
            }
        } gridMap[moverRow][moverColumn-s] = '<', gridMap[moverRow][moverColumn] = '.';
    }




}
