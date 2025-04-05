// orders.h
#ifndef ORDERS_H
#define ORDERS_H

typedef struct {
    char *pizza_id;
    char *order_id;
    char *pizza_name_id;
    int quantity;
    char *order_date;
    char *order_time;
    float unit_price;
    float total_price;
    char *pizza_size;
    char *pizza_category;
    char *pizza_ingredients;
    char *pizza_name;
} Order;


void free_orders(Order *orders, int num_orders);

#endif // ORDERS_H
