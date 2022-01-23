/*Programmazine linguaggio macchina*/
#include <stdio.h>
#include <stdlib.h>

/*Prototipi di funzione*/
void read(int m[], int *o);
void write(int m[], int *o);
void dump(int m[], int *acc);
void load(int m[], int *o, int *acc);
void store(int m[], int *o, int *acc);
void add(int m[], int *o, int *acc);
void multiply(int m[], int *o, int *acc);
void subtract(int m[], int *o, int *acc);
void divide(int m[], int *o, int *acc);
void branch(int m[], int *istru, int *o);
void branchneg(int m[], int *acc, int *o, int *istru);
void branchzero(int m[], int *acc, int *o, int *istru);
void stampa_messagio();

/*Costanti simboliche CODICI DI ATTIVAZIONE*/
#define SIZE 100
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43
#define DUMP 50

/*Funzione principale*/
main()
{
      int memoria[SIZE] = {0}, comando, accomulatore = 0, cont_comandi = 0, reg_comandi = 0, ocode = 0, operando = 0, cont;
      
      /*messagio principale*/
      stampa_messagio();
      
      /*Inserisci le istruzioni in memoria finch� non viene inserito il comando sentinella*/
      do
      {
                  printf("%d ---- ", cont_comandi);
                  
                 /*inserisce l'istruzione*/
                 scanf("%d", &comando);
                 
                 /*verifica se il comando inserito sia un comando valido*/
                 /*se e compreso tra -9999 e 9999*/
                 if(comando >= -9999 && comando <= 9999)
                 {
                            /*assegna la parola in memoria*/
                            memoria[cont_comandi] = comando;
                            ++cont_comandi;
                 }
                 else
                 {
                     /*messaggio di errore*/
                     printf("Il numero non e di 4 cifre\n\n");
                     getch();
                     system("cls");
                     
                     /*Menu principale*/
                     stampa_messagio();
                     
                     /*ristampa la lista comandi fino alla posizione attuale*/
                     for(cont = 0; cont < cont_comandi; cont++)
                     {
                              printf("%d ---- %d\n", cont, memoria[cont]);
                     }
                 }
                 
          
      }while(comando != 9999);
      
      /*azzera cont_comandi*/
      cont_comandi = 0;
      
      /*Esegue tutte le operazioni inserite nel vettore memoria[]*/
      do
      {
                                  /*copia nella variabile reg_comandi l'istruzione inserita nella locazione di memoria corrente*/
                                  reg_comandi = memoria[cont_comandi];
                                  ++cont_comandi;
                                  
                                  /*assegna le prime 2 cifre del comando cioe il codice di operazione*/
                                  ocode = reg_comandi / 100;
                                  
                                  /*assegna le ultime 2 cifre del comando cioe l'operando*/
                                  operando = reg_comandi % 100;
                                  
       
                                  /*Comando READ
                                  Legge un numero e lo inserisce in memoria*/
                                  if(ocode == READ)
                                  {
                                             read(memoria, &operando); 
                                  }
                     
                                  /*comando WRITE*/
                                  /*Stampa la parola contenuta in una locazione di memoria*/
                                  else if(ocode == WRITE)
                                  {
                                       write(memoria, &operando);
                                  }
                     
                                  /*comando LOAD*/
                                  /*Carica la parola di una locazione di memoria nell'accomulatore*/
                                  else if(ocode == LOAD)
                                  {
                                       load(memoria, &operando, &accomulatore);
                                  }
                                  
                                  /*comando STORE*/
                                  /*Archivia il contenuto dell'accomulatore in una locazione di memoria*/
                                  else if(ocode == STORE)
                                  {
                                       store(memoria, &operando, &accomulatore);
                                  }
                                  
                                  /*Comando ADD*/
                                  /*Aggiunge una parola contenuta in una locazione di memoria all'accomulatore*/
                                  else if(ocode == ADD)
                                  {
                                       add(memoria, &operando, &accomulatore);
                                  }
                                
                                  /*comando SUBTACT*/
                                  /*Sottrae una parola contenuta in una locazione di memoria dall'accomulatore*/
                                  else if(ocode == SUBTRACT)
                                  {
                                       subtract(memoria, &operando, &accomulatore);
                                  }
                                  
                                  /*comando MULTIPLY*/
                                  /*Moltiplica una parola contenuta in una locazione di memoria all'accomulatore*/
                                  else if(ocode == MULTIPLY)
                                  {
                                       multiply(memoria, &operando, &accomulatore);
                                  }
                                  
                                  /*comando DIVIDE*/
                                  /*divide una parola contenuta in una locazione di memoria all'accomulatore*/
                                  else if(ocode == DIVIDE)
                                  {
                                       /*se la divisione e per 0*/
                                       if(memoria[operando] == 0)
                                       {
                                                           printf("Non e possibile effettuare una divisione per 0");
                                                           getch();
                                                           ++cont_comandi;
                                       }
                                       else
                                       {
                                           divide(memoria, &operando, &accomulatore);
                                       }
                                  }
                                  
                                  /*Comando BRANCh*/
                                  /*Salta a una specifica locazione di memoria*/
                                  else if(ocode == BRANCH)
                                  {
                                       branch(memoria, &cont_comandi, &operando);
                                  }
                                  
                                  /*comando BRANCHNEG*/
                                  /*salta a una specifica locazione di memoria sei l'accomulatore e negativo*/
                                  else if(ocode == BRANCHNEG)
                                  {
                                       branchneg(memoria, &accomulatore, &operando, &cont_comandi);
                                  }
                                  
                                  /*comando BRANCHNEG*/
                                  /*salta a una specifica locazione di memoria sei l'accomulatore e negativo*/
                                  else if(ocode == BRANCHZERO)
                                  {
                                       branchzero(memoria, &accomulatore, &operando, &cont_comandi);
                                  }

                                  /*comando DUMP*/
                                  /*Visualizza la memoria del simpleton con tutte le parole inserite*/
                                  else if(ocode == DUMP)
                                  {
                                       dump(memoria, &accomulatore);
                                  }
                                  
                                  else{
                                  	ocode = 43;
								  }
       }while(ocode != 43);
       printf("Programma terminato");
       getch();
}

/*Funzione READ
  Legge una parola dal terminale e la inserisce in una locazione di memoria*/
void read(int m[], int *o)
{
     int numero;
     printf("\n\n\n\n                Comando 0\n\n");
     printf("-----------------------------------------\n");
     printf("          Comando inserito READ\n");
     printf("-----------------------------------------\n\n");
                     
     /*Verifica che la locazione di memoria non sia gia stata utilizata*/
     /*Se � libera*/
     if(m[*o] == 0)
     {
                        printf("Inserisci un numero da inserire nella locazione %d: ", *o);
                        scanf("%d", &numero);
                                        
                        /*se il numero inserito e di 4 cifre*/
                        if(numero > -10000 && numero < 10000)
                        {
                                  /*assegna il numero alla locazione in memoria*/
                                  m[*o] = numero;
                                  printf("\n\n********** La cifra %d e stata inserita nella locazione %d **********\n\n\n\n\n", numero, *o);
                                  getch();
                        }
                                        
                        /*altrimenti reinserire*/
                        else
                        {
                            printf("\n\n\n\n********** Comando NON VALIDO **********\n\n\n\n\n\n");
                            getch();
                        }
                                        
     }
                     
     /*Messaggio di errore*/
     else
     {
                 printf("\n\n ********** Memoria %d gia stata utilizzata **********\n\n\n\n\n", *o);
                 getch();
     }
}

/*Stampa la memoria del simpleton con tutte le parole inserite*/
void dump(int m[], int *acc)
{
     int cont, cont2 = 0;
     
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito DUMP\n");
     printf("-----------------------------------------\n\n");
     printf("\n\nAccomulatore = %d\n", *acc);
     printf("        0     1     2     3     4     5     6     7     8     9\n");
     for(cont = 0; cont < 100; cont++)
     {
           /*se e stata creata la decima colonna vai a capo*/
           if(cont % 10 == 0)
           {
                   if(cont < 10)
                   {
                           printf("\n\n %d     ", cont);
                   }
                   else
                   {
                       printf("\n\n %d    ", cont);
                   }
           }
           printf("%.4d  ", m[cont]);
     }
     getch();
}

/*Funzione WRITE
 stampa a video la parola contenuta in una locazione di memoria*/
void write(int m[], int *o)
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito WRITE\n");
     printf("-----------------------------------------\n\n");
     printf("La parola contenuta nella locazione %d e %d\n\n\n\n\n", *o, m[*o]);
     getch();
}

/*Funzione LOAD*/
/*Aggiunge la parola contenuta in una locazione di memoria nell'accomulatore*/
void load(int m[], int *o, int *acc) 
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito LOAD\n");
     printf("-----------------------------------------\n\n");
     printf("La parola %d contenuta nella locazione %d e stata assegnata all'accomulatore\n\n\n\n\n", m[*o], *o);
     *acc = m[*o];
     getch();
}

/*Funzionne add*/
/*Aggiunge una parola da una locazione di memoria all'accomulatore*/
void add(int m[], int *o, int *acc)
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito ADD\n");
     printf("-----------------------------------------\n\n");
     printf("La parola %d contenuta nella locazione %d e stata sommata all'accomulatore", m[*o], *o);
     *acc += m[*o];
     getch();
}

/*Funzionne DIVIDE*/
/*Divide una parola da una locazione di memoria all'accomulatore*/
void divide(int m[], int *o, int *acc)
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito DIVIDE\n");
     printf("-----------------------------------------\n\n");
     printf("La parola %d contenuta nella locazione %d e stata divisa dall'accomulatore", m[*o], *o);
     *acc /= m[*o];
     getch();
     system("cls");
}

/*comando STORE*/
/*Archivia il contenuto dell'accomulatore in una locazione di memoria*/
void store(int m[], int *o, int *acc)
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito STORE\n");
     printf("-----------------------------------------\n\n");
     printf("Il contenuto dell'accomulatore %d e stato salvato nella locazione %d", *acc, *o);
     m[*o] = *acc;
     getch();
}

/*comando SUBTACT*/
/*Sottrae una parola contenuta in una locazione di memoria dall'accomulatore*/
void subtract(int m[], int *o, int *acc)
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito SUBTRACT\n");
     printf("-----------------------------------------\n\n");
     printf("La parola %d contenuta nella locazione %d e stata sottratta dall'accomulatore", m[*o], *o);
     *acc -= m[*o];
     getch();
}

void multiply(int m[], int *o, int *acc)
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito MULTIPLY\n");
     printf("-----------------------------------------\n\n");
     printf("La parola %d contenuta nella locazione %d e stata moltiplicata all'accomulatore", m[*o], *o);
     *acc *= m[*o];
     getch();
}

void branch(int m[], int *istru, int *o)
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito BRANCH\n");
     printf("-----------------------------------------\n\n");
     printf("Il controllo e stato spostato dalla locazione %d alla %d", *istru - 1, *o);
     *istru = *o;
     getch();
}

void branchneg(int m[], int *acc, int *o, int *istru)
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito BRANCHNEG\n");
     printf("-----------------------------------------\n\n");
     
     /*se l'accomulatore e negativo*/
     if(*acc < 0)
     {
             printf("Il controllo e stato spostato dalla locazione %d alla %d", *istru - 1, *o);
             *istru = *o;
     }
     else
     {
         printf("L'accomulatore non e negativo");
     }
     getch();
}

void branchzero(int m[], int *acc, int *o, int *istru)
{
     printf("\n\n\n\n-----------------------------------------\n");
     printf("          Comando inserito BRANCHZERO\n");
     printf("-----------------------------------------\n\n");
     
     /*se l'accomulatore e uguale a zerp*/
     if(*acc == 0)
     {
             printf("Il controllo e stato spostato dalla locazione %d alla %d", *istru - 1, *o);
             *istru = *o;
     }
     else
     {
         printf("L'accomulatore non e uguale a zero");
     }
     getch();
}

/*stampa messagio principale*/
void stampa_messagio()
{
     /*Menu principale*/
      printf("\n\n\n          *****   Benvenuti a Simpletron                  *****\n");
      printf("          *****   Inserisci nel programma un istruzione   *****\n");
      printf("          *****   (o dei dati) alla volta.                *****\n");
      printf("          *****   Il codice aperazione e la locazione     *****\n");
      printf("          *****   in memoria.                             *****\n");
      printf("          *****   Inserisci 9999 per terminare           *****\n");
      printf("          *****   Simpletron                              *****\n");
      printf("\n\n\n\n\nInserisci i comandi\n\n");
}
