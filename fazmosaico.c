//ssh gs12@macalan.c3sl.ufpr.br
// gcc `pkg-config --cflags --libs opencv` -o fazmosaico fazmosaico.c

//./fazmosaico 14.jpg ci067 mosaic.txt 1 10

#include <stdlib.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#define M 6
#define ZERO 0
#define UM 1
#define DOIS 2

typedef struct auxiliar {
	char n[10];
	int r;
	int g;
	int b;
} auxiliar;

//Protótipos de funções
void  encontrar_car (IplImage *img , int *red, int *green, int *blue);
char * dados(int red,int green,int blue, char * foto);
void mosaico (IplImage *img, char * inf[]);

void subimg(IplImage *img, char *nome, int k, int l, int tamm)
{
	IplImage *imagem;
	int a,b,i,j,x=ZERO,y=ZERO;
	int altura    = img->height;            //altura da imagem
	int largura   = img->width;	        //largura da imagem
	int step      = img->widthStep;         //tamanho de uma linha em bytes	
	int channels  = img->nChannels;         // chanel representa 3 cores
	uchar * data  = (uchar *)img->imageData;// data é um vetor que guarda todos  os pixels

	a=(altura/tamm);
	b=(largura/tamm);
	
	imagem=cvLoadImage(nome,1);
	printf("%s",nome);

	IplImage* imgnew = cvCreateImage(cvSize(b, a), img->depth, 3); //nova imagem com o tamanho que é preciso
        cvResize(imagem, imgnew,CV_INTER_LINEAR ); //reduz a foto para o tamanho necessario
	int step2      = imgnew->widthStep; //tamanho de uma linha em bytes	
	uchar * data2  = (uchar *)imgnew->imageData;// data é um vetor que guarda todos  os pixels

	        printf("ok4\n");
	
	//cvNamedWindow("Imagem", CV_WINDOW_AUTOSIZE);
	///cvShowImage("Imagem", imgnew);
	//cvWaitKey(0);
		        printf("ok5\n");
	for(i=k*a; i<(k+1)*a; i++,x++)
        	for(j=l*b,y=0;j<(l+1)*b; j++,y++)
		{
			data[i*step+j*channels+0]=data2[x*step2+y*channels+0];
     	               	data[i*step+j*channels+1]=data2[x*step2+y*channels+1];
            		data[i*step+j*channels+2]=data2[x*step2+y*channels+2];
        	}
	// libera a imagem
	//cvReleaseImage(&imagem);
	cvReleaseImage(&imgnew);

}

char * dados(int red,int green,int blue, char *arq)
{
	FILE *car;
	auxiliar aux;
	int a,b=10000;
	char *nome;

	car=fopen(arq, "r");
	nome=(char*)malloc(sizeof(char)*10);

	while (!feof(car))
	{
		fscanf(car, "%[^:]:%d:%d:%d\n",aux.n,&aux.r,&aux.g,&aux.b);
		a=(abs((aux.r) -(red)) + abs((aux.g)-(green)) + abs((aux.b) -(blue)));
		
		if (a<b)
		{
			b=a;
			sprintf(nome, "%s",aux.n);
		}
	}
	        printf("ok2 \n");
	fclose(car); 
	return nome;
}

void mosaico (IplImage *img, char * inf[])
{
int i,j,a,b,c,k,l;
int red,green,blue;
int altura, largura,step,channels;
    uchar *data;
char *nome;
// recupera parametros da imagem
altura    = img->height;
largura   = img->width;
step      = img->widthStep; //tamanho de uma linha em bytes
channels  = img->nChannels;// channel representa 3 cores
data      = (uchar *)img->imageData;// data é um vetor que guarda todos  os pixels

//divide a foto
c=atoi(inf[5]); //tammatriz
a=(altura/c);
b=(largura/c);


// pega a carct da primeira posição
	for (k=0; k<c;k++)
	{
		for (l=0; l<c;l++)
		{
			red=0; green=0; blue=0;
			for(i=k*a; i<(k+1)*a; i++)
        			for(j=l*b;j<(l+1)*b; j++)
				{
					red = red + data[i*step+j*channels+0];
     		                	green = green+data[i*step+j*channels+1];
                			blue = blue +data[i*step+j*channels+2];
        			}			
		        red= red/(a*b); // altura e largura da regiao  
        		green= green/(a*b); 
        		blue= blue/(a*b);
	        printf("ok1 %d %d\n", k, l);
			// busca no banco de dados a caract mais proxima
			nome= dados(red,green,blue, inf[3]);

			//substitui o pedaço da foto
			subimg(img, nome,k,l,c);
	        printf("ok3 %d %d\n", k, l);
		}
	}




//vai para a proxima possição
}	

int main(int argc, char *argv[])
{
IplImage *img; 


char nome[10];
int i=1;
int red, green, blue;

	if(argc != M)
	{
		// senao existir parametros na execuçao do programa, o programa é interrompido 
		printf("Erro. Comandos insuficientes");
		exit(1);
	}

        img=cvLoadImage(argv[1],1);

	mosaico(img,argv);

	cvSaveImage("nova.jpg",img,0);                    
}//fecha main 
