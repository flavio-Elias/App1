#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orders.h"
#include "csv_reader.h"
#include "metrics.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <archivo.csv> <métricas...>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    int num_orders = 0;
    Order *orders = read_csv(filename, &num_orders);

    for (int i = 2; i < argc; i++) {
        char *metric_name = argv[i];
        int found = 0;

        for (int j = 0; metric_table[j].name != NULL; j++) {
            if (strcmp(metric_table[j].name, metric_name) == 0) {
                char *result = metric_table[j].func(&num_orders, orders);

                // Mensajes personalizados
                if (strcmp(metric_name, "pms") == 0) {
                    printf("Pizza más vendida: %s\n", result);
                } else if (strcmp(metric_name, "pls") == 0) {
                    printf("Pizza menos vendida: %s\n", result);
                } else if (strcmp(metric_name, "dms") == 0) {
                    printf("Fecha con más ventas: %s\n", result);
                } else if (strcmp(metric_name, "dls") == 0) {
                    printf("Fecha con menos ventas: %s\n", result);
                } else if (strcmp(metric_name, "apd") == 0) {
                    printf("Cantidad de pizzas vendidas por fecha:\n %s\n", result);
                } else if (strcmp(metric_name, "hp") == 0) {
                    printf("Cantidad de pizzas vendidas según categoria: %s\n", result);
                } else {
                    printf("%s: %s\n", metric_name, result); // fallback
                }

                free(result);
                found = 1;
                break;
            }
        }

        if (!found) {
            fprintf(stderr, "Métrica desconocida: %s\n", metric_name);
        }
    }

    free_orders(orders, num_orders);
    return EXIT_SUCCESS;
}
