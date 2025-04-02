#include "csv_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

Order* read_csv(const char* filename, int* order_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file); // Ignorar la primera línea (encabezados)

    Order* orders = malloc(sizeof(Order) * 1000); // Capacidad inicial
    int count = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        Order order;
        char* temp_line = strdup(line); // Create a copy for strtok operations
        char* token;

        // Parse pizza_id
        token = strtok(temp_line, ",");
        if (token) {
            char* endptr;
            order.pizza_id = strtol(token, &endptr, 10);
            if (*endptr != '\0' && *endptr != '\r' && *endptr != '\n') {
                printf("Error al convertir pizza_id: %s\n", token);
                free(temp_line);
                continue;
            }
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse order_id
        token = strtok(NULL, ",");
        if (token) {
            char* endptr;
            order.order_id = strtol(token, &endptr, 10);
            if (*endptr != '\0' && *endptr != '\r' && *endptr != '\n') {
                printf("Error al convertir order_id: %s\n", token);
                free(temp_line);
                continue;
            }
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse pizza_name_id
        token = strtok(NULL, ",");
        if (token) {
            strncpy(order.pizza_name_id, token, sizeof(order.pizza_name_id) - 1);
            order.pizza_name_id[sizeof(order.pizza_name_id) - 1] = '\0';
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse quantity
        token = strtok(NULL, ",");
        if (token) {
            char* endptr;
            order.quantity = strtol(token, &endptr, 10);
            if (*endptr != '\0' && *endptr != '\r' && *endptr != '\n') {
                printf("Error al convertir quantity: %s\n", token);
                free(temp_line);
                continue;
            }
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse order_date
        token = strtok(NULL, ",");
        if (token) {
            strncpy(order.order_date, token, sizeof(order.order_date) - 1);
            order.order_date[sizeof(order.order_date) - 1] = '\0';
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse order_time
        token = strtok(NULL, ",");
        if (token) {
            strncpy(order.order_time, token, sizeof(order.order_time) - 1);
            order.order_time[sizeof(order.order_time) - 1] = '\0';
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse unit_price
        token = strtok(NULL, ",");
        if (token) {
            order.unit_price = (float)atof(token);
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse total_price
        token = strtok(NULL, ",");
        if (token) {
            order.total_price = (float)atof(token);
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse pizza_size
        token = strtok(NULL, ",");
        if (token && strlen(token) > 0) {
            order.pizza_size = token[0];
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse pizza_category
        token = strtok(NULL, ",");
        if (token) {
            strncpy(order.pizza_category, token, sizeof(order.pizza_category) - 1);
            order.pizza_category[sizeof(order.pizza_category) - 1] = '\0';
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        // Parse pizza_ingredients - this field may contain commas within quotes
        token = strtok(NULL, "\"");  // Skip to the opening quote
        token = strtok(NULL, "\"");  // Get content between quotes
        if (token) {
            strncpy(order.pizza_ingredients, token, sizeof(order.pizza_ingredients) - 1);
            order.pizza_ingredients[sizeof(order.pizza_ingredients) - 1] = '\0';
        } else {
            // Try without quotes if quotes aren't present
            token = strtok(NULL, ",");
            if (token) {
                strncpy(order.pizza_ingredients, token, sizeof(order.pizza_ingredients) - 1);
                order.pizza_ingredients[sizeof(order.pizza_ingredients) - 1] = '\0';
            } else {
                printf("Error: formato CSV inválido\n");
                free(temp_line);
                continue;
            }
        }

        // Parse pizza_name - the last field
        token = strtok(NULL, "\r\n");
        if (token) {
            // Remove leading comma if present
            if (token[0] == ',') token++;
            strncpy(order.pizza_name, token, sizeof(order.pizza_name) - 1);
            order.pizza_name[sizeof(order.pizza_name) - 1] = '\0';
        } else {
            printf("Error: formato CSV inválido\n");
            free(temp_line);
            continue;
        }

        free(temp_line);

        // Verificación de los datos leídos
        printf("Leída orden: pizza_name_id=%s, quantity=%d, total_price=%.2f\n",
               order.pizza_name_id, order.quantity, order.total_price);

        orders[count++] = order;
    }

    fclose(file);
    *order_count = count;
    return orders;
}