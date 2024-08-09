//
// Created by MSI-PC on 2024/8/9.
//
#include "pine.h"

bool pineStart(JNIEnv *env, bool isSystem) {
    auto classLoaderClz = env->FindClass("java/lang/ClassLoader");
    auto getSystemClassLoaderMID = env->GetStaticMethodID(classLoaderClz, "getSystemClassLoader", "()Ljava/lang/ClassLoader;");
    auto sysClassLoader = env->CallStaticObjectMethod(classLoaderClz, getSystemClassLoaderMID);
    if(!sysClassLoader) {
        LOGD("getSystemClassLoader failed!!");
        return false;
    }

    auto pathClassLoaderClz = env->FindClass("dalvik/system/PathClassLoader");
    auto initMID = env->GetMethodID(pathClassLoaderClz, "<init>",
                                    "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/ClassLoader;)V");
    auto modulePath = env->NewStringUTF("/system/app/testpine/testpine.apk");
    jstring libPath = nullptr;
#if defined(__arm__)
    libPath = env->NewStringUTF("/system/app/testpine/lib/armeabi-v7a");
#elif defined(__aarch64__)
    libPath = env->NewStringUTF("/system/app/testpine/lib/arm64-v8a");
#endif
    if(!libPath) {
        LOGD("libPath == null");
    }
    if(auto clzLoader = env->NewObject(pathClassLoaderClz, initMID, modulePath, libPath, sysClassLoader)) {
        jmethodID loadClassMID = env->GetMethodID(pathClassLoaderClz, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
        auto entryClz = static_cast<jclass>(env->CallObjectMethod(clzLoader, loadClassMID, env->NewStringUTF("ng1ok.demo.pinexposed.PineFramework")));
        if(!entryClz) {
            LOGD("entry class not find!");
            return false;
        }

        jmethodID entryClzInitMID = env->GetStaticMethodID(entryClz, "init", "(Z)V");
        if(entryClzInitMID) {
            env->CallStaticVoidMethod(entryClz, entryClzInitMID, isSystem);
            return true;
        }else{
            LOGD("entryClzInitMID is null");
        }



        return false;
    }


}