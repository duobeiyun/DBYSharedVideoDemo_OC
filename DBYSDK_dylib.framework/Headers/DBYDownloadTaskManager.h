//
//  DBYDownloadTaskManager.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/9/19.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class DBYDownloadModel;

@interface DBYDownloadTaskManager : NSObject

@property (nonatomic, assign) NSInteger maxConcurrentCount;

+ (instancetype)sharedInstance;

#pragma mark - download methods
- (void)startDownloadWithModel:(DBYDownloadModel *)model;
- (void)pauseDownloadWithModel:(DBYDownloadModel *)model;
- (void)cancelDownloadWithModel:(DBYDownloadModel *)model;

//暂停所有下载任务
- (void)pauseAllDownloadTask;

@end

NS_ASSUME_NONNULL_END
