#include "export.h"
#include "connection_counter_module.h"
#include "connection_counter_config.h"
#include "connection_counter_handler.h"

ngx_int_t connection_counter_module::post_config_init(ngx_conf_t* cf) {
    ngx_http_handler_pt *h;
    ngx_http_core_main_conf_t* core_http_conf;
    core_http_conf = static_cast<ngx_http_core_main_conf_t*>(ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module));
    h = static_cast<ngx_http_handler_pt*>(ngx_array_push(&core_http_conf->phases[NGX_HTTP_ACCESS_PHASE].handlers));
    if (h == NULL) return NGX_ERROR;
    *h = connection_counter_handler::http_post_access_phase_handler;

    h = static_cast<ngx_http_handler_pt*>(ngx_array_push(&core_http_conf->phases[NGX_HTTP_LOG_PHASE].handlers));
    if (h == NULL) return NGX_ERROR;
    *h = connection_counter_handler::http_log_phase_handler;
    return NGX_OK;
}

void* connection_counter_module::create_location_conf(ngx_conf_t *cf) {
    char* memory = static_cast<char*>(ngx_pcalloc(cf->pool, sizeof(connection_counter_config)));
    if (memory == NULL) return NULL;
    connection_counter_config *counter = new(memory) connection_counter_config;
    return counter;
}

char* connection_counter_module::config_set_zone(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
    return NGX_CONF_OK;
}



