#include "structs.h"

json estructuraFechaAJSON(Fecha &fecha)
{
    json j;
    j["dia"] = fecha.dia;
    j["mes"] = fecha.mes;
    j["ano"] = fecha.ano;
    return j;
}

json estructuraLoteAJSON(Lote &lote)
{
    json j;
    j["id_lote"] = lote.id_lote;
    j["ingreso_fecha"] = estructuraFechaAJSON(lote.ingreso_fecha);
    j["expiracion_fecha"] = estructuraFechaAJSON(lote.expiracion_fecha);
    j["cantidad_de_producto"] = lote.cantidad_de_producto;
    j["precio_producto"] = lote.precio_producto;
    j["validacion"] = (lote.validacion) ? "Si" : "No";
    j["motivo"] = lote.motivo;
    j["costo_venta"] = lote.costo_venta;
    return j;
}
json agregarListaLote(cola_Lote *cola_lote)
{
    json j = json::array();
    cola_Lote *aux = cola_lote;
    while (aux != NULL)
    {
        j.push_back(estructuraLoteAJSON(aux->lote));
        aux = aux->siguiente;
    }
    return j;
}
json estructuraInformacionMesAJSON(Informacion_Mes *mes_actual)
{
    json j;
    j["mes"] = mes_actual->mes;
    j["lotes"] = agregarListaLote(mes_actual->lotes);
    j["lotes_cantidad"] = mes_actual->lotes_cantidad;
    return j;
}
json agregarInformacionMes(Informacion_Mes *mes)
{
    json j = json::array();
    for (int i = 0; i < 12; i++)
    {
        if (mes[i].lotes != NULL)
        {
            j.push_back(estructuraInformacionMesAJSON(&mes[i]));
        }
    }
    return j;
}
json estructuraListaAnoAJSON(Ano_Producto &ano_producto)
{
    json j;
    j["ano"] = ano_producto.ano;
    j["informacion_mes"] = agregarInformacionMes(ano_producto.producto);
    return j;
}
json agregarListaAno(Lista_Ano *lista_ano)
{
    json j = json::array();
    Lista_Ano *aux = lista_ano;
    while (aux != NULL)
    {
        j.push_back(estructuraListaAnoAJSON(aux->ano_producto));
        aux = aux->siguiente;
    }
    return j;
}
json estructuraProductoAJSON(Producto &producto)
{
    json j;
    j["id_producto"] = producto.id_producto;
    j["nombre_producto"] = producto.nombre_producto;
    j["descripcion_producto"] = producto.descripcion_producto;
    j["existencia_cantidad"] = producto.existencia_cantidad;
    j["minima_cantidad"] = producto.minima_cantidad;
    bool anulado = (producto.anulado);
    j["anulado"] = (anulado) ? "Si" : "No";
    j["lista_ano"] = agregarListaAno(producto.anos_producto);
    j["costo_de_venta_total"] = producto.costo_de_venta_total;
    j["porcentaje_ganancia"] = producto.porcentaje_ganancia;
    return j;
}

json listaProductoAJSON(lista_Producto *lista_producto)
{
    json j = json::array();
    lista_Producto *aux = lista_producto;
    while (aux != NULL)
    {
        j.push_back(estructuraProductoAJSON(aux->producto));
        aux = aux->siguiente;
    }
    return j;
}
void escribirProductosEnArchivoJSON(lista_Producto *lista_producto)
{
    std::ofstream file("productos.json");
    if (file.is_open())
    {
        json j = listaProductoAJSON(lista_producto);
        file << j.dump(4);
        file.close();
    }
}
char *agregarPuntero(std::string texto, const json &item)
{
    if (!item.contains(texto))
    {
        return NULL;
    }
    std::string information = item[texto].get<std::string>();
    char *dato = new char[information.length() + 1];
    strcpy(dato, information.c_str());
    return dato;
}
void guardarAnoEnLista(lista_Producto *&producto_actual, Lista_Ano *&ano_actual)
{
    Lista_Ano *aux = producto_actual->producto.anos_producto; // Reservamos el valor original de la lista
    Lista_Ano *aux2;
    while (aux != NULL)
    {                         // Comprobamos que aux no apunte a null
        aux2 = aux;           // Reservamos el valor original de aux que por ahora es la lista
        aux = aux->siguiente; // Corre una posición, buscando NULL
    }
    if (producto_actual->producto.anos_producto == aux)
    { // Nunca pasó por el while
        producto_actual->producto.anos_producto = ano_actual;
    }
    else
    { // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
        aux2->siguiente = ano_actual;
    }
    ano_actual->siguiente = aux; // nuevo_producto apunta a NULL
}
Fecha leerFecha(const json &item)
{
    Fecha fecha;
    fecha.dia = item["dia"].get<int>();
    fecha.mes = item["mes"].get<int>();
    fecha.ano = item["ano"].get<int>();
    return fecha;
}
void agregarListaAno(lista_Producto *&producto_actual, const json &item)
{

    if (item.contains("lista_ano") && item["lista_ano"].is_array())
    {

        for (const json &year_item : item["lista_ano"])
        {

            Lista_Ano *nuevo_ano = new Lista_Ano();
            nuevo_ano->ano_producto.ano = year_item["ano"].get<int>();
            if (year_item.contains("informacion_mes") && year_item["informacion_mes"].is_array())
            {

                for (const json &month_item : year_item["informacion_mes"])
                {
                    int mes = month_item["mes"].get<int>();
                    Informacion_Mes *mes_actual = &nuevo_ano->ano_producto.producto[mes - 1];
                    mes_actual->mes = month_item["mes"].get<int>();
                    if (month_item.contains("lotes") && month_item["lotes"].is_array())
                    {

                        for (const json &lot_item : month_item["lotes"])
                        {
                            cola_Lote *nuevo_lote = new cola_Lote();
                            nuevo_lote->lote.id_lote = agregarPuntero("id_lote", lot_item);
                            nuevo_lote->lote.ingreso_fecha = leerFecha(lot_item["ingreso_fecha"]);
                            nuevo_lote->lote.expiracion_fecha = leerFecha(lot_item["expiracion_fecha"]);
                            nuevo_lote->lote.cantidad_de_producto = lot_item["cantidad_de_producto"].get<int>();
                            nuevo_lote->lote.precio_producto = lot_item["precio_producto"].get<double>();
                            bool validacion = (lot_item["validacion"].get<std::string>() == "Si");
                            nuevo_lote->lote.validacion = validacion;
                            nuevo_lote->lote.motivo = lot_item["motivo"].get<int>();
                            nuevo_lote->lote.costo_venta = lot_item["costo_venta"].get<double>();

                            guardarLoteEnProducto(mes_actual, nuevo_lote);
                        }
                    }
                    mes_actual->lotes_cantidad = month_item["lotes_cantidad"].get<int>();
                }
            }
            guardarAnoEnLista(producto_actual, nuevo_ano);
        }
    }
}
void leerProductosDeArchivo(lista_Producto *&lista_producto)
{
    std::ifstream file("productos.json");
    if (file.is_open())
    {
        json j;
        file >> j;
        for (const auto &item : j)
        {
            lista_Producto *nuevo_producto = new lista_Producto();
            nuevo_producto->producto.id_producto = item["id_producto"].get<int>();
            nuevo_producto->producto.nombre_producto = agregarPuntero("nombre_producto", item);
            nuevo_producto->producto.descripcion_producto = agregarPuntero("descripcion_producto", item);
            agregarListaAno(nuevo_producto, item);
            nuevo_producto->producto.existencia_cantidad = item["existencia_cantidad"].get<int>();
            nuevo_producto->producto.minima_cantidad = item["minima_cantidad"].get<int>();
            bool anulado = (item["anulado"].get<std::string>() == "Si");
            nuevo_producto->producto.anulado = anulado;
            nuevo_producto->producto.costo_de_venta_total = item["costo_de_venta_total"].get<double>();
            nuevo_producto->producto.porcentaje_ganancia = item["porcentaje_ganancia"].get<double>();
            guardarProductoEnLista(lista_producto, nuevo_producto);
            conteo_id_producto++;
        }
    }
    file.close();
}

json estructuraUsuarioAJSON(Usuario &usuario)
{
    json j;
    j["nombres"] = usuario.nombres;
    j["apellidos"] = usuario.apellidos;
    j["telefono"] = usuario.telefono;
    j["correo"] = usuario.correo;
    j["contrasena"] = usuario.contrasena;
    j["validacion"] = (usuario.validacion) ? "Si" : "No";
    j["administrador"] = (usuario.administrador) ? "Si" : "No";
    return j;
}
json listaUsuariosAJSON(lista_Usuario *&lista_usuario)
{
    lista_Usuario *aux = lista_usuario->siguiente;
    json j = json::array();
    while (aux != NULL)
    {
        j.push_back(estructuraUsuarioAJSON(aux->usuario));
        aux = aux->siguiente;
    }
    return j;
}
void escribirUsuariosAJSON(lista_Usuario *&lista_usuario)
{
    std::ofstream archivo_usuario("usuarios.json");
    if (archivo_usuario.is_open())
    {
        json j = listaUsuariosAJSON(lista_usuario);
        archivo_usuario << j.dump(6);
        archivo_usuario.close();
    }
}
void leerUsuariosEnJSON(lista_Usuario *&lista_usuario)
{
    std::ifstream archivo_usuario_lectura("usuarios.json");
    if (archivo_usuario_lectura.is_open())
    {
        json j;
        archivo_usuario_lectura >> j;
        for (const auto &usuario : j)
        {
            lista_Usuario *nuevo_usuario = new lista_Usuario();
            nuevo_usuario->usuario.nombres = agregarPuntero("nombres", usuario);
            nuevo_usuario->usuario.apellidos = agregarPuntero("apellidos", usuario);
            nuevo_usuario->usuario.telefono = usuario["telefono"].get<int>();
            nuevo_usuario->usuario.correo = agregarPuntero("correo", usuario);
            nuevo_usuario->usuario.contrasena = agregarPuntero("contrasena", usuario);
            bool validacion = (usuario["validacion"].get<std::string>() == "Si");
            nuevo_usuario->usuario.validacion = validacion;
            bool administrador = (usuario["administrador"].get<std::string>() == "Si");
            nuevo_usuario->usuario.administrador  = administrador;
            guardarUsuario(nuevo_usuario);
        }
    }
}

void guardarUsuario(lista_Usuario *&nuevo_usuario)
{
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
