//
//  DBYLessonItem.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/8/13.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DBYLessonItem : NSObject

@property (nonatomic, copy) NSString *roomId;
@property (nonatomic, copy) NSString *secret;
@property (nonatomic, copy) NSString *partnerId;
@property (nonatomic, copy) NSString *appkey;

@property (nonatomic, copy) NSString *iconName;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *time;
@property (nonatomic, copy) NSString *size;

@property (nonatomic, assign) BOOL hasVideo;

- (instancetype)initWithDictionary:(NSDictionary *)dict;

@end

NS_ASSUME_NONNULL_END
