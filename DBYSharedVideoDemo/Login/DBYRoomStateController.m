//
//  DBYRoomStateController.m
//  DBYSharedVideoDemo
//
//  Created by 钟凡 on 2020/2/25.
//  Copyright © 2020 钟凡. All rights reserved.
//

#import "DBYRoomStateController.h"
#import <DBYSharedVideo/DBYSharedVideo-umbrella.h>

#import "DBYTheme.h"

@interface DBYRoomStateController ()

@property (weak, nonatomic) IBOutlet UILabel *titleLab;
@property (weak, nonatomic) IBOutlet UILabel *tipLab;
@property (weak, nonatomic) IBOutlet DBYButton *goBackBtn;
@property (weak, nonatomic) IBOutlet DBYButton *reTryBtn;

@end

@implementation DBYRoomStateController
- (IBAction)goBack:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}
- (IBAction)reTry:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}
- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait;
}
- (void)viewWillAppear:(BOOL)animated {
    [self.navigationController setNavigationBarHidden:YES];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    CGFloat radius = _goBackBtn.bounds.size.height * 0.5;
    [_reTryBtn setBackgroudnStyleWithFillColor:DBYTheme.darkColor strokeColor:UIColor.whiteColor radius:radius];
    [_goBackBtn setBackgroudnStyleWithFillColor:UIColor.whiteColor strokeColor:DBYTheme.darkColor radius:radius];
    
    _titleLab.text = _tipTitle;
    _tipLab.text = _tipMessage;
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
