#include <stdio.h>
#include <conio.h>
#include <iostream>

int main()
{
    int i = 0;
    char ch;
    char psw[30];

    std::cout << "Enter a password: ";

    while (true)
    {
        ch = _getch();

        if (ch == 13) // Presiono enter
        {
            if (i != 0) // Verifica si el primero que puso no es un enter
            {
                break;
            }
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                std::cout << "\b \b";
            }
        }
        else
        {
            psw[i] = ch;
            i++;
            std::cout << "*";
        }
    }
    psw[i] = '\0';

    std::cout << "\nTu contraseña es: " << psw;
    return 0;
}
