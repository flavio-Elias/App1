// csv_reader.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_reader.h"
#include "orders.h"

#define MAX_LINE_LENGTH 1024

Order* read_csv(const char *filename, int *num_orders) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error abriendo archivo");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int capacity = 100;
    int count = 0;
    Order *orders = malloc(capacity * sizeof(Order));
    if (!orders) {
        perror("Error reservando memoria");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Saltar la primera línea (encabezados)
    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (count >= capacity) {
            capacity *= 2;
            orders = realloc(orders, capacity * sizeof(Order));
            if (!orders) {
                perror("Error al redimensionar memoria");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }

        // Eliminar salto de línea
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        orders[count].pizza_id = strdup(token);

        token = strtok(NULL, ",");
        orders[count].order_id = strdup(token);

        token = strtok(NULL, ",");
        orders[count].pizza_name_id = strdup(token);

        token = strtok(NULL, ",");
        orders[count].quantity = atoi(token);

        token = strtok(NULL, ",");
        orders[count].order_date = strdup(token);

        token = strtok(NULL, ",");
        orders[count].order_time = strdup(token);

        token = strtok(NULL, ",");
        orders[count].unit_price = atof(token);

        token = strtok(NULL, ",");
        orders[count].total_price = atof(token);

        token = strtok(NULL, ",");
        orders[count].pizza_size = strdup(token);

        token = strtok(NULL, ",");
        orders[count].pizza_category = strdup(token);

        token = strtok(NULL, ",");
        orders[count].pizza_ingredients = strdup(token);

        token = strtok(NULL, ",");
        orders[count].pizza_name = strdup(token);

        count++;
    }

    fclose(file);
    *num_orders = count;
    return orders;
}
