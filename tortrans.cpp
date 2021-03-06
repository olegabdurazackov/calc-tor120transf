#include <stdio.h>
#include <math.h>
#include "tortrans.h"
TorTrans::TorTrans()
{
   //const float pi=3.14;
    nu=0.92; // КПД трансформатора
//    w1; /* число витков на вольт первичной обмотки */
//    w2; /* число витков на вольт вторичной обмотки */
    U1=220.0; // напряжение питания, В
    U2=12.6; // напряжение нагрузки, В
    U3=0; // напряжение нагрузки, В
    U4=0; // напряжение нагрузки, В
    U5=0; // напряжение нагрузки, В
    U6=0; // напряжение нагрузки, В
    r1; // активное сопротивление первичной обмотки, Ом
    r2; // активное сопротивление вторичной обмотки, Ом
    I1; // ток первичной обмотки , А
    I2=1.0; // ток вторичной обмотки , А
    A=4;  // плотность тока в обмотках,А/мм2 

    /*еры сердечника трансформатора*/
    D=8.0; // наружный диаметр сердечника, см
    d=5.0;  //внутренний диаметр сердечника, см
    h=2.0; // высота сердечника, см
    is_hot_steel=true; // горячекатанная сталь
    Ks=0.9; // коэф.заполнения сердечника железом
    Kok=0.3;// коэф.заполнения окна медью
    //mu=250;

    raschet0();
}

TorTrans::~TorTrans()
{

}

int TorTrans::raschet()
{
    printf("\nНачало расчета...\n");
    raschet0();
    float w;//число виктов на вольт
    if(is_hot_steel) w=ww1;
    else w=ww2;
    N1=U1*w;
    N2=U2*w*1.03;
    N3=U3*w*1.03;
    N4=U4*w*1.03;
    N5=U5*w*1.03;
    N6=U6*w*1.03;
    /* расчитываем диаметры проводов */
    d1=1.13*sqrt(I1/A);
    d2=1.13*sqrt(I2/A);
    d3=1.13*sqrt(I3/A);
    d4=1.13*sqrt(I4/A);
    d5=1.13*sqrt(I5/A);
    d6=1.13*sqrt(I6/A);
    r1=0.0175/((d1*d1*pi)/4)*N1*lo/100;
    r2=0.0175/((d2*d2*pi)/4)*N2*lo/100;
    r3=0.0175/((d3*d3*pi)/4)*N3*lo/100;
    r4=0.0175/((d4*d4*pi)/4)*N4*lo/100;
    r5=0.0175/((d5*d5*pi)/4)*N5*lo/100;
    r6=0.0175/((d6*d6*pi)/4)*N6*lo/100;

    //r2=r1*n2*(1.0-A)/A;
    printf("\nПараметры обмоток:\n");
    Kok=(d1*d1/4*pi*N1+d2*d2/4*pi*N2+d3*d3/4*pi*N3+d4*d4/4*pi*N4
            +d5*d5/4*pi*N5+d6*d6/4*pi*N6)*(1e-2)/So;
    printf("\tКоэффициент заполнения окна медью : %.3f\n",Kok);
    printf("\tCредняя длина витка : %.1f см\n", lo);
    printf("\n\tr1 = %.2f Ом,\tr2 = %.2f Ом\n",r1,r2);
    if(U3>0 || U4>0)
    {
        printf("\tr3 = %.2f Ом,\tr4 = %.2f Ом\n",r3,r4);
    }
    if(U5>0 || U6>0)
    {
        printf("\tr5 = %.2f Ом,\tr6 = %.2f Ом\n",r5,r6);
    }
//    N2=sqrt(n2)*N1;
    printf("\n\tN1 = %d ,\tN2 = %d \n",N1,N2);
    if(N3>0 || N4>0)
    {
        printf("\tN3 = %d ,\tN4 = %d \n",N3,N4);
    }
    if(N5>0 || N6>0)
    {
        printf("\tN5 = %d ,\tN6 = %d \n",N5,N6);
    }
  //  d1=sqrt(2.23e-4*lo*N1/r1);
  //  d2=sqrt(2.23e-4*lo*N2/r2);
    
    printf("\n\td1 = %.2f мм,\td2 = %.2f мм\n",d1,d2);
    if(N3>0 || N4>0)
    {
        printf("\td3 = %.2f мм,\td4 = %.2f мм\n",d3,d4);
    }
    if(N5>0 || N6>0)
    {
        printf("\td5 = %.2f мм,\td6 = %.2f мм\n",d5,d6);
    }
    //delta=9.0e-4*N1*I0;
    //printf("\tЗазор при сборке сердечника : %.2f мм\n",delta);
    /* рассчитываем заполнение окна */
    float l1=lo*N1/100;
    float l2=lo*N2/100;
    float l3=lo*N3/100;
    float l4=lo*N4/100;
    float l5=lo*N5/100;
    float l6=lo*N6/100;
    printf("\nРасход провода:\n");
    printf("\t%.2f = %.2f м \t%.2f = %.2f м\n",d1,l1,d2,l2);
    if(N3>0 || N4>0)
    {
        printf("\t%.2f = %.2f м \t%.2f = %.2f м\n",d3,l3,d4,l4);
    }
    if(N5>0 || N6>0)
    {
        printf("\t%.2f = %.2f м \t%.2f = %.2f м\n",d5,l5,d6,l6);
    }

    printf("\n");
    return 0;
}

int TorTrans::raschet0()
{
    Pgb=(U2*I2+U3*I3+U4*I4+U5*I5+U6*I6)/nu;
    I1=1.1*(Pgb/U1);
    //r1=(1-nu)*Ra;
    lc=((D-d)/4+d)*pi;;
    Sc=h*(D-d)/2;//*Ks;
    So=pi*d*d/4;
    lo=((D-d)+h*2+d); // todo  расчетная средняя длина витка
    if(Pgb<=10)
    {
        ww1=41/Sc;
        ww2=38/Sc;
        S=sqrt(Pgb);
        A=4.5;
        nu=0.8;
    }
    if(Pgb<=30 && Pgb>10)
    {
        ww1=36/Sc;
        ww2=32/Sc;
        S=sqrt(Pgb)/1.1;
        A=4.0;
        nu=0.9;
    }
    if(Pgb>30 && Pgb<=50)
    {
        ww1=33.3/Sc;
        ww2=29/Sc;
        S=sqrt(Pgb)/1.2;
        A=3.5;
        nu=0.92;
    }
    if(Pgb>50 && Pgb<=120)
    {
        ww1=32/Sc;
        ww2=28/Sc;
        S=sqrt(Pgb)/12;
        A=3.0;
        nu=0.95;
    }
    if(Pgb>120)
    {
        printf("\n Мощность трансформатора = %.1f  ватт ",Pgb);
        printf("\n Это вне компетенции данной программы\n");
        return 1;
    }
    if(S>Sc)
    {
        printf("\n Сердечник д.б. не менее %.2f см2",S);
        return 1;
    }
    if(d<sqrt(2.4*Sc))
    {
        printf("\n Внутренний диаметр сердечника Sc = %2.f -- (%.2f см) маловат",Sc,d);
        return 1;
    }
    printf("\n Мощность трансформатора = %.1f  ватт ",Pgb);
    print_data();
    return 0;
}

int TorTrans::print_data()
{
    printf("\nИсходные данные: \n");
    printf("\tНапряжение первичной обмотки = %.1f В\n",U1);
    printf("\tToк первичной обмотки = %.3f А \n", I1);
    printf("\tНапряжение вторичной обмотки = %.1f В\n",U2);
    printf("\tToк вторичной обмотки = %.3f А \n", I2);
    if(U3>0)
    {
        printf("\tНапряжение обмотки №3 = %.1f В\n",U3);
        printf("\tToк обмотки №3 = %.3f А \n", I3);
    }
    if(U4>0)
    {
        printf("\tНапряжение обмотки №4 = %.1f В\n",U4);
        printf("\tToк обмотки №4 = %.3f А \n", I4);
    }
    if(U5>0)
    {
        printf("\tНапряжение обмотки №5 = %.1f В\n",U5);
        printf("\tToк вторичной обмотки №5 = %.3f А \n", I5);
    }
    if(U6>0)
    {
        printf("\tНапряжение обмотки №6 = %.1f В\n",U6);
        printf("\tToк обмотки №6 = %.3f А \n", I6);
    }
    printf("\nПараметры сердечника трансформатора: \n");
    printf("\tis_hot_steel = %s\n",((is_hot_steel)?"true (Сталь горячекатанная)":"false (Сталь холоднокатанная)"));
    printf("\tСердечник : К%dX%dX%d  \n", (int)(D*10),(int)(d*10),(int)(h*10));
    printf("\tСечение окна  = %.2f(см) и железа = %.2f(см)\n",So, Sc);
    printf("\tСредняя длина магнитной силовой лuнuu : %.1f см\n", lc);


    return 0;
}

