#include "com_example_XLog.h"
#ifdef __ANDROID__
#include <android/log.h>
#endif
#include "log/MarsLog.h"
#include "log/BaseLog.h"
/*
* Class:     com_sinosun_mstplib2_log_MLog
* Method:    nativeInit
* Signature: (Ljava/lang/String;II)V
*/
JNIEXPORT void JNICALL Java_com_example_XLog_nativeInitLog
(JNIEnv *env, jclass, jstring jpath, jint mode, jint level) {
    const char* cpath = env->GetStringUTFChars(jpath, NULL); 
    init_mstp_log(cpath, (LogSyncMode)mode, (LogLevel)level);
    env->ReleaseStringUTFChars(jpath, cpath);
}

/*
* Class:     com_sinosun_mstplib2_log_MLog
* Method:    nativeClose
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_com_example_XLog_nativeCloseLog
(JNIEnv *, jclass) {
    close_mstp_log();
}

/*
* Class:     com_sinosun_mstplib2_log_MLog
* Method:    nativelog
* Signature: (ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;)V
*/
JNIEXPORT void JNICALL Java_com_example_XLog_nativelog
(JNIEnv *env, jclass, jint jlevel, jstring jtag, jstring jfilename, jstring jclassname, jstring jfunname, jint jline, jstring jmsg) {
    const char* ctag = env->GetStringUTFChars(jtag, NULL);
    const char* cfilename = env->GetStringUTFChars(jfilename, NULL);
    const char* cclassname = env->GetStringUTFChars(jclassname, NULL);
    const char* cfunname = env->GetStringUTFChars(jfunname, NULL);
    const char* cmsg = env->GetStringUTFChars(jmsg, NULL);
    print_mstp_log(jlevel, ctag, cfilename, cclassname, cfunname, jline, "%s", cmsg);
    env->ReleaseStringUTFChars(jtag, ctag);
    env->ReleaseStringUTFChars(jfilename, cfilename);
    env->ReleaseStringUTFChars(jclassname, cclassname);
    env->ReleaseStringUTFChars(jfunname, cfunname);
    env->ReleaseStringUTFChars(jmsg, cmsg);
}

/*
* Class:     com_sinosun_mstplib2_log_MLog
* Method:    nativeFlush
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_com_example_XLog_nativeFlushLog
(JNIEnv *, jclass) {
    flush_mstp_log();
}

/*
* Class:     com_sinosun_mstplib2_log_MLog
* Method:    nativeSetStdOutLogLevel
* Signature: (Ljava/lang/Boolean;)V
*/
JNIEXPORT void JNICALL Java_com_example_XLog_nativeSwitchStdOut
(JNIEnv *, jclass, jboolean jenable) {
    enable_console_log(jenable == JNI_TRUE);
}