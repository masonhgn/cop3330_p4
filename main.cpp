#include <iostream>
#include "grid.cpp"
using namespace std;
int main() {

    Grid g(9,15,2,13,Grid::WEST);

    g.PutDown(2,1);

    for (int i = 0; i < 7; i++)
    {
        g.PlaceBlock(i,11);
        g.PlaceBlock(i,7);
        g.PlaceBlock(i,3);
        g.PlaceBlock(i+2,5);
        g.PlaceBlock(i+2,9);
    }

    g.Display();
    g.TurnLeft();
    g.Move(5);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
    g.Move(1);
    g.Display();

    for (int i = 0; i < 2; i++)
    {
        g.Move(2);
        g.Display();

        g.TurnLeft();
        g.TurnLeft();
        g.TurnLeft();
        g.Move(6);
        g.Display();

        g.PutDown();
        g.Display();

        g.TurnLeft();
        g.Move(2);
        g.Display();

        g.TurnLeft();
        g.Move(6);
        g.Display();

        g.TurnLeft();
        g.TurnLeft();
        g.TurnLeft();
    }

    g.Move(3);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
    g.Move(5);
    g.Display();

    g.PickUp();
    g.Display();

    g.TurnLeft();
    g.Move(1);
    g.Display();

    g.TogglePath();
    g.Display();
    g.TogglePath();
    g.Display();
    //g1.TogglePath();
    //path storage is fucked, we also need to look at the game test version. ask ta for help 2:30

    return 0;
}
