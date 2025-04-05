#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_reader.h"
#include "orders.h"

#define MAX_LINE_LENGTH 1024

// Limpia comillas externas de un campo, si las tiene
char* clean_field(const char *field) {
    size_t len = strlen(field);
    if (len >= 2 && field[0] == '"' && field[len - 1] == '"') {
        char *cleaned = malloc(len - 1);
        strncpy(cleaned, field + 1, len - 2);
        cleaned[len - 2] = '\0';
        return cleaned;
    } else {
        return strdup(field);
    }
}

// Parser robusto que respeta comas dentro de comillas
int split_csv_line(const char *line, char ***fields_out) {
    int capacity = 16;
    char **fields = malloc(capacity * sizeof(char*));
    int field_index = 0;

    const char *p = line;
    char field_buffer[1024];
    int buf_index = 0;
    int in_quotes = 0;

    while (*p) {
        if (*p == '"') {
            in_quotes = !in_quotes;
        } else if (*p == ',' && !in_quotes) {
            field_buffer[buf_index] = '\0';
            fields[field_index++] = strdup(field_buffer);
            buf_index = 0;
        } else {
            field_buffer[buf_index++] = *p;
        }
        p++;
    }

    field_buffer[buf_index] = '\0';
    fields[field_index++] = strdup(field_buffer);

    *fields_out = fields;
    return field_index;
}

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

    // Saltar encabezado
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

        line[strcspn(line, "\n")] = '\0';

        char **fields = NULL;
        int n = split_csv_line(line, &fields);
        if (n != 12) {
            fprintf(stderr, "Error: se esperaban 12 campos, se encontraron %d\n", n);
            for (int i = 0; i < n; i++) free(fields[i]);
            free(fields);
            continue;
        }

        orders[count].pizza_id           = clean_field(fields[0]);
        orders[count].order_id           = clean_field(fields[1]);
        orders[count].pizza_name_id      = clean_field(fields[2]);
        orders[count].quantity           = atoi(fields[3]);
        orders[count].order_date         = clean_field(fields[4]);
        orders[count].order_time         = clean_field(fields[5]);
        orders[count].unit_price         = atof(fields[6]);
        orders[count].total_price        = atof(fields[7]);
        orders[count].pizza_size         = clean_field(fields[8]);
        orders[count].pizza_category     = clean_field(fields[9]);
        orders[count].pizza_ingredients  = clean_field(fields[10]);
        orders[count].pizza_name         = clean_field(fields[11]);


        for (int i = 0; i < n; i++) free(fields[i]);
        free(fields);

        count++;
    }

    fclose(file);
    *num_orders = count;
    return orders;
}