//
//  DBYString.m
//  DBYSharedVideoDemo
//
//  Created by 钟凡 on 2020/2/25.
//  Copyright © 2020 duobei. All rights reserved.
//

#import "DBYString.h"

@implementation DBYString

+ (NSString *)retry {
    return @"请稍后重试";
}
+ (NSString *)noInviteCode {
    return @"请输入邀请码";
}
+ (NSString *)noNickname {
    return @"请输入昵称";
}
+ (NSString *)loadding {
    return @"正在登录...";
}
+ (NSString *)notSuport1v1Error {
    return @"该版本不支持1v1教室";
}
+ (NSString *)authInfoError {
    return @"获取authinfo失败";
}
+ (NSString *)inviteCodeError {
    return @"邀请码无效";
}
+ (NSString *)urlError {
    return @"url无效";
}
+ (NSString *)classOver {
    return @"课程已结束";
}
+ (NSString *)handsup {
    return @"你已提交语音申请";
}
+ (NSString *)noAnnouncement {
    return @"暂无公告";
}
+ (NSString *)canSpeak {
    return @"可以发言了";
}
+ (NSString *)speakInterupt {
    return @"发言被中断";
}
+ (NSString *)teacherOnline {
    return @"讲师上线啦";
}
+ (NSString *)teacherOffline {
    return @"讲师离开了教室";
}
+ (NSString *)nicknameError {
    return @"昵称不能包含空格";
}
+ (NSString *)courseTypeError {
    return @"课程类型错误";
}
+ (NSString *)netWorkError {
    return @"网络连接异常";
}
+ (NSString *)serverError {
    return @"服务器异常";
}
+ (NSString *)localError {
    return @"其他错误";
}
+ (NSString *)authInfoParseError {
    return @"解析authinfo失败\n请换个网络或者稍后重试";
}
+ (NSString *)roleError {
    return @"移动端只支持学生进教室";
}
+ (NSString *)classTypeError {
    return @"只支持新版大班进教室";
}

@end
