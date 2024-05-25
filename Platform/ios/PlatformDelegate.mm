#include "ios/PlatformDelegate.h"
#include "axmol.h"

@implementation PlatformDelegate

static PlatformDelegate *instance = nil;

+ (PlatformDelegate *)shared {
    if (!instance) {
        instance = [[PlatformDelegate alloc] init];
    }

    return instance;
}

+ (void)performAction:(NSString *)action data:(NSString *)data callback:(void(^)(NSString *))callback {
    if ([action isEqualToString:@"initialize"]) {
        [self onActionInitialize:data callback:callback];
    } else if ([action isEqualToString:@"get-customer-id"]) {
        [self onActionGetCustomerId:data callback:callback];
    } else if ([action isEqualToString:@"start-task-long"]) {
        [self onActionStartTaskLong:data callback:callback];
    } else if ([action isEqualToString:@"show-alert"]) {
        [self onActionShowAlert:data callback:callback];
    }
}

+ (void)onActionInitialize:(NSString *)data callback:(void(^)(NSString *))callback {
    // initialize your custom platform SDK here, example: Firebase, Facebook, Google etc

#if defined(_AX_DEBUG)
    AXLOG("[PlatformDelegate : onActionInitialize] Initialized in debug");
#else
    AXLOG("[PlatformDelegate : onActionInitialize] Initialized in release");
#endif

    callback(@"initialized");
}

+ (void)onActionStartTaskLong:(NSString *)data callback:(void(^)(NSString *))callback {
    NSURL *url = [NSURL URLWithString:@"https://httpbin.org/get"];
    NSURLSession *session = [NSURLSession sharedSession];

    NSURLSessionDataTask *dataTask = [session dataTaskWithURL:url completionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        if (error) {
            NSLog(@"Erro na requisição: %@", error.localizedDescription);
            callback(nil);
            return;
        }

        if (data) {
            NSString *responseBody = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];

            callback(responseBody);
        } else {
            callback(@"no-response");
        }
    }];

    [dataTask resume];
}

+ (void)onActionGetCustomerId:(NSString *)data callback:(void(^)(NSString *))callback {
    NSUUID *uuid = [NSUUID UUID];
    NSString *uuidString = [uuid UUIDString];
    callback(uuidString);
}

+ (void)onActionShowAlert:(NSString *)data callback:(void(^)(NSString *))callback {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSError *jsonError = nil;
        NSDictionary *jsonDict = [NSJSONSerialization JSONObjectWithData:[data dataUsingEncoding:NSUTF8StringEncoding]
                                                                 options:0
                                                                   error:&jsonError];

        if (jsonError) {
            NSLog(@"Error parsing JSON: %@", jsonError.description);
            callback(@"json-error");
            return;
        }

        NSString *message = jsonDict[@"message"];

        if (!message) {
            NSLog(@"Error: 'message' not found in JSON");
            callback(@"message-not-found");
            return;
        }

        [self shared].callback = callback;

        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Alert"
                                                                       message:message
                                                                preferredStyle:UIAlertControllerStyleAlert];

        UIAlertAction *yesAction = [UIAlertAction actionWithTitle:@"Yes" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            [self handleAlertResponse:@"yes"];
        }];

        UIAlertAction *noAction = [UIAlertAction actionWithTitle:@"No" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
            [self handleAlertResponse:@"no"];
        }];

        [alert addAction:yesAction];
        [alert addAction:noAction];

        UIViewController *rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
        [rootViewController presentViewController:alert animated:YES completion:nil];
    });
}

+ (void)handleAlertResponse:(NSString *)response {
    if ([response isEqualToString:@"yes"]) {
        if (instance.callback) {
            instance.callback(@"Clicked on: YES");
        }
    } else {
        if (instance.callback) {
            instance.callback(@"Clicked on: NO");
        }
    }
}

@end
