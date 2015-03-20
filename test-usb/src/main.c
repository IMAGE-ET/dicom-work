#include "ansi-utils.h"
#include "my-usb-utils.h"
#include <stdio.h>

void usage() {
    printf("test-usb <usb-idx> [options]\n\toptions:\n\t\t- 1: turn on\n\t\t- 0: turn off\n");
}
int main(int argc, char *argv[]) {
    if(argc < 3) {
        usage();
        return -1;
    }
    int usb_idx = atoi(argv[1]);
    int on = atoi(argv[2]);
    if(on) {
        bind_usb(usb_idx);
    }
    else {
        unbind_usb(usb_idx);
    }
    return 0;
}
