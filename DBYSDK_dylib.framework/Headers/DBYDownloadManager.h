//
//  DBYDownloadManager.h
//  DBYSDK_dylib
//
//  Created by Michael on 16/6/20.
//  Copyright © 2016年 duobei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define DOWNLOAD_FINISHED_NOTIFICATION_NAME @"downloadFinishedNotificationName" //下载完成发送通知名称


#define DOWNLOAD_FINISHED_FAIL_NOTIFICATION_NAME @"downloadFinishedFailNotificationName" //下载失败发送通知
@class DBYDownloadObject;
@interface DBYDownloadManager : NSObject


+(instancetype)sharedInstance;
#pragma mark - download methods

-(void)resumeFromBackgroundWithDownloadObject:(DBYDownloadObject *)downloadObj;
//根据下载模型 下载文件
-(void)downloadResourceWithDownloadObject:(DBYDownloadObject*)downloadObj;
//根据下载模型 暂停下载文件 
-(void)suspendDownloadResourceWithDownloadObject:(DBYDownloadObject*)downloadObj;

-(void)cancelDownloadResourceWithDownloadObject:(DBYDownloadObject*)downloadObj;
//暂停所有下载任务
-(void)pauseAllDownloadTask;
//下载播放器
-(void)downloadWebPlayerWith:(void (^)(NSError*error))complateHandler;

#pragma mark - background session
-(NSString*)sessionIdentifier;

- (void)addCompletionHandler:(void(^)(void))handler forSession:(NSString *)identifier;
@end
