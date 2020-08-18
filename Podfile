project 'DBYSharedVideoDemo.xcodeproj/'
install! 'cocoapods', :disable_input_output_paths => true

# Uncomment the next line to define a global platform for your project
platform :ios, '8.0'

def common_pods
  pod 'Bugly'
  #你下载SDK解压后的相对路径
  pod 'DBYSDK_dylib', :path => './DBYSDK_dylib.podspec'
  pod 'DBYSharedVideo', :path => './DBYSharedVideo.podspec'
end

target 'DBYSharedVideoDemo' do
    # Comment the next line if you're not using Swift and don't want to use dynamic frameworks
    use_frameworks!
    
    common_pods
    
    pod 'SDWebImage'
    pod 'SnapKit'
end
