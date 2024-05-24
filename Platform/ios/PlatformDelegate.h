#pragma once

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface PlatformDelegate : NSObject

@property(nonatomic, copy) void (^callback)(NSString *);

+ (PlatformDelegate *)shared;
+ (void)performAction:(NSString *)action data:(NSString *)data callback:(void (^)(NSString *))callback;

@end
