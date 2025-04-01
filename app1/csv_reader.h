// csv_reader.h - Declaraciones de funciones para leer el CSV
#ifndef CSV_READER_H
#define CSV_READER_H

#include "structures.h"

int read_csv(const char *filename, struct order **orders);

#endif // CSV_READER_H