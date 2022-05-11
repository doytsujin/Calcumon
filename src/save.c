#include <fileioc.h>
#include <string.h>

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
	var = ti_Open(SAVE_FILE_NAME, "w");
	ti_Write(save, sizeof(*save), 1, var);
	ti_SetArchiveStatus(true, var);
	ti_Close(var);

}

SaveData load() {
	ti_var_t var;
	SaveData **sav_in_var = NULL;
	if ((var = ti_Open(SAVE_FILE_NAME, "r"))) {
		sav_in_var = ti_GetDataPtr(var);
	}
	SaveData *save = ((SaveData*)sav_in_var);
	SaveData sav = *save;
	ti_Close(var);
	return sav;

}