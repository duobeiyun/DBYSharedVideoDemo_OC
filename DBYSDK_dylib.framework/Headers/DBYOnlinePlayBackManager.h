//
//  DBYOnlinePlayBackManager.h
//  DBYSDK_dylib
//
//  Created by duobei on 17/3/6.
//  Copyright © 2017年 duobei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeNoError = 0,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeParamsError = 1,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeParamsParseError = 2,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeAuthInfoError = 900,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeAuthInfoFail = 901,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeNoPlayBack = 10001,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeLessonNotBegin, //课程未开始
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeLessonNotOver,                  //课程未结束
    DBYOnlinePlayBackManagerStartPlayBackErrorTypePlayBackConversionFail = 10005, //回放转换失败
    DBYOnlinePlayBackManagerStartPlayBackErrorTypePlayBackConversioning = 10006,  //回放转换中
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeJsonError = 1000003,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeHttpError = 1000001,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeLocalPathError = 1000002,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeModeError = 100004,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeAuthError = 100006,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeOpenFileError = 100007,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeFLVFileError = 100008,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeRepeatStart = 100013,               //重复开始
    DBYOnlinePlayBackManagerStartPlayBackErrorTypePlayBackDataOpenFail = 100017,      //回放数据打开失败
    DBYOnlinePlayBackManagerStartPlayBackErrorTypePlayBackDataEmptyContent = 100018,  //回放数据为空
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeHttpFileGetSizeError = 100019,      //获取文件大小错误
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeHttpFileDownloadError = 100020,     //文件下载错误
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeHttpFileDownloadSizeError = 100021, //下载文件大小错误
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeDownloadDatError = 300000,
    DBYOnlinePlayBackManagerStartPlayBackErrorTypeParamHasNil,
} DBYOnlinePlayBackManagerStartPlayBackErrorType;

typedef enum : NSUInteger {
    DBYOnlinePlayBackManagerClassRoomType1V1 = 1,
    DBYOnlinePlayBackManagerClassRoomType1VN = 2,
} DBYOnlinePlayBackManagerClassRoomType;

typedef void (^OnlineStartPlayBlock)(NSString *message, DBYOnlinePlayBackManagerStartPlayBackErrorType type);

@protocol DBYOnlinePlayBackManagerDelegate;

@class DBYAuthInfo;


@interface DBYOnlinePlayBackManager : NSObject

//记录播放速度
@property (nonatomic, assign) float playSpeed;
//是否显示用户id水印 默认不显示
@property (nonatomic, assign) BOOL showPrintContent;
//需要显示的水印内容
@property (nonatomic, copy) NSString *printContent;
//水印位置变换时间间隔
@property (nonatomic, assign) NSTimeInterval positionChangeTime;
@property (nonatomic, assign) DBYOnlinePlayBackManagerClassRoomType classRoomType;
@property (nonatomic, weak) id<DBYOnlinePlayBackManagerDelegate> delegate;
//是否在播放
@property (nonatomic, assign, readonly) BOOL isPlaying;
@property (nonatomic, assign, readonly) BOOL isRendering DEPRECATED_MSG_ATTRIBUTE("已经废弃，下个版本移除");
@property (nonatomic, assign, readonly) BOOL hasPause DEPRECATED_MSG_ATTRIBUTE("这个属性将要废弃，建议使用isPlaying");
//聊天数组
@property (nonatomic, strong) NSMutableArray<NSDictionary *> *chatDictArray DEPRECATED_MSG_ATTRIBUTE("下个版本将移除");
@property (nonatomic, strong) NSMutableArray<NSDictionary *> *teacherChatDictArray DEPRECATED_MSG_ATTRIBUTE("下个版本将移除");
//总时间（秒）
@property (nonatomic, assign) NSTimeInterval totalTime;
@property (nonatomic, assign) NSTimeInterval lessonStartTime;
@property (nonatomic, assign) NSTimeInterval lessonEndTime;
@property (nonatomic, assign) NSTimeInterval currentTime;

@property (nonatomic, assign) BOOL isDev;

///使用参数进教室时，需传入appkey和partnerID
- (instancetype)initWithPartnerID:(NSString *)partnerID appKey:(NSString *)appKey;

///使用链接进教室时 可以直接调用init
- (instancetype)init;

/**
 根据roomID等参数进教室

 @param roomId roomId
 @param uid 用户id
 @param userName 用户昵称
 @param userRole 用户角色
 @param seekTime 开始时间
 @param completeHandler 完成回调
 */
- (void)startPlaybackWithRoomID:(NSString *)roomId
                            uid:(NSString *)uid
                       userName:(NSString *)userName
                       userRole:(int)userRole
                       seekTime:(NSTimeInterval)seekTime
                completeHandler:(OnlineStartPlayBlock)completeHandler;

/**
 通过url进教室
 
 @param url 请求authinfo拼接的url
 @param roomId 目前需要传roomId
 @param seekTime 开始时间
 @param completeHandler 完成回调
 */
- (void)startPlaybackWithUrl:(NSString *)url
                  withRoomId:(NSString *)roomId
                    seekTime:(NSTimeInterval)seekTime
             completeHandler:(OnlineStartPlayBlock)completeHandler;

/**
 邀请码看回放

 @param code 邀请码
 @param nickName 昵称
 @param seekTime 跳转时间
 @param completeHandler 完成回调
 */
- (void)startPlaybackWithInviteCode:(NSString *)code
                           nickName:(NSString *)nickName
                           seekTime:(NSTimeInterval)seekTime
                    completeHandler:(OnlineStartPlayBlock)completeHandler;

/**
 根据获取的authinfo进教室
 
 @param authinfo authinfo
 @param completeHandler 完成回调
 */
- (void)startPlaybackWithAuthInfo:(DBYAuthInfo *)authinfo
                         seekTime:(NSTimeInterval)seekTime
                  completeHandler:(OnlineStartPlayBlock)completeHandler;

/**
 根据获取的authinfo字符串进教室
 
 @param authInfoStr authinfo字符串
 @param completeHandler 完成回调
 */
- (void)startPlaybackWithAuthInfoStr:(NSString *)authInfoStr
                            seekTime:(NSTimeInterval)seekTime
                     completeHandler:(OnlineStartPlayBlock)completeHandler
DEPRECATED_MSG_ATTRIBUTE("这个接口将要废弃，建议使用startPlaybackWithAuthInfo:seekTime:completeHandler:代替");

/**
 根据获取的authinfo字符串进教室
 
 @param authInfoStr authinfo字符串
 @param roomId roomId
 @param completeHandler 完成回调
 */
- (void)startPlaybackWithAuthInfoStr:(NSString *)authInfoStr withRoomId:(NSString *)roomId
                            seekTime:(NSTimeInterval)seekTime
                     completeHandler:(OnlineStartPlayBlock)completeHandler
DEPRECATED_MSG_ATTRIBUTE("这个接口将要废弃，建议使用startPlaybackWithAuthInfo:seekTime:completeHandler:代替");

/**
 退出教室
 @param completeHandler
 success: code = 0, message = nil
 failed: code != 0, message != nil
 */
- (void)stopPlayWithCompleteHandler:(void (^)(int code, NSString *message))completeHandler;

/**
 切换回放线路

 @param index 线路序号，从0开始
 @param completeHandler 完成回调，errorMsg为nil则切换成功
 */
- (void)changePlaybackLineWithIndex:(int)index completeHandler:(void (^)(NSString *errorMsg))completeHandler;

//当前线路序号
- (int)currentLineIndex;
//线路总数
- (NSInteger)linesCount;

- (void)setDrawLineWidthWith:(CGFloat)lineWidth;
- (void)setPPTViewWithView:(UIView *)pptView;
- (void)setStudentViewWith:(UIView *)studentView;
- (void)setTeacherViewWith:(UIView *)teacherView;
///设置新版大班视频显示区域
- (void)setSharedVideoView:(UIView *)videoView;
//设置无ppt时的背景图片
- (void)setPPTViewBackgroundImage:(UIImage *)image;

//发送状态到动态课件webview
- (void)sendStatusToWebViewWithEventType:(NSString *)eventType data:(NSString *)jsonStr;

#pragma mark - play methods
- (void)seekToTimeWith:(NSTimeInterval)time completeHandler:(void (^)(NSString *errorMsg))completeHandler;

//暂停播放
- (void)pausePlay;
//恢复播放
- (void)resumePlay;
//暂停api
- (void)pauseApi;
//恢复api
- (void)resumeApi;

//设置播放速度 返回是否设置成功 （0.5-3.0）
- (void)setPlaySpeedWith:(float)speed CompleteHandler:(void (^)(BOOL result))completeHandler;

@end


@protocol DBYOnlinePlayBackManagerDelegate <NSObject>

@optional

/**
 添加显示课件View到设置的pptView上时调用，方便对设置的pptView的子View做一些处理。
 @param view 设置的pptView
 */
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager hasAddPPTView:(UIView *)view;
#pragma mark - 视频相关
/**
 开始视频或结束视频时调用
 
 @param hasVideo 是否有视频
 @param view     在哪个View上
 */
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager hasVideo:(BOOL)hasVideo inView:(UIView *)view;
#pragma mark - seek
/**
 seek失败回调
 @param code 失败类型
 */
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager seekFailWithCode:(int)code;
#pragma mark - play
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager playStateChange:(BOOL)isPlaying;
/**
 播放完调用
 */
- (void)playbackManagerDidPlayEnd:(DBYOnlinePlayBackManager *)manager;

//返回播放时间
- (void)playBackManager:(DBYOnlinePlayBackManager *)manager playedAtTime:(NSTimeInterval)time;
//开始播放时调用 总时长
- (void)playBackManager:(DBYOnlinePlayBackManager *)manager totalTime:(NSTimeInterval)time;
//重复登录时调用 （提示被踢）
- (void)playBackManagerDidDuplicateLogin:(DBYOnlinePlayBackManager *)manager;
#pragma mark - 聊天相关
/**
 有聊天时调用 返回收到的消息
 这个数组是sdk自己维护的数组，最多有30条，超过30条会将之前的聊天移除
 @param chatDictArray 收到的消息的数组
 */
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager hasChatMessageWithChatArray:(NSArray *)chatDictArray
DEPRECATED_MSG_ATTRIBUTE("下个版本将移除");
/**
 有聊天时调用 返回当前时间的消息数组
 可以在上层viewcontroller用一个数组存起来作为聊天列表的数据源，自己管理。
 @param newChatDictArray 收到的最新消息的数组
 */
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager hasNewChatMessageWithChatArray:(NSArray *)newChatDictArray;
/**
 聊天数组需要清空时调用
 如果使用自己维护的数组来管理聊天，则需要在这个方法中清空相应数组，避免后续回调聊天数据导致聊天重复
 */
- (void)playBackManagerChatMessageShouldClear:(DBYOnlinePlayBackManager *)manager;
/**
 有聊天时调用 返回收到老师助教的消息
 这个数组是sdk自己维护的数组，最多有30条，超过30条会将之前的聊天移除
 @param teacherChatDictArray 收到的老师助教消息的数组
 */
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager hasTeacherChatMessageWithChatArray:(NSArray *)teacherChatDictArray
DEPRECATED_MSG_ATTRIBUTE("下个版本将移除");

/**
 有聊天时调用 返回当前时间的老师助教消息数组
 可以在上层viewcontroller用一个数组存起来作为聊天列表的数据源，自己管理。
 @param newTeacherChatDictArray 收到的最新消息的数组
 */
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager hasTeacherNewChatMessageWithChatArray:(NSArray *)newTeacherChatDictArray;
/**
 老师聊天数组需要清空时调用
 如果使用自己维护的数组来管理聊天，则需要在这个方法中清空相应数组，避免后续回调聊天数据导致聊天重复
 */
- (void)playBackManagerTeacherChatMessageShouldClear:(DBYOnlinePlayBackManager *)manager;

#pragma mark - 新版大班
- (void)playBackManager:(DBYOnlinePlayBackManager *)manager thumbupWithCount:(NSInteger)count;
- (void)playBackManager:(DBYOnlinePlayBackManager *)manager onlineWithuserId:(NSString*)uid nickName:(NSString*)nickName userRole:(int)role;

#pragma mark - ppt
//加载ppt失败时调用
- (void)playbackManagerDidFailLoadPPT:(DBYOnlinePlayBackManager *)manager;
#pragma mark - status
//在加载中调用，应该给出UI提示
- (void)playbackManagerIsLoading:(DBYOnlinePlayBackManager *)manager;
//加载失败时调用，应该移除当前loading提示，给出错误提示。
- (void)playbackManagerLoadFailed:(DBYOnlinePlayBackManager *)manager;
//加载完成，移除提示
- (void)playbackManagerFinishedLoading:(DBYOnlinePlayBackManager *)manager;
//回放音频会话被打断（短信、来电、闹钟等） 会进入暂停状态
- (void)playbackManagerPausedByAudioInterruption:(DBYOnlinePlayBackManager *)manager;
//回放音频会话恢复 会继续播放
- (void)playbackManagerResumedAfterAudioInterruption:(DBYOnlinePlayBackManager *)manager;
#pragma mark - 底层自动seek
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager shouldSeekTo:(NSTimeInterval)time;

@end
