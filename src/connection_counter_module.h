#pragma once
#include "export.h"

class connection_counter_module {
public:
    static ngx_int_t post_config_init(ngx_conf_t* cf);
    static void* create_location_conf(ngx_conf_t *cf);

    static char* config_set_zone(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
};