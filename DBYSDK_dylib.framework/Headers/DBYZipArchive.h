//
//  DBYZipArchive.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/7/15.
//  Copyright © 2019 duobei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "zip_common.h"

NS_ASSUME_NONNULL_BEGIN

@protocol DBYZipArchiveDelegate;

@interface DBYZipArchive : NSObject

// Unzip
+ (BOOL)unzipFileAtPath:(NSString *)path
          toDestination:(NSString *)destination
               uniqueId:(NSString *)uniqueId;

+ (BOOL)unzipFileAtPath:(NSString *)path
          toDestination:(NSString *)destination
              overwrite:(BOOL)overwrite
               password:(NSString *)password
                  error:(NSError **)error
               uniqueId:(NSString *)uniqueId;

+ (BOOL)unzipFileAtPath:(NSString *)path
          toDestination:(NSString *)destination
               delegate:(id<DBYZipArchiveDelegate>)delegate
               uniqueId:(NSString *)uniqueId;

+ (BOOL)unzipFileAtPath:(NSString *)path
          toDestination:(NSString *)destination
              overwrite:(BOOL)overwrite
               password:(NSString *)password
                  error:(NSError **)error
               delegate:(id<DBYZipArchiveDelegate>)delegate
               uniqueId:(NSString *)uniqueId;

// Zip
+ (BOOL)createZipFileAtPath:(NSString *)path
           withFilesAtPaths:(NSArray *)filenames;
+ (BOOL)createZipFileAtPath:(NSString *)path
    withContentsOfDirectory:(NSString *)directoryPath;

- (id)initWithPath:(NSString *)path;
- (BOOL)open;
- (BOOL)writeFile:(NSString *)path;
- (BOOL)writeData:(NSData *)data filename:(NSString *)filename;
- (BOOL)close;

@end


@protocol DBYZipArchiveDelegate <NSObject>

@optional

- (void)zipArchiveWillUnzipArchiveAtPath:(NSString *)path
                                 zipInfo:(unz_global_info)zipInfo;

- (void)zipArchiveDidUnzipArchiveAtPath:(NSString *)path
                                zipInfo:(unz_global_info)zipInfo
                           unzippedPath:(NSString *)unzippedPat
                               uniqueId:(NSString *)uniqueId;

- (void)zipArchiveWillUnzipFileAtIndex:(NSInteger)fileIndex
                            totalFiles:(NSInteger)totalFiles
                           archivePath:(NSString *)archivePath
                              fileInfo:(unz_file_info)fileInfo;

- (void)zipArchiveDidUnzipFileAtIndex:(NSInteger)fileIndex
                           totalFiles:(NSInteger)totalFiles
                          archivePath:(NSString *)archivePath
                             fileInfo:(unz_file_info)fileInfo;

@end

NS_ASSUME_NONNULL_END
