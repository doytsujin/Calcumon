#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

#include "gfx/gfx.h"

#include "titlescr.h"
#include "dialog.h"
#include "save.h"

extern unsigned char tilemap_map[];

#define TILE_WIDTH          16
#define TILE_HEIGHT         16

#define TILEMAP_WIDTH       64
#define TILEMAP_HEIGHT      64

#define TILEMAP_DRAW_WIDTH  21
#define TILEMAP_DRAW_HEIGHT 16

#define Y_OFFSET            0
#define X_OFFSET            0

#define IS_TI               1   /*version TI = 1 CE = 0*/

int main(void)
{
    sk_key_t key;
    bool is_male = true;
    bool instant_exit = false;
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

    uint8_t direction = 1; /*0 up 1 down 2 left 3 right*/

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
    SaveData sav;
    if (!(save_exists())) {
    ShowText("Bonjour cher Aventurier !          Bienvenue dans CALCUMON !");
    ShowText("Tu peux maintenir ANNUL pour sauve-garder et quitter a tout moment.");
    ShowText("Utilise SUPPR pour quitter sans    sauvegarder.");
    ShowText("Utilise 2NDE ou ENTRER comme boutonA et (-) ou ALPHA comme bouton B.");
    ShowText("Note: il est impossible de sauve-  garder pendant certains moments.");
    ShowText("Les sauvegardes de TI ne sont pas  lisibles par CE et inversement.");
    ShowText("Mais, comment t'appelles-tu ???");
    bool finask = false;
    char inputBuffer[10/*= size*/] = "Unnamed";
    kb_Scan();
    if (!(kb_Data[6] == kb_Clear)) {
        while (!(finask)) {
            gfx_End(); // ASK FOR NAME
            os_ClrHome();
            os_GetStringInput("Votre nom : ", inputBuffer, 10/*= size*/);
            os_ClrHome();
            gfx_Begin(); // RESUMING
            gfx_SetPalette(global_palette, sizeof_global_palette, 0);
            gfx_SetColor(0);
            gfx_SetTextFGColor(1);
            gfx_SetTextBGColor(0);
            gfx_SetDrawBuffer();
            gfx_SetMonospaceFont(8);
            kb_Scan();
            if (kb_Data[6] == kb_Clear) {
                break;
            }
            ShowText(inputBuffer);
            if (AskBoolText("C'est bien ton nom ???")) {
                finask = true;
            }
        }
    }
    strcpy(sav.name, inputBuffer);
    bool _tmp_sk = false;
    gfx_FillScreen(0);
    _tmp_sk = AskBoolText("Au fait ... Est-tu un garcon ?");
    sav.is_male = _tmp_sk;
    sav.is_ti = IS_TI;
    sav.x_offset = 0;
    sav.y_offset = 0;
    sav.map_num = 0;
    sav.pballs = 10;
    sav.gballs = 0;
    sav.uballs = 0;
    sav.mball = false;
    gfx_FillScreen(0);
    ShowText("Voila, c'est tout ! Bon courage,   et merci d'utiliser CALCUMON :)");
    } else {
        sav = load();
        if (sav.is_ti != IS_TI) {
            ShowText("Données de sauvegardes incompatibles avec ce CALCUMON :/");
            instant_exit = true;
        }
    }
    is_male = sav.is_male;

    gfx_sprite_t* sprite_tile_18 = gfx_MallocSprite(16, 16);
    gfx_sprite_t* sprite_tile_19 = gfx_MallocSprite(16, 16);
    gfx_sprite_t* sprite_tile_20 = gfx_MallocSprite(16, 16);
    if (is_male) {
        gfx_FlipSpriteY(sprite_tile_3, sprite_tile_18);
        gfx_FlipSpriteY(sprite_tile_4, sprite_tile_19);
        gfx_FlipSpriteY(sprite_tile_5, sprite_tile_20);
    } else {
        gfx_FlipSpriteY(sprite_tile_12, sprite_tile_18);
        gfx_FlipSpriteY(sprite_tile_13, sprite_tile_19);
        gfx_FlipSpriteY(sprite_tile_14, sprite_tile_20);
    }

    bool moved = false;
    bool ani = false;
    uint8_t tme = 0;
    uint8_t to_walk = 2;
    x_offset = sav.x_offset;
    y_offset = sav.y_offset;

    do
    {
        kb_Scan();

        if (moved) {
            tme++;
            if (kb_Data[2] == kb_Alpha || kb_Data[4] == kb_Chs) {
                tme++;
            }
        }
        if (tme >= 4) {
            ani = !(ani);
            tme = 0;
        }

        key = kb_Data[7];
        
        gfx_Tilemap(&tilemap, x_offset, y_offset);
        
        if (direction == 0) {
            if (is_male) {
                if (!(moved)) { // MALE UP
                    gfx_TransparentSprite_NoClip(sprite_tile_6, 152, 112);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_8, 152, 112);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_7, 152, 112);
                }
            } else {
                if (!(moved)) {  // FEMALE UP
                    gfx_TransparentSprite_NoClip(sprite_tile_15, 152, 112);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_17, 152, 112);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_16, 152, 112);
                }
            }
        } else if (direction == 1) {
            if (is_male) {
                if (!(moved)) {  // MALE DOWN
                    gfx_TransparentSprite_NoClip(sprite_tile_0, 152, 112);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_2, 152, 112);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_1, 152, 112);
                }
            } else {
                if (!(moved)) {  // FEMALE DOWN
                    gfx_TransparentSprite_NoClip(sprite_tile_9, 152, 112);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_11, 152, 112);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_10, 152, 112);
                }
            }
        } else if (direction == 2) {  // MALE - FEMALE LEFT
            if (!(moved)) {
                gfx_TransparentSprite_NoClip(sprite_tile_18, 152, 112);
            } else if (ani) {
                gfx_TransparentSprite_NoClip(sprite_tile_20, 152, 112);
            } else {
                gfx_TransparentSprite_NoClip(sprite_tile_19, 152, 112);
            }
        } else {
            if (is_male) {
                if (!(moved)) {  // MALE RIGHT
                    gfx_TransparentSprite_NoClip(sprite_tile_3, 152, 112);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_5, 152, 112);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_4, 152, 112);
                }
            } else {
                if (!(moved)) {  // FEMALE RIGHT
                    gfx_TransparentSprite_NoClip(sprite_tile_12, 152, 112);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_14, 152, 112);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_13, 152, 112);
                }
            }
        }
        moved = false;
        if (kb_Data[2] == kb_Alpha || kb_Data[4] == kb_DecPnt) {
            to_walk = 4;
        } else {
            to_walk = 2;
        }

        switch (key)
        {
            case kb_Down:
            direction = 1;
            moved = true;
                if (y_offset < (TILEMAP_HEIGHT * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
                {
                    y_offset += to_walk;
                }
                break;

            case kb_Left:
            direction = 2;
            moved = true;
                if (x_offset)
                {
                    x_offset -= to_walk;
                }
                break;

            case kb_Right:
            direction = 3;
            moved = true;
                if (x_offset < (TILEMAP_WIDTH * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
                {
                    x_offset += to_walk;
                }
                break;

            case kb_Up:
            direction = 0;
            moved = true;
                if (y_offset)
                {
                    y_offset -= to_walk;
                }
                break;

            default:
                break;

            
        }
        if (y_offset > 15000000) {
            y_offset = 0;
        }
        if (x_offset > 15000000) {
            x_offset = 0;
        }  // security
        gfx_SwapDraw();
        sav.x_offset = x_offset;
        sav.y_offset = y_offset;
    } while (kb_Data[1] != kb_Del && kb_Data[6] != kb_Clear && !(instant_exit));
    gfx_ZeroScreen();
    gfx_BlitBuffer();

    save(&sav);
    gfx_End();

    return 0;
}
