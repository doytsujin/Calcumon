#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

#include "gfx/gfx.h"

#include "save.h"
#include "dialog.h"
#include "strings.h"

uint8_t ShowBag(SaveData* save) {
	gfx_SetPalette(pkmn_palette, sizeof_pkmn_palette, 0);
	gfx_FillScreen(8);
	gfx_SetColor(9);
	gfx_FillRectangle_NoClip(3, 3, 314, 234);
	gfx_BlitBuffer();
	gfx_SetTextBGColor(9);
	InstantPrintHugeText("SAC", 136, 9);
	gfx_SetTextBGColor(8);
	gfx_SetColor(8);
	gfx_FillRectangle_NoClip(19, 33, 282, 188);
	uint8_t rec_y;  // y coord for drawing
	uint8_t bag_sel = 0;  // current index selected
	uint8_t _col = 11;  // temp color var
	uint8_t drw_selection = 0;  // index for drawing
	bool break_for_confirm = false;  // if true, get out of the loop and confirm player entered enter or 2nd key;
	char _mballs_str[15] = "Master Ball: ";
	if (save->mball) {
		strncat(_mballs_str, "V", 1);
	} else {
		strncat(_mballs_str, "X", 1);
	}
	gfx_sprite_t* item_icon;
	uint8_t to_return = 0;
	uint8_t tmp_inv[7] = {
		save->pots,
		save->spots,
		save->hpots,
		save->mpots,
		save->pballs,
		save->gballs,
		save->uballs,
	};  // tmp inventory for items display
	bool pressed = false;  // hold if a key is pressed
	bool cl = false;  // blue or green ?
	for (rec_y = 36; rec_y < 218; rec_y += 26) {
		if (cl) {
			gfx_SetColor(13);
		} else {
			gfx_SetColor(11);
		}
		cl = !(cl);
		gfx_FillRectangle_NoClip(22, rec_y, 276, 26);
	}
	for (uint8_t ind = 0; ind < 7; ind++) {
		if (tmp_inv[ind] != 0) {
			if (ind < 4) {
				item_icon = pots_tileset_tiles[ind];
			} else {
				item_icon = balls_tileset_tiles[ind - 4];
			}
			gfx_TransparentSprite_NoClip(item_icon, 44, 39 + (25*drw_selection));
			gfx_SetTextBGColor(_col);
			gfx_PrintStringXY(items_name[ind], 67, 46 + (25*drw_selection));
			gfx_PrintStringXY("x", 260, 46 + (25*drw_selection));
			gfx_PrintUInt(tmp_inv[ind], 3);
			drw_selection++;
			if (_col == 11) {
				_col = 13;
			} else {
				_col = 11;
			}
		}
	}
	gfx_SetTextBGColor(9);
	gfx_PrintStringXY("2nd/Entr: Utiliser", 9, 225);
	gfx_PrintStringXY("Alpha/(-): Quitt.", 180, 225);
	gfx_PrintStringXY(_mballs_str, 203, 6);
	gfx_PrintStringXY("Util. : [prgm]", 203, 16);
	gfx_BlitBuffer();
	delay(300);
	while (kb_Data[6] != kb_Clear && kb_Data[2] != kb_Alpha && kb_Data[5] != kb_Chs && !(break_for_confirm)) {
		kb_Scan();
		pressed = true;
		if (kb_Data[7] == kb_Down) {
			if (bag_sel != 6) {
				bag_sel++;
			}
		} else if (kb_Data[7] == kb_Up) {
			if (bag_sel != 0) {
				bag_sel -= 1;
			}
		} else {
			pressed = false;
		}
		if (pressed) {
			delay(75);
		}
		_col = 11;
		for (uint8_t iii = 0; iii < 7; iii++) {
			gfx_SetColor(_col);
			gfx_FillTriangle_NoClip(31, 44 + (26*iii), 37, 48+ (26*iii), 31, 53+ (26*iii));
			if (_col == 11) {
				_col = 13;
			} else {
				_col = 11;
			}
		}
		gfx_SetColor(2);
		gfx_FillTriangle_NoClip(31, 44 + (26*bag_sel), 37, 48+ (26*bag_sel), 31, 53+ (26*bag_sel));
		if (kb_Data[6] == kb_Enter || kb_Data[1] == kb_2nd) {
			break_for_confirm = true;
		}
		gfx_BlitBuffer();
	}
	if (break_for_confirm) {
		to_return = bag_sel;
	} else {
		to_return = 255;
	}
	gfx_FillScreen(8);
	gfx_SetColor(9);
	gfx_FillRectangle_NoClip(3, 3, 314, 234);
	gfx_SetPalette(global_palette, sizeof_global_palette, 0);
	gfx_BlitBuffer();
	return to_return;
}