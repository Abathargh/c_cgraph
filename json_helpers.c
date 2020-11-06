#include "json_helpers.h"
#include <stdio.h>
#include <string.h>

// This returns -1 on error
long load_json(char **dest, const char *path) {
	FILE *data_f = fopen(path, "rb");
	if (data_f == NULL) { return -1; }
	
	fseek(data_f, 0, SEEK_END);
	long data_f_size = ftell(data_f);
	rewind(data_f);

	char *data_str = (char *) malloc(data_f_size + 1);
	if (data_str == NULL) { return -1; }
	
	fread(data_str, 1, data_f_size, data_f);
	data_str[data_f_size] = '\0';
	fclose(data_f);
	
	*dest = data_str;
	return data_f_size;
}



// This returns -1 on error
long get_tot_reg_data(totale_regione*** dest, const char* data, const long data_f_size) {
	json_value_s *json_data = json_parse(data, data_f_size);
	json_array_s *data_arr = json_value_as_array(json_data);
	if(data_arr == NULL) { return 1; }

	int tot_reg_idx = 0;
	size_t length = data_arr->length;
	totale_regione **tot_reg = malloc(length * sizeof(totale_regione*));

	json_array_element_s *curr;	
	json_object_element_s *curr_n;

	json_value_s *curr_val;

	totale_regione *curr_reg;

	for(curr = data_arr->start; curr != NULL; curr = curr->next) {
		curr_reg = (totale_regione*) malloc(sizeof(totale_regione));

		for(curr_n = json_value_as_object(curr->value)->start; curr_n != NULL; curr_n = curr_n->next) {
			const char* curr_name = curr_n->name->string;
			curr_val = curr_n->value;
			
			if(strcmp(curr_name, DATA) == 0) {
				const char* strdata = json_value_as_string(curr_val)->string;
				curr_reg->reg_data = data_from_string(strdata);
				continue;
			} 
			else if(strcmp(curr_name, DEN_REGIONE) == 0) {
				const char* strdenreg = json_value_as_string(curr_val)->string;
				curr_reg->regione = strdenreg;
				continue;
			}
			else if(strcmp(curr_name, TOT_CASI) == 0) {
				long totcasi = atol(json_value_as_number(curr_val)->number);
				curr_reg->tot_casi = totcasi;
				continue;
			}
		}
		tot_reg[tot_reg_idx++] = curr_reg;
	}
	*dest = tot_reg;
	return length; 
}

void free_tot_reg(totale_regione** tot, long length) {
	for(long i = 0; i < length; i++) {
		free(tot[i]);
	}
	free(tot);
}


void print_reg(totale_regione *reg) {
	data d = reg->reg_data;
	printf("regione %s, data: %d-%d-%d, tot_casi: %d\n", reg->regione, d.giorno, d.mese, d.anno, reg->tot_casi);
}