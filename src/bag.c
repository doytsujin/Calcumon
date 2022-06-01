#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

#include "gfx/gfx.h"

#include "save.h"
#include "dialog.h"

void ShowBag(SaveData* save) {
	gfx_SetPalette(pkmn_palette, sizeof_pkmn_palette, 0);
	gfx_FillScreen(8);
	gfx_SetColor(9);
	gfx_FillRectangle_NoClip(3, 3, 314, 234);
	gfx_SetTextBGColor(9);
	InstantPrintHugeText("SAC", 136, 9);
	gfx_SetTextBGColor(8);
	gfx_SetColor(8);
	gfx_FillRectangle_NoClip(19, 33, 282, 188);
	uint8_t rec_y;
	uint8_t bag_sel = 0;
	uint8_t _col = 0;
	bool pressed = false;
	bool cl = false;
	for (rec_y = 36; rec_y < 218; rec_y += 26) {
		if (cl) {
			gfx_SetColor(13);
		} else {
			gfx_SetColor(11);
		}
		cl = !(cl);
		gfx_FillRectangle_NoClip(22, rec_y, 276, 26);
	}
	delay(100);
	gfx_BlitBuffer();
	while (kb_Data[6] != kb_Clear && kb_Data[2] != kb_Alpha) {
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
		gfx_BlitBuffer();
	}
	gfx_SetPalette(global_palette, sizeof_global_palette, 0);
}