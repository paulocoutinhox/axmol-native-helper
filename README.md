# Axmol Platform Helper

This is a project that add the ability to call specific `Platform Functions`.

## Files To Add

These are the files that you need:

- /Platform
- /proj.android/app/src/org/axmol/platform/PlatformDelegate.java
- /proj.android/app/src/org/axmol/app/MainApplication.java

## Code Changes

These are the code changes that you need:

**CMakeLists.txt:**

```cmake
add_subdirectory(Platform)
```

**AppDelegate.cpp:**

```cpp
#include "common/PlatformHelperConfig.hpp"
```

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
