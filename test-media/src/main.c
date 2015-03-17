#include "my-pjlib-utils.h"
#include <pjlib.h>
#include <pjmedia.h>
#include <stdio.h>

void list_devices() {
    pjmedia_aud_dev_index dev_idx;
    int dev_cnt;
    dev_cnt = pjmedia_aud_dev_count();
    printf("Got %d audio devices\n", dev_cnt);

    for (dev_idx=0; dev_idx < dev_cnt; ++dev_idx) {
        pjmedia_aud_dev_info info;
        CHECK(__FILE__, pjmedia_aud_dev_get_info(dev_idx, &info));
        printf("%d. %s (in=%d, out=%d)\n", dev_idx, info.name, info.input_count, info.output_count);
    }
}

int is_rec_dev(int dev_idx) {
    pjmedia_aud_dev_info info;
    CHECK(__FILE__, pjmedia_aud_dev_get_info(dev_idx, &info));
    return info.input_count > 0;
}

int is_play_dev(int dev_idx) {
    pjmedia_aud_dev_info info;
    CHECK(__FILE__, pjmedia_aud_dev_get_info(dev_idx, &info));
    return info.output_count > 0;
}

typedef struct player_s {
    pjmedia_port *file_port;
    pjmedia_snd_port *snd_port;
    pjmedia_port *resample_port;
} player_t;
#if 0
void init_player(pj_pool_t *pool, int dev_idx, char *file_name, player_t *player) {
    CHECK(__FILE__, pjmedia_wav_player_port_create(pool, file_name, 20, 0, -1, &(player->file_port)));
    CHECK(__FILE__, pjmedia_snd_port_create_player(pool, dev_idx,
                    PJMEDIA_PIA_SRATE(&player->file_port->info),
                    PJMEDIA_PIA_CCNT(&player->file_port->info),
                    PJMEDIA_PIA_SPF(&player->file_port->info),
                    PJMEDIA_PIA_BITS(&player->file_port->info),
                    0, &player->snd_port));
}
void start_player(player_t* player) {
    CHECK_NULL(__FILE__, player->file_port);
    CHECK_NULL(__FILE__, player->snd_port);
    CHECK(__FILE__, pjmedia_snd_port_connect(player->snd_port, player->file_port));
}
void destroy_player(player_t *player) {
    pjmedia_snd_port_disconnect(player->snd_port);
    pjmedia_snd_port_destroy(player->snd_port);
    pjmedia_port_destroy(player->file_port);
}
#else
void init_player(pj_pool_t *pool, int dev_idx, int sampling_rate, char *file_name, player_t *player) {
    int samples_per_frame = sampling_rate * 20 / 1000;
    int nbits;
    int ptime;
    int ccnt;
    unsigned options = PJMEDIA_RESAMPLE_USE_LINEAR | PJMEDIA_RESAMPLE_USE_SMALL_FILTER;

    CHECK(__FILE__, pjmedia_wav_player_port_create(pool, file_name, 20, 0, -1, &(player->file_port)));

    nbits = PJMEDIA_PIA_BITS(&player->file_port->info);
    ptime = PJMEDIA_PIA_PTIME(&player->file_port->info);
    ccnt = PJMEDIA_PIA_CCNT(&player->file_port->info);
    samples_per_frame = sampling_rate * ptime / 1000;

    CHECK(__FILE__, pjmedia_resample_port_create(pool, player->file_port, sampling_rate, 
                                options, &(player->resample_port)));

    CHECK(__FILE__, pjmedia_snd_port_create_player(pool, dev_idx, sampling_rate, ccnt,
                    samples_per_frame,
                    nbits,
                    0, &player->snd_port));
}

void start_player(player_t* player) {
//    CHECK_NULL(__FILE__, player->file_port);
    CHECK_NULL(__FILE__, player->resample_port);
    CHECK_NULL(__FILE__, player->snd_port);
//    CHECK(__FILE__, pjmedia_snd_port_connect(player->snd_port, player->file_port));
    CHECK(__FILE__, pjmedia_snd_port_connect(player->snd_port, player->resample_port));
}

void destroy_player(player_t *player) {
    pjmedia_snd_port_disconnect(player->snd_port);
    pjmedia_snd_port_destroy(player->snd_port);
    pjmedia_port_destroy(player->resample_port);
    //pjmedia_port_destroy(player->file_port);
}
#endif

int main(int argc, char *argv[]) {
    pj_caching_pool cp;
    pj_pool_t *pool;
    pjmedia_endpt *endpt;
    pj_log_set_level(5);
    CHECK(__FILE__, pj_init());

    pj_caching_pool_init(&cp, 0, 4000);

    pool = pj_pool_create( &cp.factory, "test-media", 1000, 1000, NULL);

    pjmedia_endpt_create(&cp.factory, NULL, 1, &endpt);
    list_devices();

    int dev_idx = atoi(argv[1]);

    player_t player;

    int sampling_rate = atoi(argv[2]);

    init_player(pool, dev_idx, sampling_rate, argv[3], &player);

    start_player(&player);

    printf("Press ENTER to exit ...");
    char tmp[10];
    fgets(tmp, sizeof(tmp), stdin);

    destroy_player(&player);

    pj_pool_release(pool);

    pjmedia_endpt_destroy(endpt);
    pj_caching_pool_destroy(&cp);
    pj_shutdown();
    return 0;
}
