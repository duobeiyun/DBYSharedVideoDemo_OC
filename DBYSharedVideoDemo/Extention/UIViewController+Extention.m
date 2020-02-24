//
//  UIViewController+Extention.m
//  DBYSharedVideoDemo
//
//  Created by 钟凡 on 2020/2/25.
//  Copyright © 2020 duobei. All rights reserved.
//

#import "UIViewController+Extention.h"

@implementation UIViewController (Extention)
- (instancetype)initWithNibName:(NSString *)name
{
    if (name == nil) {
        name = NSStringFromClass([self class]);
    }
    NSBundle *bundle = [NSBundle mainBundle];
    return [self initWithNibName:name bundle:bundle];
}
@end
