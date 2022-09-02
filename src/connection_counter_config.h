#pragma once
#include "export.h"
#include <boost/system/error_code.hpp>

class connection_counter_config {
public:
    boost::system::error_code error;
    connection_counter_config() = default;
};