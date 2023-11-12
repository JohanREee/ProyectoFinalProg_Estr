#include <iostream>
#include <windows.h>
#include <string>
int main()
{
    char *correo = new char[40];
    std::cout << "Dame un correo: ";
    std::cin.getline(correo, 40, '\n');
    if ((strchr(correo, '@') != NULL) &&(strlen(correo) > 1))
    {
        std::cout << "@ encontrado";
    }
    else
    {
        std::cout << "@ no encontrado.";
    }

    delete[] correo;
    return 0;
}
