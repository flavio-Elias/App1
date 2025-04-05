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


MetricEntry metric_table[] = {
    {"pms", pms},
    {"pls", pls},
    {"dms", dms},
    {"dls", dls},
    {NULL, NULL}
};
