#pragma once

#include <functional>
#include <memory>
#include <string>

class PlatformHelperProtocol {
public:
    virtual void performAction(
        const std::string &action,
        const std::string &data = "",
        std::function<void(std::string)> callback = [](std::string) {}) = 0;
};
