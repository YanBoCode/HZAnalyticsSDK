//
//  HZConfigOptions.h
//  HZAnalyticsSDK
//
//  Created by 闫博 on 2024/5/14.
//

#import <Foundation/Foundation.h>

typedef NS_OPTIONS(NSInteger, HZAnalyticsAutoTrackEventType) {
    HZAnalyticsEventTypeNone      = 0,
    HZAnalyticsEventTypeAppStart      = 1 << 0,
    HZAnalyticsEventTypeAppEnd        = 1 << 1,
    HZAnalyticsEventTypeAppClick      = 1 << 2,
    HZAnalyticsEventTypeAppViewScreen = 1 << 3,
};

NS_ASSUME_NONNULL_BEGIN

@interface HZConfigOptions : NSObject


@property (nonatomic ,strong)NSDictionary *launchOptions;
/**
 指定初始化方法，设置 serverURL
 @param serverURL 数据接收地址
 @return 配置对象
 */
- (instancetype)initWithServerURL:(nonnull NSString *)serverURL
                    launchOptions:(nullable id)launchOptions NS_DESIGNATED_INITIALIZER;


/**
 * @property
 *
 * @abstract
 * 两次数据发送的最小时间间隔，单位毫秒
 *
 * @discussion
 * 默认值为 15 * 1000 毫秒， 在每次调用 track 和 profileSet 等接口的时候，
 * 都会检查如下条件，以判断是否向服务器上传数据:
 * 1. 是否 WIFI/3G/4G/5G 网络
 * 2. 是否满足以下数据发送条件之一:
 *   1) 与上次发送的时间间隔是否大于 flushInterval
 *   2) 本地缓存日志数目是否超过 flushBulkSize
 * 如果满足这两个条件之一，则向服务器发送一次数据；如果都不满足，则把数据加入到队列中，等待下次检查时把整个队列的内容一并发送。
 * 需要注意的是，为了避免占用过多存储，队列最多只缓存10000条数据。
 */
@property (nonatomic) NSInteger flushInterval;

/**
 * @property
 *
 * @abstract
 * 本地缓存的最大事件数目，当累积日志量超过阈值时发送数据
 *
 * @discussion
 * 默认值为 100，在每次调用 track 和 profileSet 等接口的时候，都会检查如下条件，以判断是否向服务器上传数据:
 * 1. 是否 WIFI/3G/4G/5G 网络
 * 2. 是否满足以下数据发送条件之一:
 *   1) 与上次发送的时间间隔是否大于 flushInterval
 *   2) 本地缓存日志数目是否超过 flushBulkSize
 * 如果同时满足这两个条件，则向服务器发送一次数据；如果不满足，则把数据加入到队列中，等待下次检查时把整个队列的内容一并发送。
 * 需要注意的是，为了避免占用过多存储，队列最多只缓存 10000 条数据。
 */
@property (nonatomic) NSInteger flushBulkSize;

/// 设置本地缓存最多事件条数，默认为 10000 条事件
@property (nonatomic) NSInteger maxCacheSize;

/// 开启 log 打印
@property (nonatomic, assign) BOOL enableLog;

/// 是否禁用采集 deviceId
@property (nonatomic, assign) BOOL disableDeviceId;

/// 数据接收地址 serverURL
@property(atomic, copy) NSString *serverURL;

///开启自动采集页面浏览时长
@property (nonatomic, assign) BOOL enableTrackPageLeave;

/// 是否自动采集子页面的页面浏览事件
///
/// 开启页面浏览事件采集时，有效。默认为不采集
@property (nonatomic,assign) BOOL enableAutoTrackChildViewScreen;
//开启推送点击事件自动采集
@property (nonatomic, assign) BOOL enableTrackPush;
/**
 * @property
 *
 * @abstract
 * 打开 SDK 自动追踪,默认只追踪 App 启动 / 关闭、进入页面、元素点击
 *
 * @discussion
 * 该功能自动追踪 App 的一些行为，例如 SDK 初始化、App 启动 / 关闭、进入页面 等等，
 * 该功能默认关闭
 */
@property (nonatomic) HZAnalyticsAutoTrackEventType autoTrackEventType;
//开启 Crash 信息的自动采集
@property (nonatomic, assign) BOOL enableTrackAppCrash;

/// 开启可视化全埋点
@property (nonatomic, assign) BOOL enableVisualizedAutoTrack API_UNAVAILABLE(macos) NS_EXTENSION_UNAVAILABLE("VisualizedAutoTrack not supported for iOS extensions.");

/// 开启可视化全埋点自定义属性
///
/// 开启后，SDK 会默认开启可视化全埋点功能
@property (nonatomic, assign) BOOL enableVisualizedProperties API_UNAVAILABLE(macos) NS_EXTENSION_UNAVAILABLE("VisualizedAutoTrack not supported for iOS extensions.");

/// 是否开启 WKWebView 的 H5 打通功能，该功能默认是关闭的
@property (nonatomic) BOOL enableJavaScriptBridge;

@end

NS_ASSUME_NONNULL_END
