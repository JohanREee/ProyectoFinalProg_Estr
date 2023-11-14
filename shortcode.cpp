#include <iostream>
#include <windows.h>
#include <string>
#include <limits>
int soloEnteros()
{
    const int bufferSize = 100; // Suponiendo que el número de teléfono no excederá los 100 caracteres
    char buffer[bufferSize];

    int numero;
    bool esNumeroValido;

    do
    {
        std::cout << "Ingrese un número: ";
        esNumeroValido = true; 
        std::cin.getline(buffer, bufferSize);
        for (int i = 0; buffer[i] != '\0'; ++i)
        {
            if (!std::isdigit(buffer[i]))
            {
                esNumeroValido = false;
                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cout << "Entrada inválida. Por favor, ingrese solo números enteros.\n";
                break; 
            }
        }

        if (esNumeroValido)
        {
            numero = std::atoi(buffer);
        }
    }while (!esNumeroValido);

    return numero;
}
int main()
{
    int telefono;
    std::cout << "Ingrese un telefono: ";
    telefono = soloEnteros();
    std::cout << "Tu telefono es: " << telefono << "\n";
    return 0;
}
