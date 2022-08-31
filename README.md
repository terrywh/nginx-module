# 原理
1. 使用 ngx_http_core_module 模块实现对请求速度限速；
2. 使用 ngx_http_limit_conn_module 模块实现对连接数控制；
3. 使用 ngx_http_auth_request_module 模块实现鉴权 (默认依赖 HTTP 响应 STATUS_CODE 值)；

**扩展**
4. 使用 ngx_http_mp4_module 支持流媒体播放机制及按时间定位（MP4 按码率限速需要商业版支持）；
5. 使用 ngx_http_limit_req_module 实现对请求速度限制；
6. 使用 njs 模块实现对鉴权调用，并获取用户信息、配置等；

# 编译部署流程
``` bash
# 版本信息
NGINX_VERSION=1.22.0
NJS_VERSION=0.7.7
# 目标路径
TARGET_PATH=`pwd`/release/nginx
SOURCE_PATH=`pwd`
# 1. 解压源码包，创建编译环境；
mkdir stage; cd stage
tar xf ../vendor/nginx-${NGINX_VERSION}.tar.gz
tar xf ../vendor/njs-${NJS_VERSION}.tar.gz
mv njs-* njs-${NJS_VERSION}
cd nginx-${NGINX_VERSION}
# 2. 编译服务进程
# -- 是否需要独立的 nginx 运行用户？
./configure --prefix=${TARGET_PATH}  --with-http_ssl_module --with-http_auth_request_module --with-http_mp4_module --add-module=../njs-${NJS_VERSION}/nginx
make install
# 3. 覆盖配置
cd ${SOURCE_PATH}
rm -rf ${TARGET_PATH}/conf/vhost
cp -rf conf/* ${TARGET_PATH}/conf/
# 4. 启动 NGINX 进程
${TARGET_PATH}/sbin/nginx
```

# 参考
http://nginx.org/en/docs/


# 三方源
* nginx - https://nginx.org/en/download.html
* njs - http://hg.nginx.org/njs
