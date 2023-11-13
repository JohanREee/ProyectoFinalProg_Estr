#include "structs.h"
#include "complemento.cpp"

void agregarUsuarioMaestro(lista_Usuario *&lista_usuario) // Primer Usuario
{
    lista_Usuario *nuevo_usuario = new lista_Usuario();
    nuevo_usuario->usuario.nombres = new char[6]; // admin
    strcpy(nuevo_usuario->usuario.nombres, "@admin");
    nuevo_usuario->usuario.apellidos = new char[6]; // admin
    strcpy(nuevo_usuario->usuario.apellidos, "@admin");
    nuevo_usuario->usuario.telefono = -100;
    nuevo_usuario->usuario.correo = new char[17];
    strcpy(nuevo_usuario->usuario.correo, "admin@admin.com");
    nuevo_usuario->usuario.contraseña = new char[12];
    strcpy(nuevo_usuario->usuario.contraseña, "admin123456");
    nuevo_usuario->usuario.administrador = true;
    lista_Usuario *aux = lista_usuario; // Reservamos el valor original de la lista
    lista_Usuario *aux2;
    while (aux != NULL)
    {                         // Comprobamos que aux no apunte a null
        aux2 = aux;           // Reservamos el valor original de aux que por ahora es la llista
        aux = aux->siguiente; // Corre una posición, buscando NULL
    }
    if (aux == lista_usuario) // Nunca pasó por el while
    {
        lista_usuario = nuevo_usuario;
    }
    else // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
    {
        aux2->siguiente = nuevo_usuario;
    }
    nuevo_usuario->siguiente = aux; // nuevo_usuario apunta a NULL
}
void agregarUsuarioEnLista(lista_Usuario *&lista_usuario)
{
    lista_Usuario *nuevo_usuario = new lista_Usuario();
    int administrador;
    std::cout << "Ingrese sus nombres: ";
    agregarElementoPuntero(nuevo_usuario->usuario.nombres, input);
    std::cout << "Ingrese sus apellidos: ";
    agregarElementoPuntero(nuevo_usuario->usuario.apellidos, input);
    while (true)
    {
        std::cout << "Ingrese su telefono: ";
        nuevo_usuario->usuario.telefono = soloEnteros();
        if (nuevo_usuario->usuario.telefono < 0)
        {
            std::cout << "Se ha producido un error al ingresar el numero de telefono.\n";
            std::cout << "Vuelve a intentar.\n";
            continue;
        }
        break;
    }
    while (true)
    {
        std::cout << "Ingrese su correo: ";
        agregarElementoPuntero(nuevo_usuario->usuario.correo, input);
        if (!comprobarCorreo(nuevo_usuario->usuario.correo, lista_usuario))
        {
            std::cout << "Este correo no es valido.\n";
            std::cout << "Vuelve a intentarlo.\n";
            continue;
        }
        break;
    }
    std::cout << "Ingrese su contraseña: ";
    agregarElementoPuntero(nuevo_usuario->usuario.contraseña, input);
    char *user = nombreFormal(nuevo_usuario->usuario);
    std::cout << "¿Desea otorgar permisos de administrador a \"" << user << "\"?\n";
    delete[] user;
    std::cout << "Esta opción se puede modificar con la opción de modificar usuarios posteriormente.\n";
    verificarModificacionEnUsuario(administrador);
    if (administrador == 1)
    {
        nuevo_usuario->usuario.administrador = true;
    }
    else
    {
        nuevo_usuario->usuario.administrador = false;
    }
    std::cout << "Usuario ingresado al sistema correctamente.\n";
    std::cout << "Permiso: ";
    (nuevo_usuario->usuario.administrador) ? std::cout << "Administrador\n" : std::cout << "Personal\n";
    lista_Usuario *aux = lista_usuario; // Reservamos el valor original de la lista
    lista_Usuario *aux2;
    while (aux != NULL)
    {                         // Comprobamos que aux no apunte a null
        aux2 = aux;           // Reservamos el valor original de aux que por ahora es la llista
        aux = aux->siguiente; // Corre una posición, buscando NULL
    }
    if (lista_usuario == aux)
    { // Nunca pasó por el while
        lista_usuario = nuevo_usuario;
    }
    else
    { // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
        aux2->siguiente = nuevo_usuario;
    }
    nuevo_usuario->siguiente = aux; // nuevo_usuario apunta a NULL
}

lista_Usuario *buscarUsuarioParaSesion(lista_Usuario *lista, char *correo, char *contraseña)
{
    lista_Usuario *aux = lista;
    while (aux != NULL)
    {
        if ((strcmp(correo, aux->usuario.correo) == 0) && (strcmp(contraseña, aux->usuario.contraseña) == 0))
        {
            if (aux->usuario.validacion)
            {
                return NULL;
            }
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}
lista_Usuario *buscarUsuario(lista_Usuario *lista, char *correo)
{
    lista_Usuario *aux = lista;
    while (aux != NULL)
    {
        if ((strcmp(correo, aux->usuario.correo) == 0))
        {
            if (aux->usuario.validacion)
            {
                int op;
                std::cout << "Este usuario ha sido anulado anteriormente. ¿Deseas continuar de igual forma?\n";
                verificarModificacionEnUsuario(op);
                if (op != 1)
                {
                    return NULL;
                }
            }
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}
void mostrarUsuario(Usuario usuario)
{
    std::cout << "Nombre completo: " << usuario.nombres << " " << usuario.apellidos << ".\n";
    std::cout << "Teléfono: " << usuario.telefono << "\n";
    std::cout << "Correo: " << usuario.correo << "\n";
    std::cout << "Contraseña: ";
    if (strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0)
    {
        std::cout << usuario.contraseña << "\n";
    }
    else
    {
        for (int i = 0; i < strlen(usuario.contraseña); i++)
        {
            std::cout << "*";
        }
        std::cout << "\n";
    }
    std::cout << "Permiso: ";
    (usuario.administrador) ? std::cout << "Administrador" : std::cout << "Personal";
    std::cout << "\n";
}

void modificarUsuario(lista_Usuario *&lista_usuario, char *&user)
{
    char *correo;
    std::cout << "Ingrese el correo del usuario: ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "Correo no valido.\n";
        std::cout << "Volviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    lista_Usuario *usuario_actual = buscarUsuario(lista_usuario, correo);
    delete[] correo;
    if (usuario_actual == NULL)
    {
        std::cout << "Usuario no encontrado.";
        std::cout << "\nVolviendo al menú anterior.\n";
        return;
    }
    if (strcmp(usuario_actual->usuario.correo, "admin@admin.com") == 0)
    {
        std::cout << "Error. Este usuario no se puede modificar.\n";
        return;
    }
    if (!usuario_activo->usuario.administrador)
    {
        std::cout << "No tienes suficientes permisos para modificar los datos.\n";
        return;
    }
    char *actual_user = nombreFormal(usuario_actual->usuario);
    int op;
    std::cout << "Usuario actual: " << actual_user << "\n";
    std::cout << "\nSeleccione uno de los campos que desea modificar.\n";
    std::cout << "1. Nombre.\n";
    std::cout << "2. Telefono.\n";
    std::cout << "3. Correo.\n";
    std::cout << "4. Contraseña.\n";
    std::cout << "5. Permisos de administrador.\n";
    std::cout << "Ingresar numero: ";
    op = soloEnteros();
    int opt;
    switch (op)
    {
    case 1:
        std::cout << "¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "Volviendo al menú anterior.\n";
            break;
        }
        modificarNombreYApellido(usuario_actual, actual_user);
        break;
    case 2:
        std::cout << "¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "Volviendo al menú anterior.\n";
            break;
        }
        modificarTelefono(usuario_actual, actual_user);
        break;
    case 3:
        std::cout << "¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "Volviendo al menú anterior.\n";
            break;
        }
        modificarCorreo(usuario_actual, actual_user);
        break;
    case 4:
        std::cout << "¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "Volviendo al menú anterior.\n";
            break;
        }
        modificarContraseña(usuario_actual, actual_user);
        break;
    case 5:
        std::cout << "¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "Volviendo al menú anterior.\n";
            break;
        }
        modificarPermiso(usuario_actual, actual_user);
        break;
    default:
        std::cout << "Valor incorrecto.\n";
        std::cout << "Serás enviado al menú anterior.\n";
        break;
    }
    delete[] actual_user;
    if ((op == 1) && ((strcmp(usuario_activo->usuario.correo, usuario_actual->usuario.correo) == 0)))
    {
        delete[] user;
        char *user = nombreFormal(usuario_actual->usuario);
    }
}

void modificarNombreYApellido(lista_Usuario *&usuario_actual, char *user)
{
    char *nombre;
    char *apellido;
    std::cout << "Ingrese los nuevos nombres del usuario " << user << ": ";
    agregarElementoPuntero(nombre, input);
    std::cout << "Ingrese los nuevos apellidos del usuario " << user << ": ";
    agregarElementoPuntero(apellido, input);
    std::cout << "El nombre completo de \"" << usuario_actual->usuario.nombres << " " << usuario_actual->usuario.apellidos << "\" ha sido reemplazado por \"";
    std::cout << nombre << " " << apellido << "\"\n";
    delete[] usuario_actual->usuario.nombres;
    delete[] usuario_actual->usuario.apellidos;
    usuario_actual->usuario.nombres = new char[strlen(nombre) + 1];
    usuario_actual->usuario.apellidos = new char[strlen(apellido) + 1];
    strcpy(usuario_actual->usuario.nombres, nombre);
    strcpy(usuario_actual->usuario.apellidos, apellido);
    delete[] nombre;
    delete[] apellido;
}
void modificarTelefono(lista_Usuario *&usuario_actual, char *user)
{
    int telefono;
    while (true)
    {
        std::cout << "Ingrese el nuevo teléfono del usuario " << user << ": ";
        telefono = soloEnteros();
        if (telefono < 0)
        {
            std::cout << "Se ha producido un error al ingresar el número de teléfono.\n";
            std::cout << "Volver a intentar.\n";
            continue;
        }
        break;
    }
    std::cout << "El telefono \"" << usuario_actual->usuario.telefono << "\" ha sido reemplazado por \"" << telefono << "\"\n";
    usuario_actual->usuario.telefono = telefono;
}

void modificarCorreo(lista_Usuario *&usuario_actual, char *user)
{
    char *correo;
    std::cout << "Ingrese el nuevo correo de " << user << ": ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "Este correo no es valido.\n";
        std::cout << "Serás enviado al menú anterior/\n";
        delete[] correo;
        return;
    }
    std::cout << "El correo \"" << usuario_actual->usuario.correo << "\" ha sido reemplazado por \"" << correo << "\"\n";
    delete[] usuario_actual->usuario.correo;
    usuario_actual->usuario.correo = new char[strlen(correo) + 1];
    strcpy(usuario_actual->usuario.correo, correo);
    delete[] correo;
}
void modificarContraseña(lista_Usuario *&usuario_actual, char *user)
{

    if ((strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0) || (strcmp(usuario_activo->usuario.correo, usuario_actual->usuario.correo) == 0))
    {
        char *contraseña = NULL;
        char *contraseña2 = NULL;
        std::cout << "Ingrese la nueva contraseña de " << user << ": ";
        agregarElementoPuntero(contraseña, input);

        std::cout << "Valide la contraseña: ";
        agregarElementoPuntero(contraseña2, input);
        if (strcmp(contraseña, contraseña2) == 0)
        {
            std::cout << "La contraseña ha sido modificada por \"" << contraseña << "\".\n";
            delete[] usuario_actual->usuario.contraseña;
            usuario_actual->usuario.contraseña = new char[strlen(contraseña) + 1];
            strcpy(usuario_actual->usuario.contraseña, contraseña);
        }
        else
        {
            std::cout << "Validación incorrecta.\n";
            std::cout << "Volviendo al menú anterior.\n";
        }
        delete[] contraseña2;
        delete[] contraseña;
    }
    else
    {
        std::cout << "No tienes suficientes permisos para modificar este parámetro.\n";
        std::cout << "Volviendo al menú anterior.\n";
    }
}
void modificarPermiso(lista_Usuario *&usuario_actual, char *user)
{
    int opt;
    if ((strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0) || (strcmp(usuario_activo->usuario.correo, usuario_actual->usuario.correo) == 0))
    {
        std::cout << "El usuario actual tiene un permiso de \"";
        (usuario_actual->usuario.administrador) ? std::cout << "Administrador" : std::cout << "Personal";
        std::cout << "\"\n ¿Deseas convertirlo en ";
        (usuario_actual->usuario.administrador) ? std::cout << "Personal" : std::cout << "Administrador";
        std::cout << "?\n";
        verificarModificacionEnUsuario(opt);
        if (opt == 1)
        {
            usuario_actual->usuario.administrador = !usuario_actual->usuario.administrador;
            std::cout << "Ahora el usuario " << user << " es un ";
            (usuario_actual->usuario.administrador) ? std::cout << "Administrador" : std::cout << "Personal";
            std::cout << "\n";
        }
        else
        {
            if (opt != 2)
            {
                std::cout << "Valor incorrecto.\n";
            }
            std::cout << "Serás enviado al menú anterior.\n";
        }
    }
    else
    {
        std::cout << "No tienes los permisos suficientes para modificar los permisos de " << user << "\n";
        std::cout << "Serás enviado al menú anterior.\n";
    }
}

void eliminarUsuario(lista_Usuario *&lista_usuario)
{
    char *correo;
    std::cout << "Ingrese el correo del usuario: ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "Correo no valido.\n";
        std::cout << "Volviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    lista_Usuario *usuario_actual = buscarUsuario(lista_usuario, correo);
    if (usuario_actual == NULL)
    {
        std::cout << "Usuario no encontrado.";
        std::cout << "\nVolviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    delete[] correo;
    char *user = nombreFormal(usuario_actual->usuario);
    int opt;
    std::cout << "Estás seguro de que quieres anular al usuario " << user << "?\n";
    verificarModificacionEnUsuario(opt);
    if (opt != 1)
    {
        std::cout << "Volviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    if ((strcmp(usuario_actual->usuario.correo, "admin@admin.com") == 0))
    {
        std::cout << "El usuario maestro no puede ser anulado.\n";
    }
    else if ((usuario_activo->usuario.administrador && usuario_actual->usuario.administrador))
    {
        if ((strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0))
        {
            std::cout << "Usuario " << user << " eliminado.\n";
            usuario_actual->usuario.validacion = !usuario_actual->usuario.validacion;
        }
        else
        {
            std::cout << "El usuario " << user << " no puede ser eliminado porque también es un administrador.\n";
        }
    }
    else if (!usuario_actual->usuario.administrador)
    {
        std::cout << "Usuario " << user << " eliminado.\n";
        usuario_actual->usuario.validacion = !usuario_actual->usuario.validacion;
    }
    delete[] user;
}

void activarUsuario(lista_Usuario *&lista_usuario)
{
    char *correo;
    std::cout << "Ingrese el correo del usuario: ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "Correo no valido.\n";
        std::cout << "Volviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    lista_Usuario *usuario_actual = buscarUsuario(lista_usuario, correo);
    if (usuario_actual == NULL)
    {
        std::cout << "Usuario no encontrado.";
        std::cout << "\nVolviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    char *user = nombreFormal(usuario_actual->usuario);
    if (!usuario_actual->usuario.validacion)
    {
        std::cout << "Error. El usuario " << user << " ya está activado.\n";
        std::cout << "Volviendo al menú anterior.\n";
        delete[] correo;
        delete[] user;
        return;
    }
    delete[] correo;
    if (usuario_activo->usuario.administrador)
    {
        std::cout << "Usuario " << user << " activado exitosamente.\n";
        usuario_actual->usuario.validacion = !usuario_actual->usuario.validacion;
    }
    else
    {
        std::cout << "No cuentas con los permisos para activar este usuario.\n";
        std::cout << "Volviendo al menú anterior. \n";
    }
    delete[] user;
}

void mostrarUsuarioEnPantalla(lista_Usuario *lista_usuario)
{
    char *correo;
    std::cout << "Ingrese el correo del usuario: ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "Correo no valido.\n";
        std::cout << "Volviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    lista_Usuario *usuario_actual = buscarUsuario(lista_usuario, correo);
    delete[] correo;
    if (usuario_actual == NULL)
    {
        std::cout << "Usuario no encontrado.";
        std::cout << "\nVolviendo al menú anterior.\n";

        return;
    }
    if (usuario_actual->usuario.validacion)
    {
        if ((strcmp(usuario_actual->usuario.correo, "admin@admin.com") != 0) && (strcmp(usuario_activo->usuario.correo, "admin@admin.com") != 0))
        { // El usuario que buscamos es el admin                 el que estamos usando es el admin
            std::cout << "Usuario no encontrado.\n";
            std::cout << "Volviendo al menú anterior.\n";
            return;
        }
        mostrarUsuario(usuario_actual->usuario);
        return;
    }
    else if ((strcmp(usuario_actual->usuario.correo, usuario_activo->usuario.correo) == 0))
    //               el usuario que buscamos          el que manejamos, en este caso es un personal si o si
    {
        mostrarUsuario(usuario_actual->usuario);
        return;
    }
    //
    else
    {
        std::cout << "Usuario no encontrado.\n";
        std::cout << "Volviendo al menú anterior.\n";
        return;
    }
}
void mostrarUsuarios(lista_Usuario *lista_usuario)
{
    lista_Usuario *aux = lista_usuario;
    while (aux != NULL)
    {
        if (strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0)
        {
            mostrarUsuario(aux->usuario);
            std::cout << "\n";
        }
        else if (usuario_activo->usuario.validacion)
        {
            if ((strcmp(aux->usuario.correo, "admin@admin.com") != 0))
            {
                mostrarUsuario(aux->usuario);
                std::cout << "\n";
            }
        }

        aux = aux->siguiente;
    }
}