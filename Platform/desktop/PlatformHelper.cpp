#include "desktop/PlatformHelper.hpp"

std::shared_ptr<PlatformHelperProtocol> PlatformHelper::shared() {
    static std::shared_ptr<PlatformHelper> instance(new PlatformHelper());
    return instance;
}

void PlatformHelper::performAction(const std::string &action, const std::string &data, std::function<void(std::string)> callback) {
    callback("need-implement");
}
