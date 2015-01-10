#ifndef __MY_PJMEDIA_UTILS_H__
#define __MY_PJMEDIA_UTILS_H__
#include <pjlib.h>
#include <pjmedia.h>

pj_status_t create_mstream(
                    pj_pool_t *pool,
                    pjmedia_endpt *endpt,
                    const pjmedia_codec_info *codec_info,
                    pjmedia_dir dir,
                    pj_uint16_t port,
                    const char *remote,
                    int rport,
                    pjmedia_stream **stream
                );

pj_status_t create_stream(
                    pj_pool_t *pool,
                    pjmedia_endpt *endpt,
                    const pjmedia_codec_info *codec_info,
                    pjmedia_dir dir,
                    pj_uint16_t port,
                    const char *remote,
                    int rport,
                    //pj_sockaddr_in *remote,
                    pjmedia_stream **stream
                );
#define create_mcast_in_stream(pool, endpt, ci, lport, mcast, stream) \
        create_mstream(pool, endpt, ci, PJMEDIA_DIR_DECODING, lport, mcast, 0, stream)

#define create_in_stream(pool, endpt, ci, lport, stream) \
        create_mstream(pool, endpt, ci, PJMEDIA_DIR_DECODING, lport, NULL, 0, stream)
#define create_out_stream(pool, endpt, ci, lport, r, rp, stream) \
        create_mstream(pool, endpt, ci, PJMEDIA_DIR_ENCODING, lport, r, rp, stream)
void dump_codec_info(const char *file, const pjmedia_codec_info *cinfo);
void dump_codec_param(const char *file, const pjmedia_codec_param *param);
void dump_port_info(const char *file, pjmedia_port *port);

#endif
