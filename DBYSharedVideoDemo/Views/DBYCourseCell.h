//
//  DBYCourseCell.h
//  DBYSharedVideoDemo
//
//  Created by 钟凡 on 2020/2/25.
//  Copyright © 2020 duobei. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface DBYCourseCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UILabel *nameLab;
@property (weak, nonatomic) IBOutlet UILabel *timeLab;
@property (weak, nonatomic) IBOutlet UILabel *statusLab;
@property (weak, nonatomic) IBOutlet UIImageView *iconView;
@property (weak, nonatomic) IBOutlet UIButton *oprationBtn;

@property (copy, nonatomic) void (^progressChangeBlock)(float progress, float currentSize, float totalsize);

@end

NS_ASSUME_NONNULL_END
