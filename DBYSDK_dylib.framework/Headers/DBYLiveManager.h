//
//  DBYLiveManager.h
//  DBYSDK_dylib
//
//  Created by duobei on 16/11/2.
//  Copyright © 2016年 duobei. All rights reserved.
//  使用c++内核的直播管理类

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import "DBYStreamType.h"
#import "DBYEnumerates.h"
#import "DBYInteractionModel.h"

typedef void (^LiveStartPlayBlock)(NSString *message, DBYLiveManagerEnterRoomErrorType type);

@protocol DBYLiveManagerDelegate;
@class DBYVideoRecorder;

@interface DBYLiveManager : NSObject

#pragma mark - properties

///是否允许学生画线 只对1v1学生有效 1v1学生默认打开画线，不需画线时请设置此值为NO
@property (nonatomic, assign) BOOL allowDrawLine;
///是否显示用户id水印 默认不显示
@property (nonatomic, assign) BOOL showPrintContent;
///需要显示的水印内容
@property (nonatomic, copy) NSString *printContent;
///水印位置变换时间间隔
@property (nonatomic, assign) NSTimeInterval positionChangeTime;
///代理
@property (nonatomic, weak) id<DBYLiveManagerDelegate> delegate;
///助教的id，如果有助教上线
@property (nonatomic, copy) NSString *assitantId;

#pragma mark - life cycle

///使用参数进教室时，需传入appkey和partnerID
- (instancetype)initWithPartnerId:(NSString *)partnerId
                       withAppKey:(NSString *)appKey;

///使用链接进教室时 可以直接调用init
- (instancetype)init;

/**
 进入教室
 
 @param roomID 教室id
 @param uid 用户id
 @param nickName 用户昵称
 @param userRole 用户身份 老师、学生、助教等
 @param completeHandler 完成回调
 */
- (void)enterRoomWithRoomID:(NSString *)roomID
                        uid:(NSString *)uid
                   nickName:(NSString *)nickName
                   userRole:(DBYLiveManagerUserRoleType)userRole
            completeHandler:(LiveStartPlayBlock)completeHandler;

/**
 获取完authinfo后，转成json的字符串，然后进教室
 
 @param authJson authinfo的json的字符串
 @param completeHandler 完成回调
 */
- (void)enterRoomWithAuthJson:(NSString *)authJson
              completeHandler:(LiveStartPlayBlock)completeHandler;

/**
 通过url进教室
 
 @param url 请求authinfo拼接的url
 @param completeHandler 完成回调
 */
- (void)enterRoomWithUrl:(NSString *)url
         completeHandler:(LiveStartPlayBlock)completeHandler;

/**
 邀请码进教室
 
 @param inviteCode 邀请码
 @param nickName 用户昵称
 @param completeHandler 完成回调
 */
- (void)enterRoomWithInviteCodeWith:(NSString *)inviteCode
                           nickName:(NSString *)nickName
                    completeHandler:(LiveStartPlayBlock)completeHandler;

/**
 退出教室
 @param completeHandler
 success: code = 0, failMsg = nil
 failed: code != 0, failMsg != nil
 */
- (void)quitClassRoomWithCompleteHandler:(void (^)(NSString *failMsg, int code))completeHandler;

///暂停(进后台用)
- (void)pauseLive;

///恢复（回到前台）
- (void)recoverLive;

#pragma mark - video config

///设置摄像头方向
- (void)setVideoOrientationWith:(AVCaptureVideoOrientation)orientation;

///切换前后摄像头
- (void)swapFrontAndBackCameras;

///设置音频采样率
- (void)setAudioSampleRate:(int)sampleRate;

///设置学生开启视频时的清晰度等级
- (void)setCaptureVideoLevelWithLevel:(DBYLiveManagerVideoCaptureLevel)level
                      completeHandler:(void (^)(NSString *errorMsg))completeHandler;

///设置采集数据是否做镜像处理
- (void)setCaptureVideoMirrored:(BOOL)videoMirrored;

#pragma mark - setup views

///设置ppt显示区域view
- (void)setPPTViewWithView:(UIView *)pptView;

///设置自己视频显示区域
- (void)setLocalVideoView:(UIView *)localView;

///设置学生视频显示区域
- (void)setStudentViewWith:(UIView *)studentView;

///设置老师视频显示区域（视频课可用）
- (void)setTeacherViewWith:(UIView *)teacherView;

///设置新版大班桌面共享显示区域
- (void)setSharedVideoView:(UIView *)videoView;

///设置新版大班学生视频显示区域
- (void)setStudentView:(UIView *)studentView withUserId:(NSString *)userId;

///设置画线宽度
- (void)setDrawLineWidthWith:(CGFloat)lineWidth;

///设置无ppt时的背景图片
- (void)setPPTViewBackgroundImage:(UIImage *)image;

/**
 设置PPT加载失败的默认图

 @param image the image
 */
- (void)setPPTViewLoadFailedImage:(UIImage *)image;
#pragma mark - 获取用户信息
- (void)getUserInfo:(NSString *)userId compeletion:(void(^)(NSDictionary *userInfo))compeletion;
#pragma mark - 上台、上麦相关方法
///开、关麦克风
///@param isOpen YES打开摄像头 NO关闭
- (void)openMic:(BOOL)isOpen
completeHandler:(void (^)(NSString *failMsg))completeHandler;
/**
 开关摄像头
 学生只能在1v1课程中开启摄像头
 @param isOpen YES打开摄像头 NO关闭
 */
- (void)openCam:(BOOL)isOpen
completeHandler:(void (^)(NSString *failMsg))completeHandler;
/**
 回应老师上台请求
 @param openCamera 是否同意开启摄像头
 @param completeHandler 完成回调 如果errorMsg不为空，则发送失败
 */
- (void)responseTeacherOpenCamRequestWithOpenCamera:(BOOL)openCamera
                                    completeHandler:(void (^)(NSString *errorMsg))completeHandler;

/**
 学生下台请求
 @param completeHandler 完成回调 如果errorMsg不为空，则发送失败
 */
- (void)requestOffTheStageWithCompleteHandler:(void (^)(NSString *errorMsg))completeHandler;
/**
 有视频的时候，可以通过此接口设置是否接收视频
 在网络状况较差的时候，设置不接收视频可以减少网络占用，保证音频质量
 @param isReceiveVideo 是否接收视频
 */
- (void)setReceiveVideoWith:(BOOL)isReceiveVideo
            completeHandler:(void (^)(NSString *failMsg))completeHandler;
#pragma mark - 新版大班互动消息
- (void)getInteractionList:(DBYInteractionType)type completion:(void(^)(NSArray<DBYInteractionModel *> *list))completion;
- (void)requestInteraction:(DBYInteractionType)type state:(DBYInteractionState)state completion:(void(^)(BOOL result))completion;
- (void)acceptInteraction:(DBYInteractionType)type completion:(void(^)(BOOL result))completion;
#pragma mark -
#pragma mark - 消息发送

/**
 发送消息接口

 @param message 消息内容
 @param save 是否保存（回放）
 @param successHandler 成功回调
 @param failHandler 失败回调
 */
- (void)sendMessage:(NSString *)message
               save:(BOOL)save
     successHandler:(void (^)(void))successHandler
        failHandler:(void (^)(NSString *errorMsg))failHandler;

/**
 发送聊天信息
 */
- (void)sendChatMessageWith:(NSString *)message;

/**
 发送消息

 @param message 消息内容
 @param completeHandler 完成回调 如果errorMsg不为空，则发送失败
 */
- (void)sendChatMessageWith:(NSString *)message completeHandler:(void (^)(NSString *errorMsg))completeHandler;

///发送举手发言请求 (仅限1VN)
- (void)requestRaiseHand;

/**
 发送举手发言请求 (仅限1VN)
 @param completeHandler 完成回调 如果errorMsg不为空，则发送失败
 */
- (void)requestRaiseHandWithCompleteHandler:(void (^)(NSString *errorMsg))completeHandler;

///发送投票消息
- (void)sendVoteWithOptionIndex:(NSInteger)index;

- (void)sendVoteWithOptionIndex:(NSInteger)index
                completeHandler:(void (^)(NSString *errorMsg))completeHandler;
- (void)thumbsupWithCount:(int)count completion:(void (^)(NSString *errorMsg))completion;
#pragma mark - utils

///错误代码对应的提示
+ (NSString *)enterRoomErrorMessageWithErrorType:(DBYLiveManagerEnterRoomErrorType)errorType;
#pragma mark - test

- (void)sendPPTDrawCleanWithCompleteHandler:(void (^)(NSString *errorMsg))completeHandler;
- (void)openDefalutPPtWithCompleteHandler:(void (^)(NSString *errorMsg))completeHandler;
- (void)sendSlideChangeWithIndex:(int)index completeHandler:(void (^)(NSString *errorMsg))completeHandler;

@end

#pragma mark - DBYLiveManagerDelegate
@protocol DBYLiveManagerDelegate <NSObject>
#pragma mark - 其他地方需要的回调
/**
 远端将要获取到视频数据
 
 @param liveManager DBYLiveManager singleton instance
 @param uid userid 用来区分不同用户
 */
@optional
- (void)willReceivedVideoData:(DBYLiveManager *)liveManager userId:(NSString *)uid;
/**
 远端获取到视频数据
 
 @param liveManager DBYLiveManager singleton instance
 @param data 视频数据
 @param width 视频数据宽
 @param height 视频数据高
 @param uid userid 用来区分不同用户
 */
- (void)didReceivedVideoData:(DBYLiveManager *)liveManager data:(void *)data widht:(int)width height:(int)height userId:(NSString *)uid;
/**
 远端将要中断视频数据
 
 @param liveManager DBYLiveManager singleton instance
 @param uid userid 用来区分不同用户
 */
@optional
- (void)willInterruptVideoData:(DBYLiveManager *)liveManager userId:(NSString *)uid;
///开启摄像头
- (void)initVideoRecorder:(DBYLiveManager *)liveManager userId:(NSString *)uid;
///采集数据
- (void)didRecordVideoData:(DBYVideoRecorder *)videoRecorder data:(void *)data width:(size_t)width height:(size_t) height;
///关闭摄像头
- (void)destroyVideoRecorder:(DBYLiveManager *)liveManager userId:(NSString *)uid;
///获取到音频数据
- (void)didReceivedAudioData:(DBYLiveManager *)liveManager data:(void *)data length:(unsigned int)length  userId:(NSString *)uid;
///开启麦克风
- (void)initAudioRecorder:(DBYLiveManager *)liveManager userId:(NSString *)uid;
///本地采集到音频数据
- (void)didRecordAudioData:(DBYLiveManager *)liveManager data:(void *)data length:(unsigned int)length  userId:(NSString *)uid;
///关闭麦克风
- (void)destroyAudioRecorder:(DBYLiveManager *)liveManager userId:(NSString *)uid;
///用户被踢出教室
-(void)kickedOff:(DBYLiveManager *)liveManager;
///状态码
-(void)liveManager:(DBYLiveManager *)liveManager didReceivedStatusCode:(int)code;
#pragma mark - flash 大班
@optional
///收到服务器clientOnline消息
-(void)clientOnline:(DBYLiveManager *)liveManager userId:(NSString*)uid nickName:(NSString*)nickName userRole:(int)role;
/**
 课程结束（老师主动触发的结束）
 */
- (void)liveManagerClassOver:(DBYLiveManager *)manager;
/**
 获取到远端视频数据
 @param manager DBYLiveManager singleton instance
 @param view      在哪个View上
 */
- (void)liveManager:(DBYLiveManager *)manager didReceivedVideoDataOfView:(UIView *)view;
/**
 开始视频或结束视频时调用
 @param hasVideo 是否有视频
 @param view     在哪个View上
 */
- (void)liveManager:(DBYLiveManager *)manager hasVideo:(BOOL)hasVideo inView:(UIView *)view;
///回调网络延迟 ms
- (void)liveManager:(DBYLiveManager *)manager netDelay:(int)netDelay;
///回调丢包率
- (void)liveManager:(DBYLiveManager *)manager netPacketLoss:(double)netPacketLoss;
///回调网络质量
- (void)liveManager:(DBYLiveManager *)manager netQuality:(DBYNetworkQuality)quality;
/**
 添加显示课件View到设置的pptView上时调用，方便对设置的pptView的子View做一些处理。
 @param view 设置的pptView
 */
- (void)liveManager:(DBYLiveManager *)manager hasAddPPTView:(UIView *)view;
///有状态改变时调用
- (void)liveManager:(DBYLiveManager *)manager statusChangeWith:(DBYLiveManagerStatusType)statusType;
///老师点击禁止或允许显示在线用户数时调用
- (void)liveManager:(DBYLiveManager *)manager denyOnlineNumber:(BOOL)isDeny;
///用户在线数变化时调用
- (void)liveManager:(DBYLiveManager *)manager onlineUserCountWith:(NSInteger)count;
///老师在线状态改变时调用
- (void)liveManager:(DBYLiveManager *)manager teacherStatusChangedWithOnline:(BOOL)online name:(NSString *)name;
///有教室公告时调用
- (void)liveManager:(DBYLiveManager *)manager hasAnnounceContent:(NSString *)announceContent;
///全体禁言或解禁时调用 YES为禁言
- (void)liveManager:(DBYLiveManager *)manager denyChatStatusChange:(BOOL)isDeny;
///自己是否可以发言 NO为不能
- (void)liveManager:(DBYLiveManager *)manager canChat:(BOOL)canChat;
///教师端切换视频和ppt区域位置时调用 0为ppt为主，视频右上角，1为视频为主
- (void)liveManager:(DBYLiveManager *)manager videoPositionChangeWithPosition:(int)position;
///聊天频次过高时调用
- (void)liveManagerChatTooFastWith:(DBYLiveManager *)manager;
///被踢下线时调用
- (void)liveManagerDidKickedOff:(DBYLiveManager *)manager;
///选择服务器ip后调用
- (void)liveManager:(DBYLiveManager *)manager didChooseIpAddress:(NSString *)ipAddress;
///authInfo成功后调用
- (void)liveManagerDidAuthInfoSuccess:(DBYLiveManager *)manager;
///开启摄像头失败后调用
- (void)liveManagerOpenCameraFail:(DBYLiveManager *)manager;
///重连媒体服务器时调用
- (void)liveManagerDidReconnectMediaServer:(DBYLiveManager *)manager;
///连接媒体服务器失败时调用
- (void)liveManagerConnectMediaServerFail:(DBYLiveManager *)manager;
///获得教室信息后，第一次连接消息服务器成功时调用
- (void)liveManagerFirstConnectSucess:(DBYLiveManager *)manager;
///获得教室信息后，第一次连接消息服务器失败时调用
- (void)liveManagerFirstConnectError:(DBYLiveManager *)manager;
///网络差时调用
- (void)liveManagerHasNetErrorWith:(DBYLiveManager *)manager;
///网络恢复时调用
- (void)liveManagerNetOKWith:(DBYLiveManager *)manager;
/**
 定时返回音频流上下行等信息
 @param status audioUp 音频上行速度 audioDown 音频下行速度 单位KB/s 等于-1时表示无速度
 */
- (void)liveManager:(DBYLiveManager *)manager hasAudioStreamStatus:(NSDictionary *)status;
/**
 定时返回视频流上下行等信息
 @param status videoUp 视频上行速度 videoDown 视频下行速度 单位KB/s 等于-1时表示无速度 fps 每秒帧数
 */
- (void)liveManager:(DBYLiveManager *)manager hasVideoStreamStatus:(NSDictionary *)status;
/**
 老师点击清空举手列表时调用
 */
- (void)liveManagerTeacherDownHands:(DBYLiveManager *)manager;
/**
 老师禁止举手时调用
 
 @param isDeny 是否禁止
 */
- (void)liveManager:(DBYLiveManager *)manager denyRaiseHand:(BOOL)isDeny;
/**
 举手失败时调用
 */
- (void)liveManagerRaiseHandFail:(DBYLiveManager *)manager;
#pragma mark - 聊天相关
/**
 有聊天时调用 返回收到的最新的消息
 可以在上层viewcontroller用一个数组存起来作为聊天列表的数据源，自己管理。
 @param newChatDictArray 收到的最新消息的数组
 */
- (void)liveManager:(DBYLiveManager *)manager hasNewChatMessageWithChatArray:(NSArray *)newChatDictArray;
/**
 聊天数组需要清空时调用
 如果使用自己维护的数组来管理聊天，则需要在这个方法中清空相应数组，避免后续回调聊天数据导致聊天重复
 */
- (void)liveManagerChatMessageShouldClear:(DBYLiveManager *)manager;
/**
 有聊天时调用 返回收到的最新的老师助教消息
 可以在上层viewcontroller用一个数组存起来作为聊天列表的数据源，自己管理。
 @param newChatDictArray 收到的最新消息的数组
 */
- (void)liveManager:(DBYLiveManager *)manager teacherHasNewChatMessageWithChatArray:(NSArray *)newChatDictArray;
/**
 老师聊天数组需要清空时调用
 如果使用自己维护的数组来管理聊天，则需要在这个方法中清空相应数组，避免后续回调聊天数据导致聊天重复
 */
- (void)liveManagerTeacherChatMessageShouldClear:(DBYLiveManager *)manager;
///发送聊天失败时调用
- (void)liveManagerSendChatFail:(DBYLiveManager *)manager;
///发送聊天超出限制长度时调用
- (void)liveManagerSendChatMessageTooLong:(DBYLiveManager *)manager;
#pragma mark - ppt加载相关方法
///打开ppt或切换ppt时调用,回调总页数
- (void)liveManager:(DBYLiveManager *)manager pptOpenWithSlideCount:(int)slideCount;
///加载ppt失败时调用
- (void)liveManagerDidFailLoadPPT:(DBYLiveManager *)manager;
///ppt翻页时调用，回调页数
- (void)liveManager:(DBYLiveManager *)manager pptChangeAtPageIndex:(int)pageIndex;
#pragma mark - 新版大班
- (void)liveManager:(DBYLiveManager *)manager receivedQuestion:(NSDictionary *)dict;
- (void)liveManager:(DBYLiveManager *)manager removedQuestion:(NSString *)questionId;

/**
 教师给麦或收麦时调用
 
 @param canSpeak YES 表示教师给麦 ；NO 表示教师收麦
 */
- (void)liveManager:(DBYLiveManager *)manager studentCanSpeak:(BOOL)canSpeak;

/**
 老师给/收 其他学生麦时调用
 
 @param userInfo 学生信息 
 @param canSpeak YES 给麦 / NO 收麦
 */
- (void)liveManager:(DBYLiveManager *)manager teacherGiveMicToStudentWithUserInfo:(NSDictionary *)userInfo canSpeak:(BOOL)canSpeak;
/**
 老师请求学生开启摄像头（仅限1vN）
 */
- (void)liveManagerTeacherAskStudentOpenCamera:(DBYLiveManager *)manager;
///点赞
- (void)liveManager:(DBYLiveManager *)manager thumbupWithCount:(NSInteger)count userName:(NSString *)userName;
///互动状态变化，需要执行上台（openCam）或上麦（openMic）的操作
- (void)liveManager:(DBYLiveManager *)manager interActionListChange:(NSArray<DBYInteractionModel *> *)list type:(DBYInteractionType)type;
#pragma mark -
#pragma mark - 答题相关方法

/**
 显示投票界面时调用
 @param voteType 投票类型
 */
- (void)liveManager:(DBYLiveManager *)manager shouldShowVoteWithType:(DBYLiveManagerVoteType)voteType;
/**
 停止答题时调用
 */
- (void)liveManagerShouldStopVote:(DBYLiveManager *)manager;
/**
 应该隐藏投票界面时调用
 */
- (void)liveManagerShouldHideVote:(DBYLiveManager *)manager;

/**
 投票数量变化时调用
 @param index   第几个选项 0为第一个选项
 @param count   此选项的变化数量 需累加
 */
- (void)liveManager:(DBYLiveManager *)manager voteChangeWithOptionIndex:(NSInteger)index optionCount:(NSInteger)count;

/**
 投票结束时调用

 @param index 第几个选项
 @param count 此选项的总数
 */
- (void)liveManager:(DBYLiveManager *)manager voteEndWithOptionIndex:(NSInteger)index ontionSumCount:(NSInteger)count;
/**
 投票失败时调用
 */
- (void)liveManagerSendVoteFail:(DBYLiveManager *)manager;

#pragma mark - admin

- (void)liveManager:(DBYLiveManager *)manager receivedMessage:(NSString *)jsonMessage;
@end
