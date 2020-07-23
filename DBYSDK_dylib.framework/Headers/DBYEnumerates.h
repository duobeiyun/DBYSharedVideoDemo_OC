//
//  DBYEnumerates.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/7/4.
//  Copyright © 2019 duobei. All rights reserved.
//
#import <Foundation/Foundation.h>

#ifndef DBYEnumerates_h
#define DBYEnumerates_h

typedef NS_ENUM(NSUInteger, DBYDomainType) {
    /** com域名 */
    DBYDomainTypeCom = 0,
    /** net域名 */
    DBYDomainTypeNet = 1,
    /** 测试域名 */
    DBYDomainTypeDev = 2
};

typedef NS_ENUM(NSUInteger, DBYClassType) {
    /** 其他 */
    DBYClassTypeUnknow = 0,
    /** 1v1 */
    DBYClassTypeOneToOne = 1,
    /** 1vn */
    DBYClassTypeOneToMultiple = 2,
    /** 新版1vn */
    DBYClassTypeSharedVideo = 3,
};

typedef NS_ENUM(NSUInteger, DBYCourseType) {
    /** 其他 */
    DBYCourseTypeUnknow = 0,
    /** 视频课 */
    DBYCourseTypeVideo = 1,
    /** 音频课 */
    DBYCourseTypeAudio = 2
};

typedef NS_ENUM(NSUInteger, DBYCourseStatus) {
    /** 其他 */
    DBYCourseStatusUnknow = 0,
    /** 课程未开始 */
    DBYCourseStatusBeforeLive = 1,
    /** 直播中 */
    DBYCourseStatusLiving = 2,
    /** 可以看回放 */
    DBYCourseStatusCanPlayback = 3,
    /** 空录像 */
    DBYCourseStatusPlaybackEmpty = 4,
    /** 转换失败 */
    DBYCourseStatusNoPlayback = 5,
    /** 转换中 */
    DBYCourseStatusBeforePlayback = 6,
};

typedef NS_ENUM(NSUInteger, DBYVideoFrameRate) {
    /** 10 fps. */
    DBYVideoFrameRateFps10 = 10,
    /** 15 fps. */
    DBYVideoFrameRateFps15 = 15,
    /** 20 fps. */
    DBYVideoFrameRateFps20 = 20,
    /** 24 fps. */
    DBYVideoFrameRateFps24 = 24,
    /** 30 fps. */
    DBYVideoFrameRateFps30 = 30,
    /** 60 fps (macOS only). */
    DBYVideoFrameRateFps60 = 60,
};

typedef NS_ENUM(NSUInteger, DBYVideoOutputOrientationMode) {
    DBYVideoOutputOrientationModeAdaptative,
    DBYVideoOutputOrientationModeFixedLandscape,
    DBYVideoOutputOrientationModeFixedPortrait,
};

typedef NS_ENUM(NSUInteger, DBYVideoMirrorMode) {
    /** 和系统相机一致 */
    DBYVideoMirrorModeAuto = 0,
    /** Enables mirror mode. */
    DBYVideoMirrorModeEnabled = 1,
    /** Disables mirror mode. */
    DBYVideoMirrorModeDisabled = 2,
};

typedef enum : NSUInteger {
    DBYLiveManagerVideoCaptureLevelFluent = 0, //流畅
    DBYLiveManagerVideoCapture320x240 = 1, //流畅
    DBYLiveManagerVideoCaptureLevelClear = 2, //清晰
    DBYLiveManagerVideoCaptureLevelHigh = 3, //高清
} DBYLiveManagerVideoCaptureLevel; //采集视频清晰度等级

typedef enum : NSUInteger {
    DBYLiveManagerStatusTypeAppsConnect = 10, //apps消息连接成功
    DBYLiveManagerStatusTypeAppsError, //apps连接失败
    DBYLiveManagerStatusTypeAppsReconnect, //apps重连
    DBYLiveManagerStatusTypeAppsVeryBadNetwork = 15, //网络很差，一直连不上
    DBYLiveManagerStatusTypeAudioConnect = 100, //音频连接成功
    DBYLiveManagerStatusTypeAudioError, //音频连接失败
    DBYLiveManagerStatusTypeAudioReconnect, //音频重连
    DBYLiveManagerStatusTypeVideoConnect = 200, //视频连接成功
    DBYLiveManagerStatusTypeVideoError, //视频连接失败
    DBYLiveManagerStatusTypeVideoReconnect //视频重连
} DBYLiveManagerStatusType;

typedef enum : NSUInteger {
    DBYLiveManagerEnterRoomErrorTypeNoError = 0,
    DBYLiveManagerEnterRoomErrorTypeAuthInfoFail = 900,
    DBYLiveManagerEnterRoomErrorTypeAuthHttpError = 901,
    DBYLiveManagerEnterRoomErrorTypeTestVMEmpty = 902,             //测速列表为空
    DBYLiveManagerEnterRoomErrorTypeTestVMTimeout = 903,           //测速超时
    DBYLiveManagerEnterRoomErrorTypeAuthReturnFalse = 10000,       //返回失败
    DBYLiveManagerEnterRoomErrorTypeAuthNotBegin,                  //课程未开始
    BYLiveManagerEnterRoomErrorTypeAuthCanWatchPlayBack = 10003,   //课程已结束，可观看回放
    DBYLiveManagerEnterRoomErrorTypeAuthNoOneToLive = 10004,       //没有人直播
    DBYLiveManagerEnterRoomErrorTypeAuthPlaybackConversionFailed,  //回放转换失败
    DBYLiveManagerEnterRoomErrorTypeAuthPlaybackConversion,        //回放转换中
    DBYLiveManagerEnterRoomErrorTypeTestVMError,                   //测速失败
    DBYLiveManagerEnterRoomErrorTypeAppsStartFail,                 //链接apps失败
    DBYLiveManagerEnterRoomErrorTypeAPIHasStart,                   //多次进入教室
    DBYLiveManagerEnterRoomErrorTypeRECOVERY_NOTSTART_OR_NOTPAUSE, //未暂停就调用恢复
    DBYLiveManagerEnterRoomErrorTypePAUSE_NOTSTART_OR_HASPAUSE,    //未恢复就调用暂停
    DBYLiveManagerEnterRoomErrorTypeUserRoleTypeWrong = 10100,     //用户角色错误
    DBYLiveManagerEnterRoomErrorTypeParamHasNil = 20000            //参数为空
    
} DBYLiveManagerEnterRoomErrorType;

typedef enum : NSUInteger {
    DBYLiveManagerUserRoleTypeTeacher = 1, //老师
    DBYLiveManagerUserRoleTypeStudent = 2, //学生
    DBYLiveManagerUserRoleTypeAdmin = 3,
    DBYLiveManagerUserRoleTypeTeacherAssistant = 4, //助教
    DBYLiveManagerUserRoleTypeParent = 6, //加载
} DBYLiveManagerUserRoleType;

typedef enum : NSUInteger {
    DBYLiveManagerVoteType2Options = 10, //两个选项
    DBYLiveManagerVoteType3Options,
    DBYLiveManagerVoteType4Options,
    DBYLiveManagerVoteType5Options,
    DBYLiveManagerVoteType6Options,
    DBYLiveManagerVoteTypeTrueOrFalse = 30 //判断题
} DBYLiveManagerVoteType; //答题类型枚举

typedef enum : NSUInteger {
    DBYLiveManagerClassRoomType1V1 = 1,
    DBYLiveManagerClassRoomType1VN = 2,
    DBYLiveManagerClassRoomType1VNVideo = 5,
} DBYLiveManagerClassRoomType; //进入教室类型

typedef NS_ENUM(NSUInteger, DBYStreamModel) {
    DBYStreamModelLow = 0,
    DBYStreamModelHigh,
};

typedef NS_ENUM(NSUInteger, DBYPPTSizeMode) {
    DBYPPTSizeModeNone,
    //超宽ppt
    DBYPPTSizeModeWider,
    //水平居中
    DBYPPTSizeModeCenterH,
    //等宽等高
    DBYPPTSizeModeNormal,
    //垂直居中
    DBYPPTSizeModeCenterV,
    //超宽ppt
    DBYPPTSizeModeLonger,
};

typedef NS_ENUM(NSUInteger, DBYClientDownloadObjectState) {
    /** 未下载 */
    DBYClientDownloadObjectStateNotDownload = 0,
    /** 下载中 */
    DBYClientDownloadObjectStateDownloading = 1,
    /** 下载暂停 */
    DBYClientDownloadObjectStatePausing = 2,
    /** 下载等待 */
    DBYClientDownloadObjectStateWaiting = 3,
    /** 下载完成 */
    DBYClientDownloadObjectStateDownloaded = 4
};
typedef NS_ENUM(NSInteger, DBYDownloadState) {
    DBYDownloadStateDefault = 0,  // 默认
    DBYDownloadStateDownloading,  // 正在下载
    DBYDownloadStateWaiting,      // 等待
    DBYDownloadStatePaused,       // 暂停
    DBYDownloadStateFinished,     // 完成
    DBYDownloadStateError,        // 错误
};

typedef NS_ENUM(NSUInteger, DBYContentType) {
    DBYContentTypeJson,
    DBYContentTypeUrlEncode
};

typedef NS_ENUM(NSUInteger, DBYMessageType) {
    DBYMessageTypeUnknow,
    DBYMessageTypeAudioInvite,
    DBYMessageTypeAudioRequest,
    DBYMessageTypeAudioInviteTimeout,
    DBYMessageTypeAudioInviteEnd,
    DBYMessageTypeAudioKickedOut,
    DBYMessageTypeAudioOnline,
    DBYMessageTypeAudioOffline,
    DBYMessageTypeVideoOnline,
    DBYMessageTypeVideoInvite,
    DBYMessageTypeVideoRequest,
    DBYMessageTypeVideoOffline,
};

typedef NS_ENUM(NSUInteger, DBYInteractionState) {
    DBYInteractionStateNormal,  //默认状态
    DBYInteractionStateInqueue, //请求上台或上麦
    DBYInteractionStateAbort,   //取消请求上台或上麦
    DBYInteractionStateQuit,    //退出上台或上麦
    DBYInteractionStateJoined   //上台或上麦中
};

typedef NS_ENUM(NSUInteger, DBYInteractionType) {
    DBYInteractionTypeAudio,    //音频
    DBYInteractionTypeVideo     //视频
};
#endif /* DBYEnumerates_h */
