/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_reader.h"
#include "metrics.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Uso: %s archivo.csv metrica1 metrica2 ...\n", argv[0]);
        return 1;
    }
    
   int order_count;
    Order* orders = read_csv(argv[1], &order_count);
    if (!orders) return 1;
    
    MetricFunction metrics[] = {
        most_sold_pizza, least_sold_pizza, highest_sales_date, lowest_sales_date,
        highest_pizza_count_date, lowest_pizza_count_date, avg_pizzas_per_order,
        avg_pizzas_per_day, most_sold_ingredient, pizzas_per_category
    };
    
    char* metric_names[] = {"pms", "pls", "dms", "dls", "dmsp", "dlsp", "apo", "apd", "ims", "hp"};
    
    for (int i = 2; i < argc; i++) {
        for (int j = 0; j < 10; j++) {

            if (strcmp(argv[i], metric_names[j]) == 0) {
                int size = order_count;
                char* result = metrics[j](&size, orders);
                printf("%s\n", result);
                free(result);
                break;
            }
        }
    }
    
    free(orders);
    return 0;
}
