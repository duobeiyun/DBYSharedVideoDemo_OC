//
//  DBYConstants.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/6/5.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@interface DBYConstants : NSObject

extern CGSize const DBYVideoDimension192x144;
extern CGSize const DBYVideoDimension320x240;
extern CGSize const DBYVideoDimension640x480;
extern CGSize const DBYVideoDimension1280x720;

extern NSInteger const DBYVideoBitrate140kbps;
extern NSInteger const DBYVideoBitrate70kbps;
extern NSInteger const DBYVideoBitrate40kbps;

///下载完成通知名称
extern NSString *const DBYDownloadDidFinishNotificationName;
///下载失败通知名称
extern NSString *const DBYDownloadDidFailedNotificationName;
///下载完成通知名称, 1.8.10 以上版本使用 DBYDownloadDidFinishNotificationName
extern NSString *const DBYDownloadObjectDidFinishDownloadNotificationName;

///最大并发下载数
extern NSString *const DBYDownloadMaxConcurrentCountKey;
///下载session id
extern NSString *const DBYBackgroundTaskIdentifier;

extern NSInteger const DBYOfflineUpdateTimeInterval;

@end

NS_ASSUME_NONNULL_END
