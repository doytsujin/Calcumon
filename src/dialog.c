#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <string.h>

uint8_t _ShowText(const char* text, const uint8_t mode, const uint8_t max) { // mode 0: just print 1: bool 2: ask for num
	bool can_exit;
	bool finished;
	finished = false; /*Override previous values in case of recall*/
	can_exit = false;
	kb_Scan();
	gfx_SetColor(5);
	gfx_FillRectangle_NoClip(10, 170, 300, 60);
	gfx_SetColor(4);
	gfx_FillRectangle_NoClip(13, 173, 294, 54);
	gfx_SetTextFGColor(3);
	gfx_SetTextBGColor(4);
	gfx_SetTextXY(24, 185);
	bool jumped = false;
	uint8_t length = 0;
	for (length = 0; text[length] != '\0'; ++length);
	uint8_t current_char;
	current_char = 0;
	bool selection = true;
	uint8_t num_selection = 0;
	gfx_sprite_t* behind_box;
	if (mode != 0) {
		behind_box = gfx_MallocSprite(58, 34);
		if (behind_box == NULL) {
			gfx_End();
			os_ClrHome();
        	os_ThrowError(OS_E_MEMORY);
		}
		gfx_GetSprite_NoClip(behind_box, 252, 122);
	}
	do {
		
		if (!(finished)) {
			gfx_BlitBuffer();
		}
        delay(10);
        kb_Scan();
        if (current_char == length) {  // max length = 34
        	finished = true;
        	if (mode == 0) {
        		gfx_SetColor(5);
        		gfx_FillTriangle_NoClip(292, 214, 296, 219, 301, 214);
        		gfx_BlitBuffer();
        	} else if (mode == 1) {
        		gfx_SetColor(5);
        		gfx_FillRectangle_NoClip(252, 122, 58, 34);
        		gfx_SetColor(4);
        		gfx_FillRectangle_NoClip(255, 125, 52, 28);
        		gfx_SetColor(5);
        		if (selection) {
        			gfx_FillTriangle_NoClip(258, 128, 264, 132, 258, 137);
        		} else {
        			gfx_FillTriangle_NoClip(258, 141, 263, 145, 258, 150);
        		}
        		gfx_PrintStringXY("Oui", 270, 128);
        		gfx_PrintStringXY("Non", 270, 141);
        		gfx_BlitBuffer();
        	} else if (mode == 2) {
        		gfx_SetColor(5);
        		gfx_FillRectangle_NoClip(252, 122, 58, 34);
        		gfx_SetColor(4);
        		gfx_FillRectangle_NoClip(255, 125, 52, 28);
        		gfx_SetColor(5);
        		gfx_FillTriangle_NoClip(277, 144, 282, 150, 286, 144);
        		gfx_FillTriangle_NoClip(277, 132, 282, 126, 286, 132);
        		gfx_SetTextXY(271, 135);
        		gfx_PrintUInt(num_selection, 3);
        		gfx_BlitBuffer();
        	}
        } else {
        	if (current_char > 34 && !(jumped)) {
        		jumped = true;
        		gfx_SetTextXY(24, 208);

        	} else {
        		gfx_PrintChar(text[current_char]);
        		current_char++;
        	}
   
        }
        if (mode == 1 && finished) {
        	if (kb_Data[7] == kb_Up) {
        		selection = true;
        	} else if (kb_Data[7] == kb_Down) {
        		selection = false;
        	}
        }
        if (mode == 2 && finished) {
        	if (kb_Data[7] == kb_Up) {
        		if (!(num_selection == max)) {
        			num_selection++;
        			if (num_selection == 0) {
        				num_selection = 255;
        			}
        			delay(10);
        		}
 
        	} else if (kb_Data[7] == kb_Down) {
        		num_selection = num_selection - 1;
        		if (num_selection == 255) {
        			num_selection = 0;
        			delay(10);
        		}
        	}
        }
        if (mode == 1 && finished && (kb_Data[2] == kb_Alpha || kb_Data[5] == kb_Chs)) {
        	can_exit = true;
        	selection = false;
        }
        if ((kb_Data[6] == kb_Enter || kb_Data[1] == kb_2nd) && finished) {
        		can_exit = true;
        }
        if (kb_Data[6] == kb_Clear) {
        	can_exit = true;
        }

	} while (!(can_exit));
	uint8_t return_val = 0;
	if (mode == 1) {
		return_val = ((uint8_t)selection);
	}
	if (mode == 2) {
		return_val = (num_selection);
	}
	if (mode != 0) {
		gfx_Sprite_NoClip(behind_box, 252, 122);
		free(behind_box);
	} else {
		gfx_SetColor(4);
		gfx_FillRectangle_NoClip(292, 214, 10, 6);
	}

	return return_val;
}

char* AskText() {
	static char inpt[10] = "";
	uint8_t cc = 0;
	uint8_t sel = 0;
	char to_add;
	kb_key_t key;
	gfx_SetColor(5);
	gfx_FillRectangle_NoClip(23, 23, 274, 107);
	gfx_SetColor(4);
	gfx_FillRectangle_NoClip(26, 26, 268, 101);
	gfx_SetTextBGColor(0);
	gfx_SetTextFGColor(3);
	gfx_PrintStringXY("Entrez votre nom :", 48, 6);
	gfx_PrintStringXY("    SUPPR pour reecrire du debut.", 0, 214);
	gfx_PrintStringXY(" Appuyez sur ALPHA ou (-) pour valider.", 0, 224);
	gfx_BlitBuffer();
	delay(100);
	kb_Scan();
	while (kb_Data[5] != kb_Chs && kb_Data[2] != kb_Alpha && kb_Data[6] != kb_Clear) {
		gfx_SetTextXY(32, 32);
		kb_Scan();
		key = kb_Data[7];
		if (key == kb_Up) {
			sel -= 16;
			if (sel > 95) {
				sel += 16;
			}
		}
		if (key == kb_Down) {
			sel += 16;
			if (sel > 95) {
				sel -= 16;
			}
		}
		if (key == kb_Right && !((sel + 1) % 16 == 0)) {
			if (!(sel == 95)) {
				sel += 1;
			}
		}
		if (key == kb_Left && !(sel % 16 == 0)) {
			if (!(sel ==0)) {
				sel -= 1;
			}
		}
		if (kb_Data[6] == kb_Enter || kb_Data[1] == kb_2nd) {
			if (strlen(inpt) < 9) {
				to_add = (char)sel+32;
				strcpy(&to_add, &to_add);
				strncat(inpt, &to_add, 1);
			}
		}
		if (kb_Data[1] == kb_Del || kb_Data[6] == kb_Clear) {
			char* _tmptt = "\0";
			inpt[0] = *_tmptt;
		}
		while (cc != 96) {
			if (sel == cc) {
				gfx_SetTextBGColor(1);
			}
			gfx_PrintChar((char)cc + 32);
			gfx_SetTextBGColor(4);
			if (!(gfx_GetTextX() == 280)) {
				gfx_PrintChar(*" ");
			}
			if (gfx_GetTextX() == 280) {
				gfx_SetTextXY(32, gfx_GetTextY() + 16);
			}
			cc++;
		}

		gfx_SetTextBGColor(0);

		gfx_PrintStringXY(inpt, 40, 180);
		gfx_SetTextBGColor(4);
		gfx_BlitBuffer();
		cc = 0;
		delay(75);
	}
	return inpt;
}

void ShowText(const char* text) {
	_ShowText(text, 0, 0);
}

bool AskBoolText(const char* text) {
	return ((bool)_ShowText(text, 1, 0));
}

uint8_t AskNumText(const char* text, const uint8_t _max) {
	return _ShowText(text, 2, _max);
}

void InstantPrintHugeText(const char* text, const uint24_t x, const uint8_t y) {
	uint8_t length = 0;
	for (length = 0; text[length] != '\0'; ++length);
	gfx_sprite_t* char_img;
	gfx_sprite_t* ori_char;
	char_img = gfx_MallocSprite(16, 16);
	if (char_img == NULL) {
		gfx_End();
		os_ClrHome();
		os_ThrowError(OS_E_MEMORY);
	} else {
		for (uint8_t index = 0; index < length; index++) {
			ori_char = gfx_GetSpriteChar(text[index]);
			gfx_ScaleSprite(ori_char, char_img);
			gfx_Sprite(char_img, x + (index * 16), y);
		}
	}
	free(ori_char);
	free(char_img);
}