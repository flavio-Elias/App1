// structures.h - Definición de estructuras
#ifndef STRUCTURES_H
#define STRUCTURES_H

// Estructura para representar una orden
struct order {
    int pizza_id;
    int order_id;
    char pizza_name_id[50];
    int quantity;
    char order_date[20];
    char order_time[10];
    float unit_price;
    float total_price;
    char pizza_size[5];
    char pizza_category[20];
    char pizza_ingredients[200];
    char pizza_name[50];
};

#endif // STRUCTURES_H