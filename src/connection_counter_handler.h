#pragma once
#include "export.h"

class connection_counter_handler {
public:
    static ngx_int_t http_post_access_phase_handler(ngx_http_request_t *r);
    static ngx_int_t http_log_phase_handler(ngx_http_request_t *r);
};