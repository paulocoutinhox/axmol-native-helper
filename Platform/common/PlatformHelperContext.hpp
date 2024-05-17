#pragma once

#include <functional>
#include <string>

class PlatformHelperContext {
public:
    std::function<void(const std::string &)> callback;

    PlatformHelperContext(std::function<void(const std::string &)> cb)
        : callback(cb) {}

    void triggerCallback(std::string result) {
        if (callback) {
            callback(result);
        }
    }
};
