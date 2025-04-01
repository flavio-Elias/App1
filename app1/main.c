// main.c - Punto de entrada del programa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_reader.h"
#include "metrics.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <archivo_csv> <metrica1> [metrica2 ...]\n", argv[0]);
        return 1;
    }

    struct order *orders = NULL;
    int total_orders = read_csv(argv[1], &orders);
    if (total_orders <= 0) {
        printf("Error al leer el archivo CSV.\n");
        return 1;
    }

    // Arreglo de métricas
    metric_function metrics[] = {
        most_sold_pizza,
        least_sold_pizza,
        date_most_sales_money,
        date_least_sales_money,
        date_most_sales_quantity,
        date_least_sales_quantity,
        avg_pizzas_per_order,
        avg_pizzas_per_day,
        most_sold_ingredient,
        pizzas_per_category
    };

    // Mapear nombres de métricas a funciones
    const char *metric_names[] = {
        "pms", "pls", "dms", "dls", "dmsp", "dlsp", "apo", "apd", "ims", "hp"
    };

    // Ejecutar métricas según argumentos
    for (int i = 2; i < argc; i++) {
        for (int j = 0; j < 10; j++) {
            if (strcmp(argv[i], metric_names[j]) == 0) {
                int size;
                char *result = metrics[j](&size, orders);
                printf("%s\n", result);
                free(result);
            }
        }
    }

    free(orders);
    return 0;
}
