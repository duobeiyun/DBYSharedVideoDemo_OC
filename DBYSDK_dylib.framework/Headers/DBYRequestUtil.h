//
//  DBYRequestUtil.h
//  DBYSDK_dylib
//
//  Created by Michael on 2018/5/15.
//  Copyright © 2018年 duobei. All rights reserved.
//  发请求通用工具类

#import <Foundation/Foundation.h>
#import "DBYEnumerates.h"

NS_ASSUME_NONNULL_BEGIN

@interface DBYRequestUtil : NSObject

+ (void)getRequestWithURL:(NSString *)url
          successHandler:(void(^)(NSData *responseData))successHandler
             failHandler:(void(^)(NSError *error))failHandler;

+ (void)getRequestWithSession:(NSURLSession *)session url:(NSString*)url
              successHandler:(void(^)(NSData *responseData))successHandler
                 failHandler:(void(^)(NSError *error))failHandler;

+ (void)postRequestWithURL:(NSString *)url
           successHandler:(void (^)(NSData *data))successHandler
              failHandler:(void (^)(NSError *error))failHandler;

+ (void)postRequestWithURL:(NSString *)url
                 postBody:(NSString *)postBody
           successHandler:(void(^)(NSData *responseData))successHandler
              failHandler:(void(^)(NSError*error))failHandler;

/// 发送post请求，可指定contentType
/// @param url 请求的url
/// @param params 参数 可以是NSDictiionary、NSArray、NSString、NSData
/// @param contentType 请求格式，枚举
/// @param successHandler 成功回调
/// @param failHandler 失败回调
+ (void)postRequestWithURL:(NSString *)url
                   session:(NSURLSession *)session
                    params:(id)params
               contentType:(DBYContentType)contentType
                   success:(void (^)(NSData *data))successHandler
                   failure:(void (^)(NSError *error))failHandler;

+ (void)postRequestWithURL:(NSString *)url
                  session:(NSURLSession *)session
              paramObject:(id)paramDict
           successHandler:(void (^)(NSData *data))successHandler
              failHandler:(void (^)(NSError *error))failHandler;

+ (void)postRequestWithSession:(NSURLSession*)session url:(NSString*)url
                     postBody:(NSString*)postBody
               successHandler:(void(^)(NSData *responseData))successHandler
                   failHandler:(void(^)(NSError *error))failHandler;

+ (void)postRequestWithURL:(NSString *)url
               paramObject:(id)paramDict
            successHandler:(void (^)(NSData *data))successHandler
               failHandler:(void (^)(NSError *error))failHandler;

+ (void)downloadFileWithUrl:(NSString *)url
            completeHandler:(void(^)(NSURL *location , NSError *error))completeHandler;

+ (void)downloadFileWithSession:(NSURLSession *)session
                            url:(NSString *)url
                completeHandler:(void(^)(NSURL *location , NSError *error))completeHandler;

+ (void)getContentLengthWithUrl:(NSString*)url
                completeHandler:(void(^)(NSInteger length , NSError *error))completeHandler;

+ (void)getContentLengthWithSession:(NSURLSession *)session
                                url:(NSString *)url
                    completeHandler:(void(^)(NSInteger length , NSError *error))completeHandler;

+ (void)getEtagWithUrl:(NSString *)url
       completeHandler:(void (^)(NSString *Etag, NSError *error))completeHandler;

+ (void)getEtagWithSession:(NSURLSession *)session
                       url:(NSString *)url
           completeHandler:(void (^)(NSString *Etag, NSError *error))completeHandler;

+ (NSURLSession *)sharedSession;

@end

NS_ASSUME_NONNULL_END
