//
//  DBYInviteCodeController.m
//  DBYSharedVideoDemo
//
//  Created by 钟凡 on 2020/2/24.
//  Copyright © 2020 钟凡. All rights reserved.
//

#import "DBYInviteCodeController.h"
#import <DBYSharedVideo/DBYSharedVideo-umbrella.h>
#import <DBYSDK_dylib/DBYSDK_dylib.h>
#import "DBYString.h"
#import "DBYRoomStateController.h"
#import "DBYCourseListController.h"

@interface DBYInviteCodeController ()
@property (weak, nonatomic) IBOutlet UIButton *enterBtn;
@property (weak, nonatomic) IBOutlet UILabel *tipLab;
@property (weak, nonatomic) IBOutlet UITextField *inviteCodeTextField;
@property (weak, nonatomic) IBOutlet UITextField *nickNameTextField;
@property (weak, nonatomic) IBOutlet UIButton *domainBtn;
@property (weak, nonatomic) IBOutlet UIButton *enterRoomBtn;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *indicator;

@property (copy, nonatomic) NSString *identifier;
@property (copy, nonatomic) NSString *roomid;
@property (strong, nonatomic) NSArray<NSString *> *domains;
@property (assign, nonatomic) int domainIndex;
@property (copy, nonatomic) NSString *qrCodeString;
@property (strong, nonatomic) DBYReachability *reachability;

@end

@implementation DBYInviteCodeController

- (IBAction)enterPlayback:(id)sender {
    DBYCourseListController *vc = [[DBYCourseListController alloc] initWithNibName:nil];
    [self.navigationController pushViewController:vc animated:YES];
}
- (IBAction)domainChange:(id)sender {
    _domainIndex += 1;
    if (_domainIndex >= _domains.count) {
        _domainIndex = 0;
    }
    [self switchDomain:_domainIndex];
    NSUserDefaults *standard = [NSUserDefaults standardUserDefaults];
    [standard setObject:@(_domainIndex) forKey:[NSString stringWithFormat:@"%@domainIndex", _indicator]];
    [standard synchronize];
}
- (IBAction)editChanged:(id)sender {
    
}
- (IBAction)enterRoom:(id)sender {
    [self.view endEditing:YES];
    NetworkStatus netStatus = [_reachability currentReachabilityStatus];
    if (netStatus == NotReachable) {
        [self showErrorMessage:@"未检测到可用网络\n可以尝试切换您的网络" withTitle:DBYString.netWorkError];
        return;
    }
    NSString *inviteCode = _inviteCodeTextField.text;
    NSString *nickname = _nickNameTextField.text;
    if (inviteCode.length <= 0) {
        [self showTipMessage:DBYString.noInviteCode];
        return;
    }
    if (nickname.length <= 0) {
        [self showTipMessage:DBYString.noNickname];
        return;
    }
    if ([nickname containsString:@"  "]) {
        [self showTipMessage:DBYString.nicknameError];
        return;
    }
    if (_indicator.isAnimating) {
        [self showTipMessage:DBYString.loadding];
        return;
    }
    
    [_indicator startAnimating];
    [_enterRoomBtn setTitle:@"登录中" forState:UIControlStateNormal];
    
    [DBYAuthInfoUtil authInfoWithInviteCode:inviteCode nickName:nickname successHandler:^(DBYAuthInfo *authinfo) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.indicator stopAnimating];
            [self enterRoomWithAuthinfo:authinfo];
        });
    } failHandler:^(NSError *error) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.indicator stopAnimating];
            [self showErrorMessage:DBYString.netWorkError withTitle:DBYString.localError];
        });
    }];
    NSUserDefaults *standard = [NSUserDefaults standardUserDefaults];
    [standard setObject:inviteCode forKey:[NSString stringWithFormat:@"%@inviteCode", _indicator]];
    [standard setObject:inviteCode forKey:[NSString stringWithFormat:@"%@nickName", _indicator]];
    [standard synchronize];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    _reachability = [DBYReachability reachabilityForInternetConnection];
    _domains = @[@"com", @"net"];
    _identifier = @"DBYSharedVideoDemo";
}
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.view endEditing:YES];
}
- (void)switchDomain:(int)index {
    if (index == 0) {
        [DBYClient setDomainType:DBYDomainTypeCom];
    }else {
        [DBYClient setDomainType:DBYDomainTypeNet];
    }
    NSString *title = _domains[_domainIndex];
    [_domainBtn setTitle:title forState:UIControlStateNormal];
}
- (void)enterRoomWithAuthinfo:(DBYAuthInfo *)authInfo {
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
    
    [self.navigationController pushViewController:liveVC animated:YES];
}
- (void)enterOnline:(DBYAuthInfo *)authInfo {
    DBYOnlineController *onlineVC = [[DBYOnlineController alloc] init];
    onlineVC.authinfo = authInfo;
    
    [self.navigationController pushViewController:onlineVC animated:YES];
}
- (void)showErrorMessage:(NSString *)message withTitle:(NSString *)title {
    DBYRoomStateController *roomVC = [[DBYRoomStateController alloc] initWithNibName:nil];
    roomVC.tipTitle = title;
    roomVC.tipMessage = message;
    
    [self.navigationController pushViewController:roomVC animated:YES];
}
- (void)showTipMessage:(NSString *)message {
    [_tipLab setHighlighted:NO];
    _tipLab.text = message;
}
@end
