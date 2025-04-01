// csv_reader.c - Implementación de la lectura del CSV
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_reader.h"

#define MAX_LINE_LENGTH 512

int read_csv(const char *filename, struct order **orders) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s\n", filename);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;
    struct order *temp_orders = malloc(sizeof(struct order) * 1000); // Reserva inicial
    if (!temp_orders) {
        printf("Error: No se pudo asignar memoria.\n");
        fclose(file);
        return -1;
    }

    fgets(line, MAX_LINE_LENGTH, file); // Leer y descartar encabezado
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        struct order o;
        sscanf(line, "%d,%d,%49[^,],%d,%19[^,],%9[^,],%f,%f,%4[^,],%19[^,],%199[^,],%49[^"]",
               &o.pizza_id, &o.order_id, o.pizza_name_id, &o.quantity, o.order_date, o.order_time,
               &o.unit_price, &o.total_price, o.pizza_size, o.pizza_category, o.pizza_ingredients, o.pizza_name);
        temp_orders[count++] = o;
    }

    fclose(file);
    *orders = realloc(temp_orders, sizeof(struct order) * count);
    return count;
}
