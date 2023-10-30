#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<graphics.h>

int N;
float yaricap;
float X=0,Y=0,g,h;

float mesafe(float aa, float bb){
    return aa*aa+bb*bb;
}

int main(){
    printf("Bir N sayisi giriniz : ");
    scanf("%d",&N);
    int noktalarx[N],noktalary[N];

    //dosyadan degerler aliniyor kordinatlar diziye ataniyor
    FILE *dosya;
    dosya = fopen("noktalar.txt","r");
    if(dosya!=NULL){
        for(int i=0 ; i<N ; i++){
            fscanf(dosya,"%d%d",&noktalarx[i],&noktalary[i]);
            X = X+noktalarx[i];
            Y = Y+noktalary[i];
        }
        X=X/N;
        Y=Y/N;
        printf("\nAlinan noktalar : \n\n");
        for(int j=0 ; j<N ; j++){
            printf("{%d,%d}\n",noktalarx[j],noktalary[j]);
        }
    }
    else{
        printf("Noktalar dosyasi bulunamadi!\n");
        return 0;
    }

    //merkez ve yaricap hesaplaniyor
    float P =1;
    int deneme;
    for(int i=0;i<30000;i++){
        int f=0;
        g=mesafe(X-noktalarx[0],Y-noktalary[0]);
        for(int j=1;j<N;j++){
            h=mesafe(X-noktalarx[j],Y-noktalary[j]);
            if(g<h){
                g=h;
                f=j;
                deneme=f;
            }
        }
        X=X+(noktalarx[f]-X)*P;
        Y=Y+(noktalary[f]-Y)*P;
        P=P*0.999;
    }
    yaricap=sqrt(g);

    printf("\nMerkez: { %f , %f }\n",X,Y);
    printf("Yaricap: %f\n",yaricap);

    initwindow(640,640,"pencere");

    //koordinat sistemi cizimi
    setcolor(WHITE);
    line(0,320,640,320); // x ekseni
    line(320,640,320,0); // y ekseni
    int c = -20;
    for(int a=0 ; a<=640 ; a=a+16){
        char sayi[3];
        pieslice(a,320,0,360,3);
        if(a%5==0 && a!=320){
             sprintf(sayi,"%d",c);
             outtextxy(a-8,330,sayi);
             pieslice(a,320,0,360,5);
        }
        c++;
    }
    int d = 20;
    for(int b=0 ; b<=640 ; b=b+16){
        char sayi[3];
        pieslice(320,b,0,360,3);
        if(b%5==0 && b!=320){
            sprintf(sayi,"%d",d);
            outtextxy(330,b-8,sayi);
            pieslice(320,b,0,360,5);
        }
        d--;
    }
    setcolor(YELLOW);
    line((X*16)+320,320-(Y*16),(noktalarx[deneme]*16)+320,320-(noktalary[deneme]*16));//yaricap
    //noktalarin gosterimi
    for(int k=0 ; k<N ; k++){
        setcolor(BLUE);
        pieslice((noktalarx[k]*16)+320,320-(noktalary[k]*16),0,360,5);
    }
    setcolor(LIGHTGREEN);
    circle((X*16)+320,320-(Y*16),(yaricap*16));//minimum cevreleyen cember
    setcolor(RED);
    pieslice((X*16)+320,320-(Y*16),0,360,5);//merkez gosterimi
    setcolor(LIGHTMAGENTA);
    outtextxy((X*16)+325,310-(Y*16),"M");

    getch();
    closegraph();

    return 0;
}
