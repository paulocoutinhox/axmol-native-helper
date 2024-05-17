# Source code
if(ANDROID)
    set(GAME_HEADER ${GAME_HEADER}
        Platform/common/PlatformHelperProtocol.hpp
        Platform/android/PlatformHelper.hpp
        PARENT_SCOPE
    )
    set(GAME_SOURCE ${GAME_SOURCE}
        Platform/android/PlatformHelper.cpp
        PARENT_SCOPE
    )
elseif(LINUX)
    set(GAME_HEADER ${GAME_HEADER}
        Platform/common/PlatformHelperProtocol.hpp
        Platform/desktop/PlatformHelper.hpp
        PARENT_SCOPE
    )
    set(GAME_SOURCE ${GAME_SOURCE}
        Platform/desktop/PlatformHelper.cpp
        PARENT_SCOPE
    )
elseif(WASM)
    set(GAME_HEADER ${GAME_HEADER}
        Platform/common/PlatformHelperProtocol.hpp
        Platform/wasm/PlatformHelper.hpp
        PARENT_SCOPE
    )
    set(GAME_SOURCE ${GAME_SOURCE}
        Platform/wasm/PlatformHelper.cpp
        PARENT_SCOPE
    )
elseif(WINDOWS)
    set(GAME_HEADER ${GAME_HEADER}
        Platform/common/PlatformHelperProtocol.hpp
        Platform/desktop/PlatformHelper.hpp
        PARENT_SCOPE
    )
    set(GAME_SOURCE ${GAME_SOURCE}
        Platform/desktop/PlatformHelper.cpp
        PARENT_SCOPE
    )
elseif(APPLE)
    if(IOS)
        set(GAME_HEADER ${GAME_HEADER}
            Platform/common/PlatformHelperProtocol.hpp
            Platform/ios/PlatformHelper.hpp
            Platform/ios/PlatformDelegate.h
            PARENT_SCOPE
        )
        set(GAME_SOURCE ${GAME_SOURCE}
            Platform/ios/PlatformHelper.mm
            Platform/ios/PlatformDelegate.mm
            PARENT_SCOPE
        )
    elseif(MACOSX)
        set(GAME_HEADER ${GAME_HEADER}
            Platform/common/PlatformHelperProtocol.hpp
            Platform/desktop/PlatformHelper.hpp
            PARENT_SCOPE
        )
        set(GAME_SOURCE ${GAME_SOURCE}
            Platform/desktop/PlatformHelper.cpp
            PARENT_SCOPE
        )
    endif()
endif()

# Include directories
set(GAME_INC_DIRS ${GAME_INC_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}
    PARENT_SCOPE
)
