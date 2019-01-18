package com.app.falcon;

import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class EspConnect extends AsyncTask<Void,Void,String>{
    private static  final String IP_Address="http://192.168.43.104/";
    private String  post;
    public   void addOn(String url){
        post=IP_Address.concat(url);
    }
    @Override
    protected String doInBackground(Void... voids) {
        JsonHttp jsonHttp=new JsonHttp();
        try {
            jsonHttp.setUrl(post);
            Log.d("POST",post);
            jsonHttp.makeRequest();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}
class  JsonHttp{
    private String url=null;
    private URL url_def=null;

    public void setUrl(String url) throws MalformedURLException {
        this.url = url;
    }
    public  String makeRequest()throws MalformedURLException,IOException{
        this.url_def=new URL(this.url);
        HttpURLConnection con=(HttpURLConnection) url_def.openConnection();

        return  readStream(con.getInputStream());
    }

    private static String readStream(InputStream in) {
        BufferedReader reader = null;
        StringBuilder sb = new StringBuilder();

        try{
            reader = new BufferedReader(new InputStreamReader(in));
            String line;

            while((line = reader.readLine()) != null){
                sb.append(line + "\n");
                Log.d("Output",sb.toString());
            }
        }catch (IOException e){
            e.printStackTrace();
        }finally {
            if(reader != null){
                try{
                    reader.close();
                }catch (IOException e){
                    e.printStackTrace();
                }
            }
        }
        return sb.toString();
    }
}