//
//  DBYDownloadDataManager.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/9/5.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class DBYDownloadModel;

@interface DBYDownloadDataManager : NSObject

// 获取单例
+ (instancetype)shareManager;

/// 添加数据
- (void)appendDownloadModel:(DBYDownloadModel *)model;
/// 删除数据
- (void)removeDownloadModel:(DBYDownloadModel *)model;
/// 更新数据
- (void)updateDownloadModel:(DBYDownloadModel *)model;
/// 查找数据
- (DBYDownloadModel *)getDownloadModelWithUniqueId:(NSString *)uniqueId;

/// 获取所有数据
- (NSArray<DBYDownloadModel *> *)getAllDownloadModel;
/// 获取下载列表（包括下载中、暂停、等待下载）
- (NSArray<DBYDownloadModel *> *)getDownloadList;
/// 获取所有正在下载的数据
- (NSArray<DBYDownloadModel *> *)getAllDownloadingModel;
/// 获取所有下载完成的数据
- (NSArray<DBYDownloadModel *> *)getAllDownloadedModel;
/// 获取所有暂停的数据
- (NSArray<DBYDownloadModel *> *)getAllPausedModel;
/// 获取所有等待下载的数据
- (NSArray<DBYDownloadModel *> *)getAllWaitingModel;

@end

NS_ASSUME_NONNULL_END
