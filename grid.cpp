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
    currentSize = 1;
}



Grid::Grid(int r, int c) {

    if (r < 3) rows = 3;
    else if (r > 40) rows = 40;
    else rows = r;
    if (c < 3) columns = 3;
    else if (c > 40) columns = 40;
    else columns = c;
    currentSize = 1;

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

void Grid::addToPathStorage(int a, int b) {
    pathStorage[currentSize][0] = a;
    pathStorage[currentSize][1] = b;
    currentSize++;
}

bool Grid::Move(int s) {
    if (s<0) return false;
    if (direction == NORTH) { /////////////NORTH
        for (int i = moverRow; i >= moverRow-s; i--) {
            if (gridMap[i][moverColumn] == '#') { //if blocked then return false, exit loop
                return false;
            } else { //else then add to path storage for later
                addToPathStorage(moverRow, moverColumn);

            }
        }

        ///////////NORTH MOVEMENT
        if ((char)gridMap[moverRow-s][moverColumn] == '.') { //if it's empty...
            gridMap[moverRow-s][moverColumn] = '^'; //replace new spot with mover
        } else if ((char)gridMap[moverRow-s][moverColumn] == '0') { //if has item
            gridMap[moverRow-s][moverColumn] = '@'; //replace with @
        }
        if ((char)gridMap[moverRow][moverColumn] == '^') { //if mover not on item
            gridMap[moverRow][moverColumn] = '.'; //replace with empty
        } else if ((char) gridMap[moverRow][moverColumn] == '@') { //else
            gridMap[moverRow][moverColumn] = '0'; //replace with initial item
        }


        moverRow -= s;
        return true;
    }
    else if (direction == SOUTH) { /////////SOUTH
        for (int i = moverRow; i <= moverRow+s; i++) {
            if (gridMap[i][moverColumn] == '#') { //if blocked then return false, exit loop
                return false;
            } else { //else then add to path storage for later
                addToPathStorage(moverRow, moverColumn);
            }
        }
        ///////////SOUTH MOVEMENT
        if ((char)gridMap[moverRow+s][moverColumn] == '.') { //if it's empty...
            gridMap[moverRow+s][moverColumn] = 'v'; //replace new spot with mover
        } else if ((char)gridMap[moverRow+s][moverColumn] == '0') { //if has item
            gridMap[moverRow+s][moverColumn] = '@'; //replace with @
        }
        if ((char)gridMap[moverRow][moverColumn] == 'v') { //if mover not on item
            gridMap[moverRow][moverColumn] = '.'; //replace with empty
        } else if ((char) gridMap[moverRow][moverColumn] == '@') { //else
            gridMap[moverRow][moverColumn] = '0'; //replace with initial item
        }

        moverRow += s;
    }
    else if (direction == EAST) { //////////EAST
        for (int i = moverColumn; i <= moverColumn+s; i++) {
            if (gridMap[moverRow][i] == '#') { //if blocked then return false, exit loop
                return false;
            } else { //else then add to path storage for later
                addToPathStorage(moverRow, moverColumn);
            }
        }
        //////////EAST MOVEMENT
        if ((char)gridMap[moverRow][moverColumn+s] == '.') { //if it's empty...
            gridMap[moverRow][moverColumn+s] = '>'; //replace new spot with mover
        } else if ((char)gridMap[moverRow][moverColumn+s] == '0') { //if has item
            gridMap[moverRow][moverColumn+s] = '@'; //replace with @
        }
        if ((char)gridMap[moverRow][moverColumn] == '>') { //if mover not on item
            gridMap[moverRow][moverColumn] = '.'; //replace with empty
        } else if ((char) gridMap[moverRow][moverColumn] == '@') { //else
            gridMap[moverRow][moverColumn] = '0'; //replace with initial item
        }

        moverColumn += s;
    }
    else if (direction == WEST) { /////////WEST
        for (int i = moverColumn; i >= moverColumn-s; i--) {
            if (gridMap[moverRow][i] == '#') { //if blocked then return false, exit loop
                return false;
            } else { //else then add to path storage for later
                addToPathStorage(moverRow, moverColumn);
            }
        }
        /////////WEST MOVEMENT
        if ((char)gridMap[moverRow][moverColumn-s] == '.') { //if it's empty...
            gridMap[moverRow][moverColumn-s] = '<'; //replace new spot with mover
        } else if ((char)gridMap[moverRow][moverColumn-s] == '0') { //if has item
            gridMap[moverRow][moverColumn-s] = '@'; //replace with @
        }
        if ((char)gridMap[moverRow][moverColumn] == '<') { //if mover not on item
            gridMap[moverRow][moverColumn] = '.'; //replace with empty
        } else if ((char) gridMap[moverRow][moverColumn] == '@') { //else
            gridMap[moverRow][moverColumn] = '0'; //replace with initial item
        }

        moverColumn -= s;
    }
}

void Grid::TurnLeft() {
    if (direction == EAST) {
        direction = NORTH;
        gridMap[moverRow][moverColumn] = '^';
    } else if (direction == NORTH) {
        direction = WEST;
        gridMap[moverRow][moverColumn] = '<';
    } else if (direction == WEST) {
        direction = SOUTH;
        gridMap[moverRow][moverColumn] = 'v';
    } else if (direction == SOUTH) {
        direction = EAST;
        gridMap[moverRow][moverColumn] = '>';
    }
}

void Grid::TogglePath() {
    if (path) {
        for (int i = 0; i < currentSize; i++) {
            //gridMap[pathStorage[i][0]][pathStorage[i][1]] = ' ';
        }
    }
    else {
        for (int i = 0; i < currentSize; i++) {
            //gridMap[pathStorage[i][0]][pathStorage[i][1]] = '.';
            cout << "pathstorage 0: " << pathStorage[i][0] << " pathstorage 1: " << pathStorage[i][1] << endl;
        }
    }
}

bool Grid::FrontIsClear() const {
    if (direction == NORTH) {
        if ((char)(gridMap[moverRow - 1][moverColumn]) == '.' || (char)(gridMap[moverRow - 1][moverColumn]) == '0') {
            return true;
        }
    } else if (direction == SOUTH) {
        if ((char)(gridMap[moverRow + 1][moverColumn]) == '.' || (char)(gridMap[moverRow + 1][moverColumn]) == '0') {
            return true;
        }
    } else if (direction == EAST) {
        if ((char)(gridMap[moverRow][moverColumn+1]) == '.' || (char)(gridMap[moverRow][moverColumn+1]) == '0') {
            return true;
        }
    } else if (direction == WEST) {
        if ((char)(gridMap[moverRow][moverColumn-1]) == '.' || (char)(gridMap[moverRow][moverColumn-1]) == '0') {
            return true;
        }
    }
    return false;
}

bool Grid::RightIsClear() const {
    if (direction == WEST) {
        if ((char)(gridMap[moverRow - 1][moverColumn]) == '.' || (char)(gridMap[moverRow - 1][moverColumn]) == '0') {
            return true;
        }
    } else if (direction == EAST) {
        if ((char)(gridMap[moverRow + 1][moverColumn]) == '.' || (char)(gridMap[moverRow + 1][moverColumn]) == '0') {
            return true;
        }
    } else if (direction == NORTH) {
        if ((char)(gridMap[moverRow][moverColumn+1]) == '.' || (char)(gridMap[moverRow][moverColumn+1]) == '0') {
            return true;
        }
    } else if (direction == SOUTH) {
        if ((char)(gridMap[moverRow][moverColumn-1]) == '.' || (char)(gridMap[moverRow][moverColumn-1]) == '0') {
            return true;
        }
    }
    return false;
}

int Grid::GetRow() const {
    return moverRow;
}

int Grid::GetCol() const {
    return moverColumn;
}

void Grid::PutDown() {
    gridMap[moverRow][moverColumn] = '@';
}

bool Grid::PutDown(int r, int c) {
    if (r < 0 || r > rows || c < 0 || c > columns) return false;
    if ((char)(gridMap[r][c] == '>' || (char)gridMap[r][c] == 'v')
    || ((char)gridMap[r][c] == '<' || (char)(gridMap[r][c] == '^'))) {
        gridMap[r][c] = '@';
        return true;
    }
    else if ((char)gridMap[r][c] == '#' ||(char)gridMap[r][c]=='0'
        || (char) gridMap[r][c] == '@') {
        return false;
    }
    else {
        gridMap[r][c] = '0';
        return true;
    }

}

bool Grid::PickUp() {
    if ((char)gridMap[moverRow][moverColumn] == '@') {
        if (direction == NORTH) gridMap[moverRow][moverColumn] = '^';
        else if (direction == SOUTH) gridMap[moverRow][moverColumn] = 'v';
        else if (direction == EAST) gridMap[moverRow][moverColumn] = '>';
        else gridMap[moverRow][moverColumn] = '<';
        return true;
    }
    return false;
}

void Grid::Grow(int gr, int gc) {
    if ((rows + gr) > 40) {
        rows = 40;
    }else if ((columns + gc) > 40) {
        columns = 40;
    } else {
        rows += gr;
        columns += gc;
    }

}
