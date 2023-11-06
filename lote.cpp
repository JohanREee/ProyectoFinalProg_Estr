#include "structs.h"
#include "complemento.cpp"

/*void agregarLotesAProducto(cola_Lote *&cola);
void mostrarLotesDeProducto(cola_Lote *cola, char *id_producto);
void mostrarLotesDeTodosProductos(cola_Lote *cola);
void buscarLote(cola_Lote *cola, char *id_producto);
void modificarLoteDeProducto(cola_Lote *&cola);
void eliminarLoteYMovimientoDeProducto(cola_Lote *&cola_lote, lista_Movimiento *&cola_movimiento, char *id_producto, char *codigo_acceso);
void eliminarLotesYMovimientosTodoDeProducto(cola_Lote *&cola_lote, lista_Movimiento *&cola_movimiento, char *id_producto, char *codigo_acceso);
*/

#ifndef lot
#define lot

char *generarIdLote(int dia, int mes, int año, Informacion_Mes *mes_actual)
{
    char id[20];
    int incremental = mes_actual->lotes_cantidad + 1;
    sprintf(id, "%d%02d%02d%d%d", conteo_id_producto, dia, mes, año % 100, incremental);
    char *id_total = new char[strlen(id) + 1];
    strcpy(id_total, id);
    return id_total;
}

void agregarLotesAProducto(lista_Producto *&producto)
{
    int id_producto;
    std::cout << "Ingrese el id del producto: ";
    id_producto = soloEnteros(id_producto);
    fflush(stdin);
    lista_Producto *producto_actual = buscarProducto(producto, id_producto);
    if (producto_actual == NULL)
    {
        std::cout << "El producto no fue encontrado.\n";
        return;
    }
    while (true)
    {
        int dia = obtenerDia();
        int mes = obtenerMes();
        int año = obtenerAño();
        bool band = false;
        Lista_Año *año_actual = buscarAñoActualDeProducto(producto_actual, año);
        if (año_actual == NULL)
        {
            año_actual = new Lista_Año();
            año_actual->siguiente = NULL;
            bool band = true;
        }
        Informacion_Mes *mes_actual = &año_actual->año_producto.producto[mes - 1];
        Lote lote_actual;
        // Estructura cola_Lote dentro de Información_mes[mes] dentro de Año_Producto dentro de Lista_Año
        cola_Lote *nuevo_lote = new cola_Lote; // 4   01 02 03
        char *id_lote = generarIdLote(dia, mes, año, mes_actual);
        lote_actual.id_lote = new char[strlen(id_lote) + 1];
        strcpy(lote_actual.id_lote, id_lote);
        delete[] id_lote;
        lote_actual.ingreso_fecha = {dia, mes, año};
        int añoe, mese, diae;
        while (true)
        {
            std::cout << "\nIngrese la fecha de expiración del lote en formato dd/mm/yyyy: ";
            scanf("%2d/%2d/%2d", &diae, &mese, &añoe);
            if ((añoe == año) && (mese == mes) && (diae > dia)) //Validar en el mes actual
            {
                if(validarDiaPorMes(añoe, mese, diae))
                {
                    lote_actual.expiracion_fecha = {diae, mese, añoe};
                    break;                    
                }
            }
            else if((añoe == año) && (mese > mes))
            {
                if(validarDiaPorMes(añoe, mese, diae))
                {
                    lote_actual.expiracion_fecha = {diae, mese, añoe};
                    break;      
                }
            }
            else if(añoe > año)
            {
                 if(validarDiaPorMes(añoe, mese, diae))
                {
                    lote_actual.expiracion_fecha = {diae, mese, añoe};
                    break;      
                }               
            }
            std::cout << "Error al ingresar la fecha. Vuelve a intentarlo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("pause");
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (true)
        {
            std::cout << "Ingrese el precio actual del producto: ";
            if (std::cin >> lote_actual.precio_producto)
            {
                if (lote_actual.precio_producto > 0)
                    break;
            }
            std::cout << "Error al ingresar el precio. Vuelve a intentarlo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("pause");
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        nuevo_lote->lote = lote_actual;
        nuevo_lote->siguiente = NULL;
        if (mes_actual->lotes == NULL)
        {
            // Si no hay lotes para este mes, el nuevo lote será el primero
            mes_actual->lotes = nuevo_lote;
        }
        else
        {
            // Si ya hay otros lotes, agregar el nuevo ltoe al final de la cola
            cola_Lote *aux_lote = mes_actual->lotes;
            while (aux_lote->siguiente != NULL) // Bucle para encontrar el penúltimo
            {
                aux_lote = aux_lote->siguiente;
            }
            aux_lote->siguiente = nuevo_lote; // Hacer que el penúltimo apunte al nuevo, que ahora es el último
        }
        // Actualizar la cantidad de lotes de toda la cola
        mes_actual->lotes_cantidad++;
        if (band)
        {
            Lista_Año *aux = producto_actual->producto.años_producto; // Reservamos el valor original de la lista
            Lista_Año *aux2;
            while (aux != NULL)
            {                         // Comprobamos que aux no apunte a null
                aux2 = aux;           // Reservamos el valor original de aux que por ahora es la llista
                aux = aux->siguiente; // Corre una posición, buscando NULL
            }
            if (aux == producto_actual->producto.años_producto) // Nunca pasó por el while
            {
                producto_actual->producto.años_producto = año_actual;
            }
            else // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
            {
                aux2->siguiente = año_actual;
            }
            año_actual->siguiente = aux; // año_actual apunta a NULL
        }
        std::cout << "\nLote agregado con exito.\n";
        int op;
        std::cout << "¿Desea agregar otro lote para este producto?\n";
        std::cout << "1. Sí\n";
        std::cout << "2. No\n";
        op = soloEnteros(op);
        if (op != 1)
        {
            break;
        }
        
    }
}

#endif