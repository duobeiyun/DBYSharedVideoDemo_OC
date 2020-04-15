//
//  DBYMD5.h
//  DBYSDK_dylib
//
//  Created by 钟凡 on 2019/7/4.
//  Copyright © 2019 duobei. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DBYMD5 : NSObject

+ (NSString *)md5ValueFromString:(NSString*)str;

@end

NS_ASSUME_NONNULL_END
