/* csv_reader.h */
#ifndef CSV_READER_H
#define CSV_READER_H
#include "orders.h"

Order* read_csv(const char* filename, int* order_count);

#endif
