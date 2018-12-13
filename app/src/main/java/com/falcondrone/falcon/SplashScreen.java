package com.falcondrone.falcon;

import android.content.Intent;
import android.graphics.Typeface;
import android.graphics.drawable.AnimationDrawable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;

import butterknife.BindView;
import butterknife.ButterKnife;

public class SplashScreen extends AppCompatActivity implements View.OnClickListener{

    @BindView(R.id.welcomeButton) Button mWelcomeButton;
    @BindView(R.id.splashR_Layout) RelativeLayout mSplashR_Layout;
    @BindView(R.id.logoTextView) TextView mLogoTextView;
    @BindView(R.id.Version) TextView mVersion;
    AnimationDrawable anim;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash_screen);
        ButterKnife.bind(this);

        Typeface stripesFonts = Typeface.createFromAsset(getAssets(), "fonts/Monoton/Monoton-Regular.ttf" );
        mVersion.setTypeface(stripesFonts);
        Typeface blackOpsFonts = Typeface.createFromAsset(getAssets(), "fonts/Black_Ops_One/BlackOpsOne-Regular.ttf");
        mLogoTextView.setTypeface(blackOpsFonts);



//        Animation fadeIn = AnimationUtils.loadAnimation(getApplication(),R.anim.fadein);
//        fadeIn.setDuration(3000);
//        mWelcomeButton.setOnClickListener(this);
//        mWelcomeButton.startAnimation(fadeIn);
//        mLogoTextView.startAnimation(fadeIn);
//        mVersion.startAnimation(fadeIn);

//        anim = (AnimationDrawable) mSplashR_Layout.getBackground();
//        anim.setEnterFadeDuration(2000);
//        anim.setExitFadeDuration(1000);

    }

    @Override
    public void onClick(View v) {
        if (v == mWelcomeButton){
            Intent intent = new Intent(SplashScreen.this, MainActivity.class);
            startActivity(intent);
        }
    }

//    @Override
//    protected void onResume() {
//        super.onResume();
//        if (anim != null && !anim.isRunning())
//            anim.start();
//    }
//
//    @Override
//    protected void onPause() {
//        super.onPause();
//        if (anim != null && anim.isRunning())
//            anim.stop();
//    }
}
