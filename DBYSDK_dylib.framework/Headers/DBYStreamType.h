//
//  DBYStreamType.h
//  DBYSDK_dylib
//
//  Created by duobei on 2019/1/26.
//  Copyright © 2019年 duobei. All rights reserved.
//

#ifndef DBYStreamType_h
#define DBYStreamType_h

typedef enum : NSUInteger {
    DBYNetworkQualityUnknown = 0,    // 未知
    DBYNetworkQualityExcellent = 1,  // 极好
    DBYNetworkQualityGood = 2,
    DBYNetworkQualityPoor = 3,
    DBYNetworkQualityBad = 4,
    DBYNetworkQualityVBad = 5,
    DBYNetworkQualityDown = 6, //断网
} DBYNetworkQuality;

#endif /* DBYStreamType_h */
