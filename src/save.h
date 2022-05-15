#ifndef save_include_file
#define save_include_file

#ifdef __cplusplus
extern "C" {
#endif

extern bool save_exists();

typedef struct {
   bool is_ti;
   char name[10];
   bool is_male;
   unsigned int x_offset;
   unsigned int y_offset;
   uint8_t map_num;
   uint8_t pballs;
   uint8_t gballs;
   uint8_t uballs;
   bool mball;
   uint8_t location; // 0 = outside, 1 = Pokémon center, 2 = Market
   bool free_control_vertical;
   bool free_control_horizontal;
   uint24_t x;
   uint8_t y;
   bool is_down;
   bool is_right;
} SaveData;

// typedef struct {
//    uint8_t tilemap_height;
//    uint8_t tilemap_width;
//    unsigned char tilemap_map[9312];
// } Map;

extern void save(SaveData* save);
extern SaveData load();
// extern void get_world(Map* _map, uint8_t map_num);

#ifdef __cplusplus
}
#endif

#endif
