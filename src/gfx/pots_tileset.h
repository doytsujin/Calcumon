#ifndef pots_tileset_include_file
#define pots_tileset_include_file

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char pots_tileset_tile_0_data[354];
#define pots_tileset_tile_0 ((gfx_sprite_t*)pots_tileset_tile_0_data)
extern unsigned char pots_tileset_tile_1_data[354];
#define pots_tileset_tile_1 ((gfx_sprite_t*)pots_tileset_tile_1_data)
extern unsigned char pots_tileset_tile_2_data[354];
#define pots_tileset_tile_2 ((gfx_sprite_t*)pots_tileset_tile_2_data)
extern unsigned char pots_tileset_tile_3_data[354];
#define pots_tileset_tile_3 ((gfx_sprite_t*)pots_tileset_tile_3_data)
#define pots_tileset_num_tiles 4
extern unsigned char *pots_tileset_tiles_data[4];
#define pots_tileset_tiles ((gfx_sprite_t**)pots_tileset_tiles_data)

#ifdef __cplusplus
}
#endif

#endif
