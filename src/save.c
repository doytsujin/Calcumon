#include <fileioc.h>
#include <string.h>
#include <tice.h>

#include "save.h"

#define SAVE_FILE_NAME  "ClcMonSv"

bool save_exists() {
	ti_var_t variable;
	bool found;
	found = ((bool)((variable = ti_Open(SAVE_FILE_NAME, "r"))));
	ti_Close(variable);
	return found;
}

void save(SaveData* save) {
	ti_var_t var;
	if ((var = ti_Open(SAVE_FILE_NAME, "w"))) {
		ti_Write(save, sizeof(*save), 1, var);
		ti_SetArchiveStatus(true, var);
		ti_Close(var);
	}

}

void load(SaveData* data) {
	ti_var_t var;
	// SaveData **sav_in_var = NULL;
	if ((var = ti_Open(SAVE_FILE_NAME, "r"))) {
		// sav_in_var = ti_GetDataPtr(var);
		if (!(ti_Read(data, sizeof(SaveData), 1, var) == 1)) {
			data->map_num = 255;
		}
		ti_Close(var);
	}

}

// void get_world(Map* _map, uint8_t map_num) {
// 	char* file_name = "ClcMonM";
// 	char str;
// 	real_t tmp_real = os_FloatToReal((float)map_num);
// 	os_RealToStr(&str, &tmp_real, 6, 1, 0);
// 	strncat(file_name, &str, 1);
// 	ti_var_t var;
// 	Map **map_in_var = NULL;
// 	if ((var = ti_Open(file_name, "r"))) {
// 		map_in_var = ti_GetDataPtr(var);
// 		_map = ((Map*)map_in_var);
// 	} else {
// 		_map->tilemap_height = 2;  // check in main.c to cancel
// 	}
// 	ti_Close(var);
// }

