#include "android/PlatformHelper.hpp"
#include "common/PlatformHelperContext.hpp"
#include "core/platform/android/jni/JniHelper.h"
#include <jni.h>

using namespace ax;

std::shared_ptr<PlatformHelperProtocol> PlatformHelper::shared() {
    static std::shared_ptr<PlatformHelper> instance(new PlatformHelper());
    return instance;
}

void PlatformHelper::performAction(const std::string &action, const std::string &data, std::function<void(std::string)> callback) {
    auto context = std::make_shared<PlatformHelperContext>(callback);
    auto contextAddress = new std::shared_ptr<PlatformHelperContext>(context);

    JniHelper::callStaticVoidMethod("dev.axmol.platform.PlatformDelegate", "performAction", action.c_str(), data.c_str(), reinterpret_cast<jlong>(contextAddress));
}

extern "C" JNIEXPORT void JNICALL Java_dev_axmol_platform_PlatformDelegate_nativeOnActionComplete(JNIEnv *env, jclass clazz, jstring result, jlong contextAddress) {
    auto contextPtr = reinterpret_cast<std::shared_ptr<PlatformHelperContext> *>(contextAddress);

    if (contextPtr && *contextPtr) {
        const char *cResult = env->GetStringUTFChars(result, JNI_FALSE);
        std::string strResult(cResult);
        env->ReleaseStringUTFChars(result, cResult);

        (*contextPtr)->triggerCallback(strResult);
    }

    delete contextPtr;
}
