#include "wasm/PlatformHelper.hpp"
#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include <sstream>

std::shared_ptr<PlatformHelperProtocol> PlatformHelper::shared() {
    static std::shared_ptr<PlatformHelper> instance(new PlatformHelper());
    return instance;
}

void PlatformHelper::performAction(const std::string &action, const std::string &data, std::function<void(std::string)> callback) {
    this->callback = callback;

    if (action == "initialize") {
        onActionInitialize(data, callback);
    } else if (action == "get-customer-id") {
        onActionGetCustomerId(data, callback);
    } else if (action == "start-task-long") {
        onActionStartTaskLong(data, callback);
    } else if (action == "show-alert") {
        onActionShowAlert(data, callback);
    }
}

void PlatformHelper::onActionInitialize(const std::string &data, std::function<void(std::string)> callback) {
    // initialize your custom platform SDK here, example: Firebase, Facebook, Google etc.

#if defined(_AX_DEBUG)
    std::cout << "[PlatformHelper : onActionInitialize] Initialized in debug" << std::endl;
#else
    std::cout << "[PlatformHelper : onActionInitialize] Initialized in release" << std::endl;
#endif

    callback("initialized");
}

void PlatformHelper::onActionGetCustomerId(const std::string &data, std::function<void(std::string)> callback) {
    // clang-format off
    EM_ASM({
        function uuidv4() {
            return "10000000-1000-4000-8000-100000000000".replace(/[018]/g, c =>
                (+c ^ crypto.getRandomValues(new Uint8Array(1))[0] & 15 >> +c / 4).toString(16)
            );
        }

        Module.platformHelperJsCallback(uuidv4());
    });
    // clang-format on
}

void PlatformHelper::onActionStartTaskLong(const std::string &data, std::function<void(std::string)> callback) {
    // clang-format off
    EM_ASM({
        var url = "https://httpbin.org/get";
        fetch(url)
            .then(response => response.text())
            .then(data => {
                Module.platformHelperJsCallback(data);
            })
            .catch(error => {
                Module.platformHelperJsCallback("no-response");
            });
    });
    // clang-format on
}

void PlatformHelper::onActionShowAlert(const std::string &data, std::function<void(std::string)> callback) {
    EM_ASM_ARGS({
        var jsonString = UTF8ToString($0);
        try {
            var jsonData = JSON.parse(jsonString);
            var message = jsonData.message;

            if (message) {
                var result = confirm(message);
                var response = result ? "Clicked on: YES" : "Clicked on: NO";
                Module.platformHelperJsCallback(response);
            } else {
                Module.platformHelperJsCallback("message-not-found");
            }
        } catch (e) {
            Module.platformHelperJsCallback("json-error");
        }
    },
                data.c_str());
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
