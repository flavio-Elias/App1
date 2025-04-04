// metrics.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "metrics.h"

typedef struct {
    char *pizza_name;
    int total_quantity;
} PizzaSales;

char* pms(int *size, Order *orders) {
    int count = *size;
    PizzaSales *sales = NULL;
    int sales_count = 0;

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < sales_count; j++) {
            if (strcmp(sales[j].pizza_name, orders[i].pizza_name) == 0) {
                sales[j].total_quantity += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            sales = realloc(sales, (sales_count + 1) * sizeof(PizzaSales));
            sales[sales_count].pizza_name = strdup(orders[i].pizza_name);
            sales[sales_count].total_quantity = orders[i].quantity;
            sales_count++;
        }
    }

    char *top_pizza = NULL;
    int max_qty = -1;

    for (int i = 0; i < sales_count; i++) {
        if (sales[i].total_quantity > max_qty) {
            max_qty = sales[i].total_quantity;
            top_pizza = sales[i].pizza_name;
        } else {
            free(sales[i].pizza_name);
        }
    }

    free(sales);
    char *result = malloc(strlen(top_pizza) + 1);
    strcpy(result, top_pizza);
    return result;
}

char* pls(int *size, Order *orders) {
    int count = *size;
    PizzaSales *sales = NULL;
    int sales_count = 0;

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < sales_count; j++) {
            if (strcmp(sales[j].pizza_name, orders[i].pizza_name) == 0) {
                sales[j].total_quantity += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            sales = realloc(sales, (sales_count + 1) * sizeof(PizzaSales));
            sales[sales_count].pizza_name = strdup(orders[i].pizza_name);
            sales[sales_count].total_quantity = orders[i].quantity;
            sales_count++;
        }
    }

    char *least_pizza = NULL;
    int min_qty = INT_MAX;

    for (int i = 0; i < sales_count; i++) {
        if (sales[i].total_quantity < min_qty) {
            min_qty = sales[i].total_quantity;
            least_pizza = sales[i].pizza_name;
        } else {
            free(sales[i].pizza_name);
        }
    }

    free(sales);
    char *result = malloc(strlen(least_pizza) + 1);
    strcpy(result, least_pizza);
    return result;
}

// Tabla de métricas
MetricEntry metric_table[] = {
    {"pms", pms},
    {"pls", pls},
    // {"dms", dms}, ...
    {NULL, NULL} // Terminador
};
