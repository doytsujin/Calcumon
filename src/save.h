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

extern void save(SaveData* save);
extern SaveData load();

#ifdef __cplusplus
}
#endif

#endif
