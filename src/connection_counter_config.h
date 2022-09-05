#pragma once
#include "export.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <string>
#include <map>

class connection_counter_config {
public:
    typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> allocator_c;
    using key_type = boost::interprocess::basic_string<char, std::char_traits<char>, allocator_c>;
    using val_type = int;
    typedef boost::interprocess::allocator<
        std::pair<key_type, val_type>, boost::interprocess::managed_shared_memory::segment_manager> allocator_p;
    typedef boost::interprocess::map<
        key_type, val_type, std::less<boost::interprocess::string>, allocator_p> shmmap;
    
    connection_counter_config() = default;
    struct memory_zone_config {
        std::size_t size;
    };
    bool zone_already_existed(const std::string& zone) const;
private:
    std::map<std::string, memory_zone_config> zones_;
};
