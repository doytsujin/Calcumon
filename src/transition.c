#include <graphx.h>
#include <tice.h>

void Transition() {
	uint8_t radius = 200;
	gfx_SetColor(3);
	while (radius != 0) {
		if (radius <= 160) {
			gfx_Circle_NoClip(160, 120, radius);
			gfx_Circle_NoClip(159, 119, radius);
			gfx_Circle_NoClip(158, 118, radius);
			gfx_Circle_NoClip(157, 117, radius);
			gfx_Circle_NoClip(161, 119, radius);
			gfx_Circle_NoClip(161, 119, radius);
			gfx_Circle_NoClip(159, 121, radius);
			gfx_Circle_NoClip(160, 121, radius);
		} else {
			gfx_Circle(160, 120, radius);
			gfx_Circle(159, 119, radius);
			gfx_Circle(158, 118, radius);
			gfx_Circle(157, 117, radius);
			gfx_Circle(161, 119, radius);
			gfx_Circle(161, 119, radius);
			gfx_Circle(159, 121, radius);
			gfx_Circle(160, 121, radius);
		}
		// gfx_SwapDraw();
		gfx_BlitBuffer();
		radius = radius - 1;
	}
	delay(100);
}