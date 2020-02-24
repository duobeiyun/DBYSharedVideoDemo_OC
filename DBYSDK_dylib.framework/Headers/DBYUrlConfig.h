//
//  DBYUrlConfig.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/5/8.
//  Copyright © 2019 duobei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DBYEnumerates.h"

NS_ASSUME_NONNULL_BEGIN

@interface DBYUrlConfig : NSObject

@property (assign, nonatomic) DBYDomainType dbyDomain;
@property (copy, nonatomic, readonly) NSString *domainString;
@property (copy, nonatomic, readonly) NSString *domainTail;

+ (instancetype)sharedConfig;

- (NSString *)authinfoUrl;

- (NSString *)authinfoUrlV4;

- (NSString *)authinfoUrlWithRoomID:(NSString *)roomID
                           userName:(NSString *)userName
                             userID:(NSString *)userID
                           userRole:(int)userRole
                          partnerID:(NSString *)partnerID
                             appkey:(NSString *)appkey;

- (NSString *)authinfoUrlWithInviteCode:(NSString *)inviteCode
                                nickame:(NSString *)nickame;

- (NSString *)datUrlWithRoomID:(NSString *)roomID;

- (NSString *)pptUrlWithPPTID:(NSString*)pptID
                    pageIndex:(NSInteger)pageIndex;

- (NSString *)staticUrlWithSourceName:(NSString *)name;

- (NSString *)roomConfigUrlWithRoomID:(NSString *)roomID;

- (NSString *)playbackUrl;

- (NSString *)statusLogUrl;

- (NSString *)iosLogUrl;

- (NSString *)dataCenterUrl;

- (NSString *)staticUrl;
@end

NS_ASSUME_NONNULL_END
