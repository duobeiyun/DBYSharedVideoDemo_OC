//
//  DBYCourseCell.m
//  DBYSharedVideoDemo
//
//  Created by 钟凡 on 2020/2/25.
//  Copyright © 2020 duobei. All rights reserved.
//

#import "DBYCourseCell.h"

@implementation DBYCourseCell

- (void)awakeFromNib {
    [super awakeFromNib];
    
    __weak typeof(self) weakSelf = self;
    _progressChangeBlock = ^(float progress, float currentSize, float totalsize) {
        printf("%f \n", progress);
    };
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
