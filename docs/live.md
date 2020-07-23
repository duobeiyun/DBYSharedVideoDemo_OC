# 多贝云 SaaS SDK iOS 直播 API 参考文档

## 主动调用模块

### 初始化

```objc
///使用参数进教室时，需传入appkey和partnerID
- (instancetype)initWithPartnerId:(NSString *)partnerId
                       withAppKey:(NSString *)appKey;

///使用链接进教室时 可以直接调用init
- (instancetype)init;
```

#### 概述

目前 SDK 只支持创建一个实例，多次 init 会返回同一个对象。SDK 的所有接口函数，如无特殊说明，都需要在主线程调用。异步操作在回调函数中返回结果，同步函数默认成功，没有返回值。

#### 参数

| 参数 | 说明 |
| --- | --- |
| partnerId| 多贝云为开发者提供的partnerId |
| appkey | 多贝云为开发者提供的appkey |

#### 返回
实例对象

### enterRoom
```objc
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
```

#### 概述

进入教室。

有多种不同的进入教室方法可以调用，在回调中会返回结果，type为DBYLiveManagerEnterRoomErrorTypeNoError表示成功。其他类型表示失败，业务层可以根据结果做出相应的处理。

成功进入教室后，会触发 [clientOnline()](#clientOnline)回调。

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


### quitClassRoom

```objc
- (void)quitClassRoomWithCompleteHandler:(void (^)(NSString *failMsg, int code))completeHandler;
```

#### 概述
退出教室。

退出教室，会断开所有音视频连接。 当调用 [enterRoom](#enterRoom) API 方法后，必须调用 quitClassRoom 退出教室，否则无法进入下一个教室。 该方法会把教室内相关的所有相关资源释放掉。该方法是异步操作，回调完成后才是真正退出教室。

#### 回调

- code: 0：方法调用成功，其他：方法调用失败
- message: 错误消息，调用成功消息为空

### setSharedVideoView

```objc
///设置新版大班视频显示区域
- (void)setSharedVideoView:(UIView *)videoView;  
```
#### 概述

设置新版大班的画板或者桌面共享视频显示区域。

需要在[enterRoom](#enterRoom)之前设置。

#### 参数

| 参数 | 说明 |
| --- | --- |
| videoView |  一个UIView的实例|

## SDK回调


### hasNewChatMessageWithChatArray

```objc
/**
 有聊天时调用 返回收到的最新的消息
 可以在上层viewcontroller用一个数组存起来作为聊天列表的数据源，自己管理。
 @param newChatDictArray 收到的最新消息的数组
 */
- (void)liveManager:(DBYLiveManager *)manager hasNewChatMessageWithChatArray:(NSArray *)newChatDictArray;  
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

### hasAnnounceContent

```objc
///有教室公告时调用
- (void)liveManager:(DBYLiveManager *)manager hasAnnounceContent:(NSString *)announceContent;
```

#### 概述

教师端发了公告后触发。

#### 参数

| 参数     | 说明  |
| -------- | ---- |
| announceContent | 公告内容 |

### studentCanSpeak


```objc
/**
 教师给麦或收麦时调用
 
 @param canSpeak YES 表示教师给麦 ；NO 表示教师收麦
 */
- (void)liveManager:(DBYLiveManager *)manager studentCanSpeak:(BOOL)canSpeak;  
```

#### 概述

学生端经过上麦流程后开始发送音频数据，或者经过下麦流程后结束发送音频数据时触发。自己的上麦、下麦通知。

#### 参数

| 参数 | 说明 |
| ---| --- |
| canSpeak| YES:开始发送 NO:结束发送 |


### shouldShowVoteWith

```objc
/**
 显示投票界面时调用
 @param voteType 投票类型
 */
- (void)liveManager:(DBYLiveManager *)manager shouldShowVoteWithType:(DBYLiveManagerVoteType)voteType;  
```

#### 概述
教师端发起了答题触发

#### 参数

|参数 | 说明|
| ---| --- |
| voteType | 答题的类型 |
```objc
typedef enum : NSUInteger {
    DBYLiveManagerVoteType2Options = 10, //两个选项
    DBYLiveManagerVoteType3Options,
    DBYLiveManagerVoteType4Options,
    DBYLiveManagerVoteType5Options,
    DBYLiveManagerVoteType6Options,
    DBYLiveManagerVoteTypeTrueOrFalse = 30 //判断题
} DBYLiveManagerVoteType; //答题类型枚举
```

### liveManagerShouldHideVote

```objc
/**
 应该隐藏投票界面时调用
 */
- (void)liveManagerShouldHideVote:(DBYLiveManager *)manager; 
```
#### 概述
教师端隐藏答题组件时触发

### voteChangeWithOptionIndex

```objc
/**
 投票数量变化时调用
 @param index   第几个选项 0为第一个选项
 @param count   此选项的变化数量 需累加
 */
- (void)liveManager:(DBYLiveManager *)manager voteChangeWithOptionIndex:(NSInteger)index optionCount:(NSInteger)count; 
```
#### 概述
有人答题时触发，广播消息，需要本地统计总数

#### 参数

|参数 | 说明|
| ---| --- |
| index | 选项的序号 |
| count | 选中的次数 |

### teacherGiveMicToStudentWithUserInfo

```objc
/**
 老师给/收 其他学生麦时调用
 
 @param userInfo 学生信息 
 @param canSpeak YES 给麦 / NO 收麦
 */
- (void)liveManager:(DBYLiveManager *)manager teacherGiveMicToStudentWithUserInfo:(NSDictionary *)userInfo canSpeak:(BOOL)canSpeak;  
```
#### 概述

某个学生上麦或者下麦时触发，包括自己。

#### 参数

|参数 | 说明|
| ---| --- |
| userInfo | 用户信息 |
| canSpeak | YES:给麦 NO:收麦 |
userInfo结构如下:
```objc
@{
       @"userName" : "nickName",
       @"userRole" : @(2),
       @"uid" : "userId"
};
```

### hasVideo

```objc
/**
 开始视频或结束视频时调用
 @param hasVideo 是否有视频
 @param view     在哪个View上
 */
- (void)liveManager:(DBYLiveManager *)manager hasVideo:(BOOL)hasVideo inView:(UIView *)view; 
```

#### 概述

收到/断开远端老师或者学生的视频流时触发。

#### 参数

| 参数 | 说明  |
| --- | --- |
| hasVideo | 收到视频或者断开视频 |
| view | 业务传递的视图，用来区分身份 |


### liveManagerDidKickedOff

```objc
///被踢下线时调用
- (void)liveManagerDidKickedOff:(DBYLiveManager *)manager; 
```
#### 概述

当同一个用户同时登录了两个设备时，先登录的设备会收到改回调。此时需要重新登录，或者退出。

### receivedMessage
```objc
- (void)liveManager:(DBYLiveManager *)manager
    receivedMessage:(DBYMessageType)type
       withUserInfo:(NSDictionary<NSString *, NSString *> *)userInfo;  
```
#### 概述
收到自定义消息时触发。

#### 参数

|参数 | 说明|
| ---| --- |
| type | 消息类型 |
| userInfo | 用户信息 |
userInfo结构如下:
```objc
@{
       @"userName" : "nickName",
       @"userRole" : @(2),
       @"uid" : "userId"
};
```

### denyChatStatusChange

```objc
///全体禁言或解禁时调用 YES为禁言
- (void)liveManager:(DBYLiveManager *)manager denyChatStatusChange:(BOOL)isDeny;  
```
#### 概述
教师端全体禁言或解禁时触发。

#### 参数

|参数 | 说明|
| ---| --- |
| isDeny | YES:禁言 NO:解禁 |

### canChat

```objc
///自己是否可以发言 NO为不能
- (void)liveManager:(DBYLiveManager *)manager canChat:(BOOL)canChat;
```

#### 概述

教师端对自己禁言时触发。

#### 参数

| 参数    | 说明                     |
| ------- | ------------------------ |
| canChat     | YES:解禁 NO:禁言 |

### receivedQuestions

```objc
- (void)liveManager:(DBYLiveManager *)manager receivedQuestions:(NSArray<NSDictionary *> *)array;
```

#### 概述

问答初始化数据，进教室成功后触发。

#### 参数

| 参数    | 说明                     |
| ------- | ------------------------ |
| array | 问答数据数组 |
数组结构
```json
[{"id":"11111","ts":11111.0,"value":"jsonString"}]
```
jsonString结构
```json
{ 
  "questionInfo":{ 
    "msgId":"c360ca00-3126-11ea-adca-9fa19804416d", // 提出问题的消息id
    "type":"CHAT_MESSAGE", // 提出问题的消息类型
    "msg":"今天晚上吃什么？", // 问答中的提问
    "uid":"jze5a46c8f24bb423f805e909482291d47", // 提出问题的用户id
    "username":"生动的夏娜", // 提出问题的用户名
    "role":"2", // 提出问题的用户角色
    "timestamp":1578383584960 // 提出问题的时间
   },
  "answerInfo":{ 
    "uid":"jz114b2f3c78b84552b350bf218f97b528", // 回答问题的用户id
    "username":"d", // 回答问题的用户名字
    "msg":"吃米线都可以",
    "role":"1"  // 回答问题的用户角色
  }
}
```

### receivedQuestion

```objc
- (void)liveManager:(DBYLiveManager *)manager receivedQuestion:(NSDictionary *)dict;
```

#### 概述

教师端收集到一条新的问答时触发。
#### 参数

| 参数    | 说明                     |
| ------- | ------------------------ |
| dict | 一条问答数据 |
```json
[{"id":"11111","ts":11111.0,"value":"jsonString"}]
```

### removedQuestion

```objc
- (void)liveManager:(DBYLiveManager *)manager removedQuestion:(NSString *)questionId;   
```

#### 概述

教师端移除一条问答时触发。根据id遍历数组，如果包含一条数据的id等于要删除的id然后移除。

#### 参数

| 参数    | 说明               |
| ------- | ------------------ |
| questionId | 问答的id |

### interActionListChange
```objc
///互动状态变化，需要执行上台（openCam）或上麦（openMic）的操作
- (void)liveManager:(DBYLiveManager *)manager interActionListChange:(NSArray<DBYInteractionModel *> *)list type:(DBYInteractionType)type;

```
#### 概述

上台上麦的列表，type，互动类型，上台还是上麦。list互动列表包含所有参与互动的人，每个人有上台（麦）中，等待中等状态。

#### 参数

| 参数    | 说明               |
| ------- | ------------------ |
| list | 互动列表 |
| type | 互动类型 |

### getInteractionList
```
- (void)getInteractionList:(DBYInteractionType)type completion:(void(^)(NSArray<DBYInteractionModel *> *list))completion;
```
#### 概述

获取初始互动列表，在加入教室或者显示互动列表的时候调用。

#### 参数

| 参数    | 说明               |
| ------- | ------------------ |
| list | 互动列表 |

### requestInteraction
```
- (void)requestInteraction:(DBYInteractionType)type state:(DBYInteractionState)state completion:(void(^)(BOOL result))completion;
```

#### 概述

请求参与互动

#### 参数

| 参数    | 说明               |
| ------- | ------------------ |
| type | 互动类型，上台还是上麦 |
| state | 加入还是离开，具体使用参考DBYSharedVideo实现 |

### acceptInteraction
```
- (void)acceptInteraction:(DBYInteractionType)type completion:(void(^)(BOOL result))completion;
```
#### 概述

接受老师或者助教的互动邀请

#### 参数

| 参数    | 说明               |
| ------- | ------------------ |
| type | 邀请上台还是上麦 |