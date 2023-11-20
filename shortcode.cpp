/*

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string.h>

char input[250];

long double digitarFlotante()
{
    int i = 0;
    char ch;
    bool punto = false;
    bool signo = false;
    while (true)
    {

        ch = _getch();

        if (ch == 13) // Presiono enter
        {
            if (i != 0 && input[i - 1] != '.' && strcmp(input, "-") != 0)
            {
                break;
            }
        }                 // -0.
        else if (ch == 8) // Backspace
        {
            if (i > 0)
            {
                if (input[i - 1] == '.')
                {
                    punto = false;
                }
                if (input[i - 1] == '-')
                {
                    signo = false;
                }
                i--;
                std::cout << "\b \b";
            }
        }
        else if (std::isdigit(ch)) // Digito
        {
            input[i] = ch;
            i++;
            std::cout << ch;
        }
        else if (ch == '.') // PUnto decimal
        {
            if (!punto && i > 0 && std::isdigit(input[i - 1]))
            {
                input[i] = ch;
                i++;
                std::cout << ch;
                punto = true;
            }
        }
        else if (ch == '-') // signo negativo
        {
            if (!signo && i == 0)
            {
                input[i] = ch;
                i++;
                std::cout << ch;
                signo = true;
            }
        }
    }
    return std::atof(input);
}
long int digitarEntero()
{
    int i = 0;
    char ch;
    bool signo = false;
    while (true)
    {

        ch = _getch();

        if (ch == 13) // Presiono enter
        {
            if (i != 0  && strcmp(input, "-") != 0)
            {
                break;
            }
        }                 // -0.
        else if (ch == 8) // Backspace
        {
            if (i > 0)
            {
                if (input[i - 1] == '-')
                {
                    signo = false;
                }
                i--;
                std::cout << "\b \b";
            }
        }
        else if (std::isdigit(ch)) // Digito
        {
            input[i] = ch;
            i++;
            std::cout << ch;
        }
        else if (ch == '-') // signo negativo
        {
            if (!signo && i == 0)
            {
                input[i] = ch;
                i++;
                std::cout << ch;
                signo = true;
            }
        }
    }
    return std::atoi(input);
}
int main()
{
    std::cout << "Ingresar numero: ";
    long int numero = digitarEntero();
    std::cout << "\nEl numero digitado es: " << numero << "\n";
    system("pause");
    return 0;
}

*/


#include <iostream>
#include <limits>

int main() {
    std::cout << "El rango de int es de " << std::numeric_limits<double>::min() << " a " << std::numeric_limits<double>::max() << std::endl;
   
    return 0;
}


