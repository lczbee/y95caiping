
#ifndef GIFDEC_H
#define GIFDEC_H

#include "generic/typedef.h"
// #include "gifdec_platform.h"
// #include "stream.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    int width;
    int height;
    int palette_size;
    uint8_t bgcolor[3];
} gif_info_t;

/*
* how to use:
*
int delay;
gif_info_t gif_info;
int format = 0;
int has_cancas = 0;
int lbl = 1;
int bpp = 3;
int ret = 0;

if (format == 0)
    bpp = 2;

int heap_size = gif_get_heap_size(12);

char* heap_buf = malloc(heap_size);

if (!heap_buf) {
    fprintf(stderr, "Could not allocate heap_buf\n");
    return 1;
}

gif = gif_open(argv[1], 12, format, heap_buf, heap_size);

if (!gif) {
    fprintf(stderr, "Could not open %s\n", argv[1]);
    return 1;
}

int canvas_size = gif_get_canvas_size(gif);
char* canvas_buf = malloc(canvas_size);

if (!canvas_buf) {
    fprintf(stderr, "Could not allocate canvas_buf\n");
    return 1;
}

if(has_cancas)
    gif_set_canvas(gif, canvas_buf);


gif_get_info(gif, &gif_info);

while(1)
{
    if(lbl)
        ret = gif_get_frame_lbl(gif, frame);
    else
        ret = gif_get_frame(gif, frame);


    if (ret == 0)
    {
        gif_rewind(gif);
        continue;
    }
    else
    {
        delay(delay);
        display();
    }
}

gif_close(gif);

free(frame);
free(heap_buf);
free(canvas_buf);
*
*
*/


/*
* get the heap size used by gifdec
*/
int gif_get_heap_size(int lzw_bits_max);

/*
* open the given gif file
*
parameters
lzw_bits_max:  the max width of lzw key
format: the output format of frame,  0 for rgb565, 1 for rgb888
endian : 0 for little endian, 1 for big endian
heap_buf: heap memory address
heap_size: heap memory size
*/
void *gif_open(const char *fname, int lzw_bits_max, int format, int endian, char *heap_buf, int heap_size);

/*
* get the gif infomation
*/
int gif_get_info(void *gif, gif_info_t *info);

/*
* get the delay time
*/
int gif_get_delay(void *gif);

/*
* return
* -1: error
* 0: end of frame
* 1: has more frames
*/
int gif_get_frame(void *gif, uint8_t *buffer);

/*
* return
* -1: error
* 0: end of frame
* 1: has more frames
*/
int gif_get_frame_lbl(void *gif, uint8_t *buffer);

/*
* return
* -1: error
* 0: end of frame
* 1: has more frames
*/
int gif_next_line(void *_gif, uint8_t *buffer);

/*
* get the next y value if interlace is active
*/
int gif_next_line_y(void *_gif);

/*
* whetherornot the color is background color
*/
int gif_is_bgcolor(void *gif, uint8_t color[3]);

/*
* rewind to the first frame after reaching the end of gif file
*/
void gif_rewind(void *gif);

/*
* close the gif decoder
*/
void gif_close(void *gif);

/*
* get the canvas  size needed by gifdec
*/
int gif_get_canvas_size(void *_gif);

/*
* set the canvas buffer to gifdec
*/
void gif_set_canvas(void *_gif, uint8_t *canvas);

#ifdef __cplusplus
}
#endif

#endif /* GIFDEC_H */

