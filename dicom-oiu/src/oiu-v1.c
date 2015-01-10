#include <pjlib.h>
#include <pjmedia.h>
#include <pjmedia-codec.h>
#include <stdio.h>
#include "my-pjlib-utils.h"
#include "my-pjmedia-utils.h"
#include "dicom-config.h"

#define APP_NAME "stream-oiu"
#define CONFIG_FILE "../conf/test.ini"

struct {
    int in_stream_on;
    int out_stream_on;
} stream_state;

#define SENT_PTT 4
#define ON_PTT 1
#define OFF_PTT 2
#define NONE_PTT 0
struct {
    volatile int ptt_status;
} app_commands;

struct {
    int lport;
    char *raddr;
    int rport;
} app_params;

dicom_config_t config;
int me_idx;

pjmedia_stream *out_stream = NULL;
pjmedia_stream *in_stream = NULL;

void send_on_ptt() {
    app_commands.ptt_status = ON_PTT;
}
void send_off_ptt() {
    app_commands.ptt_status = OFF_PTT;
}
void dicom_oiu_turn_on_in_stream(pjmedia_stream *in_stream) {
    if( !stream_state.in_stream_on ) {
        CHECK(__FILE__, pjmedia_stream_resume(in_stream, PJMEDIA_DIR_DECODING));
        stream_state.in_stream_on = 1;
    }
}

void dicom_oiu_turn_off_in_stream(pjmedia_stream *in_stream) {
    if( stream_state.in_stream_on ) {
        CHECK(__FILE__, pjmedia_stream_pause(in_stream, PJMEDIA_DIR_DECODING));
        stream_state.in_stream_on = 0;
    }
}

void dicom_oiu_turn_on_out_stream(pjmedia_stream *out_stream) {
    if( !stream_state.out_stream_on ) {
        CHECK(__FILE__, pjmedia_stream_resume(out_stream, PJMEDIA_DIR_ENCODING));
        stream_state.out_stream_on = 1;
    }
}

void dicom_oiu_turn_off_out_stream(pjmedia_stream *out_stream) {
    if( stream_state.out_stream_on ) {
        CHECK(__FILE__, pjmedia_stream_pause(out_stream, PJMEDIA_DIR_ENCODING));
        stream_state.out_stream_on = 0;
    }
}

int multicast_sender(void *data) {
    pj_sockaddr_in addr;
    pj_sockaddr_in to_addr;
    pj_sock_t sock;
    int sock_len;
    static char *on_req = "on_PTT";
    static char *off_req = "off_PTT";
    pj_ssize_t len;

    CHECK( __FILE__, pj_sock_socket(PJ_AF_INET, PJ_SOCK_DGRAM, 0, &sock) );

    setup_addr_with_port(&addr, 4096);
    CHECK( __FILE__, pj_sock_bind_random(sock, &addr, 20000, 3) );

    setup_addr_with_host_and_port(&to_addr, app_params.raddr, app_params.rport);

    while(1) {
        if(app_commands.ptt_status == ON_PTT) {
            len = pj_ansi_strlen(on_req) + 1;
            PJ_LOG(3, (__FILE__, "sending out command:%s %d", on_req, len));
            CHECK( __FILE__, pj_sock_sendto(sock, on_req, &len, 0, &to_addr, sizeof(to_addr)) );
            app_commands.ptt_status = NONE_PTT;
        }
        else if(app_commands.ptt_status == OFF_PTT) {
            len = pj_ansi_strlen(off_req) + 1;
            PJ_LOG(3, (__FILE__, "sending out command:%s %d", off_req, len));
            CHECK( __FILE__, pj_sock_sendto(sock, off_req, &len, 0, &to_addr, sizeof(to_addr)) );
            app_commands.ptt_status = NONE_PTT;
        }
        pj_thread_sleep(1000);
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
/*
    if( argc < 2 ) {
        PJ_LOG(1, ("Usage:", "dicom-riu <device>"));
        pj_shutdown();
        exit(0);
    }
*/
    pj_caching_pool_init(&cp, NULL, 0);

    dicom_config_load(CONFIG_FILE, &config);
    me_idx = dicom_config_find(&config, APP_NAME);

    if( me_idx < 0 ) {
        PJ_LOG(1, (__FILE__, APP_NAME" does not exist in config file"));
        pj_shutdown();
        exit(-1);
    }

    pool = pj_pool_create(&cp.factory, APP_NAME, 4000, 4000, NULL);

    CHECK(__FILE__, pjmedia_endpt_create(&cp.factory, NULL, 1, &med_endpt));

    pjmedia_codec_register_audio_codecs(med_endpt, 0);

    pjmedia_codec_mgr_get_codec_info(pjmedia_endpt_get_codec_mgr(med_endpt), 0, &codec_info);

    CHECK(__FILE__,\
             create_mcast_in_stream(pool, med_endpt, codec_info,\
             config.stm_port[me_idx], config.stm_maddr[me_idx], &in_stream)\
    );
    pjmedia_stream_get_port( in_stream, &in_stream_port);

    CHECK(__FILE__,\
             create_out_stream(pool, med_endpt, codec_info,\
             3456,"239.0.0.1", 33333, &out_stream)\
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
//    CHECK(__FILE__, pjmedia_stream_pause(in_stream, PJMEDIA_DIR_DECODING));

    CHECK(__FILE__, pjmedia_snd_port_connect(mic_port, out_stream_port));
    CHECK(__FILE__, pjmedia_stream_start(out_stream));
    CHECK(__FILE__, pjmedia_stream_pause(out_stream, PJMEDIA_DIR_ENCODING));

    app_params.lport = 5555;
    app_params.raddr = "239.0.0.1";
    app_params.rport = 44444;

    pj_thread_create(pool, "ptt_thread", multicast_sender, NULL, PJ_THREAD_DEFAULT_STACK_SIZE, 0, &thread);
    int fEnd = 0;
    while(!fEnd) {
        fgets(temp, sizeof(temp), stdin);
        switch (temp[0]) {
            case '+':
                    send_on_ptt();
                    pj_thread_sleep(500);
                    //dicom_oiu_turn_off_in_stream(in_stream);
                    dicom_oiu_turn_on_out_stream(out_stream);
                    break;
            case '-':
                    send_off_ptt();
                    pj_thread_sleep(500);
                    //dicom_oiu_turn_off_in_stream(in_stream);
                    dicom_oiu_turn_off_out_stream(out_stream);
                    break;
            case 'q':
                    fEnd = 1;
                    break;
            default:
                    PJ_LOG(3, (__FILE__, "Unknown command"));
                    break;
        }
    }
    
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
