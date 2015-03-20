#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#define SYSFS_USB_DIR "/sys/bus/usb/drivers/usb"
#define BIND_FILE "bind"
#define UNBIND_FILE "unbind"
char *USB_NAME[] = {
    "1-1.1", "1-1.2", "1-1.3", "1-1.4"
};

static void bind_or_unbind(int usb_idx, char *sysfs_file) {
    int fd;
    fd = open(sysfs_file, O_WRONLY);
    if(fd > 0) {
        write(fd, USB_NAME[usb_idx], strlen(USB_NAME[usb_idx]));
        close(fd);
    }
    else {
        fprintf(stderr, "bind_or_unbind: error - %s\n", strerror(errno));
        exit(-1);
    }
}
void bind_usb(int usb_idx) {
    bind_or_unbind(usb_idx, SYSFS_USB_DIR"/"BIND_FILE);
}
void unbind_usb(int usb_idx) {
    bind_or_unbind(usb_idx, SYSFS_USB_DIR"/"UNBIND_FILE);
}
int is_binding(int usb_idx) {
    DIR *d;
    struct dirent *dir;
    d = opendir(SYSFS_USB_DIR);
    if(d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name, USB_NAME[usb_idx]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
