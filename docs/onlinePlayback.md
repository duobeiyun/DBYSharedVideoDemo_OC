# 多贝云 SaaS SDK iOS 在线回放 API 参考文档

## 主动调用模块

### 初始化

```objc
///使用参数进教室时，需传入appkey和partnerID
- (instancetype)initWithPartnerID:(NSString *)partnerID appKey:(NSString *)appKey;
```

#### 概述

目前 SDK 只支持创建一个实例，多次 init 会返回同一个对象。SDK 的所有接口函数，如无特殊说明，都需要在主线程调用。异步操作在回调函数中返回结果，同步函数默认成功，没有返回值。

#### 参数

| 参数 | 说明 |
| --- | --- |
| partnerID| partnerID |
| appkey | 多贝云为开发者提供的appkey |

#### 返回
实例对象

### startPlayback
```objc
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
```

#### 概述

进入教室。

有多种不同的进入教室方法可以调用，在回调中会返回结果，type为DBYOnlinePlayBackManagerStartPlayBackErrorTypeNoError表示成功。其他类型表示失败，业务层可以根据结果做出相应的处理。

#### 参数

|参数 | 说明|
| ---| --- |
| roomID | 教室的id |
| uid | 用户Id|
| nickName | 用户昵称 |
| userRole | 用户角色 |
| authJson | authinfo的json的字符串 |
| url | 请求authinfo的url |
| inviteCode | 邀请码 |


### stopPlay

```objc
/**
 退出教室
 @param completeHandler
 success: code = 0, message = nil
 failed: code != 0, message != nil
 */
- (void)stopPlayWithCompleteHandler:(void (^)(int code, NSString *message))completeHandler;
```

#### 概述
退出教室。

退出教室，会断开所有音视频连接。 当调用 [startPlayback](#startPlayback) API 方法后，必须调用 stopPlay 退出教室，否则无法进入下一个教室。 该方法会把教室内相关的所有相关资源释放掉。该方法是异步操作，回调完成后才是真正退出教室。

#### 回调

- code == 0: 方法调用成功
- code < 0: 方法调用失败
- message: 错误消息，调用成功消息为空

### setSharedVideo

```objc
///设置新版大班视频显示区域
- (void)setSharedVideoView:(UIView *)videoView; 
```
#### 概述

设置新版大班的画板视频显示区域。

需要在[startPlayback](#startPlayback)之前设置。

#### 参数

| 参数 | 说明 |
| --- | --- |
| videoView |  一个UIView的实例|

## SDK回调


### hasNewChatMessageWithChatArray

```objc
/**
 有聊天时调用 返回当前时间的消息数组
 可以在上层viewcontroller用一个数组存起来作为聊天列表的数据源，自己管理。
 @param newChatDictArray 收到的最新消息的数组
 */
- (void)playbackManager:(DBYOnlinePlayBackManager *)manager hasNewChatMessageWithChatArray:(NSArray *)newChatDictArray;  
```

#### 概述

当收到的别人的聊天消息时触发。是新的消息。

#### 参数

| 参数    | 说明                                 |
| ------- | ------------------------------------ |
| newChatDictArray | 消息数组，里面的数据结构是字典 |
oc数据结构如下：
```objc
@{ 
       @"userName" : "nickName",
       @"message" : "message",
       @"isOwner" : @(YES),
       @"time" : "Tue Jan 14 15:51:42 2020",//NSDate
       @"uid" : "userId",
       @"role" : @(2)
}
```

### playBackManagerChatMessageShouldClear

```objc
/**
 聊天数组需要清空时调用
 如果使用自己维护的数组来管理聊天，则需要在这个方法中清空相应数组，避免后续回调聊天数据导致聊天重复
 */
- (void)playBackManagerChatMessageShouldClear:(DBYOnlinePlayBackManager *)manager;
```

#### 概述

清除所有聊天。

### totalTime


```objc
//开始播放时调用 总时长
- (void)playBackManager:(DBYOnlinePlayBackManager *)manager totalTime:(NSTimeInterval)time;
```

#### 概述

通知回放的总时长。

#### 参数

| 参数 | 说明 |
| ---| --- |
| time| NSTimeInterval |


### playedAtTime

```objc
//返回播放时间
- (void)playBackManager:(DBYOnlinePlayBackManager *)manager playedAtTime:(NSTimeInterval)time;  
```

#### 概述
回放时间回调

#### 参数

|参数 | 说明|
| ---| --- |
| time | NSTimeInterval |

### playbackManagerDidPlayEnd

```objc
/**
 播放完调用
 */
- (void)playbackManagerDidPlayEnd:(DBYOnlinePlayBackManager *)manager; 
```
#### 概述
播放完成，在这里更新UI

