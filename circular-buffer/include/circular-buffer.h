#ifndef __CIRCULAR_BUFFER__
#define __CIRCULAR_BUFFER__
#define DUPSOCK_BUFSIZE 512
typedef struct {
    char data[DUPSOCK_BUFSIZE];
    int start, end;
    int overrun;
}cbuffer_t;

void cbuffer_init(cbuffer_t *p_cbuf);
int cbuffer_occupied_bytes(cbuffer_t *p_cbuf);
int cbuffer_is_empty(cbuffer_t *p_cbuf);
int cbuffer_avail_bytes(cbuffer_t *p_cbuf);
int cbuffer_is_full(cbuffer_t *p_cbuf);
int cbuffer_write(cbuffer_t *p_cbuf, char *data, int len);
int cbuffer_read(cbuffer_t *p_cbuf, char *data, int len);
#endif
