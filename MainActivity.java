package com.example.grabber2;
import java.io.FileNotFoundException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import android.Manifest;
import android.app.DownloadManager;
import android.content.Context;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import java.io.File;

public class MainActivity extends AppCompatActivity
{
private static final int PERMISSION_STORAGE_CODE = 1000;
    EditText urlField;
    Button download_button;
    String link;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        urlField = findViewById(R.id.EditFieldURL);
        download_button = findViewById(R.id.download_button);
//Click Listener Download button
        urlField.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
             urlField.setText("");
            }
        });

  download_button.setOnClickListener(new View.OnClickListener()
  {
  @Override
  public void onClick(View view) {
   if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
   {
       if (checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_DENIED)
       {
//Permission Denied - Request It:
        String[] permissions = {Manifest.permission.WRITE_EXTERNAL_STORAGE};
//Show Popup For RunTime Permission:
        requestPermissions(permissions, PERMISSION_STORAGE_CODE);
    } else
        { Toast.makeText(MainActivity.this, "Downloading...", Toast.LENGTH_SHORT).show();
           Log.d("YODOG", "WTF$$");
           startDownloading();
       }
   } else
       {
        Toast.makeText(MainActivity.this, "Downloading...", Toast.LENGTH_SHORT).show();
        Log.d("YODOG", "WTF$$");
        startDownloading();
       }
   }
  });
}//End onCreate();
    private void startDownloading()
    {
      link = urlField.getText().toString().trim();
      urlField.setText("");
//Create Download Manager Object To Do the Dirty Work, We Just Pass The URL and Connection Types Allowed For DL
       DownloadManager.Request newRequest = new DownloadManager.Request(Uri.parse(link));
       newRequest.setAllowedNetworkTypes(DownloadManager.Request.NETWORK_WIFI | DownloadManager.Request.NETWORK_MOBILE);
       newRequest.setTitle("Download");
       newRequest.setDescription("Downloading...");
       newRequest.allowScanningByMediaScanner();
       newRequest.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);
//Get Current TimeStamp As Filename
       newRequest.setDestinationInExternalPublicDir(Environment.DIRECTORY_DOWNLOADS, ""+System.currentTimeMillis());
//Download File - Creates DL Manager:
       DownloadManager manageNewRequest = (DownloadManager)getSystemService(Context.DOWNLOAD_SERVICE);
       manageNewRequest.enqueue(newRequest);
    }
@Override
  public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults)
{
   switch (requestCode)
    {
     case PERMISSION_STORAGE_CODE:
     {
      if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
      {
//Great To Make Heart Of Code A Static Method To Isolate Exclusionary Logic
       startDownloading();
       } else
       {
        Toast.makeText(this, "Permission Denied ", Toast.LENGTH_SHORT).show();
       }
     }
    }
  }
}

