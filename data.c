#include "json_helpers.h"

#include <string.h>
#include <stdbool.h>


#define TOKEN_DATA_ORA "T"
#define TOKEN_DATA "-"

#define LEN_DATA 3
#define IDX_ANNO 0
#define IDX_MESE 1
#define IDX_GIORNO 2


static int datefmt_to_int(const char* datefmt, const int lenght) {
    for (int idx = 0; idx < lenght; idx++) {
        if(datefmt[idx] != '0') {
            return atoi(datefmt + idx);
        }
    }
    return 0;
}

// le stringhe rappresentanti date hanno il seguente formato:
//      aaaa-mm-ggThh:mm:ss
data data_from_string(const char* str) {
    char cp_str[strlen(str)];
    strcpy(cp_str, str);

    char *c_ptr = strtok(cp_str,  TOKEN_DATA_ORA);
    if (c_ptr == NULL) {
        return (data) {false, 0, 0, 0};
    }

    char *d_ptr = strtok(c_ptr, TOKEN_DATA);
    if (d_ptr == NULL) {
        return (data) {false, 0, 0, 0};
    }

    int count_elem = 0;
    int data_elems[LEN_DATA];

    while(d_ptr != NULL) {
        data_elems[count_elem] = datefmt_to_int(d_ptr, strlen(d_ptr));
        d_ptr = strtok(NULL, TOKEN_DATA);
        count_elem++;
    }

    return (data){ 
        true, 
        data_elems[IDX_GIORNO], 
        data_elems[IDX_MESE], 
        data_elems[IDX_ANNO] 
    };

}