#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

#include "gfx/gfx.h"

#include "titlescr.h"
#include "dialog.h"

extern unsigned char tilemap_map[];

#define TILE_WIDTH          16
#define TILE_HEIGHT         16

#define TILEMAP_WIDTH       64
#define TILEMAP_HEIGHT      64

#define TILEMAP_DRAW_WIDTH  20
#define TILEMAP_DRAW_HEIGHT 16

#define Y_OFFSET            0
#define X_OFFSET            0

#define IS_TI               1   /*version TI = 1 CE = 0*/

int main(void)
{
    sk_key_t key;
    unsigned int x_offset = 0;
    unsigned int y_offset = 0;
    gfx_tilemap_t tilemap;

    /* Initialize the tilemap structure */
    tilemap.map         = tilemap_map;
    tilemap.tiles       = tileset_tiles;
    tilemap.type_width  = gfx_tile_16_pixel;
    tilemap.type_height = gfx_tile_16_pixel;
    tilemap.tile_height = TILE_HEIGHT;
    tilemap.tile_width  = TILE_WIDTH;
    tilemap.draw_height = TILEMAP_DRAW_HEIGHT;
    tilemap.draw_width  = TILEMAP_DRAW_WIDTH;
    tilemap.height      = TILEMAP_HEIGHT;
    tilemap.width       = TILEMAP_WIDTH;
    tilemap.y_loc       = Y_OFFSET;
    tilemap.x_loc       = X_OFFSET;

    /* Initialize graphics drawing */
    gfx_Begin();
    /* Draw to buffer to avoid tearing */
    gfx_SetDrawBuffer();
    gfx_SetMonospaceFont(8);

    PerformTitleScreen(IS_TI);
    gfx_FillScreen(0);
    gfx_BlitBuffer();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetColor(0);
    gfx_SetTextFGColor(1);
    gfx_SetTextBGColor(0);
    kb_Scan();
    ShowText("Bonjour cher Aventurier !          Bienvenue dans CALCUMON !");
    ShowText("Tu peux maintenir ANNUL pour sauve-garder et quitter a tout moment.");
    ShowText("Utilise SUPPR pour quitter sans    sauvegarder.");
    ShowText("Utilise 2NDE ou ENTRER comme boutonA et (-) ou ALPHA comme bouton B.");
    ShowText("Note: il est impossible de sauve-  garder pendant certains moments.");
    ShowText("Les sauvegardes de TI ne sont pas  lisibles par CE et inversement.");
    ShowText("Voila, c'est tout ! Bon courage,   et merci d'utiliser CALCUMON :)");

    do
    {
        kb_Scan();

        key = kb_Data[7];
        
        gfx_Tilemap(&tilemap, x_offset, y_offset);

        switch (key)
        {
            case kb_Down:
                if (y_offset < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
                {
                    y_offset += TILE_HEIGHT;
                }
                break;

            case kb_Left:
                if (x_offset)
                {
                    x_offset -= TILE_WIDTH;
                }
                break;

            case kb_Right:
                if (x_offset < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
                {
                    x_offset += TILE_WIDTH;
                }
                break;

            case kb_Up:
                if (y_offset)
                {
                    y_offset -= TILE_HEIGHT;
                }
                break;

            default:
                break;
        }

        gfx_SwapDraw();

    } while (kb_Data[1] != kb_Del && kb_Data[6] != kb_Clear);

    gfx_End();

    return 0;
}
