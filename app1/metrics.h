// metrics.h - Declaraciones de funciones de métricas
#ifndef METRICS_H
#define METRICS_H

#include "structures.h"

// Firma de funciones para métricas
typedef char* (*metric_function)(int *size, struct order *orders);

char* most_sold_pizza(int *size, struct order *orders);
char* least_sold_pizza(int *size, struct order *orders);
char* date_most_sales_money(int *size, struct order *orders);
char* date_least_sales_money(int *size, struct order *orders);
char* date_most_sales_quantity(int *size, struct order *orders);
char* date_least_sales_quantity(int *size, struct order *orders);
char* avg_pizzas_per_order(int *size, struct order *orders);
char* avg_pizzas_per_day(int *size, struct order *orders);
char* most_sold_ingredient(int *size, struct order *orders);
char* pizzas_per_category(int *size, struct order *orders);

#endif // METRICS_H