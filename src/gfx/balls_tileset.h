#ifndef balls_tileset_include_file
#define balls_tileset_include_file

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char balls_tileset_tile_0_data[326];
#define balls_tileset_tile_0 ((gfx_sprite_t*)balls_tileset_tile_0_data)
extern unsigned char balls_tileset_tile_1_data[326];
#define balls_tileset_tile_1 ((gfx_sprite_t*)balls_tileset_tile_1_data)
extern unsigned char balls_tileset_tile_2_data[326];
#define balls_tileset_tile_2 ((gfx_sprite_t*)balls_tileset_tile_2_data)
extern unsigned char balls_tileset_tile_3_data[326];
#define balls_tileset_tile_3 ((gfx_sprite_t*)balls_tileset_tile_3_data)
#define balls_tileset_num_tiles 4
extern unsigned char *balls_tileset_tiles_data[4];
#define balls_tileset_tiles ((gfx_sprite_t**)balls_tileset_tiles_data)

#ifdef __cplusplus
}
#endif

#endif
