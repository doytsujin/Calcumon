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
} SaveData;

typedef struct {
   uint8_t tilemap_height;
   uint8_t tilemap_width;
   unsigned char tilemap_map[16384];
} Map;

extern void save(SaveData* save);
extern SaveData load();
extern void get_world(Map* _map, uint8_t map_num);

#ifdef __cplusplus
}
#endif

#endif
