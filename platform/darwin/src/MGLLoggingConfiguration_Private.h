#import "MGLLoggingConfiguration.h"

#define mgl_log_info(message, ...)  mgl_log_with_type(MGLLoggingLevelInfo, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define mgl_log_debug(message, ...) mgl_log_with_type(MGLLoggingLevelDebug, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define mgl_log_error(message, ...) mgl_log_with_type(MGLLoggingLevelError, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define mgl_log_fault(message, ...) mgl_log_with_type(MGLLoggingLevelFault, __PRETTY_FUNCTION__, __LINE__, message, ##__VA_ARGS__)
#define mgl_log_with_type(type, function, line, message, ...) \
{ \
    if ([MGLLoggingConfiguration sharedConfiguration].loggingLevel != MGLLoggingLevelNone && type <= [MGLLoggingConfiguration sharedConfiguration].loggingLevel) \
    { \
        NSString *fmt = [NSString stringWithFormat:(message), ##__VA_ARGS__];  \
        [[MGLLoggingConfiguration sharedConfiguration] logMessageFormat:fmt callingFunction:function functionLine:line messageType:type]; \
    } \
}

@interface MGLLoggingConfiguration (Private)

- (void)logMessageFormat:(NSString *)fmt callingFunction:(const char *)callingFunction functionLine:(NSUInteger)functionLine messageType:(MGLLoggingLevel)type;

@end
