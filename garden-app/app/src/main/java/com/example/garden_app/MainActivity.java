package com.example.garden_app;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

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
    private int irrSpeed=1;
    private boolean manualControl=false;

    private Activity thisActivity=null;


    private  OutputStream tmpOut = null;

    @SuppressLint({"MissingPermission","ResourceAsColor"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        thisActivity=this;

        Button btnLed1= findViewById(R.id.btn_led1);
        Button btnLed2= findViewById(R.id.btn_led2);
        Button btnLed3up= findViewById(R.id.btn_led3up);
        Button btnLed3down= findViewById(R.id.btn_led3down);
        Button btnLed4up= findViewById(R.id.btn_led4up);
        Button btnLed4down= findViewById(R.id.btn_led4down);
        TextView txtLed3= (TextView)findViewById(R.id.txt_led3);
        TextView txtLed4 = (TextView)findViewById(R.id.txt_led4);

        ImageButton btnBT = findViewById(R.id.btn_bt);
        ImageButton btnAlarm = findViewById(R.id.btn_alarm);

        Button btnIrr = findViewById(R.id.btn_irr);
        Button btnIrrUp= findViewById(R.id.btn_irrup);
        Button btnIrrDown = findViewById(R.id.btn_irrdown);
        TextView txtIrr = findViewById(R.id.txt_irr);

        Button btnManual = findViewById(R.id.btn_rmc);



        btnLed1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                l1 =!l1;
               if(l1){l1=true;btnLed1.setBackgroundColor(Color.GREEN);}
               else{l1=false;btnLed1.setBackgroundColor(Color.RED);}
                SendToArduino();
            }
        });

        btnLed2.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                l2 =!l2;
                if(l2){l2=true;btnLed2.setBackgroundColor(Color.GREEN);}
                else{l2=false;btnLed2.setBackgroundColor(Color.RED);}
                SendToArduino();
            }
        });

        btnLed3up.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(l3<4){
                    l3++;
                    txtLed3.setText(Integer.toString(l3));
                    SendToArduino();
                }
            }
        });

        btnLed3down.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(l3>0){
                    l3--;
                    txtLed3.setText(Integer.toString(l3));
                    SendToArduino();
                }
            }
        });

        btnLed4up.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(l4<4){
                    l4++;
                    txtLed4.setText(Integer.toString(l4));
                    SendToArduino();
                }
            }
        });

        btnLed4down.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(l4>0){
                    l4--;
                    txtLed4.setText(Integer.toString(l4));
                    SendToArduino();
                }
            }
        });

        btnBT.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                ConnectToArduino();
            }
        });

        btnAlarm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try {
                    tmpOut = btSocket.getOutputStream();
                    String str= "a";
                    byte[] b = str.getBytes(StandardCharsets.UTF_8);
                    tmpOut.write(b);
                    SendToArduino();
                    ToastFactory.createPositiveToast(thisActivity,"Allarme", "l'allarme è stato disattivato").show();
                } catch (IOException e) {
                    e.printStackTrace();
                    ToastFactory.createNegativeToast(thisActivity,"Allarme", "l'allarme non è stato disattivato").show();
                }

            }
        });

        btnIrr.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                irrigation =!irrigation;
                if(irrigation){irrigation=true;btnIrr.setBackgroundColor(Color.GREEN);}
                else{irrigation=false;btnIrr.setBackgroundColor(Color.RED);}
                SendToArduino();
            }
        });

        btnIrrUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(irrSpeed<5){
                    irrSpeed++;
                    txtIrr.setText(Integer.toString(irrSpeed));
                    SendToArduino();
                }
            }
        });

        btnIrrDown.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(irrSpeed>1){
                    irrSpeed--;
                    txtIrr.setText(Integer.toString(irrSpeed));
                    SendToArduino();
                }
            }
        });

        btnManual.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                manualControl=!manualControl;
                String str;
                if(manualControl){
                    str= "m";
                    ToastFactory.createPositiveToast(thisActivity,"Modalità manuale", "Il sistema è ora in modalità manuale").show();
                }
                else{
                    str="x";
                    ToastFactory.createPositiveToast(thisActivity,"Modalità manuale disattivata", "Il sistema è ora in modalità auto").show();
                }
                try {
                    tmpOut = btSocket.getOutputStream();
                    byte[] b = str.getBytes(StandardCharsets.UTF_8);
                    tmpOut.write(b);
                    SendToArduino();
                } catch (IOException e) {
                    e.printStackTrace();
                    ToastFactory.createNegativeToast(thisActivity,"Modalità manuale", "errore").show();
                }
            }
        });


        /*--- Richiedo di accendere il BT se è spento ---*/
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        if (!btAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }

    }

    @SuppressLint("MissingPermission")
    private void ConnectToArduino() {

        /*--- CONNESSIONE ARDUINO ---*/
        int counter = 0;
        do {
            try {
                hc05 = btAdapter.getRemoteDevice(ARDUINO_MAC);
                btSocket = hc05.createRfcommSocketToServiceRecord(mUUID);
                btSocket.connect();
                ToastFactory.createPositiveToast(this, "Connessione Effettuata ", "BT device collegato").show();
            } catch (IOException e) {
                e.printStackTrace();
                ToastFactory.createNegativeToast(this, "Errore di connessione ", "BT device non collegato, riprovare").show();
            }
            counter++;
        } while (!btSocket.isConnected() && counter < 3);



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
        tmp.put("is",irrSpeed);

        return tmp.toString();
    }
}