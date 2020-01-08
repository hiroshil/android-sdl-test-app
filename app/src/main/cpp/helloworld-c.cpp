//
// Created by Patrick Martin on 1/30/19.
//

#include <android_native_app_glue.h>
#include <jni.h>
#include <iostream>
#include <android/log.h>

using namespace std;

extern "C" {
void handle_cmd(android_app *pApp, int32_t cmd) {
}

void android_main(struct android_app *pApp) {
    pApp->onAppCmd = handle_cmd;

    int events;
    android_poll_source *pSource;
    do {
        if (ALooper_pollAll(0, nullptr, &events, (void **) &pSource) >= 0) {
            if (pSource) {
                pSource->process(pApp, pSource);
            }
        }

        __android_log_print(ANDROID_LOG_DEBUG,"Hello Android","HELLO SDL OPENGL ANDROID");
        cout << "Hello World!" << endl;

    } while (!pApp->destroyRequested);
}
}