#
#  Be sure to run `pod spec lint DBY1VNSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|

  s.name         = "DBYSharedVideo"
  s.version      = "2.0.0"
  s.summary      = "新版大班"
  s.description  = <<-DESC
DBYSharedVideo主要是封装了直播和回放的界面，方便开发者快速对接自己的产品。主要特点是快速集成，不支持界面定制。
                   DESC

  s.homepage     = "http://docs.duobeiyun.com"

  s.license      = "MIT"

  s.author       = { "zhongfan" => "fan.zhong@duobei.com" }
  s.source       = { :git => "https://github.com/zhonglaoban/DBYSharedVideo.git", :tag => "#{s.version}" }
  s.vendored_frameworks  = "DBYSharedVideo.framework"
  s.dependency 'SDWebImage', '~> 5.3.3'
  s.dependency 'SnapKit'
end
