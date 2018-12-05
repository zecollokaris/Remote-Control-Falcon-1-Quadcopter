package com.falcondrone.falcon;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import butterknife.BindView;
import butterknife.ButterKnife;
import de.hdodenhof.circleimageview.CircleImageView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    @BindView(R.id.upDirection) CircleImageView mUpDirection;
    @BindView(R.id.downDirection) CircleImageView mDownDirection;
    @BindView(R.id.leftDirection) CircleImageView mLeftDirection;
    @BindView(R.id.rightDirection) CircleImageView mRightDirection;



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
