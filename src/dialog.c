#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

uint8_t _ShowText(char* text, uint8_t mode) { // mode 0: just print 1: bool 2: ask for num
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
        if (mode == 1 && finished && (kb_Data[7] == kb_Up || kb_Data[7] == kb_Down)) {
        	selection = !(selection);
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

	return return_val;
}

void ShowText(char* text) {
	_ShowText(text, 0);
}

bool AskBoolText(char* text) {
	return ((bool)_ShowText(text, 1));
}

uint8_t AskNumText(char* text) {
	return _ShowText(text, 2);
}