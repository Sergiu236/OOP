#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <string>
#include "domain.h"

class Repository {
    std::vector<Courier> couriers;
    std::vector<Package> packages;

public:
    Repository();
    const std::vector<Courier>& getCouriers() const;
    const std::vector<Package>& getPackages() const;
    void addPackage(const Package& package);
};

#endif // REPOSITORY_H
