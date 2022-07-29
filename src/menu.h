#ifndef menu_include_file
#define menu_include_file

#ifdef __cplusplus
extern "C" {
#endif

extern bool ShowMainMenu(SaveData* _save, gfx_tilemap_t* tilmap, unsigned int* _x, unsigned int* _y, uint8_t selec, uint8_t prev_selec, bool back, bool back2, bool show_bg);

#ifdef __cplusplus
}
#endif

#endif
