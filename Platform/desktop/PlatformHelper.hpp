#pragma once

#include "common/PlatformHelperProtocol.hpp"
#include <memory>

class PlatformHelper : public PlatformHelperProtocol {
public:
    static std::shared_ptr<PlatformHelperProtocol> shared();
    virtual void performAction(const std::string &action, const std::string &data, std::function<void(std::string)> callback) override;
};
