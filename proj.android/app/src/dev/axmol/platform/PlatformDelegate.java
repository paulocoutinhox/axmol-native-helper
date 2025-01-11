package dev.axmol.platform;

import android.app.AlertDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.os.Handler;
import android.util.Log;

import dev.axmol.app.MainApplication;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.UUID;

public class PlatformDelegate {
    public static void performAction(final String action, final String data, final long contextAddress) {
        switch (action) {
            case "initialize":
                onActionInitialize(action, data, contextAddress);
                break;

            case "get-customer-id":
                onActionGetCustomerId(action, data, contextAddress);
                break;

            case "start-task-long":
                onActionStartTaskLong(action, data, contextAddress);
                break;

            case "show-alert":
                onActionShowAlert(action, data, contextAddress);
                break;
        }
    }

    private static void onActionInitialize(String action, String data, long contextAddress) {
        Log.d("PLATFORM-HELPER", "[PlatformDelegate : onActionInitialize] Initialized in release");

        // initialize your custom platform SDK here, example: Firebase, Facebook, Google etc

        nativeOnActionComplete("initialized", contextAddress);
    }

    private static void onActionGetCustomerId(String action, String data, long contextAddress) {
        String uuid = UUID.randomUUID().toString();
        nativeOnActionComplete(uuid, contextAddress);
    }

    private static void onActionStartTaskLong(String action, String data, final long contextAddress) {
        new AsyncTask<Void, Void, String>() {
            @Override
            protected String doInBackground(Void... voids) {
                try {
                    URL url = new URL("https://httpbin.org/get");
                    HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
                    try {
                        BufferedReader in = new BufferedReader(new InputStreamReader(urlConnection.getInputStream()));
                        StringBuilder response = new StringBuilder();
                        String inputLine;
                        while ((inputLine = in.readLine()) != null) {
                            response.append(inputLine);
                        }
                        in.close();
                        return response.toString();
                    } finally {
                        urlConnection.disconnect();
                    }
                } catch (Exception e) {
                    Log.e("PLATFORM-HELPER", "Error in start-task-long", e);
                    return null;
                }
            }

            @Override
            protected void onPostExecute(String result) {
                if (result != null) {
                    nativeOnActionComplete(result, contextAddress);
                } else {
                    nativeOnActionComplete("no-response", contextAddress);
                }
            }
        }.execute();
    }

    private static void onActionShowAlert(String action, String data, final long contextAddress) {
        try {
            JSONObject jsonObject = new JSONObject(data);
            final String message = jsonObject.getString("message");

            Context context = MainApplication.getInstance().getCurrentActivity();

            new Handler(context.getMainLooper()).post(() -> {
                AlertDialog.Builder builder = new AlertDialog.Builder(context);
                builder.setTitle("Alert")
                    .setMessage(message)
                    .setCancelable(false)
                    .setPositiveButton("Yes", (dialog, id) -> handleAlertResponse("yes", contextAddress))
                    .setNegativeButton("No", (dialog, id) -> handleAlertResponse("no", contextAddress))
                    .create()
                    .show();
            });
        } catch (Exception e) {
            Log.e("PLATFORM-HELPER", "Error parsing JSON: ", e);
            nativeOnActionComplete("json-error", contextAddress);
        }
    }

    private static void handleAlertResponse(String response, long contextAddress) {
        if ("yes".equals(response)) {
            nativeOnActionComplete("Clicked on: YES", contextAddress);
        } else {
            nativeOnActionComplete("Clicked on: NO", contextAddress);
        }
    }

    public static native void nativeOnActionComplete(String result, long contextAddress);
}
