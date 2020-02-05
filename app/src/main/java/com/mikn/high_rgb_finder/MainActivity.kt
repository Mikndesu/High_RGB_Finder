package com.mikn.high_rgb_finder

import androidx.appcompat.app.AppCompatActivity

import android.opengl.GLSurfaceView
import android.os.Bundle
import android.widget.TextView

class MainActivity : AppCompatActivity() {

    private var glSurfaceView: GLSurfaceView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        glSurfaceView = GLSurfaceView(this)
        glSurfaceView!!.setEGLContextClientVersion(2)
        glSurfaceView!!.setRenderer(CustomRenderer(applicationContext))
        setContentView(glSurfaceView)
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
}
