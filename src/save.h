#ifndef save_include_file
#define save_include_file

#ifdef __cplusplus
extern "C" {
#endif

extern bool save_exists();

typedef struct {
   bool b1:1;
   bool b2:1;
   bool b3:1;
   bool b4:1;
   bool b5:1;
   bool b6:1;
   bool b7:1;
   bool b8:1;
} BitBools;

typedef struct {
   bool is_ti;  // Is TI or CE game
   char name[10];  // 9 char max name
   bool is_male;  // male or female
   unsigned int x_offset;  // tilemap x and y pos
   unsigned int y_offset;
   uint8_t map_num;  // map index
   uint8_t pballs;  // Poké Balls owned
   uint8_t gballs;  // Great Balls owned
   uint8_t uballs;  // Ultra Balls owned
   bool mball;  // has a masterball ? (max 1)
   uint8_t location; // 0 = Outside, 1 = Pokémon center, 2 = Market
   bool free_control_vertical;  // is the player not in center of screen ? (when near to borders of the tilemap)
   bool free_control_horizontal;
   uint24_t x;  // x on screen location
   uint8_t y;  // y on screen location
   bool is_down;  // If free_control, is in down side or up ?
   bool is_right;  // If free_control, is in right side or left ?
   uint8_t nlen;  // Name Length
   uint8_t direction;
   uint16_t money; // max = 65535
   BitBools found_mons[19];
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
