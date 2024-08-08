//
//  HZModuleManager.h
//  HZAnalyticsSDK
//
//  Created by 闫博 on 2024/5/14.
//

#import <Foundation/Foundation.h>
#import <HZAnalyticsSDK/HZConfigOptions.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface HZAnalyticsSDKManager : NSObject

+ (instancetype)sharedInstance;;

/**启动生成的 uuid,**/
@property(nonatomic,copy)NSString *sessionUUID;

/**appkey,**/
@property(nonatomic,copy)NSString *appKey;

/**secretKey,**/
@property(nonatomic,copy)NSString *secretKey;

/**
 可以上传事件的名称集成
 */
@property(nonatomic,strong)NSMutableArray *eventArrayM;

/***/
- (void)startWithOptions:(HZConfigOptions *)configOptions appId:(NSString *)appId secretKey:(NSString *)secretKey;

/**
 * @abstract
 * 设置用户的单个 Profile 的内容
 *
 * @discussion
 * 如果这个 Profile 之前已经存在了，则这次会被覆盖掉；不存在，则会创建
 *
 * @param profile Profile 的名称
 * @param content Profile 的内容
 */
- (void)set:(NSString *) profile to:(id)content;

/**
 * @abstract
 * 首次设置用户的单个 Profile 的内容
 *
 * @discussion
 * 与 set 类接口不同的是，如果这个 Profile 之前已经存在了，则这次会被忽略；不存在，则会创建
 *
 * @param profile Profile 的名称
 * @param content Profile 的内容
 */
- (void)setOnce:(NSString *) profile to:(id)content;

/**
 * @abstract
 * 给一个数值类型的 Profile 增加一个数值
 *
 * @discussion
 * 只能对 NSNumber 类型的 Profile 调用这个接口，否则会被忽略
 * 如果这个 Profile 之前不存在，则初始值当做 0 来处理
 *
 * @param profile  待增加数值的 Profile 的名称
 * @param amount   要增加的数值
 */
- (void)increment:(NSString *)profile by:(NSNumber *)amount;

/**
 * @abstract
 * 删除某个 Profile 的全部内容
 *
 * @discussion
 * 如果这个 Profile 之前不存在，则直接忽略
 *
 * @param profile Profile 的名称
 */
- (void)unset:(NSString *) profile;

#pragma mark 埋点自定义
/**
 * @abstract
 * 调用 track 接口，追踪一个带有属性的 event
 *
 * @discussion
 * propertyDict 是一个 Map。
 * 其中的 key 是 Property 的名称，必须是 NSString
 * value 则是 Property 的内容，只支持 NSString、NSNumber、NSSet、NSArray、NSDate 这些类型
 * 特别的，NSSet 或者 NSArray 类型的 value 中目前只支持其中的元素是 NSString
 *
 * @param event             event的名称
 * @param propertyDict     event的属性
 */
- (void)track:(NSString *)event withProperties:(nullable NSDictionary *)propertyDict;

#pragma mark - trackTimer
/**
 开始事件计时

 @discussion
 若需要统计某个事件的持续时间，先在事件开始时调用 trackTimerStart:"Event" 记录事件开始时间，该方法并不会真正发送事件；
 随后在事件结束时，调用 trackTimerEnd:"Event" withProperties:properties，
 SDK 会追踪 "Event" 事件，并自动将事件持续时间记录在事件属性 "event_duration" 中，时间单位为秒。

 @param event 事件名称
 @return 返回计时事件的 eventId，用于交叉计时场景。普通计时可忽略
 */
- (nullable NSString *)trackTimerStart:(NSString *)event;

/**
 暂停事件计时

 @discussion
 多次调用 trackTimerPause: 时，以首次调用为准。

 @param event 事件名称或事件的 eventId
 */
- (void)trackTimerPause:(NSString *)event;

/**
 恢复事件计时

 @discussion
 多次调用 trackTimerResume: 时，以首次调用为准。

 @param event 事件名称或事件的 eventId
 */
- (void)trackTimerResume:(NSString *)event;

/**
 结束事件计时

 @discussion
 多次调用 trackTimerEnd: 时，以首次调用为准

 @param event 事件名称或事件的 eventId
 */
- (void)trackTimerEnd:(NSString *)event;

/**
 * @abstract
 * 强制试图把数据传到对应的 SensorsAnalytics 服务器上
 *
 * @discussion
 * 主动调用 flush 接口，则不论 flushInterval 和 flushBulkSize 限制条件是否满足，都尝试向服务器上传一次数据
 */
- (void)flush;

/**
 * @abstract
 * 删除本地缓存的全部事件
 *
 * @discussion
 * 一旦调用该接口，将会删除本地缓存的全部事件，请慎用！
 */
- (void)deleteAll;

/**
 忽略页面的浏览事件
 */
- (void)ignoreAppViewScreenOnViewControllers:(NSArray<Class>*)viewControllers;

//忽略某些页面的点击事件
- (void)ignoreAppClickOnViewControllers:(NSArray<Class>*)viewControllers;

/**
 * @abstract
 * 位置信息采集功能开关
 *
 * @discussion
 * 根据需要决定是否开启位置采集
 * 默认关闭
 *Location not supported for iOS extensions.
 * @param enable YES/NO
 */
- (void)enableTrackGPSLocation:(BOOL)enable;

/**
 * @abstract
 * 登录，设置当前用户的 loginId
 *
 * @param loginId 当前用户的 loginId
 */
- (void)login:(NSString *)loginId;

/**
 @abstract
 ID-Mapping 3.0 功能下绑定业务 ID 功能

 @param key 绑定业务 ID 的键名
 @param value 绑定业务 ID 的键值
 */
- (void)bind:(NSString *)key value:(NSString *)value;

/**
 @abstract
 ID-Mapping 3.0 功能下解绑业务 ID 功能

 @param key 解绑业务 ID 的键名
 @param value 解绑业务 ID 的键值
 */
- (void)unbind:(NSString *)key value:(NSString *)value;

/**生成一个随机的UUID（通用唯一标识符,不带-）**/
-(NSString *)generateUUID;

/// 获取上传事件
/// - Parameter completion: 回调
-(void)obtainUploadEventCompletion:(void(^)(void))completion;

// AES 加密函数
NSData* aesEncrypt(NSData *data, NSData *keyData, NSData *ivData);

// AES 解密函数
NSData *aesDecrypt(NSData *data, NSData *keyData,NSData *ivData);

- (void)setServerUrl:(NSString *)serverUrl;

/**
 * @abstract
 * 通过代码触发 UIView 的 $AppClick 事件
 *
 * @param view UIView
 * @param properties 自定义属性
 */
- (void)trackViewAppClick:(nonnull UIView *)view withProperties:(nullable NSDictionary *)properties;

/**
 * @abstract
 * 通过代码触发 UIViewController 的 $AppViewScreen 事件
 *
 * @param viewController 当前的 UIViewController
 */
- (void)trackViewScreen:(UIViewController *)viewController;
- (void)trackViewScreen:(UIViewController *)viewController properties:(nullable NSDictionary<NSString *,id> *)properties;

/**
 * @abstract
 * Track $AppViewScreen事件
 *
 * @param url 当前页面url
 * @param properties 用户扩展属性
 */
- (void)trackViewScreen:(NSString *)url withProperties:(NSDictionary *)properties;

/**
 * @abstract
 * 是否开启 AutoTrack
 *
 * @return YES: 开启 AutoTrack; NO: 关闭 AutoTrack
 */
- (BOOL)isAutoTrackEnabled;


@end

NS_ASSUME_NONNULL_END
