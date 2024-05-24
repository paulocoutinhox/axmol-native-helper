#include "wasm/PlatformHelper.hpp"
#include <emscripten.h>
#include <emscripten/bind.h>

std::shared_ptr<PlatformHelperProtocol> PlatformHelper::shared() {
    static std::shared_ptr<PlatformHelper> instance(new PlatformHelper());
    return instance;
}

void PlatformHelper::performAction(const std::string &action, const std::string &data, std::function<void(std::string)> callback) {
    this->callback = callback;

    EM_ASM({
        var result = prompt("Please enter a value for action '" + action + "':");
        Module.platformHelperJsCallback(result);
    });
}

void platformHelperJsCallback(std::string value) {
    auto instance = std::static_pointer_cast<PlatformHelper>(PlatformHelper::shared());

    if (instance->callback) {
        instance->callback(value);
    }
}

EMSCRIPTEN_BINDINGS(platform_helper_module) {
    emscripten::function("platformHelperJsCallback", &platformHelperJsCallback);
}
