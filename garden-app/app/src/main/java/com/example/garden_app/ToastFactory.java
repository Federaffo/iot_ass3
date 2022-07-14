package com.example.garden_app;

import android.app.Activity;
import android.graphics.BitmapFactory;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public final class ToastFactory {

    private ToastFactory(){ }

    private static View createBasicToastLayout(Activity activity, String title, String description) {
        LayoutInflater inf = activity.getLayoutInflater();
        View layout = inf.inflate(R.layout.toast_layout, null);
        ((TextView)layout.findViewById(R.id.toastTitle)).setText(title);
        if(description.equals("") || description == null){
            ((TextView)layout.findViewById(R.id.toastDesc)).setVisibility(View.GONE);
        }else{
            ((TextView)layout.findViewById(R.id.toastDesc)).setText(description);
        }
        return layout;
    }

    private static Toast createToast(Activity activity, View layout) {
        Toast myToast = new Toast(activity.getApplicationContext());
        myToast.setGravity(Gravity.BOTTOM,0,0);
        myToast.setDuration(Toast.LENGTH_LONG);
        myToast.setView(layout);
        return myToast;
    }

    public static Toast createPositiveToast(Activity activity, String title, String description){
        View toastLayout = createBasicToastLayout(activity, title, description);
        ((ImageView)toastLayout.findViewById(R.id.toastImg)).setImageBitmap(BitmapFactory.decodeResource(activity.getApplicationContext().getResources(), R.drawable.tick));
        return createToast(activity, toastLayout);
    }

    public static Toast createNegativeToast(Activity activity, String title, String description){
        View toastLayout = createBasicToastLayout(activity, title, description);
        ((ImageView)toastLayout.findViewById(R.id.toastImg)).setImageBitmap(BitmapFactory.decodeResource(activity.getApplicationContext().getResources(), R.drawable.cross));
        return createToast(activity, toastLayout);
    }

}