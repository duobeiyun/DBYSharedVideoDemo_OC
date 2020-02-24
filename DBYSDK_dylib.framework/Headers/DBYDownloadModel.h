//
//  DBYDownloadModel.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/9/3.
//

#import <Foundation/Foundation.h>
#import "DBYEnumerates.h"

NS_ASSUME_NONNULL_BEGIN

@interface DBYDownloadModel : NSObject

@property (nonatomic, copy) NSString *uniqueId;             // 文件唯一id标识
@property (nonatomic, copy) NSString *fileName;             // 文件名
@property (nonatomic, copy) NSString *url;                  // url
@property (nonatomic, strong) NSData *resumeData;           // 下载的数据
@property (nonatomic, strong) NSURLSessionDownloadTask *downloadTask; //下载任务
@property (nonatomic, assign) float progress;               // 下载进度
@property (nonatomic, assign) DBYDownloadState state;       // 下载状态
@property (nonatomic, assign) NSUInteger totalFileSize;     // 文件总大小
@property (nonatomic, assign) NSUInteger currentFileSize;   // 下载大小
@property (nonatomic, assign) NSUInteger speedFileSize;
@property (nonatomic, assign) float speed;                  // 下载速度
@property (nonatomic, assign) NSTimeInterval lastSpeedTime;

@property (nonatomic, copy) void(^stateChangeBlock)(DBYDownloadState state);
@property (nonatomic, copy) void(^progressChangeBlock)(float progress, float currentSize, float totalsize);
@property (nonatomic, copy) void(^speedChangeBlock)(float speed);

- (instancetype)initWithDictionary:(NSDictionary *)dict;
- (NSDictionary *)convertToDictionary;

@end

NS_ASSUME_NONNULL_END
