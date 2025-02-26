#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
#include <vector>

struct Courier {
    std::string name;
    std::vector<std::string> streets;
    double zone_x, zone_y, zone_radius;
};

struct Package {
    std::string recipient;
    std::string address_street;
    int address_number;
    double location_x, location_y;
    bool delivery_status;
};

#endif // DOMAIN_H
