#include <iostream>
#include "grid.cpp"
using namespace std;
int main() {
    Grid g1(10,10,8,4,0);
    g1.PutDown(4, 4);
    g1.Move(4);
    //g1.TogglePath();
    //path storage is fucked, we also need to look at the game test version. ask ta for help 2:30
    g1.Display();
    return 0;
}
