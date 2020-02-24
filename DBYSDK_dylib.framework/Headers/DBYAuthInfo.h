//
//  DBYAuthInfo.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/7/12.
//  Copyright © 2019 duobei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DBYEnumerates.h"

@interface DBYAuthInfo : NSObject

@property (copy, nonatomic) NSString *roomID;
@property (copy, nonatomic) NSString *userId;
@property (copy, nonatomic) NSString *nickName;
@property (copy, nonatomic) NSString *apiUserId;
@property (copy, nonatomic) NSString *uniqueUserId;
@property (copy, nonatomic) NSString *teacherId;
@property (copy, nonatomic) NSString *courseTitle;
@property (copy, nonatomic) NSString *courseTimeRange;
@property (copy, nonatomic) NSString *authinfoString;
@property (copy, nonatomic) NSString *merchant;

///1:老师 2:学生 3:管理员 4:助教 6:家长
@property (assign, nonatomic) int userRole;

@property (assign, nonatomic) NSTimeInterval courseStartTime;
@property (assign, nonatomic) NSTimeInterval courseEndTime;

@property (assign, nonatomic) DBYCourseType courseType;
@property (assign, nonatomic) DBYCourseStatus courseStatus;
@property (assign, nonatomic) DBYClassType classType;


- (instancetype)initWithDictionary:(NSDictionary *)dict;

@end
