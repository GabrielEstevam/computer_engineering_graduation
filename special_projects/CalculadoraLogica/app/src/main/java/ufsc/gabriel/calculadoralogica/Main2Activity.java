package ufsc.gabriel.calculadoralogica;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.*;

public class Main2Activity extends AppCompatActivity {

    private TextView txtArea;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        txtArea = (TextView) findViewById(R.id.textArea);
        Bundle bundle = getIntent().getExtras();

        if(bundle.containsKey("TABELA")){
            String tabela = bundle.getString("TABELA");
            txtArea.setText(tabela);
        }
    }
}
