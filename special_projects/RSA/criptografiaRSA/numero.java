   // Nome da classe:  numero
   // Escrito por: Gabriel Estevam Oliveira
   // Data: 28 de outubro de 2016
   // Proposito: Definir um tipo de objeto, numero, para guardar um numero com grande quantidade de algarismos.
   //
   // Atributos:
   //       n[]         Vetor de inteiros, cada posicao armazera um algarismo na base 10 do numero a ser guardado.
   //                   Os algarismos sao armazenados da esquerda para a direita, ou seja, ficam no inicio do vetor e na ordem inversa.
   //
   //       sinal       Armazena o sinal do numero a ser guardado.
   //                   Ha apenas dois valores possiveis, 1 se o numero for positivo e -1 se o numero for negativo                
   //                   Obs: o tratamento de sinal foi necessario devido a funcao EuclidesEstendido(classe criptografiaRSA) poder retornar numero negativos.
   //
   //       tamanho     Armazena a quantidade de posicoes utilizadas no armazenamento do numero.
   //                   Todas as operacoes realizados com o numero levam em consideracao apenas esta quantidade de posicoes.
   //
   // Funcoes:
   //       numero ()
   //           Construtor do numero. Determina valor default para sinal como 1 (positivo) e tamanho como 0 (que determina o valor nulo para o numero).       
   //                 
   //       void imprimirNumero()
   //           Funcao que imprime o numero no terminal, algarismo por algarismo. 
   //           O vetor é percorrido da direita para esquerda considerando apenas as posicoes utilizadas.
   //

public class numero {
    
    int n[] = new int [500];
    int sinal; // sinal = 1 para positivo e sinal = -1 para negativo
    int tamanho; // (tamanho-1)posicao em que a parte util do numero termina
    
    numero() {
        sinal = 1;
        tamanho = 0;
    }
    
    void imprimirNumero () {
	int i;
        if (sinal == -1)
            System.out.print("-");
  	for (i = tamanho-1; i >= 0; i--) {
		System.out.print(n[i]);
	}
	System.out.println();
    }
}
