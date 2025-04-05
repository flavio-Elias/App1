#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "metrics.h"



typedef struct {
    char *pizza_name;
    int total_quantity;
} PizzaSales;

PizzaSales* count_pizza_sales(int size, Order *orders, int *count_out) {
    PizzaSales *sales = NULL;
    int count = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(sales[j].pizza_name, orders[i].pizza_name) == 0) {
                sales[j].total_quantity += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            sales = realloc(sales, (count + 1) * sizeof(PizzaSales));
            sales[count].pizza_name = strdup(orders[i].pizza_name);
            sales[count].total_quantity = orders[i].quantity;
            count++;
        }
    }

    *count_out = count;
    return sales;
}

char* pms(int *size, Order *orders) {
    int count;
    PizzaSales *sales = count_pizza_sales(*size, orders, &count);

    int max = -1;
    char *result = NULL;

    for (int i = 0; i < count; i++) {
        if (sales[i].total_quantity > max) {
            max = sales[i].total_quantity;
            if (result) free(result);
            result = strdup(sales[i].pizza_name);
        }
        free(sales[i].pizza_name);
    }

    free(sales);
    return result;
}

char* pls(int *size, Order *orders) {
    int count;
    PizzaSales *sales = count_pizza_sales(*size, orders, &count);

    int min = INT_MAX;
    char *result = NULL;

    for (int i = 0; i < count; i++) {
        if (sales[i].total_quantity < min) {
            min = sales[i].total_quantity;
            if (result) free(result);
            result = strdup(sales[i].pizza_name);
        }
        free(sales[i].pizza_name);
    }

    free(sales);
    return result;
}

// ---------------------- DATE SALES ------------------------

typedef struct {
    char *date;
    float total;
} DateSales;

DateSales* aggregate_sales_by_date(int size, Order *orders, int *count_out) {
    DateSales *sales = NULL;
    int count = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(sales[j].date, orders[i].order_date) == 0) {
                sales[j].total += orders[i].total_price;
                found = 1;
                break;
            }
        }
        if (!found) {
            sales = realloc(sales, (count + 1) * sizeof(DateSales));
            sales[count].date = strdup(orders[i].order_date);
            sales[count].total = orders[i].total_price;
            count++;
        }
    }

    *count_out = count;
    return sales;
}

char* dms(int *size, Order *orders) {
    int count;
    DateSales *sales = aggregate_sales_by_date(*size, orders, &count);

    float max = -1.0;
    char *best_date = NULL;

    for (int i = 0; i < count; i++) {
        if (sales[i].total > max) {
            max = sales[i].total;
            if (best_date) free(best_date);
            best_date = strdup(sales[i].date);
        }
        free(sales[i].date);
    }

    free(sales);

    char *result = malloc(64);
    snprintf(result, 64, "%s ($%.2f)", best_date, max);
    free(best_date);
    return result;
}

char* dls(int *size, Order *orders) {
    int count;
    DateSales *sales = aggregate_sales_by_date(*size, orders, &count);

    float min = sales[0].total;
    char *worst_date = strdup(sales[0].date);

    for (int i = 1; i < count; i++) {
        if (sales[i].total < min) {
            min = sales[i].total;
            free(worst_date);
            worst_date = strdup(sales[i].date);
        }
        free(sales[i].date);
    }

    free(sales);

    char *result = malloc(64);
    snprintf(result, 64, "%s ($%.2f)", worst_date, min);
    free(worst_date);
    return result;
}

char* hp(int *size, Order *orders) {
    typedef struct {
        char category[64];
        int count;
    } CategoryCount;

    CategoryCount counts[100];
    int count_size = 0;

    for (int i = 0; i < *size; i++) {
        char *category = orders[i].pizza_category;

        // Ver si ya existe
        int found = 0;
        for (int j = 0; j < count_size; j++) {
            if (strcmp(counts[j].category, category) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }

        // Si no se encontró, agregar nueva categoría
        if (!found && count_size < 100) {
            strncpy(counts[count_size].category, category, 63);
            counts[count_size].category[63] = '\0'; // Asegurar terminación
            counts[count_size].count = 1;
            count_size++;
        }
    }

    // Construir resultado como string
    char *result = malloc(1024); // tamaño fijo, ajusta si necesitas más
    result[0] = '\0';

    for (int i = 0; i < count_size; i++) {
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "%s: %d", counts[i].category, counts[i].count);
        strcat(result, buffer);
        if (i < count_size - 1) strcat(result, " | ");
    }

    return result;
}


char* apd(int *size, Order *orders) {
    char dates[1000][64]; // lista de fechas únicas
    int unique_days = 0;

    for (int i = 0; i < *size; i++) {
        char *date = orders[i].order_date;

        // Ver si ya está en la lista
        int found = 0;
        for (int j = 0; j < unique_days; j++) {
            if (strcmp(dates[j], date) == 0) {
                found = 1;
                break;
            }
        }

        // Si no está, agregarla
        if (!found && unique_days < 1000) {
            strncpy(dates[unique_days], date, 63);
            dates[unique_days][63] = '\0';
            unique_days++;
        }
    }

    int total_pizzas = *size;
    float average = (float)total_pizzas / unique_days;

    // Crear string de salida
    char *result = malloc(64);
    snprintf(result, 64, "%.2f", average);
    return result;
}


char* apo(int *size, Order *orders) {
    char order_ids[1000][64]; // lista de IDs únicos
    int unique_count = 0;

    for (int i = 0; i < *size; i++) {
        char *oid = orders[i].order_id;

        // Ver si ya lo tenemos
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(order_ids[j], oid) == 0) {
                found = 1;
                break;
            }
        }

        // Si no lo tenemos, agregarlo
        if (!found && unique_count < 1000) {
            strncpy(order_ids[unique_count], oid, 63);
            order_ids[unique_count][63] = '\0';
            unique_count++;
        }
    }

    int total_pizzas = *size;
    int total_orders = unique_count;

    float average = (float)total_pizzas / total_orders;

    // Crear string de salida
    char *result = malloc(64);
    snprintf(result, 64, "%.2f", average);
    return result;
}

MetricEntry metric_table[] = {
    {"pms", pms},
    {"pls", pls},
    {"dms", dms},
    {"dls", dls},
    {"hp", hp},
    {"apd", apd},
    {"apo", apo},
    {NULL, NULL}
};
