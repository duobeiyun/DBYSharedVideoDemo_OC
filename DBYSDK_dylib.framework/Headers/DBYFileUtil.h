//
//  DBYFileUtil.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/8/13.
//

#import <Foundation/Foundation.h>

@class DBYLessonItem;

NS_ASSUME_NONNULL_BEGIN

@interface DBYFileUtil : NSObject

+ (NSString *)rootPath;
+ (NSString *)contentsPath;
+ (NSString *)archivePath;

+ (NSArray<DBYLessonItem *> *)getAllDownloadedLessons;
+ (void)addLessonItem:(DBYLessonItem *)item;
+ (void)removeLessonItem:(DBYLessonItem *)item;

@end

NS_ASSUME_NONNULL_END
