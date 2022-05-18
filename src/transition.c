#include <graphx.h>
#include <tice.h>

void Transition() {
	gfx_SetColor(3);
	// while (radius > 0) {
	// 	for (uint8_t i = 0; i < 50; i++) {
	// 		if (radius <= 160) {
	// 			gfx_Circle_NoClip(160, 120, radius);
	// 			gfx_Circle_NoClip(159, 119, radius);
	// 			gfx_Circle_NoClip(158, 118, radius);
	// 			gfx_Circle_NoClip(157, 117, radius);
	// 			gfx_Circle_NoClip(161, 119, radius);
	// 			gfx_Circle_NoClip(161, 119, radius);
	// 			gfx_Circle_NoClip(159, 121, radius);
	// 			gfx_Circle_NoClip(160, 121, radius);
	// 		} else {
	// 			gfx_Circle(160, 120, radius);
	// 			gfx_Circle(159, 119, radius);
	// 			gfx_Circle(158, 118, radius);
	// 			gfx_Circle(157, 117, radius);
	// 			gfx_Circle(161, 119, radius);
	// 			gfx_Circle(161, 119, radius);
	// 			gfx_Circle(159, 121, radius);
	// 			gfx_Circle(160, 121, radius);
	// 		}
	// 		// gfx_SwapDraw();
	// 		if (radius != 0) { 
	// 			radius = radius - 1;
	// 		} else {
	// 			break;
	// 		}
	// 	}
	// 	gfx_BlitBuffer();
	// }
	// delay(100);
	uint8_t y = 0;
	uint24_t x = 0;
	while (y < 120) {
		gfx_HorizLine_NoClip(0, y, 320);
		gfx_HorizLine_NoClip(0, y + 1, 320);
		gfx_HorizLine_NoClip(0, 240 - y, 320);
		gfx_HorizLine_NoClip(0, 240 - y - 1, 320);
		gfx_VertLine_NoClip(x, 0, 240);
		gfx_VertLine_NoClip(x + 1, 0, 240);
		gfx_VertLine_NoClip(320 - x, 0, 240);
		gfx_VertLine_NoClip(320 - x - 1, 0, 240);
		y += 2;
		x += 2;
		gfx_BlitBuffer();
	}
}