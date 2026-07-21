#include "headers.h"

void init_system(t_system *system, t_config *config)
{
    system->coders = malloc(sizeof(t_coder) * system->config.n_coders);
    if (!system->coders)
    {
        printf("malloc fails in coders");
        return;
    }
    system->dongles = malloc(sizeof(t_dongle) * system->config.n_coders);
    if (!system->dongles)
    {
        free(system->coders);
        printf("malloc fails in dongles");
        return;
    }
    system->config = *config;
    // should initial the starting time
    // should initial the mutex of every dongle
    // should initial the mutex of the system
}
