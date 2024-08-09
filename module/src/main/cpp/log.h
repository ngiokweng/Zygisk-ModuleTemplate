//
// Created by MSI-PC on 2024/8/9.
//

#ifndef ZYGISK_MODULETEMPLATE_LOG_H
#define ZYGISK_MODULETEMPLATE_LOG_H
#include <android/log.h>



#define  TAG    "nglog"

// 定義info信息

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)

// 定義debug信息

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

// 定義error信息

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)


#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG,__VA_ARGS__)
#endif //ZYGISK_MODULETEMPLATE_LOG_H
