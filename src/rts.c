#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rts/rts.h"
#include "rts/metrics.h"
#include "rts/server.h"

/* test */
#include <unistd.h>

int rts_init(rts_t *rts)
{
    rts->metrics = NULL;

    return 0;
}

void rts_destroy(rts_t *rts)
{
}

/* global metrics struct in users program */
struct metrics
{
    int wifi_sniffed;
    int wifi_pushed;
};

int main()
{
    struct metrics metrics;
    rts_t          rts;
    int            i;

    metrics.wifi_pushed  = 10;
    metrics.wifi_pushed += 5;
    metrics.wifi_sniffed = 7;

    rts_init(&rts);

    rts_metrics_add(&rts, "wifi_sniffed", &metrics.wifi_sniffed);
    rts_metrics_add(&rts, "wifi_pushed", &metrics.wifi_pushed);

    rts_serve(&rts, "127.0.0.1", "8000");

    for (i = 0; i < 10; i++)
    {
        printf("i: %d\n", i);
        sleep(2);
    }

    rts_destroy(&rts);

    return 0;
}
