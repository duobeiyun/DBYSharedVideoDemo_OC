//
//  DBYCourseListController.m
//  DBYSharedVideoDemo
//
//  Created by 钟凡 on 2017/5/16.
//  Copyright © 2020年 duobei. All rights reserved.
//

#import <DBYSDK_dylib/DBYSDK.h>

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
    //测试数据
    DBYLessonItem *item = self.items[indexPath.row];
    NSString *url = [[DBYUrlConfig sharedConfig] authinfoUrlWithRoomID:item.roomId
                                                              userName:@"学员1650474"
                                                                userID:@"222"
                                                              userRole:2
                                                             partnerID:item.partnerId
                                                                appkey:item.appkey];
    
    DBYUrlController *vc = [[DBYUrlController alloc] init];
    vc.urlString = url;
    [self.navigationController pushViewController:vc animated:YES];
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
