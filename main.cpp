/* *************************************
 * Использована методика Николаенко М.Н.
 * опубликованная в книге 
 * "Секреты радиолюбителя-конструктора" 
 * в 2006г. 
 * 
 ************************************* */
#include <stdio.h>
#include <math.h>
#include "tortrans.h"
#include <iostream>
#include "charint.h"
#include <string.h>
int main(int argc, char *argv[])
{
    printf("\nИспользование : w -значение параметр...");
    printf("\n\tпример : w -Un 12.6 -In 3.5 -h 5.0\n");
    if (argc>0)
    {
      if (argc%2==0)
      {
          printf("\nневерное количество параметров : %d\n",argc);
          return 1;
      }
    }
    TorTrans tr;
    //std::cout<<'\n'<<"argc= "<<argc;
    for (int i=(argc-1)/2;i>0;i-=1)
    {
      printf("\n i=%d agr=%s",i,argv[i*2-1]);  
      //std::cout<<'\n'<<strcmp(argv[i*2-1],"-is_hot_steel");
      if (strcmp(argv[i*2-1],"-is_hot_steel")==0)
      {
          tr.is_hot_steel=false;
          continue;
      }
      CharInt chi(argv[i*2]);
     // std::cout<<"\n"
     //     <<argv[i*2-1]<< " : " <<argv[2*i]
      //    <<" =  "<<chi.dfloat  ;
      if (strcmp(argv[i*2-1],"-U1")==0)
      {
          tr.U1=(float)chi.dfloat;
         // std::cout<<"\n Ri="<<tr.Ri;
          continue;
      }
      if (strcmp(argv[i*2-1],"-U2")==0)
      {
          tr.U2=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-I2")==0)
      {
          tr.I2=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-U3")==0)
      {
          tr.U3=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-I3")==0)
      {
          tr.I3=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-U4")==0)
      {
          tr.U4=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-I4")==0)
      {
          tr.I4=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-U5")==0)
      {
          tr.U5=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-I5")==0)
      {
          tr.I5=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-U6")==0)
      {
          tr.U6=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-I6")==0)
      {
          tr.I6=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-D")==0)
      {
          tr.D=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-d")==0)
      {
          tr.d=(float)chi.dfloat;
          continue;
      }
      if (strcmp(argv[i*2-1],"-h")==0)
      {
          tr.h=(float)chi.dfloat;
          continue;
      }
    }
    //tr.print_data();
    tr.raschet();
    return 0;
}

