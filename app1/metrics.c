/* metrics.c */
#include "metrics.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* most_sold_pizza(int* size, Order* orders) {
    // Check for valid input
    if (*size <= 0 || orders == NULL) {
        return strdup("No hay datos de pizzas");
    }

    // Create arrays to track unique pizzas and their counts
    char pizza_names[1000][50];
    int pizza_counts[1000] = {0};
    int unique_pizzas = 0;

    // Count pizza occurrences by name_id, accounting for quantity
    for (int i = 0; i < *size; i++) {
        // Debug
        printf("Procesando: %s (cantidad: %d)\n", orders[i].pizza_name_id, orders[i].quantity);

        // Look for this pizza in our existing list
        int found = -1;
        for (int j = 0; j < unique_pizzas; j++) {
            if (strcmp(orders[i].pizza_name_id, pizza_names[j]) == 0) {
                found = j;
                break;
            }
        }

        // Add to existing entry or create new one
        if (found >= 0) {
            pizza_counts[found] += orders[i].quantity;
        } else {
            strncpy(pizza_names[unique_pizzas], orders[i].pizza_name_id, 49);
            pizza_names[unique_pizzas][49] = '\0';
            pizza_counts[unique_pizzas] = orders[i].quantity;
            unique_pizzas++;
        }
    }

    // Debug output
    printf("Conteo final de pizzas:\n");
    for (int i = 0; i < unique_pizzas; i++) {
        printf("  %s: %d unidades\n", pizza_names[i], pizza_counts[i]);
    }

    // Find the pizza with highest count
    if (unique_pizzas == 0) {
        return strdup("No hay datos de pizzas");
    }

    int max_index = 0;
    for (int i = 1; i < unique_pizzas; i++) {
        if (pizza_counts[i] > pizza_counts[max_index]) {
            max_index = i;
        }
    }

    // Prepare result
    char* result = malloc(100);
    if (!result) {
        return strdup("Error de memoria");
    }

    sprintf(result, "Pizza más vendida: %s con %d unidades",
            pizza_names[max_index], pizza_counts[max_index]);

    return result;
}