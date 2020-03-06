//
//  DBYCourseListController.m
//  DBYSharedVideoDemo
//
//  Created by 钟凡 on 2017/5/16.
//  Copyright © 2020年 duobei. All rights reserved.
//

#import <DBYSDK_dylib/DBYSDK.h>
#import <DBYSharedVideo/DBYSharedVideo-umbrella.h>

#import "DBYCourseListController.h"
#import "DBYCourseCell.h"
#import "DBYUrlController.h"

NSString *reuseIdentifier = @"DBYCourseCell";


@interface DBYCourseListController ()<UITableViewDelegate,UITableViewDataSource>

@property(nonatomic, weak) IBOutlet UITableView *tableView;


@property (nonatomic, strong) NSMutableArray<DBYLessonItem *> *items;
@end

@implementation DBYCourseListController
- (IBAction)goback:(id)sender {
    [[DBYDownloadTaskManager sharedInstance] pauseAllDownloadTask];
    [self.navigationController popViewControllerAnimated:YES];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"课程列表";
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    UINib *nib = [UINib nibWithNibName:@"DBYCourseCell" bundle:[NSBundle mainBundle]];
    [_tableView registerNib:nib forCellReuseIdentifier:reuseIdentifier];
    
    _tableView.delegate = self;
    _tableView.dataSource = self;
    
    [self loadItems];
}
-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self.tableView reloadData];
}
- (void)loadItems {
    NSString *path = [[NSBundle mainBundle] pathForResource:@"test_courses" ofType:@"json"];
    NSData *data = [NSData dataWithContentsOfFile:path];
    NSError *error;
    NSArray *array = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
    for (NSDictionary *dict in array) {
        DBYLessonItem *item = [[DBYLessonItem alloc] initWithDictionary:dict];
        [_items addObject:item];
    }
}
#pragma mark - UITableViewDataSource
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.items.count;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    DBYCourseCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseIdentifier];
    if (cell == nil) {
        return [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseIdentifier];
    }
    //测试数据
    DBYLessonItem *item = self.items[indexPath.row];
    
    cell.nameLab.text = item.title;
    cell.timeLab.text = item.time;
    cell.statusLab.text = item.size;
    
    return cell;
}
#pragma mark - UITableViewDelegate
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSAssert(NO, @"请在test_courses.json填写完整课程信息");
    //测试数据
    DBYLessonItem *item = self.items[indexPath.row];
    DBYCourseCell *cell = (DBYCourseCell *)[tableView cellForRowAtIndexPath:indexPath];
    
    if (item.secret.length < 1) {
        NSString *url = [[DBYUrlConfig sharedConfig] authinfoUrlWithRoomID:item.roomId
                                                                  userName:@"学员1650474"
                                                                    userID:@"222"
                                                                  userRole:2
                                                                 partnerID:item.partnerId
                                                                    appkey:item.appkey];
        
        DBYUrlController *vc = [[DBYUrlController alloc] init];
        vc.urlString = url;
        [self.navigationController pushViewController:vc animated:YES];
        return;
    }
    ///下载课程
    NSArray *list = [[DBYDownloadDataManager shareManager] getAllDownloadModel];
    DBYDownloadModel *downloadModel;
    for (DBYDownloadModel *model in list) {
        if ([model.uniqueId isEqualToString:item.roomId]) {
            downloadModel = model;
            break;
        }
    }
    if (downloadModel.state == DBYDownloadStateFinished) {
        DBYOfflineController *vc = [[DBYOfflineController alloc] init];
        vc.title = item.title;
        vc.roomID = item.roomId;
        vc.classFilePath = [DBYClient getLessonFilePathWith:item.roomId];
        vc.offlineKey = item.secret;
        [self.navigationController pushViewController:vc animated:YES];
        return;
    }
    if (downloadModel.state == DBYDownloadStateDownloading) {
        float progress = downloadModel.progress * 100;
        NSString *message = [NSString stringWithFormat:@"%.f%%", progress];
        [[DBYGlobalMessage shared] showText:message];
        return;
    }
    if (downloadModel.state == DBYDownloadStatePaused) {
        //开始下载
        [[DBYDownloadTaskManager sharedInstance] startDownloadWithModel:downloadModel];
        return;
    }
    //新版大班始终是视频课资源类型
    NSString *downloadUrl = [DBYClient lessonDownloadUrlWithRoomId:item.roomId hasVideo:YES];
    downloadModel = [[DBYDownloadModel alloc] init];
    downloadModel.uniqueId = item.roomId;
    downloadModel.fileName = item.title;
    downloadModel.url = downloadUrl;
    //开始下载
    [[DBYDownloadTaskManager sharedInstance] startDownloadWithModel:downloadModel];
    [[DBYGlobalMessage shared] showText:@"开始下载"];
    
    downloadModel.progressChangeBlock = cell.progressChangeBlock;
}

#pragma mark - lazy
- (NSArray<DBYLessonItem *> *)items
{
    if (!_items) {
        NSString *path = [[NSBundle mainBundle] pathForResource:@"test_courses" ofType:@"json"];
        
        NSData *data = [NSData dataWithContentsOfFile:path];
        
        NSArray *items = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:nil];
        
        NSMutableArray *results = @[].mutableCopy;
        for (NSDictionary *dic in items) {
            DBYLessonItem *item = [[DBYLessonItem alloc] initWithDictionary:dic];
            [results addObject:item];
        }
        _items = results;
    }
    return _items;
}
@end
