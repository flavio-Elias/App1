#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "metrics.h"



typedef struct {
    char *pizza_name;
    int total_quantity;
} PizzaSales;


PizzaSales* count_pizza_sales(int size, Order *orders, int *count_out) {
    PizzaSales *sales = NULL;
    int count = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(sales[j].pizza_name, orders[i].pizza_name) == 0) {
                sales[j].total_quantity += orders[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            sales = realloc(sales, (count + 1) * sizeof(PizzaSales));
            sales[count].pizza_name = strdup(orders[i].pizza_name);
            sales[count].total_quantity = orders[i].quantity;
            count++;
        }
    }

    *count_out = count;
    return sales;
}

//pizza mas vendida
char* pms(int *size, Order *orders) {
    int count;
    PizzaSales *sales = count_pizza_sales(*size, orders, &count);

    int max = -1;
    char *result = NULL;

    for (int i = 0; i < count; i++) {
        if (sales[i].total_quantity > max) {
            max = sales[i].total_quantity;
            if (result) free(result);
            result = strdup(sales[i].pizza_name);
        }
        free(sales[i].pizza_name);
    }

    free(sales);
    return result;
}

//pizza menos vedida
char* pls(int *size, Order *orders) {
    int count;
    PizzaSales *sales = count_pizza_sales(*size, orders, &count);

    int min = INT_MAX;
    char *result = NULL;

    for (int i = 0; i < count; i++) {
        if (sales[i].total_quantity < min) {
            min = sales[i].total_quantity;
            if (result) free(result);
            result = strdup(sales[i].pizza_name);
        }
        free(sales[i].pizza_name);
    }

    free(sales);
    return result;
}


typedef struct {
    char *date;
    float total;
    int count;
} DateSales;


void aggregate_sales_by_date(int size, Order *orders, DateSales **sales_out, DateSales **counts_out, int *count_out) {
    DateSales *sales = NULL;
    DateSales *counts = NULL;
    int sales_count = 0;
    int counts_count = 0;

    for (int i = 0; i < size; i++) {
        int found_1 = 0;
        int found_2 = 0;
        

        for (int j = 0; j < sales_count; j++) {
            if (strcmp(sales[j].date, orders[i].order_date) == 0) {
                sales[j].total += orders[i].total_price;
                found_1 = 1;
                break;
            }
        }


        if (!found_1) {
            sales = realloc(sales, (sales_count + 1) * sizeof(DateSales));
            sales[sales_count].date = strdup(orders[i].order_date);
            sales[sales_count].total = orders[i].total_price;
            sales_count++;
        }


        for (int j = 0; j < counts_count; j++) {
            if (strcmp(counts[j].date, orders[i].order_date) == 0) {
                counts[j].count++;
                found_2 = 1;
                break;
            }
        }


        if (!found_2) {
            counts = realloc(counts, (counts_count + 1) * sizeof(DateSales));
            counts[counts_count].date = strdup(orders[i].order_date);
            counts[counts_count].count = 1;
            counts_count++;
        }
    }


    *sales_out = sales;
    *counts_out = counts;
    *count_out = sales_count;
    }

// fecha con mas ventas en termino de capital
char* dms(int *size, Order *orders) {
    int count;
    DateSales *sales = NULL;
    DateSales *counts = NULL;

    aggregate_sales_by_date(*size, orders, &sales, &counts, &count);

    float max = -1.0;
    char *best_date = NULL;

    for (int i = 0; i < count; i++) {
        if (sales[i].total > max) {
            max = sales[i].total;
            if (best_date) free(best_date);
            best_date = strdup(sales[i].date);
        }
        free(sales[i].date);
    }

    free(sales);
    free(counts);

    char *result = malloc(64);
    snprintf(result, 64, "%s ($%.2f)", best_date, max);
    free(best_date);
    return result;
    }

//Fecha  con menos ventas en termino en termino de capital
char* dls(int *size, Order *orders) {
    int count;
    DateSales *sales = NULL;
    DateSales *counts = NULL;
    aggregate_sales_by_date(*size, orders, &sales, &counts, &count);

    float min = sales[0].total;
    char *worst_date = strdup(sales[0].date);

    for (int i = 1; i < count; i++) {
        if (sales[i].total < min) {
            min = sales[i].total;
            free(worst_date);
            worst_date = strdup(sales[i].date);
        }
        free(sales[i].date);
    }

    free(sales);
    free(counts);

    char *result = malloc(64);
    snprintf(result, 64, "%s ($%.2f)", worst_date, min);
    free(worst_date);
    return result;
}
// fecha con mas pizzas hechas
char* dmsp(int *size, Order *orders) {
    int count;
    DateSales *sales = NULL;
    DateSales *counts = NULL;
    aggregate_sales_by_date(*size, orders, &sales, &counts, &count);

    int max_count = counts[0].count;
    char *fecha_max = strdup(counts[0].date);

    for (int i = 1; i < count; i++) {
        if (counts[i].count > max_count) {
            max_count = counts[i].count;
            free(fecha_max);
            fecha_max = strdup(counts[i].date);
        }
    }

    // Limpiar
    free(sales);
    free(counts);

    char *result = malloc(128);
    snprintf(result, 128, "Más ventas: %s (%d)", fecha_max, max_count);
    free(fecha_max);
    return result;
}

// fecha con menos pizzas

char* dlsp(int *size, Order *orders) {
    int count;
    DateSales *sales = NULL;
    DateSales *counts = NULL;
    aggregate_sales_by_date(*size, orders, &sales, &counts, &count);

    int min_count = counts[0].count;
    char *fecha_min = strdup(counts[0].date);

    for (int i = 1; i < count; i++) {
        
        if (counts[i].count < min_count) {
            min_count = counts[i].count;
            free(fecha_min);
            fecha_min = strdup(counts[i].date);
        }
    }

    for (int i = 0; i < count; i++) {
        free(counts[i].date);
    }
    free(sales);
    free(counts);

    char *result = malloc(128);
    snprintf(result, 128, "Menos ventas: %s (%d)", fecha_min, min_count);
    free(fecha_min);
    return result;
}

//pizzas por categoria
char* hp(int *size, Order *orders) {
    typedef struct {
        char category[64];
        int count;
    } CategoryCount;

    CategoryCount counts[100];
    int count_size = 0;

    for (int i = 0; i < *size; i++) {
        char *category = orders[i].pizza_category;


        int found = 0;
        for (int j = 0; j < count_size; j++) {
            if (strcmp(counts[j].category, category) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }


        if (!found && count_size < 100) {
            strncpy(counts[count_size].category, category, 63);
            counts[count_size].category[63] = '\0';
            counts[count_size].count = 1;
            count_size++;
        }
    }


    char *result = malloc(1024);
    result[0] = '\0';

    for (int i = 0; i < count_size; i++) {
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "%s: %d", counts[i].category, counts[i].count);
        strcat(result, buffer);
        if (i < count_size - 1) strcat(result, " | ");
    }

    return result;
}

//promedio pizzas por dia
char* apd(int *size, Order *orders) {
    char dates[1000][64];
    int unique_days = 0;

    for (int i = 0; i < *size; i++) {
        char *date = orders[i].order_date;


        int found = 0;
        for (int j = 0; j < unique_days; j++) {
            if (strcmp(dates[j], date) == 0) {
                found = 1;
                break;
            }
        }


        if (!found && unique_days < 1000) {
            strncpy(dates[unique_days], date, 63);
            dates[unique_days][63] = '\0';
            unique_days++;
        }
    }

    int total_pizzas = *size;
    float average = (float)total_pizzas / unique_days;


    char *result = malloc(64);
    snprintf(result, 64, "%.2f", average);
    return result;
}

//promedio pizzas por orden de pizzas ordenada (de pedidos no de exponente tipo orden 2 para n cuadrado)
char* apo(int *size, Order *orders) {
    char order_ids[1000][64];
    int unique_count = 0;

    for (int i = 0; i < *size; i++) {
        char *oid = orders[i].order_id;


        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(order_ids[j], oid) == 0) {
                found = 1;
                break;
            }
        }


        if (!found && unique_count < 1000) {
            strncpy(order_ids[unique_count], oid, 63);
            order_ids[unique_count][63] = '\0';
            unique_count++;
        }
    }

    int total_pizzas = *size;
    int total_orders = unique_count;

    float average = (float)total_pizzas / total_orders;

    char *result = malloc(64);
    snprintf(result, 64, "%.2f", average);
    return result;
}



typedef struct {
    char *name;
    int total_quantity;
}IngredientSales;

//Ingredientes mas vendidos
char* ims(int *size, Order *orders) {
    IngredientSales *ingredients = NULL;
    int ing_count = 0;

    for (int i = 0; i < *size; i++) {
        char *ingredient_list = strdup(orders[i].pizza_ingredients); // para no modificar el original
        char *token = strtok(ingredient_list, ",");

        while (token != NULL) {
            // Eliminar espacios al inicio
            while (*token == ' ') token++;

            // Buscar si el ingrediente ya existe
            int found = 0;
            for (int j = 0; j < ing_count; j++) {
                if (strcmp(ingredients[j].name, token) == 0) {
                    ingredients[j].total_quantity += orders[i].quantity;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                ingredients = realloc(ingredients, (ing_count + 1) * sizeof(IngredientSales));
                ingredients[ing_count].name = strdup(token);
                ingredients[ing_count].total_quantity = orders[i].quantity;
                ing_count++;
            }

            token = strtok(NULL, ",");
        }

        free(ingredient_list);
    }

    // Buscar el ingrediente más vendido
    int max = -1;
    char *top_ingredient = NULL;

    for (int i = 0; i < ing_count; i++) {
        if (ingredients[i].total_quantity > max) {
            max = ingredients[i].total_quantity;
            if (top_ingredient) free(top_ingredient);
            top_ingredient = strdup(ingredients[i].name);
        }
        free(ingredients[i].name);
    }

    free(ingredients);
    return top_ingredient;
}
MetricEntry metric_table[] = {
    {"pms", pms},
    {"pls", pls},
    {"dms", dms},
    {"dls", dls},
    {"dmsp", dmsp},
    {"dlsp", dlsp},
    {"hp", hp},
    {"apd", apd},
    {"apo", apo},
    {"ims", ims},
    {NULL, NULL}
};
