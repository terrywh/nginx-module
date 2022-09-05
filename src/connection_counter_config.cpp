#include "connection_counter_config.h"

bool connection_counter_config::zone_already_existed(const std::string& zone) const {
    return zones_.find(zone) != zones_.end();
}