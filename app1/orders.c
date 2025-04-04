// orders.c
#include <stdlib.h>
#include "orders.h"

void free_orders(Order *orders, int num_orders) {
    for (int i = 0; i < num_orders; i++) {
        free(orders[i].pizza_id);
        free(orders[i].order_id);
        free(orders[i].pizza_name_id);
        free(orders[i].order_date);
        free(orders[i].order_time);
        free(orders[i].pizza_size);
        free(orders[i].pizza_category);
        free(orders[i].pizza_ingredients);
        free(orders[i].pizza_name);
    }
    free(orders);
}
