#ifndef STRUCTURED_JSON_H
#define STRUCTURED_JSON_H

#include <stdbool.h>
#include <string.h>
#include "json.h"


#define TOT_CASI "totale_casi"
#define DEN_REGIONE "denominazione_regione"
#define DATA "data"


typedef struct json_value_s json_value_s;
typedef struct json_array_s json_array_s;
typedef struct json_object_s json_object_s;
typedef struct json_array_element_s json_array_element_s;
typedef struct json_object_element_s json_object_element_s;
typedef struct json_string_s json_string_s;
typedef struct json_number_s json_number_s;

typedef struct {
    bool valida;
    int giorno;
    int mese;
    int anno;
} data;

typedef struct {
    const char* regione;
    data reg_data;
    int tot_casi;
} totale_regione;


long load_json(char **dest, const char *path);

long get_tot_reg_data(totale_regione*** dest, const char* data, const long data_f_size);
void free_tot_reg(totale_regione** tot, long length);
void print_reg(totale_regione *reg);

data data_from_string(const char* str);

#endif