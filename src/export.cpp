#include "export.h"
#include "connection_counter_module.h"

extern "C" {
ngx_module_t *ngx_modules[] = {
    &ngx_connection_counter_module,
    NULL
};

char *ngx_module_names[] = {
    "ngx_connection_counter_module",
    NULL
};

char *ngx_module_order[] = {
    NULL
};


static ngx_http_module_t ngx_connection_counter_module_ctx = {
    NULL,       /* preconfiguration */
    connection_counter_module::post_config_init, /* postconfiguration */

    NULL,       /* create main configuration */
    NULL,       /* init main configuration */

    connection_counter_module::create_location_conf,       /* create server configuration */
    NULL,       /* merge server configuration */

    NULL,       /* create location configuration */
    NULL        /* merge location configuration */
};

static ngx_command_t ngx_connection_counter_commands[] = {
    { ngx_string("counter_zone"),
      NGX_HTTP_SRV_CONF | NGX_CONF_TAKE2,
      connection_counter_module::config_set_zone,
      NGX_HTTP_SRV_CONF_OFFSET,
      0,
      NULL },

    ngx_null_command
};

ngx_module_t ngx_connection_counter_module = {
    NGX_MODULE_V1,
    &ngx_connection_counter_module_ctx,            /* module context */
    ngx_connection_counter_commands,               /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};
} // extern "C"