:Pod::Spec.new do |s|
    s.name         = "HZAnalyticsSDK"
    s.version      = "1.0.6"
    s.ios.deployment_target = '11.0'
    s.summary      = "次声波分析 SDK."
    s.homepage     = "https://github.com/YanBoCode/HZAnalyticsSDK/tree/main"
    s.license              = { :type => "MIT", :file => "LICENSE" }
    s.author             = { "小博" => " 1781794316@qq.com" }
    s.source       = { :git => "https://github.com/YanBoCode/HZAnalyticsSDK/tree/main", :tag => s.version }
    #s.source_files  = "HZAnalyticsSDK/*"
    s.resources          = "HZAnalyticsSDK/HZAnalyticsSDK.bundle"
    s.frameworks = 'HZAnalyticsSDK.framework'
    s.vendored_frameworks = 'HZAnalyticsSDK.framework'
    s.requires_arc = false
end

