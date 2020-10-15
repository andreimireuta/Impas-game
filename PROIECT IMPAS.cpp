#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <winbgim.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <cstdlib>

using namespace std;
struct punct{
    int x,y; //Coordonatele punctelor in spatiu
};
struct dreptunghi{
    punct p1; //punctul 1 de coordonate x si y
    punct p2;  // punctul 2 de coordonate x si y
    int numar;
}meniuPrincipal[5],tablaJoc[9][9],mingi[17]; // maparea meniului , a tablei de joc si ale mingilor (retine unde dam click)
int minge[9][9];
bool intre(int a,int x, int y) // verifica daca un punct de afla intre 2 coordonate
{
    return (a>=x and a<=y);
}
void Meniu() //creeaza meniul
{
    char texte[6][100] =    {
                                    "0",
                                    "Player Vs. Player", //optiunile din meniu
                                    "Player Vs. Computer",
                                    "Instructiuni",
                                    "Exit",
                            };
    initwindow(1000,700); // deschide ferestra meniului
    int numar = 4;        //numarul de chenare
    int spatiere = 20;    //spatiul dintre chenarele meniului
    int latime = 600;     //latimea chenarului din meniu
    int lungime = 150;     //lungimea chenarului
    for (int j = 1;j<=numar;j++) // asezarea in meniu a fiecarui chenar folosind o formula cu j
    {

        rectangle(200,(lungime*(j-1)+spatiere*j),800,((lungime+spatiere)*j)); // crearea fiecarui cheanar al meniului
        settextstyle(BOLD_FONT,HORIZ_DIR,5); // fontul ales, modul in care scriem (orizontal) si dimensiunea
        outtextxy(300,(lungime*(j-1)+spatiere*j)+55,texte[j]); //scrierea textuului bazandu ne pe coordonatele x si y
        meniuPrincipal[j].p1.x = 200;
        meniuPrincipal[j].p1.y = (lungime*(j-1)+spatiere*j);   //aici am marcat coordonatele meniului
        meniuPrincipal[j].p2.x = 800;
        meniuPrincipal[j].p2.y = (lungime+spatiere)*j;
    }

}
void initializareJoc()
{
    initwindow(1200,700);
    setfillstyle(1,BLUE);
    floodfill(10,10,3);
    int dist=70;
    for(int i =1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
            setcolor(WHITE);
            rectangle(dist*i,dist*j,dist*i+dist,dist*j+dist);
            tablaJoc[i][j].p1.x=dist*i;
            tablaJoc[i][j].p1.y=dist*j;
            tablaJoc[i][j].p2.x=dist*i+dist;
            tablaJoc[i][j].p2.y=dist*j+dist;
        }
    }
    setfillstyle(1,RED);
    for(int i=1;i<=4;i++)
        for(int j=5;j<=8;j++)
        {
            fillellipse(dist*i+35,dist*j+35,30,30);
            mingi[(i-1)*4+(j-4)].p1.x=dist*i;
            mingi[(i-1)*4+(j-4)].p1.y=dist*j;
            mingi[(i-1)*4+(j-4)].p2.x=dist*i+dist;
            mingi[(i-1)*4+(j-4)].p2.y=dist*j+dist;
            minge[i][j]=(i-1)*4+(j-4);

        }
    char texte2[4][100]={   "0",
                            "Time",
                            "Scor",
                            "PREDARE",
                        };
        rectangle(770,50,1130,200);
        rectangle(770,250,1130,400);
        rectangle(770,450,1130,600);
        settextstyle(BOLD_FONT,HORIZ_DIR,4);
        outtextxy(885,65,texte2[1]);
        outtextxy(885,270,texte2[2]);
        settextstyle(BOLD_FONT,HORIZ_DIR,4);
        outtextxy(885,460,texte2[3]);

}
void getCasuta(int &x,int &y)
{
    int xMouse = mousex();
    int yMouse = mousey();
    for(int i=1;i<=8;i++)
        for(int j=1;j<=8;j++)
        {
            if(intre(xMouse,tablaJoc[i][j].p1.x,tablaJoc[i][j].p2.x) and intre(yMouse,tablaJoc[i][j].p1.y,tablaJoc[i][j].p2.y))
            {
                x=i;
                y=j;
                return;
            }
        }
    x=0;
    y=0;

}
void gaseste(int x,int y,int &xMinge,int &yMinge)
{
    for(int i = y+1;i<=8;i++)
        if(minge[x][i]!=0)
        {
            xMinge=x;
            yMinge=i;
            return;
        }
    xMinge=0;
    yMinge=0;
}
void muta(int x,int y,int xMinge,int yMinge)
{
    cout<<"da intra!\n";
    int dist = 70;
    setfillstyle(1,RED);
    fillellipse(dist*x+35,dist*y+35,30,30);
    minge[x][y]=1;
    setfillstyle(1,WHITE);
    floodfill(dist*xMinge+35,dist*yMinge+35,WHITE);
    setfillstyle(1,BLUE);
    floodfill(dist*xMinge+35,dist*yMinge+35,BLUE);
    minge[xMinge][yMinge]=0;
    cout<<minge[xMinge][yMinge];
}
bool predare(int x,int y)
{
    if(x>=770 and x<=1130 and y>=450 and y<=600)
        return TRUE;
    return FALSE;
}
void mutareJucator1()
{

    while(TRUE){

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x,y;
            x=mousex();
            y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            if(predare(x,y)==1)
                {
                    initwindow(600,500);
                    outtextxy(200,200,"Jucatorul 2 a castigat prin predare");
                    getchar();
                    return;
                }
            else
            getCasuta(x,y);
            if(x!=0 and y!=0)
            {
                cout<<"gasit casuta";
                if(minge[x][y]==FALSE)
                {
                    int xMinge,yMinge;
                    gaseste(x,y,xMinge,yMinge);
                    cout<<xMinge<<" "<<yMinge<<'\n';
                    if(xMinge!=0 and yMinge!=0)
                    {
                        muta(x,y,xMinge,yMinge);
                        return;
                    }
                }
            }
        }
    }
}
void gaseste2(int x,int y,int &xMinge,int &yMinge)
{
    for(int i = x-1;i>=1;i--)
        if(minge[i][y]!=0)
        {
            xMinge=i;
            yMinge=y;
            return;
        }
    xMinge=0;
    yMinge=0;
}
void mutareJucator2()
{

    while(TRUE){

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x,y;
            x=mousex();
            y=mousey();

            clearmouseclick(WM_LBUTTONDOWN);
            if(predare(x,y)==1)
             {
                    initwindow(600,500);
                    outtextxy(200,200,"Jucatorul 1 a castigat prin predare");
                    getchar();
                    return;
            }
            else
            getCasuta(x,y);
            if(x!=0 and y!=0)
            {
                cout<<"gasit casuta";
                if(minge[x][y]==FALSE)
                {
                    int xMinge,yMinge;
                    gaseste2(x,y,xMinge,yMinge);
                    cout<<xMinge<<" "<<yMinge<<'\n';
                    if(xMinge!=0 and yMinge!=0)
                    {
                        muta(x,y,xMinge,yMinge);
                        return;
                    }
                }
            }
        }
    }
}
int SfarsitJoc()
{
    bool juc1=TRUE,juc2=TRUE;
    int nr = 0;
    for(int i =1;i<=8;i++)
    {
        int index = 1;
        while(minge[i][index])
            index++;
        nr+=index-1;
    }
    if(nr>=16)
    {
        juc1=FALSE;
    }

    nr = 0;
    for(int i =1;i<=8;i++)
    {
        int index = 1;
        while(minge[index][i])
            index++;
        nr+=index-1;
    }
    if(nr>=16)
    {
        juc2=FALSE;
    }
    if(juc1==FALSE)
    {
        if(juc2==FALSE){

            return 0;
        }
        else return 1;

    }
    else if(juc2==FALSE)
    {
        return 2;
    }
    return 3;

}
void castigaJ1()
{
    initwindow(600,400);
    outtextxy(200,200,"Felicitari! Jucatorul 1 a castigat");
    getchar();
}
void castigaJ2()
{
    initwindow(600,400);
    outtextxy(200,200,"Felicitari! Jucatorul 2 a castigat");
    getchar();
}
bool predare1()
{

}
bool predare2()
{

}
void pvp()
{

    bool gameOver = FALSE;
    initializareJoc();
    while(!gameOver)
    {
        mutareJucator1();
        int x = SfarsitJoc();
        if(x==0 )
        {
            castigaJ1();
            closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
        else if(x==1 )
        {
            castigaJ2();
           closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
        else if(x==2 )
        {
            castigaJ1();
           closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }

        mutareJucator2();
         x = SfarsitJoc();
        if(x==0 )
        {
            castigaJ2();
          closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
        else if( x==1)
        {
            castigaJ2();
           closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
        else if(x==2 )
        {
            castigaJ1();
          closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
    }
}

int GasireChenar()
{

    int x=mousex();
    int y=mousey();
    for(int i = 1;i<=4;i++)
    {
        if(intre(x,meniuPrincipal[i].p1.x,meniuPrincipal[i].p2.x) and intre(y,meniuPrincipal[i].p1.y,meniuPrincipal[i].p2.y))
            return i;
    }
    return 0;
}
void ComputerPlay()
{
    int x,y;
    bool gameOver=FALSE;
    int i,j;
    for(i=595;i>=105;i=i-70)
        for(j=595;j>=105;j=j-70)
        {
            getCasuta(j,i);
            if(x!=0 and y!=0)
            {
                cout<<"gasit casuta";
                if(minge[x][y]==FALSE)
                {
                    int xMinge,yMinge;
                    gaseste2(x,y,xMinge,yMinge);
                    cout<<xMinge<<" "<<yMinge<<'\n';
                    if(xMinge!=0 and yMinge!=0)
                    {
                        muta(x,y,xMinge,yMinge);
                        return;
                    }
                }
        }


}
}
void pvc()
{
    bool gameOver = FALSE;
    initializareJoc();
    while(!gameOver)
    {
        mutareJucator1();
        int x = SfarsitJoc();
        if(x==0){
            castigaJ1();
            closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
        else if(x==1)
        {
            castigaJ2();
           closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
        else if(x==2)
        {
            castigaJ1();
           closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }

        mutareJucator2();
        x = SfarsitJoc();
        if(x==0){
            castigaJ2();
          closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
        else if(x==1)
        {
            castigaJ2();
           closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
        else if(x==2)
        {
            castigaJ1();
          closegraph(ALL_WINDOWS);
            Meniu();
            gameOver=TRUE;
        }
    }
}
void instructiuni()
{
    //closegraph(ALL_WINDOWS);
    initwindow(600,400);
    outtextxy(200,200,"Jucatorul 1 muta in sus, jucatorul 2 muta in dreapta");
    while(!ismouseclick(WM_LBUTTONDOWN))
        ismouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONDOWN);
    Meniu();
    cout<<"a intrat in functia asta";
}
void alegereClick(bool &StartJoc){

    while(!StartJoc)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int chenar = GasireChenar();
            if(chenar==1)
            {
                StartJoc = TRUE;
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph(ALL_WINDOWS);
                pvp();
            }else if(chenar==2){
                StartJoc = TRUE;
                closegraph(ALL_WINDOWS);
                pvc();
            }
            else if(chenar==3){
                StartJoc = 0;
                clearmouseclick(WM_LBUTTONDOWN);
                closegraph(ALL_WINDOWS);
                instructiuni();
            }
            else if(chenar==4)
            {
                StartJoc = TRUE;
                closegraph(ALL_WINDOWS);
            }
            else {

                clearmouseclick(WM_LBUTTONDOWN);
            }

        }

    }

}
int main()
{
        bool StartJoc = FALSE ;
        Meniu();
        while(StartJoc==FALSE){
                alegereClick(StartJoc);
        }

        return 0;
}
