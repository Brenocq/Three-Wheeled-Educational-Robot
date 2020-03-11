package com.brenocq.threewheelapp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        move1.setOnClickListener {
            webview.loadUrl("http://192.168.4.2/motor1")
        }
        move2.setOnClickListener {
            webview.loadUrl("http://192.168.4.2/motor2")
        }
        move3.setOnClickListener {
            webview.loadUrl("http://192.168.4.2/motor3")
        }
        move4.setOnClickListener {
            webview.loadUrl("http://192.168.4.2/motor4")
        }
        move5.setOnClickListener {
            webview.loadUrl("http://192.168.4.2/motor5")
        }
        move6.setOnClickListener {
            webview.loadUrl("http://192.168.4.2/motor6")
        }

        para.setOnClickListener {
            webview.loadUrl("http://192.168.4.2/stop")
        }

        robotFace.setOnClickListener {
            webview.loadUrl("http://192.168.4.2/servo")
        }
    }
}
