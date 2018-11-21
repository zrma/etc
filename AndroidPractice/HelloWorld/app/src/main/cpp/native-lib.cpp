#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_team504_zrma_helloworld_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    auto hello = "Hello from C++";
    return env->NewStringUTF(hello);
}
