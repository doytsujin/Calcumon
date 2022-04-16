#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

void ShowText(char* text) {
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
	do {
		
		if (!(finished)) {
			gfx_BlitBuffer();
		}
        delay(10);
        kb_Scan();
        if (current_char == length) {  // max length = 34
        	finished = true;
        	gfx_SetColor(5);
        	gfx_FillTriangle_NoClip(292, 214, 296, 219, 301, 214);
        	gfx_BlitBuffer();
        } else {
        	if (current_char > 34 && !(jumped)) {
        		jumped = true;
        		gfx_SetTextXY(24, 208);

        	} else {
        		gfx_PrintChar(text[current_char]);
        		current_char++;
        	}
   
        }
        if ((kb_Data[6] == kb_Enter || kb_Data[1] == kb_2nd) && finished) {
        		can_exit = true;
        }
        if (kb_Data[6] == kb_Clear) {
        	can_exit = true;
        }

	} while (!(can_exit));
}