#include <iostream>
#include "grid.cpp"
using namespace std;
int main() {
    Grid g1(8,8,1,4,2);
    g1.Move(5);
    g1.Display();
    return 0;
}
