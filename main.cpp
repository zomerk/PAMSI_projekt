//
// Created by zomer on 19/03/2023.
//
#include "Window.h"
#include "funkcje.h"
int main()
{
    int a;
    std::cin >> a;
    switch(a) {
        case 1:
            {
            Window okno;
            okno.Action_Loop(500);
            break;
            }
       case 2:
            {
              odbijanie();
              break;
            }
       case 3:
            {
              spadanie_pionowe();
              break;
            }
    }
}
