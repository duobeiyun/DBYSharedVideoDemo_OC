//
//  DBYInteractionModel.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2020/5/22.
//

#import <Foundation/Foundation.h>
#import "DBYEnumerates.h"

NS_ASSUME_NONNULL_BEGIN

@interface DBYInteractionModel : NSObject

@property(nonatomic, copy)NSString *userId;
@property(nonatomic, copy)NSString *userName;
@property(nonatomic, copy)NSString *fromUserId;
@property(nonatomic, copy)NSString *fromUserName;
@property(nonatomic, assign)int userRole;
@property(nonatomic, assign)int fromUserRole;
@property(nonatomic, assign)DBYInteractionState state;

- (instancetype)initWithDictionary:(NSDictionary *)dict;
@end

NS_ASSUME_NONNULL_END
