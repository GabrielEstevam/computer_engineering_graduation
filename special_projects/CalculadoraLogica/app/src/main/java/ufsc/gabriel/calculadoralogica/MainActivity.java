package ufsc.gabriel.calculadoralogica;

import android.content.Intent;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.beardedhen.androidbootstrap.BootstrapButton;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private TextView txtProposicao;
    private BootstrapButton btnApaga;
    private BootstrapButton btnLimpa;
    private BootstrapButton btnGo;
    private BootstrapButton btnAbre;
    private BootstrapButton btnFecha;
    private BootstrapButton btn_p;
    private BootstrapButton btn_q;
    private BootstrapButton btn_r;
    private BootstrapButton btn_s;
    private BootstrapButton btn_t;
    private BootstrapButton btn_u;
    private BootstrapButton btnConj;
    private BootstrapButton btnDisj;
    private BootstrapButton btnNeg;
    private BootstrapButton btnImp;
    private BootstrapButton btnBiimp;
    private String Tabela;

    int colunas = 0;

    private AlertDialog alerta;

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_about) {
            sobre();
            return true;
        }


        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);



        txtProposicao = (TextView)findViewById(R.id.txtProposicao);
        btnApaga = (BootstrapButton) findViewById(R.id.btnApaga);
        btnLimpa = (BootstrapButton)findViewById(R.id.btnLimpar);
        btnGo = (BootstrapButton)findViewById(R.id.btnGo);
        btnAbre = (BootstrapButton)findViewById(R.id.btnAbre);
        btnFecha = (BootstrapButton)findViewById(R.id.btnFecha);
        btn_p = (BootstrapButton)findViewById(R.id.btn_p);
        btn_q = (BootstrapButton)findViewById(R.id.btn_q);
        btn_r = (BootstrapButton)findViewById(R.id.btn_r);
        btn_s = (BootstrapButton)findViewById(R.id.btn_s);
        btn_t = (BootstrapButton)findViewById(R.id.btn_t);
        btn_u = (BootstrapButton)findViewById(R.id.btn_u);
        btnConj = (BootstrapButton)findViewById(R.id.btnConj);
        btnDisj = (BootstrapButton)findViewById(R.id.btnDisj);
        btnNeg = (BootstrapButton)findViewById(R.id.btnNeg);
        btnImp = (BootstrapButton)findViewById(R.id.btnImp);
        btnBiimp = (BootstrapButton)findViewById(R.id.btnBiimp);

        btnGo.setOnClickListener(this);

        btnApaga.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop, prop2 = "";
                prop = (String) txtProposicao.getText();
                int n = prop.length();
                int a = n - 1;
                if (n >= 3) {
                    if (prop.charAt(n-3) == '<')
                        a = n-3;
                    else if (prop.charAt(n-2) =='-')
                        a = n-2;
                } else if (n >= 2) {
                    if (prop.charAt(n-2) =='-')
                        a = n-2;
                }

                for (int i = 0; i < a; i++)
                    prop2 += prop.charAt(i);
                txtProposicao.setText(prop2);
            }
        });

        btnLimpa.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                txtProposicao.setText("");
            }
        });

        btnAbre.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != 'p' && prop.charAt(n-1) != 'q' && prop.charAt(n-1) != 'r' && prop.charAt(n-1) != 's' && prop.charAt(n-1) != 't' && prop.charAt(n-1) != 'u' && prop.charAt(n-1) != ')')
                        txtProposicao.setText(prop+"(");
                } else {
                    txtProposicao.setText(prop+"(");
                }
            }
        });

        btnFecha.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                int i, k = 0;
                for (i = 0; i < n; i++) {
                    if (prop.charAt(i) == '(')
                        k++;
                    else if (prop.charAt(i) ==')')
                        k--;
                }
                if (k>0) {
                    if (n > 0) {
                        if (prop.charAt(n-1) != '(' && prop.charAt(n-1) != '^' && prop.charAt(n-1) != '~' && prop.charAt(n-1) != '>' && prop.charAt(n-1) != 'v')
                            txtProposicao.setText(prop+")");
                    }
                }
            }
        });

        btn_p.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != 'p' && prop.charAt(n-1) != 'q' && prop.charAt(n-1) != 'r' && prop.charAt(n-1) != 's' && prop.charAt(n-1) != 't' && prop.charAt(n-1) != 'u' && prop.charAt(n-1) != ')')
                        txtProposicao.setText(prop+"p");
                } else {
                    txtProposicao.setText(prop+"p");
                }
            }
        });

        btn_q.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != 'p' && prop.charAt(n-1) != 'q' && prop.charAt(n-1) != 'r' && prop.charAt(n-1) != 's' && prop.charAt(n-1) != 't' && prop.charAt(n-1) != 'u' && prop.charAt(n-1) != ')')
                        txtProposicao.setText(prop+"q");
                } else {
                    txtProposicao.setText(prop+"q");
                }
            }
        });

        btn_r.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != 'p' && prop.charAt(n-1) != 'q' && prop.charAt(n-1) != 'r' && prop.charAt(n-1) != 's' && prop.charAt(n-1) != 't' && prop.charAt(n-1) != 'u' && prop.charAt(n-1) != ')')
                        txtProposicao.setText(prop+"r");
                } else {
                    txtProposicao.setText(prop+"r");
                }
            }
        });

        btn_s.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != 'p' && prop.charAt(n-1) != 'q' && prop.charAt(n-1) != 'r' && prop.charAt(n-1) != 's' && prop.charAt(n-1) != 't' && prop.charAt(n-1) != 'u' && prop.charAt(n-1) != ')')
                        txtProposicao.setText(prop+"s");
                } else {
                    txtProposicao.setText(prop+"s");
                }
            }
        });

        btn_t.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != 'p' && prop.charAt(n-1) != 'q' && prop.charAt(n-1) != 'r' && prop.charAt(n-1) != 's' && prop.charAt(n-1) != 't' && prop.charAt(n-1) != 'u' && prop.charAt(n-1) != ')')
                        txtProposicao.setText(prop+"t");
                } else {
                    txtProposicao.setText(prop+"t");
                }
            }
        });

        btn_u.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != 'p' && prop.charAt(n-1) != 'q' && prop.charAt(n-1) != 'r' && prop.charAt(n-1) != 's' && prop.charAt(n-1) != 't' && prop.charAt(n-1) != 'u' && prop.charAt(n-1) != ')')
                        txtProposicao.setText(prop+"u");
                } else {
                    txtProposicao.setText(prop+"u");
                }
            }
        });

        btnConj.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != '(' && prop.charAt(n-1) != '^' && prop.charAt(n-1) != 'v' && prop.charAt(n-1) != '>' && prop.charAt(n-1) != '~')
                        txtProposicao.setText(prop+"^");
                }
            }
        });

        btnDisj.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != '(' && prop.charAt(n-1) != '^' && prop.charAt(n-1) != 'v' && prop.charAt(n-1) != '>' && prop.charAt(n-1) != '~')
                        txtProposicao.setText(prop+"v");
                }
            }
        });

        btnNeg.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != 'p' && prop.charAt(n-1) != 'q' && prop.charAt(n-1) != 'r' && prop.charAt(n-1) != 's' && prop.charAt(n-1) != 't' && prop.charAt(n-1) != 'u' && prop.charAt(n-1) !=')')
                        txtProposicao.setText(prop+"~");
                } else {
                    txtProposicao.setText(prop+"~");
                }
            }
        });

        btnImp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != '(' && prop.charAt(n-1) != '^' && prop.charAt(n-1) != 'v' && prop.charAt(n-1) != '>' && prop.charAt(n-1) != '~')
                        txtProposicao.setText(prop+"->");
                }
            }
        });

        btnBiimp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View V) {
                String prop = (String) txtProposicao.getText();
                int n = prop.length();
                if (n > 0) {
                    if (prop.charAt(n-1) != '(' && prop.charAt(n-1) != '^' && prop.charAt(n-1) != 'v' && prop.charAt(n-1) != '>' && prop.charAt(n-1) != '~')
                        txtProposicao.setText(prop+"<->");
                }
            }
        });
    }

    private void sobre() {
        //Cria o gerador do AlertDialog
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        //define o titulo
        builder.setTitle("Sobre");
        //define a mensagem
        builder.setMessage("Trabalho produzido para a disciplina Fundamentos Matemáticos para Computação pelo monitor Gabriel Estevam - Universidade Federal de Santa Catarina.\nO algoritmo de construção de tabela verdade a partir de uma proposição utiliza uma adaptação do método de transformação de equações matemáticas para forma Pos-Fixa de Paulo Feofiloff, Algoritmos em Linguagem C.");

        //cria o AlertDialog
        alerta = builder.create();
        //Exibe
        alerta.show();
    }

    public void onClick(View V) {
        Tabela = "";
        String prop = (String) txtProposicao.getText();
        int n = prop.length();
        if (n > 0) {
            if (prop.charAt(n - 1) != '(' && prop.charAt(n - 1) != '^' && prop.charAt(n - 1) != 'v' && prop.charAt(n - 1) != '>' && prop.charAt(n - 1) != '~') {
                if (bemformada(prop) == 0) {
                    String posfixa = infixaPosfixa((String) txtProposicao.getText());
                    String premissas = premissas((String) txtProposicao.getText());


                    int i = 1, j, k;
                    j = premissas.length();
                    for (k = 0; k < j; k++) i = i * 2;


                    int t[][] = new int[i][50];
                    t = gerarPremissas(i, j);
                    colunas = j;
                    t = resolvePosFixa(t, posfixa, i, premissas);
                    imprimirResultado(t, i, colunas, (String) txtProposicao.getText(), premissas);
                } else {
                    Tabela = "Entrada inválida!";
                }
            } else {
                Tabela = "Entrada inválida!";
            }
        }

        if (Tabela != "") {
            Intent it = new Intent(this, Main2Activity.class);
            it.putExtra("TABELA", Tabela);
            startActivity(it);
        }
    }

    private String infixaPosfixa(String infixa) {
        int i, n = 0, topo = 0, k = 0;
        n = infixa.length();
        char posfixa[] = new char [n];
        char pilha[] = new char [n];

        infixa += ')';
        pilha[topo++] = '(';
        for (i = 0; i < n+1; i++) {
            switch (infixa.charAt(i)) {
                case '(':
                    pilha[topo++] = infixa.charAt(i);
                    break;
                case ')':
                    while (pilha[topo-1] != '(') {
                        if (pilha[topo-1] == '>') {
                            if (pilha[topo-3] == '<') {
                                posfixa[k++] = pilha[topo-3];
                            }
                            posfixa[k++] = pilha[topo-2];
                            posfixa[k++] = pilha[topo-1];
                            if (pilha[topo-3] == '<')
                                topo = topo - 3;
                            else
                                topo = topo - 2;
                        } else {
                            posfixa[k++] = pilha[--topo];
                        }
                    }
                    topo--;
                    break;
                case '~':
                    while (pilha[topo-1] != '(' && pilha[topo-1] != '^' && pilha[topo-1] != 'v' && pilha[topo-1] != '>' && pilha[topo-1] != '~') {
                        if (pilha[topo-1] == '>') {
                            if (pilha[topo-3] == '<') {
                                posfixa[k++] = pilha[topo-3];
                            }
                            posfixa[k++] = pilha[topo-2];
                            posfixa[k++] = pilha[topo-1];
                            if (pilha[topo-3] == '<')
                                topo = topo - 3;
                            else
                                topo = topo - 2;
                        } else {
                            posfixa[k++] = pilha[--topo];
                        }
                    }
                    pilha[topo++] = infixa.charAt(i);
                    break;
                case '^':
                case 'v':
                    while (pilha[topo-1] != '(' && pilha[topo-1] != '>') {
                        if (pilha[topo-1] == '>') {
                            if (pilha[topo-3] == '<') {
                                posfixa[k++] = pilha[topo-3];
                            }
                            posfixa[k++] = pilha[topo-2];
                            posfixa[k++] = pilha[topo-1];
                            if (pilha[topo-3] == '<')
                                topo = topo - 3;
                            else
                                topo = topo - 2;
                        } else {
                            posfixa[k++] = pilha[--topo];
                        }
                    }
                    pilha[topo++] = infixa.charAt(i);
                    break;
                case '<':
                    while (pilha[topo-1] != '(') {
                        if (pilha[topo-1] == '>') {
                            if (pilha[topo-3] == '<') {
                                posfixa[k++] = pilha[topo-3];
                            }
                            posfixa[k++] = pilha[topo-2];
                            posfixa[k++] = pilha[topo-1];
                            if (pilha[topo-3] == '<')
                                topo = topo - 3;
                            else
                                topo = topo - 2;
                        } else {
                            posfixa[k++] = pilha[--topo];
                        }
                    }
                    if (infixa.charAt(i+1) == '-' && infixa.charAt(i+2) == '>'){
                        pilha[topo++] = infixa.charAt(i);
                        pilha[topo++] = infixa.charAt(++i);
                        pilha[topo++] = infixa.charAt(++i);
                    }
                    break;
                case '-':
                    while (pilha[topo-1] != '('){
                        if (pilha[topo-1] == '>') {
                            if (pilha[topo-3] == '<') {
                                posfixa[k++] = pilha[topo-3];
                            }
                            posfixa[k++] = pilha[topo-2];
                            posfixa[k++] = pilha[topo-1];
                            if (pilha[topo-3] == '<')
                                topo = topo - 3;
                            else
                                topo = topo - 2;
                        } else {
                            posfixa[k++] = pilha[--topo];
                        }
                    }
                    if (infixa.charAt(i+1) == '>') {
                        pilha[topo++] = infixa.charAt(i);
                        pilha[topo++] = infixa.charAt(++i);
                    }
                    break;
                case '>':
                    while (pilha[topo-1] != '('){
                        if (pilha[topo-1] == '>') {
                            if (pilha[topo-3] == '<') {
                                posfixa[k++] = pilha[topo-3];
                            }
                            posfixa[k++] = pilha[topo-2];
                            posfixa[k++] = pilha[topo-1];
                            if (pilha[topo-3] == '<')
                                topo = topo - 3;
                            else
                                topo = topo - 2;
                        } else {
                            posfixa[k++] = pilha[--topo];
                        }
                    }
                    pilha[topo++] = infixa.charAt(i);
                    break;
                default:
                    posfixa[k++] = infixa.charAt(i);
            }
        }

        String retorno = "";
        for (i = 0; i < k; i++)
            retorno += posfixa[i];
        return retorno;
    }

    private String premissas(String proposicao) {
        String v = "";
        int n, i, j, k, y;
        char Letras[] = {'p', 'q', 'r', 's', 't', 'u'};
        n = proposicao.length();
        k = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < 6; j++) {
                if (Letras[j] == proposicao.charAt(i)) {
                    for (y = 0; y < k; y++){
                        if (v.charAt(y) == proposicao.charAt(i))
                            break;
                    }
                    if (y == k) {
                        v += proposicao.charAt(i);
                        k++;
                    }
                }
            }
        }

        return v;
    }

    private int[][] gerarPremissas(int x, int y) {
        int t[][] =  new int[x][y];
        int i, j, k1, k2, k3;

        k1 = x/2;
        k2 = 0;
        k3 = k1;
        /*Preencher a tabela*/
        for (j = 0; j < y; j++) {
            for (i = 0; i < x; i++) {
                if (k1 > 0) {
                    t[i][j] = 1;
                    k1--;
                } else {
                    k2++;
                    t[i][j] = 0;
                }
                if (k2 == k3) {
                    k1 = k3;
                    k2 = 0;
                }
            }
            k2 = 0;
            k3 = k3/2;
            k1 = k3;
        }
        String texto ="";
        for (i = 0; i < x; i++) {
            for (j = 0; j < y; j++)
                texto += ""+t[i][j];
            texto+="\n";
        }
        Tabela = texto;
        return t;
    }

    private int[][] resolvePosFixa(int[][] t, String posfixa, int i, String prem) {
        int n, m, k, y, a, topo = 0;
        n = posfixa.length();
        m = prem.length();
        int pilha[] = new int [n];
        int prop[] = new int [i];
        y = m;
        for (k = 0; k < n; k++) {
            switch (posfixa.charAt(k)) {
                case '~':
                    prop = propNegacao(t, i, pilha[--topo]);
                    t = inserirPropTabela(t, prop, i, y);
                    y++;
                    pilha[topo++] = y-1;
                    colunas++;
                    break;
                case 'v':
                    prop = propDisjuncao(t, i, pilha[topo-1], pilha[topo-2]);
                    topo = topo-2;
                    t = inserirPropTabela(t, prop, i, y);
                    y++;
                    pilha[topo++] = y-1;
                    colunas++;
                    break;
                case '^':
                    prop = propConjuncao(t, i, pilha[topo-1], pilha[topo-2]);
                    topo = topo-2;
                    t = inserirPropTabela(t, prop, i, y);
                    y++;
                    pilha[topo++] = y-1;
                    colunas++;
                    break;
                case '<':
                    prop = propBicondicional(t, i, pilha[topo-2], pilha[topo-1]);
                    topo = topo-2;
                    t = inserirPropTabela(t, prop, i, y);
                    y++;
                    pilha[topo++] = y-1;
                    k = k+2;
                    colunas++;
                    break;
                case '-':
                    prop = propCondicional(t, i, pilha[topo-2], pilha[topo-1]);
                    topo = topo - 2;
                    t = inserirPropTabela(t, prop, i, y);
                    y++;
                    pilha[topo++] = y-1;
                    k++;
                    colunas++;
                    break;
                default:
                    for (a = 0; a < m; a++) {
                        if (posfixa.charAt(k) == prem.charAt(a))
                            pilha[topo++] = a;
                    }
            }

        }
        return t;
    }

    private int[][] inserirPropTabela(int[][] t, int[] prop, int x, int y) {
        int i, j;
        int t_nova[][] = new int [x][y+1];

        for (j = 0; j <= y; j++) {
            for (i = 0; i < x; i++) {
                if (j < y)
                    t_nova[i][j] = t[i][j];
                else
                    t_nova[i][j] = prop[i];
            }
        }
        return t_nova;
    }

    private int[] propNegacao(int[][] t, int x, int y) {
        int p[] = new int[x];
        int i;
        for (i = 0; i < x; i++) {
            if (t[i][y] == 0)
                p[i] = 1;
            else
                p[i] = 0;
        }
        return p;
    }

    private int[] propDisjuncao(int[][] t, int x, int y1, int y2) {
        int p[]= new int[x];
        int i;
        for (i = 0; i < x; i++) {
            if (t[i][y1] == 1 || t[i][y2] == 1)
                p[i] = 1;
            else
                p[i] = 0;
        }
        return p;
    }

    private int[] propConjuncao(int[][] t, int x, int y1, int y2) {
        int p[] = new int[x];
        int i;
        for (i = 0; i < x; i++) {
            if (t[i][y1] == 1 && t[i][y2] == 1)
                p[i] = 1;
            else
                p[i] = 0;
        }
        return p;
    }

    private int[] propBicondicional(int[][] t, int x, int y1, int y2) {
        int p[] = new int[x];
        int i;
        for (i = 0; i < x; i++) {
            if (t[i][y1] == t[i][y2])
                p[i] = 1;
            else
                p[i] = 0;
        }
        return p;
    }

    private int[] propCondicional(int[][] t, int x, int y1, int y2) {
        int p[] = new int[x];
        int i;
        for (i = 0; i < x; i++) {
            if (t[i][y1] == 1 && t[i][y2] == 0)
                p[i] = 0;
            else
                p[i] = 1;
        }
        return p;
    }

    void imprimirResultado (int t[][], int i, int j, String c, String prem) {
        int a, b, m, n, k = 0;
        m = prem.length();
        n = c.length();

        String texto = "";

        for (a = 0; a < m; a++)
            texto += "  "+prem.charAt(a)+"  ";
        texto +="  ";

        if (n > 1) {
            texto += c;
            texto +="\n";
            for (a = 0; a < i; a++) {
                for (b = 0; b < (m+1); b++) {
                    if (b < m) {
                        texto += "  "+t[a][b]+"  ";
                    } else {
                        texto += "  "+t[a][colunas-1]+"  ";
                    }
                }
            /*Mostra a tabela toda
            for (b = 0; b < colunas; b++)
                texto += "  "+t[a][b]+"  ";
            */
                texto +="\n";
            }
            texto +="\n";
        } else {
            texto +="\n";
            for (a = 0; a < i; a++)
                texto += "  "+t[a][0]+"  \n";
        }
        Tabela = texto;
    }

    int bemformada (String text){
        int n = text.length();
        char pilha[] = new char [n];
        int i, topo = 0;

        for (i = 0; i < n; i++){
            if (text.charAt(i) == ')') {
                if (topo != 0 && pilha[topo-1] =='(') {
                    topo--;
                } else {
                    return 1;
                }
            } else if (text.charAt(i) == '(') {
                pilha[topo++] = text.charAt(i);
            }
        }

        return topo;
    }
}
