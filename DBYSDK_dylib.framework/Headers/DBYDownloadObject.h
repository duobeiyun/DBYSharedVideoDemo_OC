//
//  DBYDownloadObject.h
//  DBYSDK_dylib
//
//  Created by duobei.on 16/6/20.
//  Copyright © 2016年 duobei. All rights reserved.
//

#import "DBYConstants.h"
#import "DBYEnumerates.h"
#import <Foundation/Foundation.h>

@protocol DBYDownloadObjectDelegate;

@interface DBYDownloadObject : NSObject <NSCoding>

//下载课程的roomID
@property (nonatomic, copy) NSString *roomID;
//下载课程名称
@property (nonatomic, copy) NSString *title;
/// 下载状态
@property (nonatomic, assign) DBYDownloadState state;
@property (nonatomic, assign, readonly) BOOL isFinished;
@property (nonatomic, assign, readonly) BOOL downloadIng;
//下载进度
@property (nonatomic, assign) float progress;
//当前下载速度
@property (nonatomic, assign) float currentDownloadSpeed;
/**
 *  下载数据大小
 */
@property (nonatomic, assign) unsigned long long totalLen;
//已下载大小
@property (nonatomic, assign) float downloadedSize;
//下载链接 （自动生成）
@property (nonatomic, copy) NSString *downloadURLString;
//续传数据
@property (nonatomic, strong) NSData *resumeData;
///下载事件代理
@property (nonatomic, weak) id<DBYDownloadObjectDelegate> delegate;
//一段时间内下载数据长度
@property (nonatomic, assign) unsigned long long orderTimeRecvLen;
//下载任务
@property (nonatomic, strong) NSURLSessionDownloadTask *downloadTask;

+ (instancetype)downloadObjectWithRoomID:(NSString *)roomID;
//设置是否下载包含视频课程 需在下载前设置
- (void)setObjectDownloadLessonWithVideo:(BOOL)withVideo;
- (void)getFileLengthWith:(void (^)(unsigned long long totalLen, NSString *errorMsg))completeHandler;

@end

/**
 *  监控Object 下载进度等信息代理
 */
@protocol DBYDownloadObjectDelegate <NSObject>
@optional
/**
 *  更新下载信息时调用
 *
 *  @param downloadObject 下载对象
 */
- (void)downloadObjectDidUpdateInfo:(DBYDownloadObject *)downloadObject;
/**
 *  下载完成调用
 *
 *  @param downloadObject 下载对象
 */
- (void)downloadObjectFinishDownload:(DBYDownloadObject *)downloadObject;
//暂停下载调用
- (void)downloadObjectDidPauseDownload:(DBYDownloadObject *)downloadObject;
//下载出错调用
- (void)downloadObject:(DBYDownloadObject *)downloadObject didDownloadFailWithError:(NSError *)error;

@end
