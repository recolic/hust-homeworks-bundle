#include "common.h"
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

static int LCD_MEM_BUFFER[SCREEN_WIDTH * SCREEN_HEIGHT];
static int *LCD_FRAME_BUFFER = NULL;

#define PURPLE	FB_COLOR(139,0,255)
#define RED		FB_COLOR(255,0,0)
#define FB_COLOR(r,g,b) (0xff000000|(r<<16)|(g<<8)|b)


static struct {
	int x1, y1, x2, y2;
} update_area = {0,0,0,0};

void fb_init(char *dev)
{
	int fd;
	struct fb_fix_screeninfo fb_fix;
	struct fb_var_screeninfo fb_var;

	if(LCD_FRAME_BUFFER != NULL) return; /*already done*/

	//First: Open the device
	if((fd = open(dev, O_RDWR)) < 0){
		printf("Unable to open framebuffer %s, errno = %d\n", dev, errno);
		return;
	}
	if(ioctl(fd, FBIOGET_FSCREENINFO, &fb_fix) < 0){
		printf("Unable to FBIOGET_FSCREENINFO %s\n", dev);
		return;
	}
	if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0){
		printf("Unable to FBIOGET_VSCREENINFO %s\n", dev);
		return;
	}

	printf("framebuffer info: bits_per_pixel=%u  width=%u  height=%u  line_length=%u  smem_len=%u\n",
		fb_var.bits_per_pixel, fb_var.xres, fb_var.yres, fb_fix.line_length, fb_fix.smem_len);

	//Second: mmap
	int *addr;
	size_t size = fb_var.xres * fb_var.yres * fb_var.bits_per_pixel/8;
	addr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if((int)addr == -1){
		printf("failed to mmap memory for framebuffer.\n");
		return;
	}
	LCD_FRAME_BUFFER = addr;
	return;
}


static void _update_area(int x, int y, int w, int h)
{
	//if((w <= 0)||(h <= 0)) return; /* sure */
	int x2 = x+w;
	int y2 = y+h;
	if(update_area.x2 == 0) {
		update_area.x1 = x;
		update_area.y1 = y;
		update_area.x2 = x2;
		update_area.y2 = y2;
	} else {
		if(update_area.x1 > x) update_area.x1 = x;
		if(update_area.y1 > y) update_area.y1 = y;
		if(update_area.x2 < x2) update_area.x2 = x2;
		if(update_area.y2 < y2) update_area.y2 = y2;
	}
	return;
}

/** copy data from mem buffer to frame buffer */
void fb_update(void)
{
	if(LCD_FRAME_BUFFER == NULL){
		printf("error: not allocate space for frame buffer\n");
		return;
	}

	if((update_area.x1 >= SCREEN_WIDTH)
		|| (update_area.x2 <= 0)
		|| (update_area.y1 >= SCREEN_HEIGHT)
		|| (update_area.y2 <= 0)) return;

	int x,y,w,h;
	x = (update_area.x1 < 0) ? 0 : update_area.x1;
	y = (update_area.y1 < 0) ? 0 : update_area.y1;
	w = (update_area.x2 > SCREEN_WIDTH)?
		SCREEN_WIDTH - x : update_area.x2 - x;
	h = (update_area.y2 > SCREEN_HEIGHT)?
		SCREEN_HEIGHT - y : update_area.y2 - y;

	int *src, *dst;
	src = LCD_MEM_BUFFER + y*SCREEN_WIDTH + x;
	dst = LCD_FRAME_BUFFER + y*SCREEN_WIDTH + x;
	while(h-- > 0){
		memcpy(dst, src, w*4);
		src += SCREEN_WIDTH;
		dst += SCREEN_WIDTH;
	}

	update_area.x2 = 0;
	return;
}


// static inline void _update_area(int x, int y, int w, int h) {}

/*======================================================================*/

void fb_draw_pixel(int x, int y, int color)
{
	if(x<0 || y<0 || x>=SCREEN_WIDTH || y>=SCREEN_HEIGHT) return;
	_update_area(x,y,1,1);
	int *tmp = LCD_MEM_BUFFER + SCREEN_WIDTH * y + x;
	*tmp = color;
	return;
}
static __attribute__((hot)) __attribute__((always_inline)) inline void fb_raw_draw_pixel(int x, int y, int color) {
	int *tmp = LCD_MEM_BUFFER + SCREEN_WIDTH * y + x;
	*tmp = color;
}

void fb_draw_rect(int x, int y, int w, int h, int color)
{
	if(x < 0) { w += x; x = 0;}
	if(x+w > SCREEN_WIDTH) { w = SCREEN_WIDTH-x;}
	if(y < 0) { h += y; y = 0;}
	if(y+h >SCREEN_HEIGHT) { h = SCREEN_HEIGHT-y;}
	if(w<=0 || h<=0) return;
	_update_area(x,y,w,h);
/*---------------------------------------------------*/
	for(int y_shift = 0; y_shift < h; ++y_shift) {
		// fuck a line
#ifdef wmemset
		if(sizeof(wchar_t) == sizeof(int))
			wmemset(LCD_MEM_BUFFER + SCREEN_WIDTH * (y+y_shift), (wchar_t)color, w);
		else
#endif
		{
			for(int x_shift = 0; x_shift < w; ++x_shift) {
				fb_raw_draw_pixel(x + x_shift, y + y_shift, color);
			}
		}
	}
/*---------------------------------------------------*/
	return;
}

void fb_clear_screen() {
	_update_area(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	for(int *ptr = LCD_MEM_BUFFER; ptr < LCD_MEM_BUFFER + SCREEN_WIDTH * SCREEN_HEIGHT; ++ptr) {
		*ptr = 0;
	}
}

#define max(a, b) ((a > b) ? (a) : (b))
#define min(a, b) ((a > b) ? (b) : (a))

void fb_draw_line(int x1, int y1, int x2, int y2, int color)
{
    int min = (x1<x2)?x1:x2;
    int max = (x1<x2)?x2:x1;
    int x = min;
    int ymin=(x1<x2)?y1:y2;
    int ymax=(x1<x2)?y2:y1;
    int y =ymin;
    if(x1==x2){
        if(x >= SCREEN_WIDTH) return;
        for(; y1<=y2; y1++){
            if(y1 >= SCREEN_HEIGHT) break;
		    fb_raw_draw_pixel(x, y1, color);
        }
        return;
    }
    double k = (y2*1.0-y1*1.0)/(x2*1.0-x1*1.0); 
   
    if(k>=2 || k<=-2){
        double x0 = x;
        for(; x0<=max; x0+=0.1)
	    {
		    fb_raw_draw_pixel(x0, k*(double)(x0-min)+(double)y, color);
		    
	    }
        
    }

    else{
        for(; x<=max; ++x)
	    {
		    fb_raw_draw_pixel(x, k*(double)(x-min)+(double)y, color);
	    }
    }
    
	
	/*画线函数*/
	return;
}

//void fb_draw_line(int x1, int y1, int x2, int y2, int color)
//{
//	const int w = abs(x1 - x2);
//	const int h = abs(y1 - y2);
//	const int xbegin = min(x1, x2), ybegin = min(y1, y2);
//	_update_area(xbegin, ybegin, w, h);
///*---------------------------------------------------*/
//	if(w > h) {
//		const float y_per_x = (float)(y2 - y1) / (x2 - x1);
//		const int xend = max(x1, x2);
//		const int y_for_xbegin = xbegin == x1 ? y1 : y2;
//		for(int curr_x = xbegin; curr_x <= xend; ++curr_x) {
//			const int curr_y = y_for_xbegin + (int)(y_per_x * (curr_x - xbegin));
//			fb_raw_draw_pixel(curr_x, curr_y, color);
//			fb_raw_draw_pixel(curr_x, curr_y+1==SCREEN_HEIGHT?curr_y-1:curr_y+1, color);
//		}
//	}
//	else {
//		const float x_per_y = (float)(x2 - x1) / (y2 - y1);
//		const int yend = max(y1, y2);
//		const int x_for_ybegin = ybegin == y1 ? x1 : x2;
//		for(int curr_y = ybegin; curr_y <= yend; ++curr_y) {
//			const int curr_x = x_for_ybegin + (int)(x_per_y * (curr_y - ybegin));
//			fb_raw_draw_pixel(curr_x, curr_y, color);
//			fb_raw_draw_pixel(curr_x+1==SCREEN_WIDTH ? curr_x-1 : curr_x+1, curr_y, color);
//		}
//	}
///*---------------------------------------------------*/
//	return;
//}


void mycircle(int x, int y, int r, int color)
{
    int ix = x - r;
    int iy = y - r;
    int size = r + r; 
    int dx = 0;
    int dy = 0;
    
	_update_area(ix,iy,size,size);
	
	int i,j;
	for(i = 0;i < size;i++){
		for(j = 0;j < size;j++){
		    dx = ix - x;
		    dy = iy - y; 
		   if(dx < 0){
		   int *tmp = LCD_MEM_BUFFER + SCREEN_WIDTH * (iy + i) + ix + j;
			*tmp = color;
		   }
		  
		}
	}
	return;
}




/*======================================================================*/

void fb_draw_image(int x, int y, fb_image *image, int color)
{
	if(image == NULL) return;

	int ix = 0; //image x
	int iy = 0; //image y
	int w = image->pixel_w; //draw width
	int h = image->pixel_h; //draw height

	if(x<0) {w+=x; ix-=x; x=0;}
	if(y<0) {h+=y; iy-=y; y=0;}
	
	if(x+w > SCREEN_WIDTH) {
		w = SCREEN_WIDTH - x;
	}
	if(y+h > SCREEN_HEIGHT) {
		h = SCREEN_HEIGHT - y;
	}
	if((w <= 0)||(h <= 0)) return;

	_update_area(x,y,w,h);

	char *dst = (char *)(LCD_MEM_BUFFER + y*SCREEN_WIDTH + x);
	char *src = image->content + iy*image->line_byte + ix*4;
/*---------------------------------------------------------------*/

	int alpha;
	int ww;

	if(image->color_type == FB_COLOR_RGB_8880) /*lab3: jpg*/
	{
	//	printf("you need implement fb_draw_image() FB_COLOR_RGB_8880\n"); exit(0);
	
		for(iy=0;iy<h;iy++){
			
			for(ix=0;ix<w;ix++){
			dst = (char *)(LCD_MEM_BUFFER + iy*SCREEN_WIDTH + ix);
			src = image->content + iy*image->line_byte + ix*4;
			switch(src[3]){
			case 0:break;
			case 255:{
			dst[0]=src[0];
			dst[1]=src[1];
			dst[2]=src[2];
			}
			default:{
			dst[0]+=(((src[0]-dst[0])*src[3])>>8);
			dst[1]+=(((src[1]-dst[1])*src[3])>>8);
			dst[2]+=(((src[2]-dst[2])*src[3])>>8);}
			}
		
			}}
		return;
	}

	if(image->color_type == FB_COLOR_RGBA_8888) /*lab3: png*/
	{
		//printf("you need implement fb_draw_image() FB_COLOR_RGBA_8888\n"); exit(0);
		
		for(iy=0;iy<h;iy++)
				{
			for(ix=0;ix<w;ix++)
				{
					dst = (char *)(LCD_MEM_BUFFER + (iy+y)*SCREEN_WIDTH + ix+x);
					src = image->content + (iy)*image->line_byte + ix*4;

			switch(src[3]){
			case 0:break;
			case 255:{
			dst[0]=src[0];
			dst[1]=src[1];
			dst[2]=src[2];
			}
			default:{
			dst[0]+=(((src[0]-dst[0])*src[3])>>8);
			dst[1]+=(((src[1]-dst[1])*src[3])>>8);
			dst[2]+=(((src[2]-dst[2])*src[3])>>8);}
			}
				}}
		return;
	}

	if(image->color_type == FB_COLOR_ALPHA_8) /*lab3: font*/
	{
		//printf("you need implement fb_draw_image() FB_COLOR_ALPHA_8\n"); exit(0);
		for(iy=0;iy<h;iy++){
						
			for(ix=0;ix<w;ix++)
				{
				
				dst = (char *)(LCD_MEM_BUFFER + (iy+y)*SCREEN_WIDTH + ix+x);
				src = image->content + (iy)*image->line_byte + ix;
				char pos0 = (char)color,
					pos1 = (char)(color >> 8),
					pos2 = (char)(color >> 16); 
				switch(src[0]){
					case 0:break;
					case 255:
						dst[0]=pos0;
						dst[1]=pos1;
						dst[2]=pos2;
						//break;
					default:
						dst[0]+=(((pos0-dst[0])*src[0])>>8);
						dst[1]+=(((pos1-dst[1])*src[0])>>8);
						dst[2]+=(((pos2-dst[2])*src[0])>>8);}
					}
			
}
		return;
	}
/*---------------------------------------------------------------*/
	return;
}
/*
void color(int alpha,char* rsc,char* dst)
{
	switch(alpha){
		case 0:break;
		case 255:
			dst[0]=rsc[0];
			dst[1]=rsc[1];
			dst[2]=rsc[2];
		default:
			dst[0]+=(((rsc[0]-dst[0])*alpha)>>8);
			dst[1]+=(((rsc[1]-dst[1])*alpha)>>8);
			dst[2]+=(((rsc[2]-dst[2])*alpha)>>8);
	}
}
*/
/** draw a text string **/
void fb_draw_text(int x, int y, char *text, int font_size, int color)
{
	fb_image *img;
	fb_font_info info;
	int i=0;
	int len = strlen(text);
	while(i < len)
	{
		img = fb_read_font_image(text+i, font_size, &info);
		if(img == NULL) break;
		fb_draw_image(x+info.left, y-info.top, img, color);
		fb_free_image(img);

		x += info.advance_x;
		i += info.bytes;
	}
	return;
}
