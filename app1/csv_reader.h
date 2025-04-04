// csv_reader.h
#ifndef CSV_READER_H
#define CSV_READER_H

#include "orders.h"

// Lee el archivo CSV y retorna un arreglo dinámico de órdenes
Order* read_csv(const char *filename, int *num_orders);

#endif // CSV_READER_H
