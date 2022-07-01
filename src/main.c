#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

#include "gfx/gfx.h"

#include "titlescr.h"
#include "dialog.h"
#include "save.h"
#include "tile_properties.h"
#include "transition.h"
#include "menu.h"

extern unsigned char uthon_map[];
extern unsigned char pc_map[];
extern unsigned char markt_map[];
extern unsigned char route_1_map[];
extern unsigned char dadark_cave_map[];

#define TILE_WIDTH          16
#define TILE_HEIGHT         16

#define TILEMAP_DRAW_WIDTH  21
#define TILEMAP_DRAW_HEIGHT 16

#define IS_TI               1   /*version TI = 1 CE = 0*/
#define ENABLE_DEBUG        false /*enable printing tilemap and player coords*/

const uint8_t tilemaps_height[3] = {
    34,
    16,
    32
};

const uint8_t tilemaps_width[3] = {
    33,
    70,
    33
};

unsigned char* maps[3] = {
    uthon_map,
    route_1_map,
    dadark_cave_map
};



const uint8_t prices[7] = {
    2,  // pots
    6,  // spots
    12,  // hpots
    24,  // mpots
    2,  // pballs
    6,  // gballs
    8  // uballs
};

uint8_t tilemap_height;
uint8_t tilemap_width;

void change_tilemap(uint8_t map_num2, uint8_t loc, gfx_tilemap_t* tilemp, bool transition) {
    if (transition) {
        Transition();
    }
    if (loc == 0) {
        // if (map_num2 == 0) {
        //     tilemp->map = uthon_map;
        // } else if (map_num2 == 1) {
        //     tilemp->map = route_1_map;
        // } else {
        //     gfx_End();
        //     os_ThrowError(OS_E_INVALID);
        // }
        tilemp->map = maps[map_num2];
        
        tilemap_height = tilemaps_height[map_num2];
        tilemap_width = tilemaps_width[map_num2];
    } else if (loc == 1) {
        tilemap_height = 16;
        tilemap_width = 21;
        tilemp->map = pc_map;
    } else if (loc == 2) {
        tilemap_height = 16;
        tilemap_width = 21;
        tilemp->map = markt_map;
    }
    tilemp->tiles       = tileset_tiles;
    tilemp->type_width  = gfx_tile_16_pixel;
    tilemp->type_height = gfx_tile_16_pixel;
    tilemp->tile_height = TILE_HEIGHT;
    tilemp->tile_width  = TILE_WIDTH;
    tilemp->draw_height = TILEMAP_DRAW_HEIGHT;
    tilemp->draw_width  = TILEMAP_DRAW_WIDTH;
    tilemp->height      = tilemap_height;
    tilemp->width       = tilemap_width;
    tilemp->y_loc       = 0;
    tilemp->x_loc       = 0;
            
}

void redraw_center(bool is_heal) {
    gfx_Sprite_NoClip(tileset_tile_146, 160, 64);
    gfx_Sprite_NoClip(tileset_tile_149, 160, 80);
    if (is_heal) {
        gfx_TransparentSprite_NoClip(tileset_tile_178, 160, 74);
        gfx_TransparentSprite_NoClip(tileset_tile_194, 160, 90);
    } else {
        gfx_TransparentSprite_NoClip(tileset_tile_177, 160, 74);
        gfx_TransparentSprite_NoClip(tileset_tile_193, 160, 90);
    }
    gfx_BlitBuffer();
}


int main(void)
{
    sk_key_t key;
    bool is_male = true;
    bool instant_exit = false;
    unsigned int x_offset = 0;
    unsigned int y_offset = 0;
    // uint8_t tilemap_height = 64;
    // uint8_t tilemap_width = 64;
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
    char* inputBuffer;
    kb_Scan();
    if (!(kb_Data[6] == kb_Clear)) {
        while (!(finask)) {
            // gfx_End(); // ASK FOR NAME
            // os_ClrHome();
            // os_GetStringInput("Votre nom : ", inputBuffer, 10/*= size*/);
            // os_ClrHome();
            // gfx_Begin(); // RESUMING
            // gfx_SetPalette(global_palette, sizeof_global_palette, 0);
            // gfx_SetColor(0);
            // gfx_SetTextFGColor(1);
            // gfx_SetTextBGColor(0);
            // gfx_SetDrawBuffer();
            // gfx_SetMonospaceFont(8);
            // kb_Scan();
            // if (kb_Data[6] == kb_Clear) {
            //     break;
            // }
            gfx_ZeroScreen();
            inputBuffer = AskText();
            gfx_ZeroScreen();
            ShowText(inputBuffer);
            if (AskBoolText("C'est bien ton nom ???")) {
                finask = true;
            }
        }
    }
    strcpy(sav.name, inputBuffer);
    sav.nlen = strlen(sav.name);
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
    sav.pots = 0;
    sav.spots = 0;
    sav.hpots = 0;
    sav.mpots = 0;
    sav.mball = false;
    sav.location = 0;
    sav.free_control_vertical = false;
    sav.free_control_horizontal = false;
    sav.x = 152;
    sav.y = 112;
    sav.is_down = false;
    sav.is_right = false;
    sav.direction = 1;
    sav.money = 30;
    for (uint8_t __i = 0; __i < 19; __i++) {
        sav.found_mons[__i].b1 = false;
        sav.found_mons[__i].b2 = false;
        sav.found_mons[__i].b3 = false;
        sav.found_mons[__i].b4 = false;
        sav.found_mons[__i].b5 = false;
        sav.found_mons[__i].b6 = false;
        sav.found_mons[__i].b7 = false;
        sav.found_mons[__i].b8 = false;
    }
    gfx_ZeroScreen();
    ShowText("Voici 10 Poke Balls.");
    ShowText("Et, cadeau : 3000 $");
    ShowText("Attention: Il n'y a pas de rappels !");
    ShowText("Pour reanimer, utilise une potion, qui couvre tout les PV max !");
    ShowText("Tu dois maitenant choisir ton Pokemon de depart. Lequel veux-tu ???");
    uint8_t choosed;
    choosed = AskNumText("0: Bulbizarre  1: Salameche        2: Carapuce ", 2, 125);
    gfx_ZeroScreen();
    ShowText("C'etait le professeur Ken,         J'espere qu'on se reverra !");
    ShowText("Voila, c'est tout ! Bon courage,   et merci d'utiliser CALCUMON :)");
    } else {
        load(&sav);
        if (sav.map_num == 255) {
            gfx_End();
            os_ClrHome();
            os_ThrowError(OS_E_INVALID);
            return 0;
        }
        if (sav.is_ti != IS_TI) {
            ShowText("Données de sauvegardes incompatibles avec ce CALCUMON :/");
            instant_exit = true;
            gfx_End();
            return 0;
        }
    }
    is_male = sav.is_male;
    uint24_t x = sav.x;
    uint8_t y = sav.y;
    bool is_down = sav.is_down;
    bool is_right = sav.is_right;
    direction = sav.direction;

    gfx_tilemap_t tilemap;
    // static Map map;
    // get_world(&map, sav.map_num);
    // if (map.tilemap_height == 2) {
    //     gfx_End();
    //     os_ClrHome();
    //     os_ThrowError(OS_E_UNDEFINED);
    //     return 1;
    // }

    /* Initialize the tilemap structure */
    change_tilemap(sav.map_num, sav.location, &tilemap, false);

    gfx_sprite_t* sprite_tile_18 = gfx_MallocSprite(16, 16);
    gfx_sprite_t* sprite_tile_19 = gfx_MallocSprite(16, 16);
    gfx_sprite_t* sprite_tile_20 = gfx_MallocSprite(16, 16);
    if (sprite_tile_18 == NULL || sprite_tile_19 == NULL || sprite_tile_20 == NULL) {  // Security Measure to prevent the gfx_FlipSpriteY writnig to NULL and cause calc restart!
        gfx_End();
        os_ClrHome();
        os_ThrowError(OS_E_MEMORY);
        return 1;
    }
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
    bool free_control_vertical = sav.free_control_vertical;
    bool free_control_horizontal = sav.free_control_horizontal;
    bool is_healing = false;
    bool computer_on = false;
    uint8_t markt_sel = 0;  // pots or balls or annul ?
    uint8_t markt_type = 0;  // super hyper max ?
    uint8_t markt_qte = 0;  // how many ?
    uint8_t markt_prevqte = 0;  // how many I already have ?
    uint16_t markt_price = 0;  // self-explanatory
    uint8_t markt_mode = 0;  // 2 = seller mode 1 buy 0 cancel
    uint8_t markt_id = 0;  // id of the item to be bought
    uint8_t tmp_inv[7];  // store the tmp inventory
    real_t tmp_real;
    real_t real_prevqte;
    real_t real_qte;
    uint8_t tmp_get_tile = 0;
    uint8_t tmp_get_tile_2 = 0;
    char tmp_str_nn[21] = "Bonjour, ";
    strncat(tmp_str_nn, sav.name, 9);
    strncat(tmp_str_nn, " !", 2);

    do
    {
        kb_Scan();

        if (kb_Data[3] == kb_GraphVar) {
            instant_exit = ShowMainMenu(&sav, &tilemap, &x_offset, &y_offset, 0, 1, false, false);
            delay(200);
        }

        if (kb_Data[6] == kb_Enter || kb_Data[1] == kb_2nd) {
            if (direction == 0 /*up*/) {
                if (gfx_GetTile(&tilemap, x_offset + x + 8, y_offset + y + 4) == 61) {  // POKEMON CENTER DOOR
                    sav.location = 1;
                    x_offset = 0;
                    y_offset = 0;
                    x = 152;
                    y = 171;
                    free_control_vertical = true;
                    free_control_horizontal = true;
                    is_down = true;
                    change_tilemap(sav.map_num, sav.location, &tilemap, true);
                } else if (gfx_GetTile(&tilemap, x + 8, y + 8) == 167) {  // COMPUTER
                    computer_on = !(computer_on);
                    if (computer_on) {
                        ShowText("Le PC est hors-service !");
                        computer_on = false;
                        // gfx_SetTileMapped(&tilemap, 13, 4, 172);
                    } else {
                        gfx_SetTileMapped(&tilemap, 13, 4, 151);
                    }
                    gfx_SwapDraw();
                    delay(200);
                } else if (gfx_GetTile(&tilemap, x + 8, y + 4) == 165) {  // POKEMON CENTER HEALER DESK
                    ShowText(tmp_str_nn);
                    if (AskBoolText("Voulez-vous soigner votre equipe ?")) {
                        redraw_center(is_healing);
                        ShowText("Tres bien ! Laissez-moi un instant ...");
                        is_healing = true;
                        redraw_center(is_healing);
                        delay(3000);
                        is_healing = false;
                        redraw_center(is_healing);
                        ShowText("C'est fait ! A bientot !");
                    }
                    delay(200);
                    kb_Scan();
                } else if (gfx_GetTile(&tilemap, x_offset + x + 8, y_offset + y + 4) == 57) {  // HOUSE DOOR
                    ShowText("La porte est ferme ...");
                    delay(200);
                } else if (gfx_GetTile(&tilemap, x_offset + x + 8, y_offset + y + 4) == 121) {  // MARKET CENTER DOOR
                    sav.location = 2;
                    x_offset = 0;
                    y_offset = 0;
                    x = 120;
                    y = 166;
                    free_control_vertical = true;
                    free_control_horizontal = true;
                    is_down = true;
                    change_tilemap(sav.map_num, sav.location, &tilemap, true);
                } else if (gfx_GetTile(&tilemap, x_offset + x + 8, y_offset + y + 4) == 230 && sav.map_num == 1) { // SWITCH TO DADARK_CAVE
                    x = 40;
                    y = 219;
                    y_offset = 256;
                    is_right = false;
                    is_down = true;
                    sav.map_num = 2;
                    x_offset = 0;
                    change_tilemap(2/* = uthon*/, 0/* = outisde*/, &tilemap, true);
                }
            } else if (direction == 1/*down*/) {
                if (gfx_GetTile(&tilemap, x + 8, y + 8) == 138 || gfx_GetTile(&tilemap, x + 8, y + 8) == 139) {  // POKEMON CENTER INDOORS
                    sav.location = 0;
                    x = 152;
                    y = 112;
                    if (sav.map_num == 0) {
                        x_offset = 168;
                        y_offset = 112;
                    }
                    free_control_horizontal = false;
                    free_control_vertical = false;
                    change_tilemap(sav.map_num, sav.location, &tilemap, true);
                } else if (gfx_GetTile(&tilemap, x + 8, y + 8) == 181 || gfx_GetTile(&tilemap, x + 8, y + 8) == 182) {  // MARKET INDOORS
                    sav.location = 0;
                    x = 152;
                    y = 112;
                    if (sav.map_num == 0) {
                        x_offset = 8;
                        y_offset = 268;
                    }
                    free_control_horizontal = false;
                    free_control_vertical = false;
                    change_tilemap(sav.map_num, sav.location, &tilemap, true);
                }
            } else if (direction == 2/*left*/) {
                if (gfx_GetTile(&tilemap, x - 4, y + 8) == 180) {  // MARKET SELLER
                    ShowText("Bienvenue dans la boutique !");
                    markt_mode = 0;
                    if (AskBoolText("Tu veux acheter des objets ?")) {
                        markt_mode = 1;
                    } else if (AskBoolText("Tu veux vendre des objets ?")) {
                        markt_mode = 2;
                    }
                    if (markt_mode != 0) {
                        tmp_inv[0] = sav.pots;
                        tmp_inv[1] = sav.spots;
                        tmp_inv[2] = sav.hpots;
                        tmp_inv[3] = sav.mpots;
                        tmp_inv[4] = sav.pballs;
                        tmp_inv[5] = sav.gballs;
                        tmp_inv[6] = sav.uballs;
                            
                        markt_sel = AskNumText("0: annul 1: potions 2: balls", 2, 100);
                        if (markt_sel != 0) {
                            if (markt_sel == 1) {
                                markt_type = AskNumText("1: Potion 2: Super 3: Hyper 4: Max", 4, 100);
                            } else {
                                markt_type = AskNumText("1: Poke 2: Super 3: Hyper", 3, 100);
                            }
                            if (markt_type != 0) {
                                markt_id = markt_sel == 1 ? markt_type - 1 : markt_type + 3;
                                markt_prevqte = tmp_inv[markt_id];  // How many the player already have ??

                                char ask_string[48] = "";
                                char price_str[6] = "";
                                char prevqte_str[6] = "";
                                char qte_str[6] = "";
                                char finprice_str[7] = "";
                                char bag_qte[8] = "";
                                char final_ask[52] = "";

                                tmp_real = os_FloatToReal((float)(prices[markt_id] * 100.0f));
                                os_RealToStr(price_str, &tmp_real, 6, 1, -1);
                                real_prevqte = os_FloatToReal((float)markt_prevqte);
                                os_RealToStr(prevqte_str, &real_prevqte, 6, 1, -1);

                                strncat(ask_string, "Combien ?            Prix: ", 28);
                                strncat(ask_string, price_str, prices[markt_id] > 9 ? 4 : 3);
                                strncat(ask_string, " $   Sac: ", 11);
                                strncat(ask_string, prevqte_str, 4);

                                markt_qte = AskNumText(ask_string, markt_mode == 1 ? (255 - markt_prevqte) : markt_prevqte, 40);
                                markt_price = markt_qte * (prices[markt_id]);

                                real_qte = os_FloatToReal((float)markt_qte);
                                os_RealToStr(qte_str, &real_qte, 6, 1, -1);
                                real_t real_price = os_FloatToReal((float)markt_price);
                                os_RealToStr(finprice_str, &real_price, 6, 1, -1);
                                real_t real_bagqte = os_FloatToReal((float)sav.money);
                                os_RealToStr(bag_qte, &real_bagqte, 6, 1, -1);

                                strncat(final_ask, qte_str, 3);
                                strncat(final_ask, " ? Ca fera ", 11);
                                strncat(final_ask, finprice_str, 6);
                                strncat(final_ask, "00", 2);
                                strncat(final_ask, " $", 2);
                                while (strlen(final_ask) !=35) {
                                    strncat(final_ask, " ", 1);
                                }
                                strncat(final_ask, "Sac: ", 5);
                                strncat(final_ask, bag_qte, 5);
                                strncat(final_ask, "00 $", 4);


                                if (AskBoolText(final_ask)) {

                                    if ((markt_price <= sav.money && markt_mode == 1) || (markt_mode == 2 && !(sav.money + markt_price < sav.money))) {
                                        uint8_t multiplier = 1;
                                        if (markt_mode == 2) {
                                            multiplier = -1;
                                        }
                                        if (multiplier == 1) {
                                            sav.money -= markt_price;
                                        } else {
                                            sav.money += markt_price;
                                        }
                                        switch (markt_id) {
                                            case 0:
                                                sav.pots += (markt_qte*multiplier);
                                                break;
                                            case 1:
                                                sav.spots += (markt_qte*multiplier);
                                                break;
                                            case 2:
                                                sav.hpots += (markt_qte*multiplier);
                                                break;
                                            case 3:
                                                sav.mpots += (markt_qte*multiplier);
                                                break;
                                            case 4:
                                                sav.pballs += (markt_qte*multiplier);
                                                break;
                                            case 5:
                                                sav.gballs += (markt_qte*multiplier);
                                                break;
                                            case 6:
                                                sav.uballs += (markt_qte*multiplier);
                                                break;
                                            default:
                                                break;
                                        }
                                    } else {
                                        ShowText("Vous n'avez pas assez d'argent !");
                                    }
                                }
                            }
                        }
                    }
                    delay(100);
                }
            }
        }

        if (x > 299 && sav.map_num == 0) {  // SWITCH TO ROUTE 1 <- UTHON
            x = 6;
            y = 184;
            is_right = false;
            sav.map_num = 1;
            x_offset = 0;
            y_offset = 0;
            change_tilemap(1/* = route 1*/, 0/* = outisde*/, &tilemap, true);
        }
        if (x > 31 && x < 47 && y > 219 && sav.map_num == 2) {  // SWITCH TO ROUTE 1 <- DADARK CAVE
            x = 240;
            y = 28;
            is_right = true;
            is_down = false;
            sav.map_num = 1;
            x_offset = 784;
            y_offset = 0;
            change_tilemap(1/* = route 1*/, 0/* = outisde*/, &tilemap, true);
        }

        if (x < 6 && sav.map_num == 1) {  // SWITCH TO UTHON <- ROUTE 1
            x = 299;
            y = 112;
            y_offset = 165;
            is_right = true;
            sav.map_num = 0;
            x_offset = 194;
            change_tilemap(0/* = uthon*/, 0/* = outisde*/, &tilemap, true);
        }
        

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

        if (sav.location == 1) {
            gfx_TransparentSprite_NoClip(tileset_tile_177, 160, 74);
            gfx_TransparentSprite_NoClip(tileset_tile_193, 160, 90);
        }
        
        if (direction == 0) {
            if (is_male) {
                if (!(moved)) { // MALE UP
                    gfx_TransparentSprite_NoClip(sprite_tile_6, x, y);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_8, x, y);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_7, x, y);
                }
            } else {
                if (!(moved)) {  // FEMALE UP
                    gfx_TransparentSprite_NoClip(sprite_tile_15, x, y);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_17, x, y);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_16, x, y);
                }
            }
        } else if (direction == 1) {
            if (is_male) {
                if (!(moved)) {  // MALE DOWN
                    gfx_TransparentSprite_NoClip(sprite_tile_0, x, y);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_2, x, y);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_1, x, y);
                }
            } else {
                if (!(moved)) {  // FEMALE DOWN
                    gfx_TransparentSprite_NoClip(sprite_tile_9, x, y);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_11, x, y);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_10, x, y);
                }
            }
        } else if (direction == 2) {  // MALE - FEMALE LEFT
            if (!(moved)) {
                gfx_TransparentSprite_NoClip(sprite_tile_18, x, y);
            } else if (ani) {
                gfx_TransparentSprite_NoClip(sprite_tile_20, x, y);
            } else {
                gfx_TransparentSprite_NoClip(sprite_tile_19, x, y);
            }
        } else {
            if (is_male) {
                if (!(moved)) {  // MALE RIGHT
                    gfx_TransparentSprite_NoClip(sprite_tile_3, x, y);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_5, x, y);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_4, x, y);
                }
            } else {
                if (!(moved)) {  // FEMALE RIGHT
                    gfx_TransparentSprite_NoClip(sprite_tile_12, x, y);
                } else if (ani) {
                    gfx_TransparentSprite_NoClip(sprite_tile_14, x, y);
                } else {
                    gfx_TransparentSprite_NoClip(sprite_tile_13, x, y);
                }
            }
        }
        if (sav.map_num == 2) {
            gfx_SetColor(3);
            gfx_FillRectangle(x - 304, y - 222, 212, 462);
            gfx_FillRectangle(x + 108, y - 222, 212, 462);
            gfx_FillRectangle(x - 92, y + 68, 200, 172);
            gfx_FillRectangle(x - 92, y - 222, 200, 170);
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
                tmp_get_tile = gfx_GetTile(&tilemap, x_offset + x + 8, y_offset + y + 18);
                if (free_control_vertical) {
                    if (!(can_collide[tmp_get_tile]) && !(tmp_get_tile == 33)) {
                        y += to_walk;
                    }
                    if (y >= 112 && !(is_down)) {
                        y = 112;
                        free_control_vertical = false;
                    }
                }
                else if (y_offset < (tilemap_height * TILE_HEIGHT) - (TILEMAP_DRAW_HEIGHT * TILE_HEIGHT))
                {
                    free_control_vertical = false;
                    if (!(can_collide[tmp_get_tile]) && !(tmp_get_tile == 33)) {
                        y_offset += to_walk; 
                    }
                } else {
                    free_control_vertical = true;
                    is_down = true;
                    if (!(can_collide[tmp_get_tile]) && !(tmp_get_tile == 33)) {
                        y += to_walk;
                    }
                }
                break;

            case kb_Left:
                direction = 2;
                moved = true;
                tmp_get_tile = gfx_GetTile(&tilemap, x_offset + x - 2, y_offset + y + 8);
                if (free_control_horizontal) {
                    if (!(can_collide[tmp_get_tile])) {
                        x -= to_walk;
                    }
                    if (x <= 152 && is_right) {
                        x = 152;
                        free_control_horizontal = false;
                        is_right = false;
                    }
                }
                else if (x_offset)  // = (x_offset == 0)
                {   
                    if (!(can_collide[tmp_get_tile])) { // x_offset + 150 
                        x_offset -= to_walk;
                    }
                } else {
                    free_control_horizontal = true;
                    is_right = false;
                    if (!(can_collide[tmp_get_tile])) {
                        x -= to_walk;
                    }
                }
                break;

            case kb_Right:
                direction = 3;
                moved = true;
                tmp_get_tile = gfx_GetTile(&tilemap, x_offset + x + 18, y_offset + y + 8);
                if (free_control_horizontal) {
                    if (!(can_collide[tmp_get_tile])) {
                        x += to_walk;
                    }
                    if (x >= 152 && !(is_right)) {
                        x = 152;
                        free_control_horizontal = false;
                    }
                }
                else if (x_offset < (tilemap_width * TILE_WIDTH) - (TILEMAP_DRAW_WIDTH * TILE_WIDTH))
                {
                    if (!(can_collide[tmp_get_tile])) {
                        x_offset += to_walk;
                    }
                } else {
                    free_control_horizontal = true;
                    is_right = true;
                    if (!(can_collide[tmp_get_tile])) {
                        x += to_walk;
                    }
                }
                break;

            case kb_Up:
                direction = 0;
                moved = true;
                tmp_get_tile = gfx_GetTile(&tilemap, x_offset + x + 8, y_offset + y + 4);
                tmp_get_tile_2 = gfx_GetTile(&tilemap, x_offset + x + 8, y_offset + y + 15);
                if (free_control_vertical) {
                    if (!(can_collide[tmp_get_tile]) && !(tmp_get_tile_2 == 33)) {
                        y -= to_walk;
                    }
                    if (y <= 112 && is_down) {
                        y = 112;
                        free_control_vertical = false;
                        is_down = false;
                    }
                }
                else if (y_offset) // = (y_offset == 0)
                {
                    if (!(can_collide[tmp_get_tile]) && !(tmp_get_tile_2 == 33)) {
                        y_offset -= to_walk;
                    }
                } else {
                    free_control_vertical = true;
                    is_down = false;
                    if (!(can_collide[tmp_get_tile]) && !(tmp_get_tile_2 == 33)) {
                        y -= to_walk;
                    }

                }
                break;

            default:
                break;

            
        }

        if (y_offset > 16777200) {
            y_offset = 0;
        }
        if (x_offset > 16777200) {
            x_offset = 0;
        }  // security
        if (sav.location == 2) {
            if (y > 166) {
                y -= to_walk;
            }
        }
        if (free_control_horizontal || free_control_vertical) {
            if (x > 304) {
                x -= to_walk;
            }
            if (x > 16777200) {
                x = 0;
            }
            if (x < 0) {
                x += to_walk;
            }
            if (y > 222) { // 234
                y -= to_walk;
            }
            if (y < 0) {
                y += to_walk;
            }
            if (y > 240 && y <= 255) {
                y = 0;
            }
        }
        if (ENABLE_DEBUG) {
            gfx_SetTextXY(0, 0);
            gfx_PrintUInt(x_offset, 6);
            gfx_SetTextXY(0, 8);
            gfx_PrintUInt(x, 6);
            gfx_SetTextXY(0, 16);
            gfx_PrintUInt(y_offset, 6);
            gfx_SetTextXY(0, 24);
            gfx_PrintUInt(y, 6);
        }
        gfx_SwapDraw();
        
    } while (kb_Data[1] != kb_Del && kb_Data[6] != kb_Clear && !(instant_exit));
    if (!(instant_exit)) {
        sav.free_control_vertical = free_control_vertical;
        sav.free_control_horizontal = free_control_horizontal;
        sav.x_offset = x_offset;
        sav.y_offset = y_offset;
        sav.x = x;
        sav.y = y;
        sav.is_down = is_down;
        sav.is_right = is_right;
        sav.direction = direction;
        save(&sav);
    }
    gfx_ZeroScreen();
    gfx_BlitBuffer();
    free(sprite_tile_18);
    free(sprite_tile_19);
    free(sprite_tile_20);
    gfx_End();

    return 0;
}
