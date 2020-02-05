package com.mikn.high_rgb_finder

import android.content.Context
import android.opengl.GLSurfaceView

import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

internal class CustomRenderer : GLSurfaceView.Renderer {

    private var context: Context

    constructor(cont: Context) {
        context = cont
    }

    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        JNIBridge().onSurfaceCreatedNdk()
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        JNIBridge().onSurfaceChangedNdk(width, height)
    }

    override fun onDrawFrame(gl: GL10) {
        JNIBridge().onDrawFrameNdk()
    }
}
