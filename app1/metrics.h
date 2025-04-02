/* metrics.h */
#ifndef METRICS_H
#define METRICS_H
#include "orders.h"

typedef char* (*MetricFunction)(int* size, Order* orders);

char* most_sold_pizza(int* size, Order* orders);
char* least_sold_pizza(int* size, Order* orders);
char* highest_sales_date(int* size, Order* orders);
char* lowest_sales_date(int* size, Order* orders);
char* highest_pizza_count_date(int* size, Order* orders);
char* lowest_pizza_count_date(int* size, Order* orders);
char* avg_pizzas_per_order(int* size, Order* orders);
char* avg_pizzas_per_day(int* size, Order* orders);
char* most_sold_ingredient(int* size, Order* orders);
char* pizzas_per_category(int* size, Order* orders);

#endif