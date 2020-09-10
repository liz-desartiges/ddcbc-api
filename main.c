#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ddcbc_api.c"

// getMonitorNumber gets the monitor number in the second argument.
unsigned int getMonitorNumber(ddcbc_bundle *bun, int argc, char **argv) {
    if (argc <= 1) {
        fprintf(stderr, "ERROR: Must specify third argument for this command");
        exit(-1);
    }

    int dispno = atoi(argv[2]);
    if (dispno <= 0 || (unsigned int) dispno > bun->ct) {
        fprintf(stderr, "ERROR: Invalid display number '%d'", dispno);
        exit(-1);
    }

    return (unsigned int) dispno;
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        fprintf(stderr, "ERROR: Must give at least one argument\n");
        return -1;
    }
    ddcbc_bundle bun = ddcbc_bundle_init();

    char *cmd = argv[1];
    unsigned int dispno = 0;

    if (strcmp(cmd, "get") == 0) {

        dispno = getMonitorNumber(&bun, argc, argv);

        brightness_stats bs = ddcbc_bundle_get_brightness(&bun, dispno);
        printf("Monitor No '%d' brightness %u/%u\n", dispno, 
            bs.cur_val, bs.max_val);
    
    } else if (strcmp(cmd, "set") == 0) {
        
        dispno = getMonitorNumber(&bun, argc, argv);

        int new_val = atoi(argv[3]);
        if (new_val < 0) {
            fprintf(stderr, "ERROR: Must give value greater than 0\n");
        }

        ddcbc_bundle_set_brightness(&bun, dispno, (uint16_t) new_val);
    
    } else if (strcmp(cmd, "getAll") == 0) {
        
        for (unsigned int i = 0; i < bun.ct; i++) {
            brightness_stats bs = ddcbc_bundle_get_brightness(&bun, i + 1);
            printf("Monitor No '%d' brightness %u/%u\n", i + 1, 
                bs.cur_val, bs.max_val);
        }

    } else if (strcmp(cmd, "setAll") == 0) {

        int new_val = atoi(argv[2]);
        if (new_val <= 0) {
            fprintf(stderr, "ERROR: Must give value greater than 0\n");
        }

        for (unsigned int i = 0; i < bun.ct; i++) {
            ddcbc_bundle_set_brightness(&bun, i + 1, (uint16_t) new_val);
            printf("Brightness on monitor '%d' set to '%d'\n", i + 1, new_val);
        }
    } else {
        
        printf("No such command '%s'", argv[1]);
        printf("Availible commands: get, set, getAll, setAll");
    
    }

    ddcbc_bundle_free(&bun);
    return 0;
}