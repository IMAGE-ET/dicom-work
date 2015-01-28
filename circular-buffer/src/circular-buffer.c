#include <pjlib.h>
#include "circular-buffer.h"

void cbuffer_init(cbuffer_t *p_cbuf) {
    pj_bzero(p_cbuf->data, DUPSOCK_BUFSIZE*sizeof(char));
    p_cbuf->start = 0;
    p_cbuf->end = 0;
    p_cbuf->overrun = 0;
}

int cbuffer_occupied_bytes(cbuffer_t *p_cbuf) {
    return ( p_cbuf->end - p_cbuf->start + DUPSOCK_BUFSIZE ) % DUPSOCK_BUFSIZE 
            + p_cbuf->overrun * DUPSOCK_BUFSIZE;
}

int cbuffer_is_empty(cbuffer_t *p_cbuf) {
    return (cbuffer_occupied_bytes(p_cbuf) == 0);
}

int cbuffer_avail_bytes(cbuffer_t *p_cbuf) {
    return DUPSOCK_BUFSIZE - cbuffer_occupied_bytes(p_cbuf);
}

int cbuffer_is_full(cbuffer_t *p_cbuf) {
    return ( cbuffer_occupied_bytes(p_cbuf) == DUPSOCK_BUFSIZE );
}

int cbuffer_write(cbuffer_t *p_cbuf, char *data, int len) {
    char *ldata = data;
    int llen = len;

    if( p_cbuf->end < p_cbuf->start ) {
        int n = p_cbuf->start - p_cbuf->end;
        if( n >= llen ) {
            memcpy(p_cbuf->data + p_cbuf->end, ldata, llen);
            p_cbuf->end += llen;
            if (p_cbuf->end == p_cbuf->start) p_cbuf->overrun = 1;
            return llen;
        }
        else {
            memcpy(p_cbuf->data + p_cbuf->end, ldata, n);
            p_cbuf->end += n;
            p_cbuf->overrun = 1;
            return n;
        }
    } 
    else if(p_cbuf->end == p_cbuf->start && p_cbuf->overrun == 1) {
        return 0;
    }
    else {
        int n = DUPSOCK_BUFSIZE - p_cbuf->end;
        if( n >= llen ) {
            memcpy(p_cbuf->data + p_cbuf->end, ldata, llen);
            p_cbuf->end = (p_cbuf->end + llen) % DUPSOCK_BUFSIZE;
            if(p_cbuf->end == p_cbuf->start) p_cbuf->overrun = 1;
            return llen;
        }
        else {
            memcpy(p_cbuf->data + p_cbuf->end, ldata, n);
            p_cbuf->end = (p_cbuf->end + n) % DUPSOCK_BUFSIZE;
            ldata += n;
            llen -= n;
            if(p_cbuf->end == p_cbuf->start) {
                p_cbuf->overrun = 1;
                return n;
            }
            else {
                return n + cbuffer_write(p_cbuf, ldata, llen);
            }
        }
    }
}

int cbuffer_read(cbuffer_t *p_cbuf, char *data, int len) {
    char *ldata = data;
    int llen = len;
    if( p_cbuf->start < p_cbuf->end) {
        int n = p_cbuf->end - p_cbuf->start;
        if( n >= llen ) {
            memcpy(ldata, p_cbuf->data + p_cbuf->start, llen);
            p_cbuf->start += llen;
            if(p_cbuf->start == p_cbuf->end) p_cbuf->overrun = 0;
            return llen;
        }
        else {
            memcpy(ldata, p_cbuf->data + p_cbuf->start, n);
            p_cbuf->start += n;
            p_cbuf->overrun = 0;
            return n;
        }
    }
    else if( (p_cbuf->start == p_cbuf->end) && ( p_cbuf->overrun == 0 ) ) { 
        return 0;
    }
    else {
        int n = DUPSOCK_BUFSIZE - p_cbuf->start;
        if( n >= llen ) {
            memcpy(ldata, p_cbuf->data + p_cbuf->start, llen);
            p_cbuf->start = (p_cbuf->start + llen) % DUPSOCK_BUFSIZE;
            return llen;
        }
        else {
            memcpy(ldata, p_cbuf->data + p_cbuf->start, n);
            p_cbuf->start = 0;
            ldata += n;
            llen -= n;
            return n + cbuffer_read(p_cbuf, ldata, llen);
        }
    }
}


