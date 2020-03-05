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
### 环境切换
由于我们的之前的业务在com环境上，现在有一部分新的业务在net环境。所以提供这个接口供切换。
```objc
//切换到net
[DBYClient setDomainType:DBYDomainTypeNet];
//切换到com
[DBYClient setDomainType:DBYDomainTypeCom];
```
注意：需要在进入教室之前使用

### 直播
[直播文档](./live.md)
### 回放
[回放文档](./playback.md)
## FAQ

### 回放进不去？
请在test_courses.json文件中填写正确的信息。

