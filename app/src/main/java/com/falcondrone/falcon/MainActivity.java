package com.falcondrone.falcon;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.DragEvent;
import android.view.View;

import com.ramotion.fluidslider.FluidSlider;

import butterknife.BindView;
import butterknife.ButterKnife;
import io.github.controlwear.virtual.joystick.android.JoystickView;

public class MainActivity extends AppCompatActivity implements View.OnDragListener{

    @BindView(R.id.directionJoyStick) JoystickView mDirectionJoyStick;
    @BindView(R.id.fluidslider) FluidSlider mFluidslider;

       @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);


    }

    @Override
    public  void onBackPressed(){
        moveTaskToBack(false);
    }



    @Override
    public boolean onDrag(View v, DragEvent event) {
        return false;
    }
}
