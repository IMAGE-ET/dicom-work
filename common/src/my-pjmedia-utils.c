#include <pjlib.h>
#include <pjmedia.h>
#include "my-pjlib-utils.h"

pj_status_t create_mstream(pj_pool_t *pool, 
                pjmedia_endpt *endpt, 
                const pjmedia_codec_info *codec_info, 
                pjmedia_dir dir, 
                int local_port,
                const char *remote_addr,
                int remote_port,
                pjmedia_stream **stream) 
{
    pjmedia_stream_info stream_info;
    pjmedia_transport *transport = NULL;

    pjmedia_codec_mgr *cmgr = pjmedia_endpt_get_codec_mgr(endpt);

    pj_bzero(&stream_info, sizeof(stream_info));

    stream_info.type = PJMEDIA_TYPE_AUDIO;
    stream_info.dir = dir;
    pj_memcpy(&stream_info.fmt, codec_info, sizeof(pjmedia_codec_info));
    stream_info.tx_pt = codec_info->pt;
    stream_info.ssrc = pj_rand();

    pjmedia_sock_info si;

    setup_udp_socket(local_port, &si.rtp_sock, &si.rtp_addr_name.ipv4);
    setup_udp_socket(local_port + 1, &si.rtcp_sock, &si.rtcp_addr_name.ipv4);

    if(dir == PJMEDIA_DIR_DECODING) {
        setup_addr_with_host_and_port(
             &(stream_info.rem_addr.ipv4), 
             "0.0.0.0", 0
        );
        if( remote_addr != NULL ) {
            CHECK(__FILE__, join_mcast_group(si.rtp_sock, remote_addr));
            CHECK(__FILE__, join_mcast_group(si.rtcp_sock, remote_addr));
        }
    }
    else if(dir == PJMEDIA_DIR_ENCODING) {
        setup_addr_with_host_and_port(
             &(stream_info.rem_addr.ipv4), 
             remote_addr, remote_port
        );
    }

    CHECK_R(__FILE__, pjmedia_transport_udp_attach(endpt, NULL, &si, 0, &transport));
    CHECK_R(__FILE__, pjmedia_stream_create(endpt, pool, &stream_info, transport, NULL, stream));
    return PJ_SUCCESS;
}

pj_status_t create_stream(pj_pool_t *pool, 
                pjmedia_endpt *endpt, 
                const pjmedia_codec_info *codec_info, 
                pjmedia_dir dir, 
                int local_port,
                const char *remote_addr,
                int remote_port,
                pjmedia_stream **stream) 
{
    pjmedia_stream_info stream_info;
    pjmedia_transport *transport = NULL;

    pjmedia_codec_mgr *cmgr = pjmedia_endpt_get_codec_mgr(endpt);

    pj_bzero(&stream_info, sizeof(stream_info));

    stream_info.type = PJMEDIA_TYPE_AUDIO;
    stream_info.dir = dir;
    pj_memcpy(&stream_info.fmt, codec_info, sizeof(pjmedia_codec_info));
    stream_info.tx_pt = codec_info->pt;
    stream_info.ssrc = pj_rand();

    if(remote_addr == NULL) {
        setup_addr_with_host_and_port(&(stream_info.rem_addr.ipv4), "127.0.0.1", 0);
    }
    else {
        setup_addr_with_host_and_port(&(stream_info.rem_addr.ipv4), remote_addr, remote_port);
    }
    CHECK_R(__FILE__, pjmedia_transport_udp_create(endpt, NULL, local_port, 0, &transport));
    CHECK_R(__FILE__, pjmedia_stream_create(endpt, pool, &stream_info, transport, NULL, stream));
    return PJ_SUCCESS;
}

int rx_volume_inc(pjmedia_snd_port *snd_port, int incremental) {
    pjmedia_aud_stream *aud_stream = pjmedia_snd_port_get_snd_stream(snd_port);
    if (aud_stream == NULL) return -1;
    unsigned vol;
    CHECK_R(__FILE__, pjmedia_aud_stream_get_cap(aud_stream, PJMEDIA_AUD_DEV_CAP_INPUT_VOLUME_SETTING, &vol));
    vol += incremental;
    vol = (vol > 100)?100:vol;
    vol = (vol < 0)?0:vol;
    CHECK_R(__FILE__, pjmedia_aud_stream_set_cap(aud_stream, PJMEDIA_AUD_DEV_CAP_INPUT_VOLUME_SETTING, &vol));
    return vol;
}
int tx_volume_inc(pjmedia_snd_port *snd_port, int incremental) {
    pjmedia_aud_stream *aud_stream = pjmedia_snd_port_get_snd_stream(snd_port);
    if (aud_stream == NULL) return -1;
    unsigned vol;
    CHECK_R(__FILE__, pjmedia_aud_stream_get_cap(aud_stream, PJMEDIA_AUD_DEV_CAP_OUTPUT_VOLUME_SETTING, &vol));
    vol += incremental;
    vol = (vol > 100)?100:vol;
    vol = (vol < 0)?0:vol;
    CHECK_R(__FILE__, pjmedia_aud_stream_set_cap(aud_stream, PJMEDIA_AUD_DEV_CAP_OUTPUT_VOLUME_SETTING, &vol));
    return vol;
}

void dump_codec_info(const char *file, const pjmedia_codec_info *cinfo) {
    PJ_LOG(3, (file, "dump_codec_info(): %*s clk:%d pt:%d, channel:%d\n", (int)cinfo->encoding_name.slen, cinfo->encoding_name.ptr, cinfo->clock_rate, cinfo->pt, cinfo->channel_cnt));
}

void dump_codec_param(const char *file, const pjmedia_codec_param *param) {
    if(param == NULL) {
        PANIC(file, "Param is NULL");
    }
    PJ_LOG(3, (file, "dump_codec_param(): clk:%d, channel:%d fmt_id:%d, ptime:%d\n", param->info.clock_rate, param->info.channel_cnt, param->info.fmt_id, param->info.frm_ptime));
}

void dump_port_info(const char *file, pjmedia_port *port) {
    pjmedia_audio_format_detail *aud;
    aud = &(port->info.fmt.det.aud);
    PJ_LOG(3, (file, "dump_port_info(): clk:%d Channel:%d frameTime:%d bps:%d\n",
                    aud->clock_rate, 
                    aud->channel_count, aud->frame_time_usec, aud->bits_per_sample));
}
