#include <iostream>
#include <cstdlib>
#include <string.h>
char input[250];

int conteo_id_producto = 3;

char *generarIdLote(int dia, int mes, int año);

int main()
{
    char *id_lote = generarIdLote(5, 3, 2023);
    std::cout << id_lote;
    delete[] id_lote;
    return 0;
}

char *generarIdLote(int dia, int mes, int año)
{
    char id[20];
    int incremental = 3;
    sprintf(id,"%d%02d%02d%d%d", conteo_id_producto, dia, mes, año %100, incremental);
    char *id_total = new char[strlen(id)+1];
    strcpy(id_total,id);
    return id_total;
}