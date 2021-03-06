package com.example.test;

import java.io.File;
import java.io.FileOutputStream;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import com.example.Level;
import com.example.XLog;

public class MainActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        
        String path = Environment.getExternalStorageDirectory().getPath() + "/xlog";
        XLog.init(path, XLog.LOG_MODE_ASYNC, Level.DEBUG);
        
        XLog.info("MainActivity", "test");
        XLog.info("MainActivity", "DeviceType=%d, %s", 333, "heloow"); 
        XLog.error("MainActivity", "test %d", 32);
        XLog.debug("MainActivity", "test %s", "it's debug.");
        
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);       
        return true;
    }

    @Override protected void onDestroy() {
        super.onDestroy();
        XLog.close();
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
