# 原理
1. 使用 ngx_http_core_module 模块实现对请求速度限速；
2. 使用 ngx_http_limit_conn_module 模块实现对连接数控制；
3. 使用 ngx_http_auth_request_module 模块实现鉴权 (默认依赖 HTTP 响应 STATUS_CODE 值)；

**扩展**
4. 使用 ngx_http_mp4_module 支持流媒体播放机制及按时间定位（MP4 按码率限速需要商业版支持）；
5. 使用 ngx_http_limit_req_module 实现对请求速度限制；
6. 使用 njs 模块实现对鉴权调用，并获取用户信息、配置等；

# 编译
``` bash
./build.sh
# 调试逻辑可考虑在 build.sh 执行后，手动下述命令（单独编译扩展模块）
cd stage/nginx-${NGINX_VERSION}
make modules
cp objs/objs/ngx_connection_counter_module.so ${NGINX_DIR}/modules/
```

# 控制
``` bash
# 启动
${TARGET_PATH}/sbin/nginx
# 重载配置
${TARGET_PATH}/sbin/nginx -s reload
# 终止
${TARGET_PATH}/sbin/nginx -s stop
# 停止
${TARGET_PATH}/sbin/nginx -s quit
```

# 参考
http://nginx.org/en/docs/


# 三方源
* nginx - https://nginx.org/en/download.html
* njs - http://hg.nginx.org/njs
