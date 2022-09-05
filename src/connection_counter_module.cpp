#include "export.h"
#include "connection_counter_module.h"
#include "connection_counter_config.h"
#include "connection_counter_handler.h"
#include "utility_config_parser.h"

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
    auto* counter = static_cast<connection_counter_config *>(conf);
    ngx_str_t* args = static_cast<ngx_str_t*>(cf->args->elts);

    ngx_http_core_main_conf_t* http_core_conf = static_cast<ngx_http_core_main_conf_t*>(ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module));

    ngx_log_error(NGX_LOG_DEBUG, cf->log, 0, "before config_zone_set %V %V", args[1], args[2]);
    std::string zone {reinterpret_cast<char*>(args[1].data), args[1].len};
    if (counter->zone_already_existed(zone)) {
        ngx_log_error(NGX_LOG_ERR, cf->log, 0, "connection_counter_module zone already existed: %V %V", &args[1]);
        return static_cast<char*>(NGX_CONF_ERROR);
    }
    utility_config_parser::key_value kv { args[2] };
    if (kv.key() == "size") ngx_log_error(NGX_LOG_INFO, cf->log, 0, "zone=%V size=%s", args[1], kv.val());
    ngx_log_error(NGX_LOG_DEBUG, cf->log, 0, "after config_zone_set %V %V", args[1], args[2]);
    return NGX_CONF_OK;
}



