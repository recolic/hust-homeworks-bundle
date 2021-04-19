#include "common.h"

#include <stdio.h>
//#include <linux/input.h>
#include "input.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

static struct finger_info{
	int x;
	int y;
	int event;
} infos[FINGER_NUM_MAX];
static int touch_fd;
static int cur_slot = 0;


/*return:
  TOUCH_NO_EVENT
  TOUCH_PRESS
  TOUCH_MOVE
  TOUCH_RELEASE
x: 0~1023
y: 0~599
finger: 0,1,2,3,4
*/
int touch_read1(int *x, int *y, int *finger)
{
	struct input_event data;
	int n, ret;
	if((n = read(touch_fd, &data, sizeof(data))) != sizeof(data)){
		printf("touch_read error %d, errno=%d\n", n, errno);
		return TOUCH_NO_EVENT;
	}
//	printf("event read: type-code-value = %d-%d-%d\n", data.type, data.code, data.value);
	switch(data.type)
	{
	case EV_ABS:
		switch(data.code)
		{
		case ABS_MT_SLOT:
			if(data.value >= 0 && data.value < FINGER_NUM_MAX){
				int old = cur_slot;
				cur_slot = data.value;
				if(infos[old].event != TOUCH_NO_EVENT){
					*x = infos[old].x;
					*y = infos[old].y;
					*finger = old;
					ret = infos[old].event;
					infos[old].event = TOUCH_NO_EVENT;
					return ret;
				}
			}
			break;
		case ABS_MT_TRACKING_ID:
			if(data.value == -1){
				*x = infos[cur_slot].x;
				*y = infos[cur_slot].y;
				*finger = cur_slot;
				infos[cur_slot].event = TOUCH_NO_EVENT;
				return TOUCH_RELEASE;
			}
			else{
				infos[cur_slot].event = TOUCH_PRESS;
			}
			break;
		case ABS_MT_POSITION_X:
			infos[cur_slot].x = data.value;
			if(infos[cur_slot].event != TOUCH_PRESS){
					infos[cur_slot].event = TOUCH_MOVE;
				}
				break;
			case ABS_MT_POSITION_Y:
				infos[cur_slot].y = data.value;
				if(infos[cur_slot].event != TOUCH_PRESS){
					infos[cur_slot].event = TOUCH_MOVE;
				}
				break;
		}
		break;
	case EV_SYN:
		switch(data.code)
		{
		case SYN_REPORT:
			if(infos[cur_slot].event != TOUCH_NO_EVENT){
				*x = infos[cur_slot].x;
				*y = infos[cur_slot].y;
				*finger = cur_slot;
				ret = infos[cur_slot].event;
				infos[cur_slot].event = TOUCH_NO_EVENT;
				return ret;
			}
			break;
		}
		break;
	}
	return TOUCH_NO_EVENT;
}

#define BTN_POS_X 10
#define BTN_POS_Y 10
#define BTN_W 40
#define BTN_H 40
#define LINE_COLOR FB_COLOR(255,100,100)
#define BTN_COLOR FB_COLOR(255,255,0)
struct rlib_pos {int x, y;};
void draw_btn() {
	const int padding = 5;
	fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,FB_COLOR(255,255,255));
	fb_draw_rect(BTN_POS_X, BTN_POS_Y, BTN_W, BTN_H, BTN_COLOR);
	fb_draw_text(BTN_POS_X+padding, BTN_POS_Y+padding, "clear", 20, BTN_COLOR);
}
bool pos_in_btn(int x, int y) {
	return x > BTN_POS_X && x < BTN_POS_X + BTN_W && y > BTN_POS_Y && y < BTN_POS_Y + BTN_H;
}
void on_touch_read_finish(int x, int y, int finger, int eventId) {
    static struct rlib_pos history_poss[FINGER_NUM_MAX];
    if(!(finger < FINGER_NUM_MAX && finger >= 0))
		return;
	printf("DEBUG: finger=%d\n", finger);
    switch(eventId) {
        case TOUCH_PRESS:
			if(pos_in_btn(x, y)) {
				draw_btn();
			}
			else {
            	history_poss[finger].x = x;
            	history_poss[finger].y = y;
				fb_draw_pixel(x, y, LINE_COLOR);
			}
			break;
        case TOUCH_MOVE:
			fb_draw_line(x, y, history_poss[finger].x, history_poss[finger].y, LINE_COLOR);
            history_poss[finger].x = x;
            history_poss[finger].y = y;
			break;
    }

}
int touch_read(int *px, int *py, int *pfinger) {
	int x,y,finger;
    int type = touch_read1(&x, &y, &finger);
    on_touch_read_finish(x, y, finger, type); // bug
	fb_update();
	*px = x; *py = y; *pfinger = finger;
    return type;
}

void touch_init(char *dev)
{
	touch_fd = open(dev, O_RDONLY);
	if(touch_fd < 0){
		printf("touch_init open %s error!errno = %d\n", dev, errno);
		return;
	}
	font_init("/data/local/font.ttc");
	draw_btn();
	fb_update();
	return;
}