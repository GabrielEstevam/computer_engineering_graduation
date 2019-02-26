   // Nome da classe:  criptografiaRSA
   // Escrito por: Gabriel Estevam Oliveira
   // Data: 28 de outubro de 2016
   // Proposito: implementacao do esquema de criptografia RSA.
   //
   // Funcoes:
   //       numero primoRelativo (numero x)
   //           - Objetivo: encontrar um primo relativo de um numero.
   //           - Parametro: numero que se deseja encontrar um primo relativo.
   //           - Retorno: um primo relativo.
   //           Faz testes com um numero que comeca com valor 3 e é incrementado em 2 a cada iteracao.          
   //           O teste é realizado com euclidesMDC(), se o retorno for 1 entao o numero é primo relativo.
   //
   //       numero euclidesMDC (numero x, numero y)
   //           - Objetivo: encontrar o minimo multiplo comum entre dois numeros.
   //           - Parametros: dois numero que se deseja encontrar o minimo multiplo comum.
   //           - Retorno: o minimo multiplo comum.
   //           Usa o Algorimo de Euclides para encontrar o minimo multiplo comum.
   //
   //       numero congruenteModuloN (numero x, numero mod)
   //           - Objetivo: encontrar o congruente em um modulo de um numero.
   //           - Parametros: numero(x) que se deseja encontrar o congruente e modulo(mod).
   //           - Retorno: numero congruente.
   //
   //       numero[] euclidesEstendido (numero x, numero y)
   //           - Objetivo: encontrar o inverso multiplicativo modular de um numero.
   //           - Parametros: dois numeros que se deseja encontrar os inversos multiplicativos.
   //           - Retorno: um primeiro numero que é o inverso multiplicativo do primeiro parametro no modulo do segundo paramentro.
   //                      e um segundo numero que é o inversor multiplicativo do segundo parametro no modulo do primeiro parametro. 
   //           Usa o algorimo de Euclides Estendido para encontrar os inversos multiplicativos.
   //
   //       numero gerarNumeroPrimo (int tamanho, int precisao)
   //           - Objetivo: encontrar um numero primo com quantidade de algarismos(tamanho) e uma determinada certeza(precisao).
   //           - Parametros: um inteiro para a quantidade de algarismos desejada e um inteiro que determinara a precisao.
   //           - Retorno: um numero primo com a quantidade de algarismo do primeiro parametro(tamanho).
   //           É gerado um numero aleatorio e entao realizado o teste de primalidade a quantidade de vezes determinada pela precisao.
   //
   //       int testePrimalidade (numero primo)
   //           - Objetivo: determinar se um numero é ou nao primo.
   //           - Parametros: numero que se deseja realizar o teste.
   //           - Retorno: inteiro com valor 1 caso o teste diga "sim" e valor 0 caso o teste diga "nao".
   //           Utiliza um corolario que afirma que se um numero é primo entao um numero a<primo elevado ao primo-1 é congruente a 1 no modulo primo.
   //
   //       numero soma (numero n1, numero n2)
   //           - Objetivo: encontrar a soma de dois numeros.
   //           - Parametros: dois numero que se deseja somar.
   //           - Retorno: o resultado da soma dos dois numeros.
   //           Divide o problema conforme o sinal e o tamanho do numero, fazendo a chamada de outras funcoes.
   // 
   //       numero subtracao (numero n1, numero n2)
   //           - Objetivo: encontrar a subtracao do primeiro numero pelo segundo.
   //           - Parametros: dois numero que se deseja subtrair.
   //           - Retorno: o resultado da subtracao dos dois numeros.
   //           Divide o problema conforme o sinal e o tamanho do numero, fazendo a chamada de outras funcoes.
   //
   //       numero somaABS (numero n1, numero n2)
   //           - Objetivo: encontrar a soma absoluta de dois numeros.
   //           - Parametros: dois numero que se deseja somar.
   //           - Retorno: o resultado da soma dos dois numeros.
   //           Nao considera o sinal do numero. 
   //           Realiza a soma de cada algarismo do primeiro numero o algarismo do segundo numero para encontra a soma resultante.
   //
   //       numero diferenca (numero a, numero b)
   //           - Objetivo: encontrar a diferenca entre dois numeros.
   //           - Parametros: dois numero que se deseja encontrar a diferenca.
   //           - Retorno: a diferenca dos dois numeros.
   //           Nao considera o sinal do numero.
   //           Verifica qual numero é maior em modulo e realiza a subtracao do outro.
   //
   //       numero multiplicacao (numero n1, numero n2)
   //           - Objetivo: encontrar a multiplicacao de dois numeros.
   //           - Parametros: dois numero que se deseja multiplicar.
   //           - Retorno: o resultado da multiplicacao dos dois numeros.
   //           Realiza o produto de cada algarismo do segundo numero por todo o primeiro numero e realiza a soma em um numero resultante.
   //
   //       int maiorEmModulo (numero n1, numero n2)
   //           - Objetivo: verificar qual o maior numero sem considerar o sinal.
   //           - Parametros: dois numero que se deseja verificar.
   //           - Retorno: inteiro com valor 1 caso o primeiro for maior ou igual ao segundo e valor 2 caso o segundo for maior que o primeiro.
   //           Verifica o tamanho dos numero, caso tiverem o mesmo tamanho verifica algarismo por algarismo.
   //   
   //       numero divisao (numero n1, numero n2)
   //           - Objetivo: encontrar a divisao inteira de dois numeros.
   //           - Parametros: o primeiro numero é o numerador e o segundo o denominador.
   //           - Retorno: o resultado da divisao inteiro do primeiro pelo segundo numero.
   //           Utiliza recursao para resolver o problema.
   //
   //       numero moduloN (numero n1, numero n2)
   //           - Objetivo: encontrar o resto da divisao de dois numero.
   //           - Parametros: o primeiro numero é que se deseja encontrar o resto da divisao e o segundo e o modulo.
   //           - Retorno: resto da divisao do primeiro pelo segundo numero.
   //   
   //       numero multiplicacaoModular (numero n1, numero n2, numero N)
   //           - Objetivo: encontrar a multiplicacao de dois numero em um modulo N.
   //           - Parametros: os dois numero a serem multiplicados e o modulo desejado.
   //           - Retorno: a multiplicacao dos dois primeiro parametros no modulo do terceiro.
   //
   //       numero exponenciacaoModular (numero n1, numero n, numero mod)
   //           - Objetivo: encontrar a exponenciacao de um numero por outro no modulo mod.
   //           - Parametros: o primeiro numero é a base, o segundo o expoente e o terceiro é o modulo.
   //           - Retorno: o resultado da exponenciacao em modulo mod.
   //           Utiliza recursao para resolver o problema.
   //

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

public class CriptografiaRSA {

    public static void main(String[] args) throws IOException {
        
        // Leitura do arquivo (chave.txt)
        String chave = "/XXXXX/esquemaRSA/chave.txt";
        String l1 = "", l2 = "";
        int i = 0;
        
        try {
            FileReader arq = new FileReader(chave);
            BufferedReader lerArq = new BufferedReader(arq);
            l1 = lerArq.readLine();
            l2 = lerArq.readLine();
            arq.close();
        } catch (IOException e) {
            System.err.printf("Erro na leitura do arquivo.\n",
                e.getMessage());
        }
        
        // Converte c de String para numero
        numero c = new numero();
        c.tamanho = l1.length();
        for (i = 0; i < c.tamanho; i++) {
            c.n[c.tamanho - i - 1] = Integer.parseInt(""+l1.charAt(i));
        }
        System.out.print("c: ");
        c.imprimirNumero();
        
        // Converte mod de String para numero
        numero N = new numero();
        N.tamanho = l2.length();
        for (i = 0; i < N.tamanho; i++) {
            N.n[N.tamanho - i - 1] = Integer.parseInt(""+l2.charAt(i));
        }
        System.out.print("N: ");
        N.imprimirNumero();
        
        // Leitura do arquivo (mensagem.txt)
        String texto = "/XXXXX/esquemaRSA/mensagem.txt";
        try {
            FileReader arq = new FileReader(texto);
            BufferedReader lerArq = new BufferedReader(arq);
            l1 = lerArq.readLine();
            arq.close();
        } catch (IOException e) {
            System.err.printf("Erro na leitura do arquivo.\n",
                e.getMessage());
        }
        
        // Converte texto de String para numero
        numero mensagem = new numero();
        mensagem.tamanho = l1.length();
        for (i = 0; i < mensagem.tamanho; i++) {
            mensagem.n[mensagem.tamanho - i - 1] = Integer.parseInt(""+l1.charAt(i));
        }
        System.out.print("Mensagem original: ");
        mensagem.imprimirNumero();
              
        // Criptografa
        numero mensagemCriptografada = exponenciacaoModular(mensagem, c, N);
		System.out.print("Mensagem criptografada: ");
        mensagemCriptografada.imprimirNumero();
        
        
        // Grava no arquivo

        FileWriter arq = new FileWriter("/XXXXX/esquemaRSA/mensagemCriptografada.txt");
        PrintWriter gravarArq = new PrintWriter(arq);
        
        for (i = mensagemCriptografada.tamanho -1 ; i >= 0; i--) {
            gravarArq.printf(mensagemCriptografada.n[i]+"");
        }
        gravarArq.printf("\n");
        arq.close();
        System.out.printf("A mensagem foi gravada com sucesso em: /XXXXX/esquemaRSA/mensagemCriptografada.txt.\n");
    }
    
    static numero primoRelativo (numero x) {
        numero y = new numero();
        y.tamanho = 1;
        y.n[0] = 1;
        numero z;
        numero dois = new numero();
        dois.tamanho = 1;
        dois.n[0] = 2;
        do {
            y = soma(y, dois);
            z = euclidesMDC(y, x);
        } while(z.tamanho != 1 || z.n[0] != 1);
        return y;
    }
    
    static numero euclidesMDC (numero x, numero y) {
        if (y.tamanho == 0) {
            return x;
        } else {
            return euclidesMDC (y, moduloN(x, y));
        }
    }

    static numero congruenteModuloN (numero x, numero mod) {
        numero r = moduloN(x, mod);
        r.sinal = 1;
        if (r.tamanho == 0) {
            return r;
        }
        if (x.sinal == -1) {
            x = subtracao(mod, r);
        }
        return x;
    }
    
    static numero [] euclidesEstendido(numero x, numero y) {
        numero v[] = new numero[3];
        numero z;
        if (y.tamanho == 0) {
            v[0] = new numero();
            v[0].tamanho = 1; 
            v[0].n[0] = 1;
            v[1] =  new numero();
            v[1].tamanho = 0; 
            v[2] = x;
        } else {
            v = euclidesEstendido (y, moduloN(x,y));
            z = v[0];
            v[0] = v[1];
            v[1] = subtracao(z, multiplicacao(v[1], divisao(x,y)));
        }
        return v;
    }
 
    static numero gerarNumeroPrimo(int tamanho, int precisao) {
        Random Aleatorio = new Random();
        numero primo = new numero();
        primo.tamanho = tamanho;
        int verifica = 0, n;
        int i, j;
        
        while (verifica == 0) {
            primo.tamanho = tamanho;
            for (i = 0; i < tamanho; i++) {
                n = Aleatorio.nextInt()%10;
                if (n < 0) {
                    n *= -1;
                }
                primo.n[i] = n;
            }
            
            if (primo.n[tamanho-1] == 0) {
                primo.n[tamanho-1] = 1;
            }
            
            for (j = 0; j < precisao; j++) {
                verifica = testePrimalidade(primo);
                if (verifica == 0) {
                    break;
                }
            }
            if (verifica == 1) {
                break;
            }
        }
        
        return primo;
    }
    
    static int testePrimalidade(numero primo) {
        // Retorna 1 para sim e 0 para nao
        Random Aleatorio = new Random();
        int n, j;
        numero a = new numero();
        
        a.tamanho = primo.tamanho-1;
        
        numero um = new numero();
        um.tamanho = 1;
        um.n[0] = 1;
        
        numero N = diferenca(primo, um);
        
        for (j = 0; j < a.tamanho; j++) {
            n = Aleatorio.nextInt()%10;
            if (n < 0) {
                n *= -1;
            }
            a.n[j] = n;
        }
        
        if (a.tamanho == 1 && a.n[0] < 2) {
            a.n[0] = 2;
        }
       
        a = exponenciacaoModular(a, N, primo);
        
        if (a.tamanho == 1 && a.n[0] == 1) {
            return 1;
        } else {
            return 0;
        }
    }
    
    static numero soma (numero n1, numero n2) {
        /* n1 maior */
                /* caso 1 - n1 e n2 positivos: somaAbs(n1, n2) */
                /* caso 2 - n1 e n2 negativos: -somaAbs(n1, n2) */
                /* caso 3 - n1 positivo e n2 negativo: diferencaAbs(n1, n2) */
                /* caso 4 - n1 negativo e n2 positivo: -diferencaAbs(n1, n2) */
        /* n2 maior */
                /* caso 5 - n1 e n2 positivos: somaAbs(n1, n2) */
                /* caso 6 - n1 e n2 negativos: -somaAbs(n1, n2) */
                /* caso 7 - n1 positivo e n2 negativo: -diferencaAbs(n1, n2) */
                /* caso 8 - n1 negativo e n2 positivo: diferencaAbs(n1, n2) */

        /* caso 1, 2, 5 e 6 */
        if (n1.sinal == n2.sinal) {
            n1 = somaAbs(n1, n2);
        } else if (maiorEmModulo(n1, n2) == 1) {
            /* caso 3 e 4 */
            n1 = diferenca(n1, n2);
        } else {
            /* caso 7 e 8 */
            n1 = diferenca(n1, n2);
            n1.sinal = n2.sinal;
        }
        return n1;
    }
    
    static numero subtracao (numero n1, numero n2) {
        /* n1 maior */
            /* caso 1 - n1 e n2 positivos: diferencaAbs(n1, n2) */
            /* caso 2 - n1 e n2 negativos: -diferencaAbs(n1, n2) */
            /* caso 3 - n1 positivo e n2 negativo: somaAbs(n1, n2) */
            /* caso 4 - n1 negativo e n2 positivo: -somaAbs(n1, n2) */
        /* n2 maior */
            /* caso 5 - n1 e n2 positivos: -diferencaAbs(n1, n2) */
            /* caso 6 - n1 e n2 negativos: diferencaAbs(n1, n2) */
            /* caso 7 - n1 positivo e n2 negativo: somaAbs(n1, n2) */
            /* caso 8 - n1 negativo e n2 positivo: -somaAbs(n1, n2) */

        /* caso 1 e 2 */
        if (n1.sinal == n2.sinal && maiorEmModulo(n1, n2) == 1) {
            n1 = diferenca(n1, n2);
        } else if (n1.sinal == n2.sinal && maiorEmModulo(n1, n2) == 2) {
            /* caso 5 e 6 */
            n1 = diferenca(n1, n2);
            n1.sinal *= -1;
        } else if (maiorEmModulo(n1, n2) == 1) {
            /* caso 3 e 4 */
            n1 = somaAbs(n1, n2);
        } else {
            /* caso 7 e 8 */
            n1 = somaAbs(n1, n2);
        }
        return n1;
    }
    
    static numero somaAbs (numero n1, numero n2) {
        int i;
  	int vai_um = 0;
        numero n = new numero();
        n.tamanho = n1.tamanho;
        n.sinal = n1.sinal;
        
        for (i = 0; i < n.tamanho; i++) {
            if (n1.n[i] + n2.n[i] + vai_um >= 10) {
                n.n[i] = (n1.n[i]+n2.n[i]+vai_um)%10;
                vai_um = 1;
            } else {
                n.n[i] = n1.n[i]+n2.n[i]+vai_um;
                vai_um = 0;
            }
	}
	if (n2.tamanho > n1.tamanho) {
            for (i = n1.tamanho; i < n2.tamanho; i++) {
                if (n2.n[i] + vai_um >= 10) {
                    n.n[i] = (n2.n[i]+vai_um)%10;
                    vai_um = 1;
                } else {
                    n.n[i] = n2.n[i]+vai_um;
                    vai_um = 0;
                }
                n.tamanho = n2.tamanho;
            }
	}
	if (vai_um == 1) {
            n.n[n1.tamanho] = 1;
            n.tamanho++;
	}
	return n;
    }

    static numero diferenca (numero a, numero b) {
        numero c = new numero();
        int i, vem_um = 0;
  	if (maiorEmModulo(a, b) == 1) {
            c.tamanho = a.tamanho;
            c.sinal = a.sinal;
            for (i = 0; i < c.tamanho; i++) {
                if (a.n[i] - vem_um - b.n[i] < 0) {
                    c.n[i] = a.n[i]+10 - b.n[i] - vem_um;
                    vem_um = 1;
		} else {
                    c.n[i] = a.n[i] - b.n[i] - vem_um;
                    vem_um = 0;
		}
            }
            
            if (vem_um == 1) {
                c.n[c.tamanho-1] -= 1;
            }
                
            i = c.tamanho-1;
            while (i >= 0) {
                if (c.n[i] == 0) {
                    c.tamanho--;
                    i--;
                } else {
                    break;
                }
            }
            return c;
	} else {
            c.tamanho = b.tamanho;
            c.sinal = b.sinal;
            for (i = 0; i < c.tamanho; i++) {
		if (b.n[i] - vem_um - a.n[i] < 0) {
                    c.n[i] = b.n[i]+10 - a.n[i];
                    vem_um = 1;
		} else {
                    c.n[i] = b.n[i] - a.n[i] - vem_um;
                    vem_um = 0;
		}
            }
            if (vem_um == 1) {
                c.n[c.tamanho-1] -= 1;
            }
            i = c.tamanho-1;
            while (i >= 0) {
                if (c.n[i] == 0) {
                    c.tamanho--;
                    i--;
                } else {
                    break;
                }
            }
        }
        return c;
    }
    
    static numero multiplicacao (numero n1, numero n2) {
        numero n = new numero();
  	int i, j, k = 0, vai = 0, tam_max;
  	for (i = 0; i < n2.tamanho; i++) {
            k = i;
            for (j = 0; j < n1.tamanho; j++) {
                if (n.n[k] + n2.n[i]*n1.n[j] + vai > 9) {
                    vai = n.n[k] + n2.n[i]*n1.n[j] + vai;
                    n.n[k] = (vai)%10;
                    vai /= 10;
		} else {
                    n.n[k] += n2.n[i]*n1.n[j] + vai;
                    vai = 0;
		}
		k++;
            }
            n.n[k] = vai;
            vai = 0;
		}
	
		// Encontra o tamanho de n
		tam_max = maiorEmModulo(n1, n2);
	  	if (tam_max == 1) {
		        tam_max = n1.tamanho*2;
		} else {
		        tam_max = n2.tamanho*2;
		}
		n.tamanho = tam_max;
		for (i = tam_max-1; i >= 0; i--) {
		        if (n.n[i] == 0) {
			n.tamanho--;
		        } else {
			break;
		        }
		}
		    
		// Tratamento de sinal para n
		if (n1.sinal == n2.sinal) {
		        n.sinal = 1;
		} else {
		        n.sinal = -1;
		}
		return n;
    }
    
    static int maiorEmModulo (numero n1, numero n2) {
        // Retorna 1 se o maior for o primeiro ou forem iguais e retorna 2 se o maior for o segundo
        int i;
        if (n1.tamanho > n2.tamanho) {
            return 1;
        } else if (n2.tamanho > n1.tamanho) {
            return 2;
        } else {
            for (i = (n1.tamanho)-1; i >= 0; i--) {
                if (n1.n[i] > n2.n[i]) {
                    return 1;
                } else if (n2.n[i] > n1.n[i]) {
                    return 2;
                }
            }
            return 1;
        }
    }
    
    static numero divisao (numero n1, numero n2) {
        numero z = new numero();
        z.tamanho = 1;
        numero x = new numero();
        x.tamanho = 1;
        numero y;
        numero a = new numero();
        numero k = new numero();
        int i;
        
        if (n1.tamanho == 0) {
            x.tamanho = 0;
            return x;
        } else {
            for (i = 0; i <= n1.tamanho - 2; i++) {
                a.n[i] = n1.n[i+1];
            }
            a.tamanho = n1.tamanho-1;
            y = divisao(a, n2);
            z = subtracao(a, multiplicacao(y, n2));
            for (i = z.tamanho; i > 0; i--) {
                z.n[i] = z.n[i-1];
            }
            z.tamanho++;
            z.n[0] = n1.n[0];
            for (i = y.tamanho; i > 0; i--) {
                y.n[i] = y.n[i-1];
            }
            y.tamanho++;
            y.n[0] = 0;
            while (maiorEmModulo(z, k) == 1) {
                x.n[0]++;
                k = multiplicacao(x, n2);
            }
            x.n[0]--;
            y = soma (y, x);
            
            // Tratamento de tamanho para y
            for (i = y.tamanho - 1; i >= 0; i--) {
                if (y.n[i] == 0) {
                    y.tamanho--;
                } else {
                    break;
                }
            }
            
            // Tratamento de sinal para y
            if (n1.sinal == n2.sinal) {
                y.sinal = 1;
            } else {
                y.sinal = -1;
            }
            return y;
        }
    }

    static numero moduloN (numero n, numero mod) {
        numero n1;
        n1 = divisao(n, mod);
        n1 = multiplicacao(n1, mod);
        n1 = subtracao(n, n1);
        return n1;
    }
    
    static numero multiplicacaoModular (numero n1, numero n2, numero N) {
        numero n;
        //n1 = moduloN(n1, N);
        //n2 = moduloN(n2, N);
        n = multiplicacao(n1, n2);
        n = moduloN(n, N);
        return n;
    }
    
    static numero exponenciacaoModular (numero n1, numero n, numero mod) {
        numero z = new numero();
        z.n[0] = 1;
        z.tamanho = 1;
        
        numero dois = new numero();
        dois.tamanho = 1;
        dois.n[0] = 2;
        
        if (n.tamanho == 0) {
            
        } else {
            z = exponenciacaoModular(n1, divisao(n, dois), mod);
            z = multiplicacaoModular(z, z, mod);
            if (n.n[0] % 2 == 1) {
                z = multiplicacaoModular(z, n1, mod);
            }
        }
        return z;
    }
}
