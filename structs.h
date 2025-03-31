/* structs.h - Definición de estructuras de datos para almacenar las órdenes del CSV */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

/* Definición de la estructura que representa una orden de venta de pizzas */
typedef struct {
    char pizza_id[50];          // Identificador único de la pizza
    char order_id[50];          // Identificador único de la orden
    char pizza_name_id[100];    // Identificador único del nombre de la pizza
    int quantity;               // Cantidad de pizzas vendidas en la orden
    char order_date[20];        // Fecha de la orden (YYYY-MM-DD)
    char order_time[10];        // Hora de la orden (HH:MM:SS)
    float unit_price;           // Precio unitario de la pizza
    float total_price;          // Precio total de la orden
    char pizza_size[10];        // Tamaño de la pizza (S, M, L, XL, etc.)
    char pizza_category[50];    // Categoría de la pizza (ej. Clásica, Gourmet)
    char pizza_ingredients[200];// Ingredientes de la pizza en formato de lista separada por comas
    char pizza_name[100];       // Nombre completo de la pizza
} Order;

#endif // STRUCTS_H