package com.falcondrone.falcon;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import butterknife.BindView;
import butterknife.ButterKnife;
import io.github.controlwear.virtual.joystick.android.JoystickView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    @BindView(R.id.directionJoyStick) JoystickView mDirectionJoyStick;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);


    }

    @Override
    public void onClick(View v) {

    }
}
