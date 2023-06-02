//
// Created by zomer on 19/03/2023.
//
#include "Window.h"
#include "funkcje.h"
int main()
{
    char a;

    cout<<"Witaj oto program silnik fizyczny czy cos xd..."<<endl;
    
    while(a!='z')
    {    
        cout<<"Menu"<<endl;
        cout<<"1 - Zderzenia"<<endl;
        cout<<"2 - Odbicia pilki z uwzglednieneim grawitacji"<<endl;
        cout<<"3 - Spadek pionowy"<<endl;
        cout<<"z - zamkij"<<endl;
        cout<<"Twoj wybor: ";
        std::cin >> a; 
        cout<<endl;
        switch(a) 
        {
            case '1':
            {
                Window okno;
                okno.Action_Loop(500);
                break;
            }
            case '2':
            {
                odbijanie();
                break;
            }
            case '3':
            {
                spadanie_pionowe();
                break;
            }
        }
    }
}

