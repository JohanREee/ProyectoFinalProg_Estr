#include "structs.h"

void agregarUsuarioMaestro(lista_Usuario *&lista_usuario) // Primer Usuario
{
    lista_Usuario *nuevo_usuario = new lista_Usuario();
    nuevo_usuario->usuario.nombres = new char[7]; // admin
    strcpy(nuevo_usuario->usuario.nombres, "@admin");
    nuevo_usuario->usuario.apellidos = new char[7]; // admin
    strcpy(nuevo_usuario->usuario.apellidos, "@admin");
    nuevo_usuario->usuario.telefono = -100;
    nuevo_usuario->usuario.correo = new char[17];
    strcpy(nuevo_usuario->usuario.correo, "admin@admin.com");
    nuevo_usuario->usuario.contrasena = new char[12];
    strcpy(nuevo_usuario->usuario.contrasena, "admin123456");
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
    pausarYLimpiar();
    marco();
    gotoxy(2,6);
    std::cout << "\tIngrese sus nombres: ";
    agregarElementoPuntero(nuevo_usuario->usuario.nombres, input);
    std::cout << "\tIngrese sus apellidos: ";
    agregarElementoPuntero(nuevo_usuario->usuario.apellidos, input);
    while (true)
    {
        std::cout << "\tIngrese su telefono: ";
        nuevo_usuario->usuario.telefono = soloEnteros();
        if (nuevo_usuario->usuario.telefono < 0)
        {
            std::cout << "\tSe ha producido un error al ingresar el numero de telefono.\n";
            std::cout << "\tVuelve a intentar.\n";
            continue;
        }
        break;
    }
    while (true)
    {
        std::cout << "\tIngrese su correo: ";
        agregarElementoPuntero(nuevo_usuario->usuario.correo, input);
        if (!comprobarCorreo(nuevo_usuario->usuario.correo, lista_usuario))
        {
            std::cout << "\tEste correo no es valido.\n";
            std::cout << "\tVuelve a intentarlo.\n";
            continue;
        }
        break;
    }
    std::cout << "\tIngrese su contrasena: ";
    nuevo_usuario->usuario.contrasena = digitarContrasena();
    char *user = nombreFormal(nuevo_usuario->usuario);
    while (true)
    {
        std::cout << "\t¿Desea otorgar permisos de administrador a \"" << user << "\"?\n";
        std::cout << "\tEsta opción se puede modificar con la opción de modificar usuarios posteriormente.\n";
        verificarModificacionEnUsuario(administrador);
        if (administrador == 1)
        {
            nuevo_usuario->usuario.administrador = true;
            break;
        }
        else if (administrador == 2)
        {
            nuevo_usuario->usuario.administrador = false;
            break;
        }
        else
        {
            std::cout << "\tValor invalido. Vuelve a intentarlo.\n";
            pausar();
        }
    }
    std::cout << "\tUsuario ingresado al sistema correctamente.\n";
    std::cout << "\tPermiso: ";
    (nuevo_usuario->usuario.administrador) ? std::cout << "Administrador\n" : std::cout << "Personal\n";
    
    delete[] user;
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
    escribirUsuariosAJSON(lista_usuario);
}

lista_Usuario *buscarUsuarioParaSesion(lista_Usuario *lista, char *correo, char *contrasena)
{
    lista_Usuario *aux = lista;
    while (aux != NULL)
    {
        if ((strcmp(correo, aux->usuario.correo) == 0) && (strcmp(contrasena, aux->usuario.contrasena) == 0))
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
                std::cout << "\tEste usuario ha sido anulado anteriormente. ¿Deseas continuar de igual forma?\n";
                verificarModificacionEnUsuario(op);
                if (op != 1) // op es 2 por ejemplo
                {
                    if (op != 2)
                    {
                        std::cout << "\tError al ingresar el número.\n";
                    }
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
    pausarYLimpiar();
    marco();
    gotoxy(2,6);
    std::cout << "\tNombre completo: " << usuario.nombres << " " << usuario.apellidos << ".\n";
    std::cout << "\tTeléfono: " << usuario.telefono << "\n";
    std::cout << "\tCorreo: " << usuario.correo << "\n";
    std::cout << "\tContrasena: ";
    if (strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0)
    {
        std::cout << usuario.contrasena << "\n";
    }
    else
    {
        for (int i = 0; i < strlen(usuario.contrasena); i++)
        {
            std::cout << "*";
        }
        std::cout << "\n";
    }
    std::cout << "\tPermiso: ";
    (usuario.administrador) ? std::cout << "Administrador" : std::cout << "Personal";
    std::cout << "\n";
}

void modificarUsuario(lista_Usuario *&lista_usuario, char *&user)
{
    char *correo;
    pausarYLimpiar();
    marco();
    gotoxy(2,6);
    std::cout << "\tIngrese el correo del usuario: ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "\tCorreo no valido.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    lista_Usuario *usuario_actual = buscarUsuario(lista_usuario, correo);
    delete[] correo;
    if (usuario_actual == NULL)
    {
        std::cout << "\tUsuario no encontrado.";
        std::cout << "\n\tVolviendo al menú anterior.\n";
        return;
    }
    if (strcmp(usuario_actual->usuario.correo, "admin@admin.com") == 0)
    {
        std::cout << "\tError. Este usuario no se puede modificar.\n";
        return;
    }
    if (!usuario_activo->usuario.administrador)
    {
        std::cout << "\tNo tienes suficientes permisos para modificar los datos.\n";
        return;
    }
    char *actual_user = nombreFormal(usuario_actual->usuario);
    int op;
    std::cout << "\tUsuario actual: " << actual_user << "\n";
    std::cout << "\n\tSeleccione uno de los campos que desea modificar.\n";
    std::cout << "\t1. Nombre.\n";
    std::cout << "\t2. Telefono.\n";
    std::cout << "\t3. Correo.\n";
    std::cout << "\t4. Contrasena.\n";
    std::cout << "\t5. Permisos de administrador.\n";
    std::cout << "\tIngresar numero: ";
    op = soloEnteros();
    int opt;
    switch (op)
    {
    case 1:
        std::cout << "\t¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "\tVolviendo al menú anterior.\n";
            break;
        }
        modificarNombreYApellido(usuario_actual, actual_user);
        escribirUsuariosAJSON(lista_usuario);
        break;
    case 2:
        std::cout << "\t¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "\tVolviendo al menú anterior.\n";
            break;
        }
        modificarTelefono(usuario_actual, actual_user);
        escribirUsuariosAJSON(lista_usuario);
        break;
    case 3:
        std::cout << "\t¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "\tVolviendo al menú anterior.\n";
            break;
        }
        modificarCorreo(usuario_actual, actual_user);
        escribirUsuariosAJSON(lista_usuario);
        break;
    case 4:
        std::cout << "\t¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "\tVolviendo al menú anterior.\n";
            break;
        }
        modificarContrasena(usuario_actual, actual_user);
        escribirUsuariosAJSON(lista_usuario);
        break;
    case 5:
        std::cout << "\t¿Estás seguro de que quieres modificar este parametro?\n";
        verificarModificacionEnUsuario(opt);
        if (opt != 1)
        {
            std::cout << "\tVolviendo al menú anterior.\n";
            break;
        }
        modificarPermiso(usuario_actual, actual_user);
        escribirUsuariosAJSON(lista_usuario);
        break;
    default:
        std::cout << "\tValor incorrecto.\n";
        std::cout << "\tSerás enviado al menú anterior.\n";
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
    std::cout << "\tIngrese los nuevos nombres del usuario " << user << ": ";
    agregarElementoPuntero(nombre, input);
    std::cout << "\tIngrese los nuevos apellidos del usuario " << user << ": ";
    agregarElementoPuntero(apellido, input);
    std::cout << "\tEl nombre completo de \"" << usuario_actual->usuario.nombres << " " << usuario_actual->usuario.apellidos << "\" ha sido reemplazado por \"";
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
        std::cout << "\tIngrese el nuevo teléfono del usuario " << user << ": ";
        telefono = soloEnteros();
        if (telefono < 0)
        {
            std::cout << "\tSe ha producido un error al ingresar el número de teléfono.\n";
            std::cout << "\tVolver a intentar.\n";
            continue;
        }
        break;
    }
    std::cout << "\tEl telefono \"" << usuario_actual->usuario.telefono << "\" ha sido reemplazado por \"" << telefono << "\"\n";
    usuario_actual->usuario.telefono = telefono;
}

void modificarCorreo(lista_Usuario *&usuario_actual, char *user)
{
    char *correo;
    std::cout << "\tIngrese el nuevo correo de " << user << ": ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "\tEste correo no es valido.\n";
        std::cout << "\tSerás enviado al menú anterior/\n";
        delete[] correo;
        return;
    }
    std::cout << "\tEl correo \"" << usuario_actual->usuario.correo << "\" ha sido reemplazado por \"" << correo << "\"\n";
    delete[] usuario_actual->usuario.correo;
    usuario_actual->usuario.correo = new char[strlen(correo) + 1];
    strcpy(usuario_actual->usuario.correo, correo);
    delete[] correo;
}
void modificarContrasena(lista_Usuario *&usuario_actual, char *user)
{

    if ((strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0) || (strcmp(usuario_activo->usuario.correo, usuario_actual->usuario.correo) == 0))
    {
        char *contrasena = NULL;
        char *contrasena2 = NULL;
        std::cout << "\tIngrese la nueva contrasena de " << user << ": ";
        contrasena = digitarContrasena();
        std::cout << "\tValide la contrasena: ";
        contrasena2 = digitarContrasena();
        agregarElementoPuntero(contrasena2, input);
        if (strcmp(contrasena, contrasena2) == 0)
        {
            std::cout << "\tLa contrasena ha sido modificada por \"" << contrasena << "\".\n";
            delete[] usuario_actual->usuario.contrasena;
            usuario_actual->usuario.contrasena = new char[strlen(contrasena) + 1];
            strcpy(usuario_actual->usuario.contrasena, contrasena);
        }
        else
        {
            std::cout << "\tValidación incorrecta.\n";
            std::cout << "\tVolviendo al menú anterior.\n";
        }
        delete[] contrasena2;
        delete[] contrasena;
    }
    else
    {
        std::cout << "\tNo tienes suficientes permisos para modificar este parámetro.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
    }
}
void modificarPermiso(lista_Usuario *&usuario_actual, char *user)
{
    int opt;
    if ((strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0) || (strcmp(usuario_activo->usuario.correo, usuario_actual->usuario.correo) == 0))
    {
        std::cout << "\tEl usuario actual tiene un permiso de \"";
        (usuario_actual->usuario.administrador) ? std::cout << "Administrador" : std::cout << "Personal";
        std::cout << "\"\n\t ¿Deseas convertirlo en ";
        (usuario_actual->usuario.administrador) ? std::cout << "Personal" : std::cout << "Administrador";
        std::cout << "?\n";
        verificarModificacionEnUsuario(opt);
        if (opt == 1)
        {
            usuario_actual->usuario.administrador = !usuario_actual->usuario.administrador;
            std::cout << "\tAhora el usuario " << user << " es un ";
            (usuario_actual->usuario.administrador) ? std::cout << "Administrador" : std::cout << "Personal";
            std::cout << "\n";
        }
        else
        {
            if (opt != 2)
            {
                std::cout << "\tValor incorrecto.\n";
            }
            std::cout << "\tSerás enviado al menú anterior.\n";
        }
    }
    else
    {
        std::cout << "\tNo tienes los permisos suficientes para modificar los permisos de " << user << "\n";
        std::cout << "\tSerás enviado al menú anterior.\n";
    }
}

void eliminarUsuario(lista_Usuario *&lista_usuario)
{
    char *correo;
    std::cout << "\tIngrese el correo del usuario: ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "\tCorreo no valido.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    lista_Usuario *usuario_actual = buscarUsuario(lista_usuario, correo);
    if (usuario_actual == NULL)
    {
        std::cout << "\tUsuario no encontrado.";
        std::cout << "\n\tVol\tviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    delete[] correo;
    char *user = nombreFormal(usuario_actual->usuario);
    int opt;
    std::cout << "\tEstás seguro de que quieres anular al usuario " << user << "?\n";
    verificarModificacionEnUsuario(opt);
    if (opt != 1)
    {
        std::cout << "\tVolviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    if ((strcmp(usuario_actual->usuario.correo, "admin@admin.com") == 0))
    {
        std::cout << "\tUsuario no encontrado.";
        std::cout << "\n\tVolviendo al menú anterior.\n";
        return;
    }
    else if ((usuario_activo->usuario.administrador && usuario_actual->usuario.administrador))
    {
        if ((strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0))
        {
            std::cout << "\tUsuario " << user << " eliminado.\n";
            usuario_actual->usuario.validacion = !usuario_actual->usuario.validacion;
            escribirUsuariosAJSON(lista_usuario);
        }
        else
        {
            std::cout << "\tEl usuario " << user << " no puede ser eliminado porque también es un administrador.\n";
        }
    }
    else if (!usuario_actual->usuario.administrador)
    {
        std::cout << "\tUsuario " << user << " eliminado.\n";
        usuario_actual->usuario.validacion = !usuario_actual->usuario.validacion;
        escribirUsuariosAJSON(lista_usuario);
    }
    
    delete[] user;
}

void activarUsuario(lista_Usuario *&lista_usuario)
{
    char *correo;
    pausarYLimpiar();
    marco();
    gotoxy(2,6);
    std::cout << "\tIngrese el correo del usuario: ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "\tCorreo no valido.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    lista_Usuario *usuario_actual = buscarUsuario(lista_usuario, correo);
    if (usuario_actual == NULL)
    {
        std::cout << "\tUsuario no encontrado.";
        std::cout << "\n\tVolviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    char *user = nombreFormal(usuario_actual->usuario);
    if (!usuario_actual->usuario.validacion)
    {
        std::cout << "\tError. El usuario " << user << " ya está activado.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
        delete[] correo;
        delete[] user;
        return;
    }
    delete[] correo;
    if (usuario_activo->usuario.administrador)
    {
        std::cout << "\tUsuario " << user << " activado exitosamente.\n";
        usuario_actual->usuario.validacion = !usuario_actual->usuario.validacion;
        escribirUsuariosAJSON(lista_usuario);
    }
    else
    {
        std::cout << "\tNo cuentas con los permisos para activar este usuario.\n";
        std::cout << "\tVolviendo al menú anterior. \n";
    }
    delete[] user;
}

void mostrarUsuarioEnPantalla(lista_Usuario *lista_usuario)
{
    char *correo;
    pausarYLimpiar();
    marco();
    gotoxy(2,6);
    std::cout << "\tIngrese el correo del usuario: ";
    agregarElementoPuntero(correo, input);
    if (comprobarCorreo(correo, lista_usuario))
    {
        std::cout << "\tCorreo no valido.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
        delete[] correo;
        return;
    }
    lista_Usuario *usuario_actual = buscarUsuario(lista_usuario, correo);
    delete[] correo;
    if (usuario_actual == NULL)
    {
        std::cout << "\tUsuario no encontrado.";
        std::cout << "\n\tVolviendo al menú anterior.\n";

        return;
    }
    if (strcmp(usuario_activo->usuario.correo, "admin@admin.com") == 0)
    {
        mostrarUsuario(usuario_actual->usuario);
        return;
    }
    else if (usuario_activo->usuario.administrador) // Con esto se comprueba que es un admin
    {
        if (strcmp(usuario_actual->usuario.correo, "admin@admin.com") != 0)
        {
            mostrarUsuario(usuario_actual->usuario);
            return;
        }

        std::cout << "\tUsuario no encontrado.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
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
        else if (usuario_activo->usuario.administrador)
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