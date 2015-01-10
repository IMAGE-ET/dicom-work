#include <pjlib.h>
#include <pjmedia.h>
#include <pjmedia-codec.h>
#include <stdio.h>
#include "my-pjlib-utils.h"
#include "my-pjmedia-utils.h"
#include "riuc_uart.h"

struct {
    int in_stream_on;
    int out_stream_on;
} stream_state;

pjmedia_stream *out_stream = NULL;
pjmedia_stream *in_stream = NULL;

void dicom_riu_turn_on_in_stream(pjmedia_stream *in_stream) {
    if( !stream_state.in_stream_on ) {
        CHECK(__FILE__, pjmedia_stream_resume(in_stream, PJMEDIA_DIR_DECODING));
        stream_state.in_stream_on = 1;
    }
}

void dicom_riu_turn_off_in_stream(pjmedia_stream *in_stream) {
    if( stream_state.in_stream_on ) {
        CHECK(__FILE__, pjmedia_stream_pause(in_stream, PJMEDIA_DIR_DECODING));
        stream_state.in_stream_on = 0;
    }
}

void dicom_riu_turn_on_out_stream(pjmedia_stream *out_stream) {
    if( !stream_state.out_stream_on ) {
        CHECK(__FILE__, pjmedia_stream_resume(out_stream, PJMEDIA_DIR_ENCODING));
        stream_state.out_stream_on = 1;
    }
}

void dicom_riu_turn_off_out_stream(pjmedia_stream *out_stream) {
    if( stream_state.out_stream_on ) {
        CHECK(__FILE__, pjmedia_stream_pause(out_stream, PJMEDIA_DIR_ENCODING));
        stream_state.out_stream_on = 0;
    }
}

void dicom_riu_on_riuc_status(int ptt, int sq) {
    PJ_LOG(3, (__FILE__, "RIUC status: ptt:%d, sq:%d", ptt, sq));
    if( ptt && sq) {
        //
        // Unexpected
        //
        return;
    }
    else {
        if(ptt){ // ptt on, sq off
            dicom_riu_turn_off_out_stream(out_stream);
            dicom_riu_turn_on_in_stream(in_stream);
        }
        else if( sq ) {
            dicom_riu_turn_off_in_stream(in_stream);
            dicom_riu_turn_on_out_stream(out_stream);
        }
        else { // both are off
            dicom_riu_turn_off_in_stream(in_stream);
            dicom_riu_turn_off_out_stream(out_stream);
        }
    }
}

struct {
    int lport;
    char *raddr;
} app_params;

volatile int fEnd;

int multicast_receiver() {
    pj_sock_t sock;
    pj_sockaddr_in addr;
    pj_ip_mreq mreq;

    pj_str_t s, s1;

    int sock_len;
    char buffer[1024];
    pj_ssize_t len;
    
    CHECK( __FILE__, pj_sock_socket(PJ_AF_INET, PJ_SOCK_DGRAM, 0, &sock) );
    
    setup_addr_with_port(&addr, app_params.lport);
    CHECK( __FILE__, pj_sock_bind(sock, &addr, sizeof(addr)) );
    
    pj_bzero(&mreq, sizeof(pj_ip_mreq));
    mreq.imr_multiaddr = pj_inet_addr(pj_cstr(&s, app_params.raddr));
    mreq.imr_interface = pj_inet_addr(pj_cstr(&s1, "0.0.0.0"));

    CHECK( __FILE__, pj_sock_setsockopt(sock, PJ_SOL_IP, PJ_IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) );

    fEnd = 0;
    while(!fEnd) {
        pj_bzero(buffer, sizeof(buffer));
        len = sizeof(buffer);
        PJ_LOG(3, (__FILE__, "Start receiving data"));
        CHECK( __FILE__, pj_sock_recv(sock, buffer, &len, 0) );
        PJ_LOG(3, (__FILE__, "Received: %d, %s", len, buffer));
        if( !strncmp(buffer, "on_PTT", 7) ) {
            riuc_on_ptt();
        }
        else if( !strncmp(buffer, "off_PTT", 8) ) {
            riuc_off_ptt();
        }
    }

    return 0;
}

int main(int argc, char *opts[]) {
    pj_caching_pool cp;
    pj_pool_t *pool;

    pj_thread_t *thread;

    pjmedia_endpt *med_endpt;
    pjmedia_port *out_stream_port;
    pjmedia_port *in_stream_port;
    pjmedia_snd_port *speaker_port;
    pjmedia_snd_port *mic_port;

    const pjmedia_codec_info *codec_info;

    char temp[10];

    pj_log_set_level(4);
    CHECK(__FILE__, pj_init());

    if( argc < 2 ) {
        PJ_LOG(1, ("Usage:", "dicom-riu <device>"));
        pj_shutdown();
        exit(0);
    }

    pj_caching_pool_init(&cp, NULL, 0);

    pool = pj_pool_create(&cp.factory, "dicom-riu", 4000, 4000, NULL);

    CHECK(__FILE__, pjmedia_endpt_create(&cp.factory, NULL, 1, &med_endpt));

    pjmedia_codec_register_audio_codecs(med_endpt, 0);

    pjmedia_codec_mgr_get_codec_info(pjmedia_endpt_get_codec_mgr(med_endpt), 0, &codec_info);

    CHECK(__FILE__,\
             create_mcast_in_stream(pool, med_endpt, codec_info,\
             33333, "239.0.0.1", &in_stream)\
    );
    pjmedia_stream_get_port( in_stream, &in_stream_port);

    CHECK(__FILE__,\
             create_out_stream(pool, med_endpt, codec_info,\
             3456,"239.0.0.1", 22222, &out_stream)\
    );
    pjmedia_stream_get_port( out_stream, &out_stream_port);

    CHECK(__FILE__, pjmedia_snd_port_create_player(pool, -1,
                    PJMEDIA_PIA_SRATE(&in_stream_port->info),
                    PJMEDIA_PIA_CCNT(&in_stream_port->info),
                    PJMEDIA_PIA_SPF(&in_stream_port->info),
                    PJMEDIA_PIA_BITS(&in_stream_port->info),
                    0, &speaker_port));

    CHECK(__FILE__, pjmedia_snd_port_create_rec(pool, -1,
                    PJMEDIA_PIA_SRATE(&out_stream_port->info),
                    PJMEDIA_PIA_CCNT(&out_stream_port->info),
                    PJMEDIA_PIA_SPF(&out_stream_port->info),
                    PJMEDIA_PIA_BITS(&out_stream_port->info),
                    0, &mic_port));

    CHECK(__FILE__, pjmedia_snd_port_connect(speaker_port, in_stream_port));
    CHECK(__FILE__, pjmedia_stream_start(in_stream));
    CHECK(__FILE__, pjmedia_stream_pause(in_stream, PJMEDIA_DIR_DECODING));

    CHECK(__FILE__, pjmedia_snd_port_connect(mic_port, out_stream_port));
    CHECK(__FILE__, pjmedia_stream_start(out_stream));
    CHECK(__FILE__, pjmedia_stream_pause(out_stream, PJMEDIA_DIR_ENCODING));

    riuc_init( dicom_riu_on_riuc_status );
    riuc_start( pool, opts[1], &thread );

    app_params.lport = 44444;
    app_params.raddr = "239.0.0.1";

    multicast_receiver();

    riuc_end(thread);
    
    pjmedia_snd_port_disconnect(speaker_port);
    pjmedia_snd_port_disconnect(mic_port);

    pjmedia_transport *tp = pjmedia_stream_get_transport(in_stream);
    pjmedia_stream_destroy(in_stream);
    pjmedia_transport_close(tp);
    
    tp = pjmedia_stream_get_transport(out_stream);
    pjmedia_stream_destroy(out_stream);
    pjmedia_transport_close(tp);

    pjmedia_snd_port_destroy(speaker_port);
    pjmedia_snd_port_destroy(mic_port);

    pj_pool_release(pool);
    pjmedia_endpt_destroy(med_endpt);
    pj_caching_pool_destroy(&cp);

    pj_shutdown();
}
