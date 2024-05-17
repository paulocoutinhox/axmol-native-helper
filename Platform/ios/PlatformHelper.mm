#include "ios/PlatformHelper.hpp"
#include "ios/PlatformDelegate.h"

std::shared_ptr<PlatformHelperProtocol> PlatformHelper::shared()
{
    static std::shared_ptr<PlatformHelper> instance = std::make_shared<PlatformHelper>();
    return instance;
}

void PlatformHelper::performAction(const std::string &action, const std::string &data, std::function<void(std::string)> callback)
{
    NSString* nsAction = [NSString stringWithCString:action.c_str() encoding:NSUTF8StringEncoding];
    NSString* nsData = [NSString stringWithCString:data.c_str() encoding:NSUTF8StringEncoding];
    
    [PlatformDelegate performAction:nsAction data:nsData callback:^(NSString* result) {
        std::string stdResult = [result UTF8String];
        callback(stdResult);
    }];
}
