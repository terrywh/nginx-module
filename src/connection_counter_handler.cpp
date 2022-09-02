#include "connection_counter_handler.h"
ngx_int_t connection_counter_handler::http_post_access_phase_handler(ngx_http_request_t *r) {
    return NGX_DECLINED;
}
ngx_int_t connection_counter_handler::http_log_phase_handler(ngx_http_request_t *r) {
    return NGX_DECLINED;
}