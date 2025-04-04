// metrics.h
#ifndef METRICS_H
#define METRICS_H

#include "orders.h"

typedef char* (*MetricFunction)(int *size, Order *orders);

typedef struct {
    char *name;
    MetricFunction func;
} MetricEntry;

// Declaraciones de funciones de métricas
char* pms(int *size, Order *orders);   // Pizza más vendida
char* pls(int *size, Order *orders);   // Pizza menos vendida
char* dms(int *size, Order *orders);   // Fecha con más ventas ($)
char* dls(int *size, Order *orders);   // Fecha con menos ventas ($)
char* dmsp(int *size, Order *orders);  // Fecha con más pizzas
char* dlsp(int *size, Order *orders);  // Fecha con menos pizzas
char* apo(int *size, Order *orders);   // Promedio pizzas por orden
char* apd(int *size, Order *orders);   // Promedio pizzas por día
char* ims(int *size, Order *orders);   // Ingrediente más vendido
char* hp(int *size, Order *orders);    // Pizzas por categoría

// Tabla de métricas
extern MetricEntry metric_table[];

#endif // METRICS_H
