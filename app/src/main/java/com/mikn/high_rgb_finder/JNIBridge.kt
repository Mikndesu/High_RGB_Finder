package com.mikn.high_rgb_finder

class JNIBridge {

    external fun onSurfaceCreatedNdk()
    external fun onSurfaceChangedNdk(height :Int, width :Int)
    external fun onDrawFrameNdk()

    companion object {
        init {
            System.loadLibrary("glRenderer")
        }
    }
}