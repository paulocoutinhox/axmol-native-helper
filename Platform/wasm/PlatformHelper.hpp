#pragma once

#include "common/PlatformHelperProtocol.hpp"
#include <memory>

extern "C" {
void platformHelperJsCallback(std::string value);
}

class PlatformHelper : public PlatformHelperProtocol {
public:
    static std::shared_ptr<PlatformHelperProtocol> shared();
    virtual void performAction(const std::string &action, const std::string &data, std::function<void(std::string)> callback) override;
    std::function<void(std::string)> callback;

private:
    void onActionInitialize(const std::string &data, std::function<void(std::string)> callback);
    void onActionGetCustomerId(const std::string &data, std::function<void(std::string)> callback);
    void onActionStartTaskLong(const std::string &data, std::function<void(std::string)> callback);
    void onActionShowAlert(const std::string &data, std::function<void(std::string)> callback);
};
