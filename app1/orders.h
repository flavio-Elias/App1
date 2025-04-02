//
// Created by flavi on 01-04-2025.
//

#ifndef ORDERS_H

#define ORDERS_H

typedef struct {
    int pizza_id;
    int order_id;
    char pizza_name_id[50];
    int quantity;
    char order_date[11];  // Formato dd/mm/yyyy
    char order_time[9];   // Formato hh:mm:ss
    float unit_price;
    float total_price;
    char pizza_size;
    char pizza_category[30];
    char pizza_ingredients[200];
    char pizza_name[50];
} Order;

#endif
