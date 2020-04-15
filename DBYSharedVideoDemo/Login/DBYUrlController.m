//
//  DBYUrlController.m
//  DBYSharedVideoDemo
//
//  Created by 钟凡 on 2020/2/25.
//  Copyright © 2020 duobei. All rights reserved.
//

#import <DBYSharedVideo/DBYSharedVideo-umbrella.h>
#import <DBYSDK_dylib/DBYSDK.h>
#import "DBYUrlController.h"
#import "DBYString.h"
#import "DBYRoomStateController.h"

@interface DBYUrlController ()

@property (nonatomic, copy) NSString *authinfoString;
@property (nonatomic, copy) NSString *roomid;
@property (nonatomic, assign) BOOL isLoadding;
@property (nonatomic, weak) UIActivityIndicatorView *indicator;

@property (weak, nonatomic) IBOutlet UIView *topView;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *marginTop;
@property (weak, nonatomic) IBOutlet UIButton *goBackBtn;
@end

@implementation DBYUrlController
- (IBAction)goback:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}
- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskLandscape;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    [_topView addSubview:_indicator];
    
    if (_isLoadding) {
        [[DBYGlobalMessage shared] showText:DBYString.loadding];
        return;
    }
    if (_urlString != nil) {
        [self getAuthInfoWithUrl:_urlString];
    }
    //刘海屏
    if (self.view.bounds.size.height > 736) {
        _marginTop.constant = 44 + 8;
    }
}
- (void)viewWillLayoutSubviews {
    _indicator.center = _topView.center;
}
- (void)viewWillAppear:(BOOL)animated {
    [_indicator startAnimating];
    [self.navigationController setNavigationBarHidden:YES];
}
- (void)viewWillDisappear:(BOOL)animated {
    [_indicator stopAnimating];
}
- (void)getAuthInfoWithUrl:(NSString *)url {
    _isLoadding = YES;
    if (_urlString == nil) {
        [self showErrorMessage:DBYString.urlError withTitle:DBYString.localError];
        return;
    }
    NSURLComponents *components = [[NSURLComponents alloc] initWithString:url];
    NSString *query = components.percentEncodedQuery;
    
    if (query == nil) {
        [self showErrorMessage:DBYString.urlError withTitle:DBYString.localError];
        return;
    }
    NSString *authinfoUrl = [[NSString alloc] initWithFormat: @"%@?%@", [[DBYUrlConfig sharedConfig] authinfoUrlV4], query];
    [DBYAuthInfoUtil authInfoWithUrl:authinfoUrl successHandler:^(DBYAuthInfo *authinfo) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self enterRoomWithAuthinfo:authinfo];
        });
    } failHandler:^(NSError *error) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self showErrorMessage:DBYString.netWorkError withTitle:DBYString.localError];
        });
    }];
}
- (void)enterRoomWithAuthinfo:(DBYAuthInfo *)authInfo {
    [_indicator stopAnimating];
    if (authInfo == nil) {
        [self showErrorMessage:DBYString.authInfoParseError withTitle:DBYString.serverError];
        return;
    }
    if (authInfo.roomID == nil) {
        [self showErrorMessage:DBYString.authInfoError withTitle:DBYString.serverError];
        return;
    }
    if (authInfo.courseStatus != DBYCourseStatusLiving && authInfo.courseStatus != DBYCourseStatusCanPlayback) {
        [self enterStatePage:authInfo];
        return;
    }
    if (authInfo.classType != DBYClassTypeSharedVideo) {
        [self showErrorMessage:DBYString.classTypeError withTitle:DBYString.localError];
        return;
    }
    if (authInfo.userRole != 2) {
        [self showErrorMessage:DBYString.roleError withTitle:DBYString.localError];
        return;
    }
    if (authInfo.courseStatus == DBYCourseStatusLiving) {
        [self enterLive:authInfo];
        return;
    }
    if (authInfo.courseStatus == DBYCourseStatusCanPlayback) {
        [self enterOnline:authInfo];
        return;
    }
}
- (void)enterStatePage:(DBYAuthInfo *)authInfo {
    NSString *tipTitle = @"";
    NSString * tipMessage = @"";
    switch (authInfo.courseStatus) {
        case DBYCourseStatusPlaybackEmpty:
            tipTitle = @"空录像";
            tipMessage = @"这节课没有上课\n请换一节课再来吧";
            break;
        case DBYCourseStatusBeforePlayback:
            tipTitle = @"回放转换中，请稍后查看";
            tipMessage = @"错过了直播课程？\n你可以等待稍后生成的直播回放";
            break;
        case DBYCourseStatusNoPlayback:
            tipTitle = @"回放转换失败";
            tipMessage = @"课程回放转换失败\n我们会积极安排重新转换\n请您耐心等待";
            break;
        case DBYCourseStatusBeforeLive:
            tipTitle = @"课程尚未开始哦";
            tipMessage = @"距离课程开始还有";
            break;
        default:
            tipTitle = @"其他错误";
            tipMessage = @"我们正在积极处理问题\n请您耐心等候";
            break;
    }
    [self showErrorMessage:tipMessage withTitle:tipTitle];
}
- (void)enterLive:(DBYAuthInfo *)authInfo {
    DBYLiveController *liveVC = [[DBYLiveController alloc] init];
    liveVC.authinfo = authInfo;
    
    [self.view addSubview: liveVC.view];
    [self addChildViewController:liveVC];
}
- (void)enterOnline:(DBYAuthInfo *)authInfo {
    DBYOnlineController *onlineVC = [[DBYOnlineController alloc] init];
    onlineVC.authinfo = authInfo;
    
    [self.view addSubview: onlineVC.view];
    [self addChildViewController:onlineVC];
}
- (void)showErrorMessage:(NSString *)message withTitle:(NSString *)title {
    DBYRoomStateController *roomVC = [[DBYRoomStateController alloc] initWithNibName:nil];
    roomVC.tipTitle = title;
    roomVC.tipMessage = message;
    
    [self.view addSubview: roomVC.view];
    [self addChildViewController:roomVC];
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
