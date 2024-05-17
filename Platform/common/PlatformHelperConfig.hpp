#pragma once

#include "axmol.h"

#if defined(AX_PLATFORM_IOS) || defined(AX_PLATFORM_TVOS)
#include "ios/PlatformHelper.hpp"
#elif defined(AX_PLATFORM_ANDROID)
#include "android/PlatformHelper.h"
#elif defined(AX_PLATFORM_WIN32)
#include "desktop/PlatformHelper.h"
#elif defined(AX_PLATFORM_MAC)
#include "desktop/PlatformHelper.h"
#elif defined(AX_PLATFORM_LINUX)
#include "desktop/PlatformHelper.h"
#elif defined(AX_PLATFORM_WASM)
#include "wasm/PlatformHelper.h"
#else
#error "Platform Helper is not defined for this platform."
#endif
