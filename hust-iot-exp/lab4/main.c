#include <stdio.h>
#include "../common/common.h"

int main(int argc, char *argv[])
{
	fb_init("/dev/graphics/fb0");
	fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,FB_COLOR(255,255,255));
	fb_update();

	touch_init("/dev/input/event3");
	
	int type,x,y,finger,i;
	while(1){
		type = touch_read(&x,&y,&finger);
		switch(type){
			case TOUCH_PRESS:
				printf("TOUCH_PRESS：x=%d,y=%d,finger=%d\n",x,y,finger);
				break;
			case TOUCH_MOVE:
				printf("TOUCH_MOVE：x=%d,y=%d,finger=%d\n",x,y,finger);
				break;
			case TOUCH_RELEASE:
				printf("TOUCH_RELEASE：x=%d,y=%d,finger=%d\n",x,y,finger);
				break;
			default:
				break;
		}
	}
	return 0;
	
}
