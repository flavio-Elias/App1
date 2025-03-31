/* csv_reader.h - Funciones para la lectura y procesamiento del archivo CSV */

#ifndef CSV_READER_H
#define CSV_READER_H

#include "structs.h"

/* Función que lee el archivo CSV y almacena los datos en un array dinámico de estructuras Order.
 * Parámetros:
 *   - filename: Nombre del archivo CSV a leer.
 *   - orders: Puntero doble donde se almacenará el array dinámico de órdenes.
 *   - size: Puntero a entero donde se almacenará la cantidad de órdenes leídas.
 * Retorna:
 *   - 1 si la lectura fue exitosa, 0 en caso de error.
 */
int read_csv_file(const char *filename, Order **orders, int *size);

#endif // CSV_READER_H
