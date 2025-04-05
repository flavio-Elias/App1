
#ifndef CSV_READER_H
#define CSV_READER_H

#include "orders.h"

// Firma de la funcion read_csv
Order* read_csv(const char *filename, int *num_orders);

#endif
