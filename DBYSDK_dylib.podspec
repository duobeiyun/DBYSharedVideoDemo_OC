#
#  Be sure to run `pod spec lint DBY1VNSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|

  s.name         = "DBYSDK_dylib"
  s.version      = "2.1.3"
  s.summary      = "多贝云全平台基础sdk"
  s.description  = "多贝云全平台基础sdk"

  s.homepage     = "http://docs.duobeiyun.com"

  s.license      = "MIT"

  s.author       = { "zhongfan" => "fan.zhong@duobei.com" }
  s.source       = { :git => "https://github.com/zhonglaoban/DBYSDK_dylib.git", :tag => "#{s.version}" }
  s.vendored_frameworks  = "DBYSDK_dylib.framework"

end
