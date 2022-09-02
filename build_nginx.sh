#!/bin/bash
# ----------------------------------------------------------------------------------------------------------------------
# 版本信息
export NGINX_VERSION=1.22.0
export NJS_VERSION=0.7.7
# 目标路径
export SOURCE_DIR=`pwd`
export NGINX_DIR=`pwd`/release/nginx
# ----------------------------------------------------------------------------------------------------------------------
# 1. 解压源码包，创建编译环境；
cd ${SOURCE_DIR}
mkdir -p stage; cd stage
tar xf ../vendor/nginx-${NGINX_VERSION}.tar.gz
# tar xf ../vendor/njs-${NJS_VERSION}.tar.gz
# mv njs-* njs-${NJS_VERSION}
cd nginx-${NGINX_VERSION}
# 2. 编译服务进程
# -- 是否需要独立的 nginx 运行用户？
# ./configure --prefix=${NGINX_DIR} --with-http_ssl_module --with-http_auth_request_module --with-http_mp4_module --add-module=../njs-${NJS_VERSION}/nginx
./configure --prefix=${NGINX_DIR} --with-http_ssl_module --with-http_auth_request_module --with-http_mp4_module
make install
# 3. 覆盖配置
cp -rf conf/* release/nginx/conf/