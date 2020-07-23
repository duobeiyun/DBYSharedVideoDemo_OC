# 多贝云 SaaS SDK iOS 离线回放 API 参考文档
## 下载模块
### DBYDownloadDataManager
下载数据管理
```objc
/// 添加数据
- (void)appendDownloadModel:(DBYDownloadModel *)model;
/// 删除数据
- (void)removeDownloadModel:(DBYDownloadModel *)model;
/// 更新数据
- (void)updateDownloadModel:(DBYDownloadModel *)model;
/// 查找数据
- (DBYDownloadModel *)getDownloadModelWithUniqueId:(NSString *)uniqueId;

/// 获取所有数据
- (NSArray<DBYDownloadModel *> *)getAllDownloadModel;
/// 获取下载列表（包括下载中、暂停、等待下载）
- (NSArray<DBYDownloadModel *> *)getDownloadList;
/// 获取所有正在下载的数据
- (NSArray<DBYDownloadModel *> *)getAllDownloadingModel;
/// 获取所有下载完成的数据
- (NSArray<DBYDownloadModel *> *)getAllDownloadedModel;
/// 获取所有暂停的数据
- (NSArray<DBYDownloadModel *> *)getAllPausedModel;
/// 获取所有等待下载的数据
- (NSArray<DBYDownloadModel *> *)getAllWaitingModel;
```
### DBYDownloadTaskManager
下载任务管理
```objc
- (void)startDownloadWithModel:(DBYDownloadModel *)model;
- (void)pauseDownloadWithModel:(DBYDownloadModel *)model;
- (void)cancelDownloadWithModel:(DBYDownloadModel *)model;

//暂停所有下载任务
- (void)pauseAllDownloadTask;
```

## 进入教室
```objc
DBYOfflineController *vc = [[DBYOfflineController alloc] init];
vc.title = item.title;
vc.roomID = item.roomId;
vc.classFilePath = [DBYClient getLessonFilePathWith:item.roomId];
vc.offlineKey = item.secret;
[self.navigationController pushViewController:vc animated:YES];
```
