#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>

#define UP_P1 119   //w
#define DOWN_P1 115 //s
#define UP_P2 111   //o
#define DOWN_P2 108 //l

void interrupt (*old_rutina)(void);

typedef struct
{
    int hora;
    int min;
    int seg;
} rel;

rel reloj;
int i = 0;
int j = 0;
int barra1x = 0;
int barra1y = 0;
int barra2x = 0;
int barra2y = 0;
int perdedor = 0;
int xmax, ymax;
int inicialxo, inicialyo;

void interrupt rutina(void)
{
    disable();
    i++;
    if ((i % 20) == 0)
    {

	if ((reloj.seg == 59) && (reloj.min == 59))
	{
	    reloj.seg = 0;
	    reloj.min = 0;
	    reloj.hora++;
	}
	else if (reloj.seg == 59)
	{
	    reloj.seg = 0;
	    reloj.min++;
	}
	reloj.seg++;
    }
    old_rutina();
    enable();
}

void moverBarra(char c)
{
    switch (c)
    {
    case 'w': //mover p1 para arriba
    {
	if (barra1y > (inicialyo + 2))
	{
	    gotoxy(barra1x, barra1y);
	    putch(' ');
	    barra1y--;
	    gotoxy(barra1x, barra1y);
	    putch('|');
	}
	break;
    }
    case 's': //mover barra P1 abajo
    {
	if (barra1y < (inicialyo + ymax))
	{
	    gotoxy(barra1x, barra1y);
	    putch(' ');
	    barra1y++;
	    gotoxy(barra1x, barra1y);
	    putch('|');
	}
	break;
    }
    case 'o': //mover barra P hacia arriba
    {
	if (barra2y > (inicialyo + 2))
	{
	    gotoxy(barra2x, barra2y);
	    putch(' ');
	    barra2y--;
	    gotoxy(barra2x, barra2y);
	    putch('|');
	}
	break;
    }
    case 'l': //mover barra P2
    {
	if (barra2y < (inicialyo + ymax))
	{
	    gotoxy(barra2x, barra2y);
	    putch(' ');
	    barra2y++;
	    gotoxy(barra2x, barra2y);
	    putch('|');
	}
	break;
    }
    default:
    {
	perdedor = 3;
	gotoxy(55, 15);
	printf(" EXIT GAME");
	break;
    }
    }
}

//int main(void)
void juego2()
{
    //declaracion de variables
    int k;
    struct tm *now;
    time_t s;
    int posicionx, posiciony;
    int xs = 1, ys = 1;
    struct text_info initial_info;
    int cuadrante = 1;
    //int gdriver=DETECT, gmode;
    char c;

    clrscr();

    gettextinfo(&initial_info);
    xmax = initial_info.screenwidth / 2;
    ymax = initial_info.screenheight / 2;

    //------RELOJ-------//
    //old_rutina = getvect(8);
    //setvect(8, rutina);

    //declaracion de cuadrantes
    inicialxo = cuadrante == 1 || cuadrante == 3 ? 0 : xmax; //si cuadrante es 1 o 3, empieza en 0 sino en 41
    inicialyo = cuadrante == 1 || cuadrante == 2 ? 0 : ymax; //si cuadrante es 1 o 2, empieza en 0 sino en 13

    posicionx = inicialxo + (xmax/2);
    posiciony = inicialyo + (ymax/2);

    //Posicion inicial barras
    barra1x = inicialxo + 2;
    barra2x = inicialxo + xmax - 2;
    barra1y = inicialyo + 4;
    barra2y = inicialyo + 4;
    gotoxy(barra1x, barra1y);
    putch('|');
    gotoxy(barra2x, barra2y);
    putch('|');

    while (perdedor == 0)
    {

	//Esperar por tecla presionada
	//while ((!kbhit())&&(perdedor==0))
	if (!kbhit())
	{

	    ///reloj
	    gotoxy(50, 20);      //posicion x,y
	    s = time(NULL);      // guardar la variable null temporal
	    now = localtime(&s); //actualizar la hora acorde a la temporal
	    //e imprimir al momento de obtener para borrar la anterior, similar
	    //a una variable de adorno
	    printf("%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
	    //imprimir hora

	    //----RELOJ-------//
	    gotoxy(45, 22);
	    printf("Tiempo de juego %02d:%02d:%02d", reloj.hora, reloj.min, reloj.seg);

	    delay(100);
	    gotoxy(posicionx, posiciony);
	    putch('*');
	    gotoxy(inicialxo + 1, inicialyo + 1);
	    delay(100);
	    gotoxy(posicionx, posiciony);
	    putch(' ');

	    // Avanza pelota segun nueva direccion
	    posicionx += xs;
	    posiciony += ys;

	    //Si pelota choca contra alguna pared arriba o abajo
	    if (posiciony >= inicialyo + ymax || posiciony <= inicialyo + 1)
		//xs=1;
		ys=-ys

	    // Si pelota choca contra la barra de un jugador
	    else if (posicionx == barra1x && (posiciony == barra1y))
		xs = 1;
	    else if (posicionx == barra2x && (posiciony == barra2y))
		xs = -1;

	    //Si pelota choca en alguna pared lateral FIN DEL JUEGO
	    else if (posicionx >= inicialxo + xmax)
	    {
		perdedor = 2;
		//break;
	    }
	    else if (posicionx <= inicialxo +1)
	    {
		perdedor = 1;
		//break;
	    }
        }
        else
        {
            //c=getch();
            //gotoxy(55,15);
            //printf("TECLA PRESIONADA %c",c);
            moverBarra(getch());
        }
    }; //endwhile

    gotoxy(50, 24);
    if(perdedor != 3)
       printf("GAME OVER, jugador %d ha perdido\n", perdedor);

    delay(5000);

    // closegraph();
    //return 0;
    exit(0);
}
