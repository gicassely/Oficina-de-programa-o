/* Limiarizacao, marca escuros

 gcc `pkg-config --cflags --libs opencv` -o mosaic mosaic.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
void  encontrar_car (IplImage *img , int *red, int *green, int *blue  );

int main(int argc, char *argv[])
{
IplImage *img; 
FILE *base;


char nome[10];
int i=1;
 int red, green, blue;


 base = fopen(argv[1], "w");
          if(base != NULL)
      {
          sprintf(nome, "%d.jpg", i);
       img=cvLoadImage(nome,1);
            while(img){
        encontrar_car (img, &red, &green, &blue);
         fprintf (base, "%s:%d:%d:%d\n", nome, red, green, blue );
       
       i++;
       sprintf(nome, "%d.jpg", i); 
        img=cvLoadImage(nome,1);
           
       }  
     fclose(base);                     
    }
}//fecha main 
     
   void  encontrar_car (IplImage *img , int *red, int *green, int *blue  )  
    {
       
   int altura, largura,step,channels;
    uchar *data;
   int i, j;
   // recupera parametros da imagem
  altura    = img->height;
  largura  = img->width;
  step      = img->widthStep;
  channels  = img->nChannels;// chanel representa 3 cores
  data      = (uchar *)img->imageData;// data é um vetor que guarda todos  os pixels
            
   *red=0; *green=0; *blue=0;
       for(i=0; i<altura; i++)
        for(j=0;j<largura; j++){
         *red = *red + data[i*step+j*channels+0];
         *green = *green+data[i*step+j*channels+1];
          *blue = *blue +data[i*step+j*channels+2];
          }
        *red= *red/(altura*largura);  
        *green= *green/(altura*largura); 
        *blue= *blue/(altura*largura);
  } 
          
/*int main(int argc, char *argv[])
{
  IplImage *img; 
  int height,width,step,channels;
  uchar *data;
  int i,j,limiar;

  if(argc<4){
    printf("Usage: marca_escuros <limiar> <imagem> <imagem_saida>\n");
    exit(0);
  }

  limiar = atoi(argv[1]);

  // carrega imagem  
  img=cvLoadImage(argv[2],1);
  if(!img){
    printf("Erro na leitura da imagem: %s\n",argv[2]);
    exit(0);
  }

  // recupera parametros da imagem
  height    = img->height;
  width     = img->width;
  step      = img->widthStep;
  channels  = img->nChannels;
  data      = (uchar *)img->imageData;

  // imprime atributos da imagem
  printf("\n%s tem tamanho %d x %d\n", argv[2], height, width);

  // atribui cor preta para os pontos escuros na imagem
  for(i=0;i<height;i++)
    for(j=0;j<width;j++) 
      if(data[i*step+j*channels+0] < limiar &&
	 data[i*step+j*channels+1] < limiar &&
	 data[i*step+j*channels+2] < limiar){
	data[i*step+j*channels+0]=0;
	data[i*step+j*channels+1]=0;
	data[i*step+j*channels+2]=0;
      }

  // salva a imagem de saida
  cvSaveImage(argv[3],img,0);

  // libera a imagem
  cvReleaseImage(&img);
  return 0;
}*/
