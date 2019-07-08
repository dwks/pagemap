#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define PAGE_SIZE 0x1000

static void print_page(uint64_t address, uint64_t data) {
    printf("0x%-16lx : pfn %-16lx soft-dirty %ld file/shared %ld "
        "swapped %ld present %ld\n",
        address,
        data & 0x7fffffffffffff,
        (data >> 55) & 1,
        (data >> 61) & 1,
        (data >> 62) & 1,
        (data >> 63) & 1);
}

int main(int argc, char *argv[]) {
    char filename[BUFSIZ];
    if(argc != 4) {
        printf("Usage: %s pid start_address end_address\n",
            argv[0]);
        return 1;
    }

    errno = 0;
    int pid = (int)strtol(argv[1], NULL, 0);
    if(errno) {
        perror("strtol");
        return 1;
    }
    snprintf(filename, sizeof filename, "/proc/%d/pagemap", pid);

    int fd = open(filename, O_RDONLY);
    if(fd < 0) {
        perror("open");
        return 1;
    }

    uint64_t start_address = strtoul(argv[2], NULL, 0);
    uint64_t end_address = strtoul(argv[3], NULL, 0);

    for(uint64_t i = start_address; i < end_address; i += 0x1000) {
        uint64_t data;
        uint64_t index = (i / PAGE_SIZE) * sizeof(data);
        if(pread(fd, &data, sizeof(data), index) != sizeof(data)) {
            perror("pread");
            break;
        }

        print_page(i, data);
    }

    close(fd);
    return 0;
}
