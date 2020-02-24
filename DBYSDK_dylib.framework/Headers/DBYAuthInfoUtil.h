//
//  DBYAuthInfoUtil.h
//  DBYSDK_dylib
//
//  Created by Michael on 2018/5/8.
//  Copyright © 2018年 duobei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DBYAuthInfo.h"

typedef enum : NSUInteger {
    DBYAuthInfoStatusError = 0, //没有获取到status
    DBYAuthInfoStatusLessonNotBegain = 1, //课程未开始
    DBYAuthInfoStatusLessonNotOver, //课程未结束
    DBYAuthInfoStatusCanWatchPlayback, //可以看回放
    DBYAuthInfoStatusNoOneLive, //空录像
    DBYAuthInfoStatusConversionFailed, //转换失败
    DBYAuthInfoStatusConversioning, //转换中
} DBYAuthInfoStatus;

typedef void (^DBYAuthInfoBlock)(DBYAuthInfo *authinfo);
typedef void (^DBYAuthInfoResponseBlock)(NSString *authRoomID, NSString *jsonStr, DBYAuthInfoStatus status);

@interface DBYAuthInfoUtil : NSObject

+ (void)postAuthInfoWithUrl:(NSString *)url
             successHandler:(void (^)(NSDictionary<NSString *, id> *dict))successHandler
                failHandler:(void (^)(NSError *error))failHandler;

+ (void)getAuthInfoWithUrl:(NSString *)url
            successHandler:(DBYAuthInfoResponseBlock)successHandler
               failHandler:(void (^)(NSError *error))failHandler;

+ (void)getAuthInfoWithInviteCode:(NSString *)code nickName:(NSString *)nickName successHandler:(DBYAuthInfoResponseBlock)successHandler failHandler:(void (^)(NSError *error))failHandler;

+ (void)getAuthInfoWithRoomID:(NSString *)roomID
                          uid:(NSString *)uid
                     userName:(NSString *)userName
                     userRole:(int)userRole
                    partnerId:(NSString *)partnerId
                       appkey:(NSString *)appkey
                        isDev:(BOOL)isDev
               successHandler:(DBYAuthInfoResponseBlock)successHandler
                  failHandler:(void (^)(NSError *error))failHandler;

+ (void)downloadPlaybackDatWithRoomID:(NSString *)roomID
                              baseUrl:(NSString *)baseUrl
                       successHandler:(void (^)(NSString *datPath))successHandler
                          failHandler:(void (^)(NSError *error))failHandler;

+ (void)authInfoWithUrl:(NSString *)url
         successHandler:(DBYAuthInfoBlock)successHandler
            failHandler:(void (^)(NSError *error))failHandler;

+ (void)authInfoWithInviteCode:(NSString *)code
                      nickName:(NSString *)nickName
                successHandler:(DBYAuthInfoBlock)successHandler
                   failHandler:(void (^)(NSError *error))failHandler;

+ (void)authInfoWithRoomID:(NSString *)roomID uid:(NSString *)uid
                  userName:(NSString *)userName
                  userRole:(int)userRole
                 partnerId:(NSString *)partnerId
                    appkey:(NSString *)appkey
                     isDev:(BOOL)isDev
            successHandler:(DBYAuthInfoBlock)successHandler
               failHandler:(void (^)(NSError *error))failHandler;

@end
