package com.example.garden_app;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    static final UUID mUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private static final int REQUEST_ENABLE_BT = 1;
    private final String ARDUINO_MAC="98:D3:32:70:4F:4C";

    private BluetoothSocket btSocket = null;
    private BluetoothAdapter btAdapter=null;
    private BluetoothDevice hc05=null;

    private boolean l1=false;
    private boolean l2=false;
    private int l3=0;
    private int l4=0;
    private int arduinoState=1;
    private boolean irrigation=false;


    private  OutputStream tmpOut = null;

    @SuppressLint("MissingPermission")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnLed1= findViewById(R.id.btn_led1);
        Button btnLed2= findViewById(R.id.btn_led2);
        Button btnLed3up= findViewById(R.id.btn_led3up);
        Button btnLed3down= findViewById(R.id.btn_led3down);
        Button btnLed4up= findViewById(R.id.btn_led4up);
        Button btnLed4down= findViewById(R.id.btn_led4down);


        btnLed1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                l1 =!l1;
               if(l1){l1=true;}else{l1=false;}
                SendToArduino();
            }
        });

        btnLed2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                l2 =!l2;
                if(l2){l2=true;}else{l2=false;}
                SendToArduino();
            }
        });

        btnLed3up.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(l3<4){l3++;}
                SendToArduino();
            }
        });

        btnLed3down.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(l3>0){l3--;}
                SendToArduino();
            }
        });

        btnLed4up.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(l4<4){l4++;}
                SendToArduino();
            }
        });

        btnLed4down.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(l4>0){l4--;}
                SendToArduino();
            }
        });




        ConnectToArduino();

    }

    @SuppressLint("MissingPermission")
    private void ConnectToArduino() {
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        if (!btAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }else {
            /*--- CONNESSIONE ARDUINO ---*/
            System.out.println("Ok");
            int counter = 0;
            do {
                try {
                    hc05 = btAdapter.getRemoteDevice(ARDUINO_MAC);
                    btSocket = hc05.createRfcommSocketToServiceRecord(mUUID);
                    btSocket.connect();
                    System.out.println(btSocket.isConnected());
                } catch (IOException e) {
                    e.printStackTrace();
                }
                counter++;
            } while (!btSocket.isConnected() && counter < 3);
        }

        ToastFactory.createPositiveToast(this, "Connessione Effettuata ", "BT device collegato").show();
    }

    private void SendToArduino(){
        try {
            tmpOut = btSocket.getOutputStream();
            String str= CreateMyJSON();;
            byte[] b = str.getBytes(StandardCharsets.UTF_8);
            tmpOut.write(b);
            System.out.println("mandato");
        } catch (IOException | JSONException e) {
            e.printStackTrace();
        }
    }

    private String CreateMyJSON() throws JSONException {
        JSONObject tmp= new JSONObject();
        tmp.put("l1",l1);
        tmp.put("l2",l2);
        tmp.put("l3",l3);
        tmp.put("l4",l4);
        tmp.put("state",arduinoState);
        tmp.put("i",irrigation);

        return tmp.toString();
    }
}