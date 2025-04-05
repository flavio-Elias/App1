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
    int count;
} DateSales;

void aggregate_sales_by_date(int size, Order *orders, DateSales **sales_out, DateSales **counts_out, int *count_out) {
    DateSales *sales = NULL;
    DateSales *counts = NULL;
    int sales_count = 0; // Contador para sales
    int counts_count = 0; // Contador para counts

    for (int i = 0; i < size; i++) {
        int found_1 = 0;
        int found_2 = 0;
        
        // Buscar en 'sales' y actualizar el total de ventas
        for (int j = 0; j < sales_count; j++) {
            if (strcmp(sales[j].date, orders[i].order_date) == 0) {
                sales[j].total += orders[i].total_price;
                found_1 = 1;
                break;
            }
        }

        // Si no se encontró la fecha, agregarla
        if (!found_1) {
            sales = realloc(sales, (sales_count + 1) * sizeof(DateSales));
            sales[sales_count].date = strdup(orders[i].order_date);
            sales[sales_count].total = orders[i].total_price;
            sales_count++;
        }

        // Buscar en 'counts' y actualizar el número de pedidos
        for (int j = 0; j < counts_count; j++) {
            if (strcmp(counts[j].date, orders[i].order_date) == 0) {
                counts[j].count++;  // Contar el número de pedidos
                found_2 = 1;
                break;
            }
        }

        // Si no se encontró la fecha, agregarla con un conteo de 1
        if (!found_2) {
            counts = realloc(counts, (counts_count + 1) * sizeof(DateSales));
            counts[counts_count].date = strdup(orders[i].order_date);
            counts[counts_count].count = 1;
            counts_count++;
        }
    }


    *sales_out = sales;
    *counts_out = counts;
    *count_out = sales_count;
    }


char* dms(int *size, Order *orders) {
    int count;
    DateSales *sales = NULL;
    DateSales *counts = NULL;

    aggregate_sales_by_date(*size, orders, &sales, &counts, &count);

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
    free(counts);

    char *result = malloc(64);
    snprintf(result, 64, "%s ($%.2f)", best_date, max);
    free(best_date);
    return result;
    }

char* dls(int *size, Order *orders) {
    int count;
    DateSales *sales = NULL;
    DateSales *counts = NULL;
    aggregate_sales_by_date(*size, orders, &sales, &counts, &count);

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
    free(counts);

    char *result = malloc(64);
    snprintf(result, 64, "%s ($%.2f)", worst_date, min);
    free(worst_date);
    return result;
}
///////KMS
///ARREGLAR STRING TEXTO EXTRA :C
char* dmsp(int *size, Order *orders) {
    int count;
    DateSales *sales = NULL;
    DateSales *counts = NULL;
    aggregate_sales_by_date(*size, orders, &sales, &counts, &count);

    int max_count = counts[0].count;
    char *fecha_max = strdup(counts[0].date);

    for (int i = 1; i < count; i++) {
        if (counts[i].count > max_count) {
            max_count = counts[i].count;
            free(fecha_max);
            fecha_max = strdup(counts[i].date);
        }
    }

    // Limpiar
    free(sales);
    free(counts);

    char *result = malloc(128);
    snprintf(result, 128, "Más ventas: %s (%d)", fecha_max, max_count);
    free(fecha_max);
    return result;
}

///////KMS 2 ELECTRIC BOOGALOO
///ARREGLAR STRING TEXTO EXTRA :C

char* dlsp(int *size, Order *orders) {
    int count;
    DateSales *sales = NULL;
    DateSales *counts = NULL;
    aggregate_sales_by_date(*size, orders, &sales, &counts, &count);

    int min_count = counts[0].count;
    char *fecha_min = strdup(counts[0].date);

    for (int i = 1; i < count; i++) {
        
        if (counts[i].count < min_count) {
            min_count = counts[i].count;
            free(fecha_min);
            fecha_min = strdup(counts[i].date);
        }
    }

    for (int i = 0; i < count; i++) {
        free(counts[i].date);
    }
    free(sales);
    free(counts);

    char *result = malloc(128);
    snprintf(result, 128, "Menos ventas: %s (%d)", fecha_min, min_count);
    free(fecha_min);
    return result;
}


/// 
MetricEntry metric_table[] = {
    {"pms", pms},
    {"pls", pls},
    {"dms", dms},
    {"dls", dls},
    {"dmsp", dmsp},
    {"dlsp", dlsp},
    {NULL, NULL}
};
