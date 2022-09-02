cmake_minimum_required(VERSION 3.16)
# --------------------------------------------------------------------------------------------------
project(ngx_connection_counter_module)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_VERSION "1.0.0")
set(NGINX_SOURCE ${PROJECT_SOURCE_DIR}/stage/nginx-1.22.0)
set(BOOST_VENDOR /data/vendor/boost-1.80)
# --------------------------------------------------------------------------------------------------
# compile config

file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*.cpp" "src/*.c")
add_library(ngx_connection_counter_module SHARED ${SOURCES})
target_include_directories(ngx_connection_counter_module SYSTEM
    PRIVATE ${NGINX_SOURCE}/src/core
    PRIVATE ${NGINX_SOURCE}/src/event
    PRIVATE ${NGINX_SOURCE}/src/event/modules
    PRIVATE ${NGINX_SOURCE}/src/os/unix
    PRIVATE ${NGINX_SOURCE}/objs
    PRIVATE ${NGINX_SOURCE}/src/http
    PRIVATE ${NGINX_SOURCE}/src/http/modules
    PRIVATE ${BOOST_VENDOR}/include
)
target_link_directories(ngx_connection_counter_module PRIVATE ${BOOST_VENDOR}/lib)
target_link_libraries(ngx_connection_counter_module boost_system)
