#include <iostream>
#include <windows.h>

void getpass(const char *prompt, char *password, int max_length, bool show_asterisk = true)
{
    unsigned char ch = 0;
    int password_index = 0;
    bool first_character_read = false;

    std::cout << prompt;

    DWORD con_mode;
    DWORD dwRead;

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(hIn, &con_mode);
    SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    // Continúa leyendo hasta que el usuario ingrese un salto de línea como primer carácter
    while (!first_character_read || (password_index < max_length - 1 && ch != '\r'))
    {
        if (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL))
        {
            if (!first_character_read)
            {
                first_character_read = true; // Se ha leído el primer carácter

                if (ch == '\r') // Si el primer carácter es un salto de línea, continúa leyendo
                {
                    continue;
                }
                else // Si el primer carácter NO es un salto de línea, detén la función aquí
                {
                    password[0] = ch;   // Guarda el primer carácter
                    password_index = 1; // Ajusta el índice de la contraseña
                    break;
                }
            }
            else
            {
                // A partir del segundo carácter, procesa normalmente
                if (ch == '\b' && password_index > 0) // Si es backspace y hay caracteres, retrocede
                {
                    if (show_asterisk)
                        std::cout << "\b \b";
                    password_index--;
                }
                else if (ch != '\b') // Si no es backspace, añade el carácter a la contraseña
                {
                    password[password_index++] = ch;
                    if (show_asterisk)
                        std::cout << '*';
                }
            }
        }
    }
    password[password_index] = '\0'; // Termina la cadena con un carácter nulo

    std::cout << std::endl;

    // Restaura el modo de la consola
    SetConsoleMode(hIn, con_mode);
}

int main()
{
    const int MAX_PASSWORD_LENGTH = 100;
    char user_password[MAX_PASSWORD_LENGTH];

    getpass("Por favor, ingrese su contraseña: ", user_password, MAX_PASSWORD_LENGTH);
    std::cout << "Tu contraseña es: " << user_password << std::endl;

    return 0;
}
