# Axmol Platform Helper

This is a project that add the ability to call specific `Platform Functions`.

## Files To Add

These are the files that you need:

- /Platform
- /proj.android/app/src/org/axmol/platform/PlatformDelegate.java
- /proj.android/app/src/org/axmol/app/MainApplication.java

## Code Changes

There are some small changes that you need do to your project to include this.

### CMake root file: CMakeLists.txt

Add platform directory:

```cmake
add_subdirectory(Platform)
```

Add emscripten code for embind:

```cmake
if (WASM)
    target_link_libraries(${APP_NAME} "embind")
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS "--bind")
endif()
```

### Project delegate file: AppDelegate.cpp

```cpp
#include "common/PlatformHelperConfig.hpp"
```

### Android project changes

**proj.android/app/AndroidManifest.xml:**

```xml
<application android:name="org.axmol.app.MainApplication"
[...]
```

**proj.android/app/build.gradle:**

```groovy
implementation 'androidx.annotation:annotation:1.8.0'
```

## Screenshot

<img width="250" src="Extras/images/ss1.jpg">
