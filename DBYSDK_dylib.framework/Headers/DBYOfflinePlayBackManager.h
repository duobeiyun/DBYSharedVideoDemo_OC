//
//  DBYOfflinePlayBackManager.h
//  DBYSDK_dylib
//
//  Created by duobei on 16/12/12.
//  Copyright © 2016年 duobei. All rights reserved.
//  离线回放(m4a)管理器

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define CHAT_ARRAY_MAX_COUNT 30 //最多显示聊天数

typedef enum : NSUInteger {
    DBYOfflinePlayBackManagerPrepareErrorTypeNoError = 0,         //没错误
    DBYOfflinePlayBackManagerPrepareErrorTypeNoRoomID,            //没设置roomID
    DBYOfflinePlayBackManagerPrepareErrorTypeClassDirNotFound,    //找不到课程文件夹
    DBYOfflinePlayBackManagerPrepareErrorTypeClassConfigNotFound, //找不到课程config.json
    DBYOfflinePlayBackManagerPrepareErrorTypeKeyWrong             //key错误
} DBYOfflinePlayBackManagerPrepareErrorType;

@class DBYChatEventInfo;

@protocol DBYOfflinePlayBackManagerDelegate;


@interface DBYOfflinePlayBackManager : NSObject

#pragma mark - properties

@property (nonatomic, weak) id<DBYOfflinePlayBackManagerDelegate> delegate;
///播放的课程的roomID
@property (nonatomic, copy) NSString *roomID;
///播放课程的路径 设置路径优先以路径播放
@property (nonatomic, copy) NSString *classFilePath;
///解密秘钥
@property (nonatomic, copy) NSString *offlineKey;
///是否正在播放
@property (nonatomic, assign) BOOL isPlaying;
///是否显示用户id水印 默认不显示
@property (nonatomic, assign) BOOL showPrintContent;
///需要显示的水印内容
@property (nonatomic, copy) NSString *printContent;
///水印位置变换时间间隔
@property (nonatomic, assign) NSTimeInterval positionChangeTime;
///所有人聊天信息数组
@property (nonatomic, strong) NSMutableArray<DBYChatEventInfo *> *chatInfoArray;
///老师聊天信息数组
@property (nonatomic, strong) NSMutableArray<DBYChatEventInfo *> *teacherChatInfoArray;
///当前播放时间
@property (nonatomic, assign) NSTimeInterval currentPlayTime;

#pragma mark - functions

- (instancetype)initWithOfflineKey:(NSString *)key;

/**
 获取课程时长
 */
- (NSTimeInterval)lessonLength;

/**
 获取ppt页数
 */
- (NSInteger)pptSlideCount;

/**
 *  设置ppt显示View ppt的大小和slideView一致
 *  @param slideView 显示ppt的View
 */
- (void)setupSlideViewWith:(UIView *)slideView;

/**
 设置老师视频显示view
 @param teacherView 显示老师视频的view
 */
- (void)setTeacherViewWith:(UIView *)teacherView;

/**
 设置学生视频显示view
 @param studentView 显示学生视频的view
 */
- (void)setStudentViewWith:(UIView *)studentView;

///设置新版大班视频显示区域
- (void)setSharedVideoView:(UIView *)videoView;

/// 设置无ppt时的背景图片
/// @param image 显示图片
- (void)setPPTViewBackgroundImage:(UIImage *)image;

/**
 准备播放
 @param completeHandler 准备完成回调
 */
- (void)prepareForPlayWithCompleteHandler:(void (^)(NSString *errorMsg, DBYOfflinePlayBackManagerPrepareErrorType error))completeHandler
DEPRECATED_MSG_ATTRIBUTE("这个接口将要废弃，建议使用startPlaybackWithRoomID:filePath:completeHandler:代替");

/// 开始播放
/// @param roomId 课程id
/// @param filePath 课程下载保存的路径
/// @param completeHandler 播放状态回调 code 为 0，表示播放成功
- (void)startPlaybackWithRoomID:(NSString *)roomId
                       filePath:(NSString *)filePath
                completeHandler:(void (^)( int code, NSString *message))completeHandler;

#pragma mark - play control

/**
 设置播放速率 （0.5-2.0）0.5为一般速度 默认为1
 @param rate 播放速度
 */
- (void)setPlayRate:(float)rate;

/**
 *  重新开始播放
 */
- (void)play;

/**
 *  停止播放
 */
- (void)stop;

/**
 *  暂停播放
 */
- (void)pause;

/**
 *  恢复播放
 */
- (void)resume;

/**
 *  到指定进度播放
 *
 *  @param progress 进度 0.0 - 1.0
 */
- (void)seekToProgress:(float)progress;

/**
 *  到指定播放时间
 *
 *  @param time 播放时间 （秒）
 */
- (void)seekToTime:(NSTimeInterval)time;

@end


@protocol DBYOfflinePlayBackManagerDelegate <NSObject>

@optional

/**
 添加显示课件View到设置的pptView上时调用，方便对设置的pptView的子View做一些处理。
 @param view 设置的pptView
 */
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager hasAddPPTView:(UIView *)view;

/**
 播放状态改变时调用
 @param isPlaying 正在播放
 */
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager playStateIsPlaying:(BOOL)isPlaying;

/**
 *  正在播放中会调用
 *  @param progress 播放进度
 *  @param time     播放时间点
 */
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager isPlayingAtProgress:(float)progress time:(NSTimeInterval)time;

/**
 聊天信息数组更新时调用
 @param chatInfoArray 包含聊天信息的数组
 */
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager chatInfoArray:(NSArray *)chatInfoArray;

/**
 更新老师聊天

 @param chatInfoArray 老师助教聊天消息数组
 */
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager teacherChatInfoArray:(NSArray *)chatInfoArray;

/**
 有聊天时调用 返回当前时间的消息数组
 可以在上层viewcontroller用一个数组存起来作为聊天列表的数据源，自己管理。
 @param newChatDictArray 收到的最新消息的数组
 */
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager hasNewChatMessageWithChatArray:(NSArray *)newChatDictArray;

/**
 聊天数组需要清空时调用
 如果使用自己维护的数组来管理聊天，则需要在这个方法中清空相应数组，避免后续回调聊天数据导致聊天重复
 */
- (void)offlinePlayBackManagerChatMessageShouldClear:(DBYOfflinePlayBackManager *)manager;

/**
 有聊天时调用 返回当前时间的老师助教消息数组
 可以在上层viewcontroller用一个数组存起来作为聊天列表的数据源，自己管理。
 @param newTeacherChatDictArray 收到的最新消息的数组
 */
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager hasTeacherNewChatMessageWithChatArray:(NSArray *)newTeacherChatDictArray;

/**
 老师聊天数组需要清空时调用
 如果使用自己维护的数组来管理聊天，则需要在这个方法中清空相应数组，避免后续回调聊天数据导致聊天重复
 */
- (void)offlinePlayBackManagerTeacherChatMessageShouldClear:(DBYOfflinePlayBackManager *)manager;

/**
 ppt改变时调用
 
 @param currentPPTPageCount 当前页数
 @param pptSlideCount       总页数
 */
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager pptHasChangedWithCurrentPPTPageCount:(NSInteger)currentPPTPageCount pptSlideCount:(NSInteger)pptSlideCount;

/**
 *  播放完调用
 *
 */
- (void)offlinePlayBackManagerFinishedPlay:(DBYOfflinePlayBackManager *)manager;

/**
 视频上下线通知
 @param manager offlinePlayBackManager
 @param hasVideo 是否有视频
 @param view 视频相关的view
 */
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager hasVideo:(BOOL)hasVideo inView:(UIView *)view;
#pragma mark - 新版大班
- (void)offlinePlayBackManager:(DBYOfflinePlayBackManager *)manager thumbupWithCount:(NSInteger)count;

@end
