#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "idx.h"


int main(int argc, char **argv) {
    int status = 1;
    int fd = -1;
    struct stat st;
    off_t size;
    void *buff = NULL;
    IdxError err;

    if (argc < 2) {
        fprintf(stderr, "idx-validate: Missing argument\n");
        goto cleanup;
    }

    if (argc > 2) {
        fprintf(stderr, "idx-validate: Unexpected arguments\n");
        goto cleanup;
    }
    
    if (strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, (
            "Usage: idx-validate [FILE]\n"
            "Checks if FILE contains a valid IDX structure\n"
        ));
        status = 0;
        goto cleanup;
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("validate");
        goto cleanup;
    }
    
    if (fstat(fd, &st) == -1) {
        perror("validate");
        goto cleanup;
    }
    
    size = st.st_size;
    
    if (size <= 0) {
        fprintf(stderr, "idx-validate: File has zero size\n");
        goto cleanup;
    }
    
    buff = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buff == MAP_FAILED) {
        perror("validate");
        goto cleanup;
    }
    
    err = idx_validate(buff, size);
    if (err != IDX_NO_ERROR) {
        fprintf(
            stderr, "idx-validate: Validation failed: %s\n",
            idx_error_string(err)
        );
        goto cleanup;
    }

    status = 0;

cleanup:
    if (buff != NULL) {
        munmap(buff, size);
    }
    
    if (fd != -1) {
        close(fd);
    }
    
    return status;   
}
