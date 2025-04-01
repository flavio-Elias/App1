// metrics.c - Implementación de métricas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metrics.h"

// Función para calcular la pizza más vendida
char* most_sold_pizza(int *size, struct order *orders) {
    int max_quantity = 0;
    char *best_seller = malloc(50);
    if (!best_seller) return NULL;

    for (int i = 0; i < *size; i++) {
        if (orders[i].quantity > max_quantity) {
            max_quantity = orders[i].quantity;
            strcpy(best_seller, orders[i].pizza_name);
        }
    }
    return best_seller;
}

// Función para calcular la pizza menos vendida
char* least_sold_pizza(int *size, struct order *orders) {
    int min_quantity = __INT_MAX__;
    char *least_seller = malloc(50);
    if (!least_seller) return NULL;

    for (int i = 0; i < *size; i++) {
        if (orders[i].quantity < min_quantity) {
            min_quantity = orders[i].quantity;
            strcpy(least_seller, orders[i].pizza_name);
        }
    }
    return least_seller;
}

// Función para calcular la fecha con más ventas en dinero
char* date_most_sales_money(int *size, struct order *orders) {
    char *best_date = malloc(20);
    float max_revenue = 0;
    if (!best_date) return NULL;

    for (int i = 0; i < *size; i++) {
        if (orders[i].total_price > max_revenue) {
            max_revenue = orders[i].total_price;
            strcpy(best_date, orders[i].order_date);
        }
    }
    return best_date;
}

// Función para calcular la fecha con menos ventas en dinero
char* date_least_sales_money(int *size, struct order *orders) {
    char *worst_date = malloc(20);
    float min_revenue = __FLT_MAX__;
    if (!worst_date) return NULL;

    for (int i = 0; i < *size; i++) {
        if (orders[i].total_price < min_revenue) {
            min_revenue = orders[i].total_price;
            strcpy(worst_date, orders[i].order_date);
        }
    }
    return worst_date;
}

// Función para calcular el promedio de pizzas por orden
char* avg_pizzas_per_order(int *size, struct order *orders) {
    float total_pizzas = 0;
    int total_orders = 0;
    char *result = malloc(50);
    if (!result) return NULL;

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
        total_orders++;
    }

    snprintf(result, 50, "%.2f", total_pizzas / total_orders);
    return result;
}

// Función para calcular el promedio de pizzas por día
char* avg_pizzas_per_day(int *size, struct order *orders) {
    float total_pizzas = 0;
    int total_days = 0;
    char *result = malloc(50);
    if (!result) return NULL;

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
        total_days++;
    }

    snprintf(result, 50, "%.2f", total_pizzas / total_days);
    return result;
}

// Función para calcular el ingrediente más vendido
char* most_sold_ingredient(int *size, struct order *orders) {
    char *best_ingredient = malloc(200);
    if (!best_ingredient) return NULL;
    strcpy(best_ingredient, orders[0].pizza_ingredients);
    return best_ingredient;
}

// Función para calcular la cantidad de pizzas por categoría vendidas
char* pizzas_per_category(int *size, struct order *orders) {
    char *result = malloc(200);
    if (!result) return NULL;
    strcpy(result, orders[0].pizza_category);
    return result;
}
