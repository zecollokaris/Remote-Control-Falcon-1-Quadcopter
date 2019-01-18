package com.app.falcon;

import android.annotation.SuppressLint;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.AppCompatRadioButton;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.ramotion.fluidslider.FluidSlider;
import io.github.controlwear.virtual.joystick.android.JoystickView;
import kotlin.Unit;
import kotlin.jvm.functions.Function0;
import kotlin.jvm.functions.Function1;


public class MainActivity extends AppCompatActivity  implements  View.OnClickListener{
    static  int throttle,angle,strength;
    JoystickView joystickView;
    Button btnState;
    FluidSlider thrust;
    TextView txtRange;
    TextView txtAngle;
    TextView txtStrength;
    AppCompatRadioButton radAutomatic;
    AppCompatRadioButton radManual;
    boolean state=true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                 if(isNetworkAvailable()){
                     Toast.makeText(MainActivity.this,"Connected",Toast.LENGTH_LONG).show();
                 }else{

                 }
            }
        },5000);
        joystickView=(JoystickView) findViewById(R.id.direction);
        thrust = (FluidSlider) findViewById(R.id.thrust);
        txtRange=(TextView) findViewById(R.id.txtPercentage);
        txtAngle=(TextView) findViewById(R.id.angle);
        txtStrength=(TextView) findViewById(R.id.strength);
        radAutomatic=(AppCompatRadioButton) findViewById(R.id.automatic);
        radManual=(AppCompatRadioButton) findViewById(R.id.manual);
        btnState=(Button) findViewById(R.id.btnState);

        thrust.setEndTrackingListener(new Function0<Unit>() {
            @Override
            public Unit invoke() {
//                String url="";
//                EspConnect espConnect=new EspConnect();
                throttle=Integer.parseInt(txtRange.getText().toString());
//                url=String.format("?%s=%s&%s=%s&%s=%s","throttle",txtRange.getText().toString(),"angle",Integer.toString(angle),"strength",Integer.toString(strength));
//                espConnect.addOn("?throttle=".concat(txtRange.getText().toString()));
//                espConnect.execute();
                return null;
            }
        });
        thrust.setPositionListener(new Function1<Float, Unit>() {
            @Override
            public Unit invoke(Float aFloat) {
                int intData=(int)  Math.round(aFloat*840) +1160;
                txtRange.setText(Integer.toString(intData));
                return null;
            }
        });



        joystickView.setOnMoveListener(new JoystickView.OnMoveListener() {
            @SuppressLint("DefaultLocale")
            @Override
            public void onMove(final int angle, final int strength) {
                MainActivity.angle=angle;
                MainActivity.strength=strength;
                        txtAngle.setText(String.format("%s : %d","Angle",angle));
                        txtStrength.setText(String.format("%s : %d %s","Strength",strength,"%"));
            }
        },1500);
        radManual.setOnClickListener(this);
        radAutomatic.setOnClickListener(this);
        btnState.setOnClickListener(this);

    }



    private boolean isNetworkAvailable() {
        ConnectivityManager connectivityManager
                = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetworkInfo = connectivityManager.getActiveNetworkInfo();
        return activeNetworkInfo != null && activeNetworkInfo.isConnected();
    }

    @Override
    public void onClick(View v) {
        String url="";
       if(v.equals(radAutomatic)){
           Toast.makeText(this,"Release Mode",Toast.LENGTH_LONG).show();
           joystickView.setAutoReCenterButton(true);
       }
       else  if(v.equals(radManual)){


           url=String.format("?%s=%s&%s=%s&%s=%s","throttle",txtRange.getText().toString(),"angle",Integer.toString(angle),"strength",Integer.toString(strength));
           EspConnect espConnect=new EspConnect();
           espConnect.addOn(url);
           espConnect.execute();
           Toast.makeText(this,"Action Sent",Toast.LENGTH_LONG).show();


           joystickView.setAutoReCenterButton(false);
       }
       else if(v.equals(btnState)){
           if(state){
               btnState.setBackgroundColor(getResources().getColor(R.color.red));
               btnState.setText("OFF");
               url=String.format("?%s=%s","status","1");
               EspConnect espConnect=new EspConnect();
               espConnect.addOn(url);
               espConnect.execute();
               Toast.makeText(this,"Off",Toast.LENGTH_SHORT).show();
               state=false;
           }
           else{
               btnState.setBackgroundColor(getResources().getColor(R.color.green));
               btnState.setText("ON");
               url=String.format("?%s=%s&%s=%s&%s=%s&%s=%s","throttle",txtRange.getText().toString(),
                       "angle",Integer.toString(angle),"strength",Integer.toString(strength),"status","0");
               EspConnect espConnect=new EspConnect();
               espConnect.addOn(url);
               espConnect.execute();
               Toast.makeText(this,"On",Toast.LENGTH_SHORT).show();
               state=true;
           }
       }
    }
}
