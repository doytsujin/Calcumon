#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include <save.h>

#include "dialog.h"
#include "bag.h"

#include "gfx/gfx.h"

void UpColor(uint8_t* color) {
	gfx_SetColor(*color);
	*color += 1;
}

bool ShowMainMenu(SaveData* _save, gfx_tilemap_t* tilmap, unsigned int* _x, unsigned int* _y, uint8_t selec, uint8_t prev_selec, bool back, bool back2, bool show_bg) {
	if (show_bg) {
		gfx_Tilemap(tilmap, *_x, *_y);
	} else {
		gfx_FillScreen(3);
	}
	gfx_SetTextFGColor(3);
	gfx_SetTextBGColor(4);
	gfx_SetColor(5);
	gfx_FillRectangle_NoClip(32, 32, 255, 175);
	gfx_SetColor(4);
	gfx_FillRectangle_NoClip(35, 35, 249, 169);
	gfx_SetTextXY(44, 42);
	gfx_PrintUInt(_save->money * 100, 7);
	gfx_PrintString(" $");
	gfx_SetTextXY(224, 44);
	if (_save->is_ti) {
		gfx_PrintString("TI");
	} else {
		gfx_PrintString("CE");
	}
	gfx_PrintStringXY(_save->name, 66, 191);
	gfx_PrintStringXY("CalcuDex: ", 174, 191);
	uint8_t dex_num = 0;
	for (uint8_t _i = 0; _i > 19; _i++) {
		BitBools _tmp = _save->found_mons[_i];
		if (_tmp.b1) {
			dex_num++;
		}
		if (_tmp.b2) {
			dex_num++;
		}
		if (_tmp.b3) {
			dex_num++;
		}
		if (_tmp.b4) {
			dex_num++;
		}
		if (_tmp.b5) {
			dex_num++;
		}
		if (_tmp.b6) {
			dex_num++;
		}
		if (_tmp.b7) {
			dex_num++;
		}
		if (_tmp.b8) {
			dex_num++;
		}
	}
	gfx_PrintUInt(dex_num, 3);
	if (_save->is_male) {
		gfx_TransparentSprite_NoClip(sprite_tile_0, 44, 187);
	} else {
		gfx_TransparentSprite_NoClip(sprite_tile_9, 44, 187);
	}
	uint8_t color = 6;
	UpColor(&color);
	gfx_FillRectangle_NoClip(43, 69, 108, 32);
	UpColor(&color);
	gfx_FillRectangle_NoClip(46, 72, 102, 26);
	UpColor(&color);
	gfx_FillRectangle_NoClip(43, 110, 108, 32);
	UpColor(&color);
	gfx_FillRectangle_NoClip(46, 113, 102, 26);
	UpColor(&color);
	gfx_FillRectangle_NoClip(43, 151, 108, 32);
	UpColor(&color);
	gfx_FillRectangle_NoClip(46, 154, 102, 26);
	UpColor(&color);
	gfx_FillRectangle_NoClip(168, 69, 108, 32);
	UpColor(&color);
	gfx_FillRectangle_NoClip(171, 72, 102, 26);
	UpColor(&color);
	gfx_FillRectangle_NoClip(168, 110, 108, 32);
	UpColor(&color);
	gfx_FillRectangle_NoClip(171, 113, 102, 26);
	UpColor(&color);
	gfx_FillRectangle_NoClip(168, 151, 108, 32);
	UpColor(&color);
	gfx_FillRectangle_NoClip(171, 154, 102, 26);
	InstantPrintHugeText("MENU", 130, 42);
	InstantPrintHugeText("EQUIPE", 51, 77);
	InstantPrintHugeText("SAC", 74, 120);
	InstantPrintHugeText("COMM.", 64, 160);
	InstantPrintHugeText("C.DEX", 183, 77);
	InstantPrintHugeText("SAUVE.", 181, 119);
	InstantPrintHugeText("QUITT.", 181, 160);
	uint8_t _delay = 0;
	uint8_t tmp_selec = 0;
	uint8_t tmp_prev_selec = 0;
	uint8_t selx = 41;
	bool exit = false;
	bool quit = false;

	delay(200);
	kb_Scan();
	do {
		_delay = 200;
		kb_Scan();
		if (kb_Data[6] == kb_Enter || kb_Data[1] == kb_2nd) {
			switch (selec) {
				case 0:  // TEAM
					break;
				case 1:  // BAG
					ShowBag(_save);
					exit = ShowMainMenu(_save, tilmap, _x, _y, selec, prev_selec, back, back2, show_bg);
					quit = true;
					break;
				case 2:  // COMMS
					break;
				case 3:  // CALCUDEX
					break;
				case 4:  // SAVE
					save(_save);
					ShowText("Partie Sauvegardee !");
					delay(200);
					exit = ShowMainMenu(_save, tilmap, _x, _y, selec, prev_selec, back, back2, show_bg);
					quit = true;
					break;
				case 5:  // EXIT
					exit = true;
					break;
				default:
					break;
			}
		}
		if (kb_Data[7] == kb_Down) {
			if (selec != 2 && selec != 5) {
				prev_selec = selec;
				selec++;
				back = false;
				back2 = false;
			}
		} else if (kb_Data[7] == kb_Up) {
			if (selec != 0 && selec != 3) {
				prev_selec = selec;
				selec -= 1;
				back = false;
				back2 = false;
			}
		} else if (kb_Data[7] == kb_Right) {
			if (selec < 3) {
				prev_selec = selec;
				selec += 3;
				back = true;
				back2 = false;
			}
		} else if (kb_Data[7] == kb_Left) {
			if (selec > 2) {
				prev_selec = selec;
				selec -= 3;
				back = false;
				back2 = true;
			}
		}
		 else {
			_delay = 0;
		}
		if (selec < 3) {
			tmp_selec = selec;
			tmp_prev_selec = prev_selec;
			selx = 41;
		} else {
			tmp_selec = selec - 3;
			tmp_prev_selec = prev_selec - 3;
			selx = 166;
		}
		gfx_SetColor(0);
		gfx_Rectangle_NoClip(selx, 67 + (41*tmp_selec), 111, 35);
		gfx_Rectangle_NoClip(selx + 1, 68 + (41*tmp_selec), 109, 33);
		gfx_SetColor(4);
		if (back) {
			selx = 41;
			tmp_prev_selec += 3;
		} else if (back2) {
			selx = 166;
			tmp_prev_selec -= 3;
		}
		gfx_Rectangle_NoClip(selx, 67 + (41*tmp_prev_selec), 111, 35);
		gfx_Rectangle_NoClip(selx + 1, 68 + (41*tmp_prev_selec), 109, 33);
		if (!(exit)&& !(quit)) {
			gfx_BlitBuffer();
			delay(_delay);
		}
	} while (kb_Data[3] != kb_GraphVar && kb_Data[6] != kb_Clear && kb_Data[2] != kb_Alpha && kb_Data[5] != kb_Chs && !(exit) && !(quit));
	return exit;
}
