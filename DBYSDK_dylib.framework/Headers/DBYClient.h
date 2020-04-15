//
//  DBYClient.h
//  DBYSDK_dylib
//
//  Created by Michael on 16/6/23.
//  Copyright © 2016年 duobei. All rights reserved.
//  SDK接口

#import "DBYDownloadObject.h"
#import "DBYEnumerates.h"
#import "DBYMedia.h"
#import <Foundation/Foundation.h>

@interface DBYClient : NSObject
#pragma mark - version
//返回sdk版本号
+ (NSString *)SDKVersion;

#pragma mark - config
///切换sdk内部请求的集群地址
+ (void)setDomainType:(DBYDomainType)type;
///获取sdk内部请求的集群地址
+ (DBYDomainType)getDomainType;

#pragma mark - offline download util
/**
 *  检查根据路径检查课程文件夹是否存在
 */
+ (BOOL)checkLessonDirExistedWithPath:(NSString *)path;
/**
 检查线上是否有含视频的离线缓存资源
 */
+ (void)checkLessonHasVideoOfflineResourceWithRoomId:(NSString *)roomId completeHandler:(void (^)(BOOL hasVideoOfflineResource))completeHandler;
//检查本地课程路径中是否包含视频
+ (BOOL)checkLessonHasVideoWithPath:(NSString *)path;
/**
 根据roomId和是否包含视频选项返回对应资源的下载链接
 
 @param roomId roomId
 @param hasVideo 是否需要包含视频
 @return zip资源下载链接
 */
+ (NSString *)lessonDownloadUrlWithRoomId:(NSString *)roomId hasVideo:(BOOL)hasVideo;

+ (NSString *)lessonDownloadUrlWithRoomId:(NSString *)roomId hasVideo:(BOOL)hasVideo domain:(DBYDomainType)domain;

#pragma mark - setting methods
/**
 *  设置解密秘钥
 *
 */
+ (void)setAppKeyWith:(NSString *)appkey;
/**
 *  设置下载、虚拟服务器 基本路径
 *
 */
+ (void)setFilePathWith:(NSString *)filePath;

#pragma mark - download methods
/**
 *  根据downloadObject对象开始下载
 *
 */
+ (void)startDownloadWith:(DBYDownloadObject *)downloadObj;

/**
 *  停止下载，不保存续传数据
 *
 */
+ (void)stopDownloadWith:(DBYDownloadObject *)downloadObj;
/**
 *  暂停下载，保存续传数据
 *
 */
+ (void)pauseDownloadWith:(DBYDownloadObject *)downloadObj;
/**
 *  恢复下载
 *
 */
+ (void)resumeDownloadWith:(DBYDownloadObject *)downloadObj;

/**
 从保存的本地归档文件恢复下载
 
 @param continueDownload 是否继续下载 YES：之前在下载的开始继续下载 暂停的存入暂停数组 等待的存入等待数组
 NO：所有下载任务存入暂停数组
 */
+ (void)recoverDownloadObjectsWithContinueDownload:(BOOL)continueDownload;
/**
 根据roomid返回课程下载状态
 */
+ (DBYClientDownloadObjectState)getDownloadStateWithRoomID:(NSString *)roomID;
/**
 根据roomID返回下载obj
 
 @return 如果没有对应roomID的Obj则返回nil
 */
+ (DBYDownloadObject *)getDownloadObjectWithRoomID:(NSString *)roomID;
//暂停所有downloadObj 下载中的会暂停下载 存入暂停数组 等待中的会直接存入暂停数组
+ (void)pauseAllDownloadObject;
//开始所有downloadObj 会根据下载限制 开始下载,并存入下载中数组 超过下载限制的存入等待数组
+ (void)startAllDownlaodObject;

#pragma mark - download manage
/**
 *  设置最大同时下载数
 *
 */
+ (void)setMaxDownloadCount:(int)maxDownloadCount;
/**
 *  获得最大下载数
 *
 */
+ (int)getMaxDownloadCount;
/**
 *  返回正在下载objs 数组
 *
 */
+ (NSArray *)downloadingObjects;
/**
 *  返回等待下载objs 数组
 *
 */
+ (NSArray *)waitingObjects;
/**
 *  返回暂停下载objs 数组
 *
 */
+ (NSArray *)pausingObjects;
/**
 *  返回下载失败的数组
 *
 */
+ (NSArray *)errorObjects;

#pragma mark - lesson methods
/**
 *  删除对应roomID的本地课程
 *
 *
 *  @return 是否删除成功
 */
+ (BOOL)removeLessonWith:(NSString *)roomID;

+ (BOOL)checkLessonHasVideoWith:(NSString *)roomID;
/**
 *  返回课程本地文件夹路径
 */
+ (NSString *)getLessonFilePathWith:(NSString *)roomID;

#pragma mark - background download
//使用后台下载时，返回session id
+ (NSString *)sessionIdentifier;
+ (NSURLSession *)downloadSession;
//保存后台下载完成回调
+ (void)addCompletionHandler:(void (^)(void))handler forSession:(NSString *)identifier;
//app被杀死后 需调用此方法恢复下载任务
+ (void)recoverDownloadFromBackground;

@end
