#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

#include "gfx/gfx.h"

extern unsigned char logo_tilemap[];

void PerformTitleScreen(uint8_t is_ti) {
    const uint8_t scale_factor = 3;

    gfx_SetColor(0);
    gfx_SetTransparentColor(1);

    gfx_FillScreen(0);

    if (is_ti == 1) {
        gfx_ScaledTransparentSprite_NoClip(TI, 100, 100, scale_factor, scale_factor);
    } else {
        gfx_ScaledTransparentSprite_NoClip(CE, 100, 100, scale_factor, scale_factor);
    }
    gfx_BlitBuffer();

    gfx_SetPalette(logo_palette, sizeof_logo_palette, 0);

    gfx_SetTextFGColor(2);

    gfx_ScaledTransparentSprite_NoClip(logo_tile_0, 0, 0, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(logo_tile_1, 64, 0, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(logo_tile_2, 128, 0, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(logo_tile_3, 192, 0, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(logo_tile_4, 256, 0, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(logo_tile_5, 0, 64, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(logo_tile_6, 64, 64, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(logo_tile_7, 128, 64, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(logo_tile_8, 192, 64, 2, 2);
    gfx_ScaledTransparentSprite_NoClip(logo_tile_9, 256, 64, 2, 2);

    gfx_PrintStringXY("Appuyez sur une touche", 75, 200);
    gfx_PrintStringXY("By SiniKraft", 0, 232);
    gfx_PrintStringXY("v1.0", 288, 232);
    gfx_BlitBuffer();

	do
    {
        kb_Scan();
        boot_WaitShort();

    } while (kb_Data[6] != kb_Enter && kb_Data[6] != kb_Clear && kb_Data[1] != kb_2nd);

}