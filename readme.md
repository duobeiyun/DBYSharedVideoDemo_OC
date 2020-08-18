## Requirements

- iOS 8.0+
- Xcode 10.2+
- Swift 5+
## Installation

### CocoaPods

[CocoaPods](https://cocoapods.org) 是iOS的一个依赖管理工具。使用它我们可以很方便的集成sdk, 在你的 `Podfile` 中添加这些配置:

```ruby
#你下载SDK解压后的相对路径
pod 'DBYSDK_dylib', :path => './DBYSDK_dylib.podspec'
pod 'DBYSharedVideo', :path => './DBYSharedVideo.podspec'
```
### Manually

如果你之前没有使用过依赖管理工具，你也可以手动添加这些framework到你的项目中。

#### Embedded Framework
- 在我们的[官网](http://docs.duobeiyun.com/ios)下载SDK然后解压。
- 选中你的项目在Xcode的导航栏中，然后在"Targets"选中你的target然后在上面的导航栏中选中"Build Phases"。
- 展开"Link Binary with Libraries"。
- 点击 `+` 按钮 添加 `DBYSDK_dylib.framework` 和 `DBYSharedVideo.framework`

## 使用
### demo运行
在有`podfile`的目录下，打开命令行，执行`pod install`。然后打开DBYSharedVideoDemo.xcworkspace。

### 环境切换
由于我们的之前的业务在com环境上，现在有一部分新的业务在net环境。所以提供这个接口供切换。
```objc
//切换到net
[DBYClient setDomainType:DBYDomainTypeNet];
//切换到com
[DBYClient setDomainType:DBYDomainTypeCom];
```
注意：需要在进入教室之前使用

### 1v1直播场景
```objc
- (void)clientOnline:(DBYLiveManager *)liveManager userId:(NSString *)uid nickName:(NSString *)nickName userRole:(int)role {
    if (![uid isEqualToString:self.userId]) {
        return;
    }
    //1v1场景需要在上线后开启摄像头，或者根据自己业务需求来
    [liveManager openMic:YES completeHandler:^(NSString *failMsg) {
        NSLog(@"openMic:%@", failMsg);
    }];
    [liveManager openCam:YES completeHandler:^(NSString *failMsg) {
        NSLog(@"openCam:%@", failMsg);
    }];
}
```
### url进教室

swift
```swift
let urlVC = DBYUrlController()
urlVC.urlString = "https://api.duobeiyun.com/api/v4/room/authinfo..."
urlVC.view.backgroundColor = UIColor.white
navigationController?.pushViewController(urlVC, animated: true)
```
objectivec
```objectivec
DBYUrlController *urlVC = [[DBYUrlController alloc] init]; 
urlVC.urlString = @"https://api.duobeiyun.com/api/v4/room/authinfo...";
urlVC.view.backgroundColor = UIColor.whiteColor
[self.navigationController pushViewController:urlVC animated:NO];
```
### 邀请码进教室

swift
```swift
let inviteVC = DBYInviteCodeController()
navigationController?.pushViewController(inviteVC, animated: true)
```
objectivec
```objectivec
let inviteVC = DBYInviteCodeController()
navigationController?.pushViewController(inviteVC, animated: true)
DBYInviteCodeController *inviteVC = [[DBYInviteCodeController alloc] init];
[self.navigationController pushViewController:inviteVC animated:NO];
```

### 离线缓存课程

离线缓存课程需要根据roomid获取下载链接，下载zip文件后，解压缩至app沙盒，播放时将课程文件夹路径、播放解密秘钥、课程对应的roomid传入离线回放控制器中，即可播放。

获取链接
swift
```swift
let downloadurl = DBYClient.lessonDownloadUrl(withRoomId: roomID, hasVideo: false)
```
objectivec
```objectivec
NSString *url = [DBYClient lessonDownloadUrlWithRoomId:cell.roomID hasVideo:NO];
```

下载并解压缩之后，创建离线回放控制器，并设置相关参数

swift
```swift
let vc = DBYOfflineController()
//设置播放课程的roomID
vc.roomID = roomID
//本地下载并解压缩后的课程路径
vc.classFilePath = path
//离线缓存解密秘钥
vc.offlineKey = offlineKey
navigationController?.pushViewController(vc, animated: true)
```
objectivec
```objectivec
DBYOfflineController*vc = [[DBYOfflineController alloc] init];
//设置播放课程的roomID
vc.roomID = roomID;
//本地下载并解压缩后的课程路径
vc.classFilePath = path;
//离线缓存解密秘钥
vc.offlineKey = offlineKey;
[self.navigationController pushViewController:vc animated:YES];
```

### 直播文档
[直播文档](./docs/live.md)
### 在线回放文档
[在线回放文档](./docs/onlinePlayback.md)
### 离线回放文档
[离线回放文档](./docs/offlinePlayback.md)

## FAQ

### DBYSharedVideo.framework/DBYSharedVideo image not found?
这个库是swift项目开发的，如果手动连接framework的时候需要在项目中新建一个swift文件编译一下（添加一些swift的系统库）。
如果使用cocoapod确保在podfile中添加了`use_frameworks!`。

### 回放进不去？
请在test_courses.json文件中填写正确的信息。

### 新版大班，新在哪？
1、上视频相关功能，新增一些业务消息，需要走对应的回调，保持和pc端的业务一致
2、上麦相关功能，新增一些业务消息，需要走对应的回调，保持和pc端的业务一致
3、问答功能，对聊天信息的问与答
4、点赞功能
6、自定义展示面板，课程介绍和一些其他展示
7、投票部分流程的更改

## 注意事项&更新内容
[注意事项](./update.md)

