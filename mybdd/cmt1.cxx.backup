#include <bdd.h>
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include<fstream>
#include<ctype.h>
#define varnum 70
 main(void )
{
 using namespace std ;
 //   
    //int varnum,tnum;
    int tnum;
//printf("pls input places' number:");
//cin>>varnum;
printf("pls input transitions' number:");
cin>>tnum;

int i,j,k,bddnodenum;
double f;
 bdd pn,pninit,pnfrom,pnnew,to,pnbad,pngood;
 bdd p[varnum][4],q[varnum][4],et[100],cet[100];
 bdd_init(100000,10000);
bdd_setvarnum(8*varnum);
for(i=0;i<varnum;i++)
for(j=0;j<4;j++)
{p[i][j]=bdd_ithvar(i*4+j);
q[i][j]=bdd_ithvar((i+varnum)*4+j);
}
//define M0 ,  transion mix //////////
char  ch[4],chline[80],infilename[20];
int pt,m,tp;
int m0[varnum];
int tpre[100][varnum]={0};
int tpos[100][varnum]={0};

printf("pls inpput your full file name:");
cin>>infilename;
printf("Now start!!\n");
  FILE *fp=fopen("result.txt","wb");
 time_t tval;
 struct tm *now;
 tval = time(NULL);
    now = localtime(&tval);
    fprintf(fp,"现在时间: %4d年 %d月 %02d日 %d:%02d:%02d\n",  now->tm_year+1900,now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min,now->tm_sec);

ifstream input;
input.open(infilename);
if(!input.is_open()) printf("File open failed! Please check  your file name\n");
else  {input.getline(chline,sizeof(chline));
for(i=0;i<varnum;i++)
{
input.getline(chline,sizeof(chline));
j=0;
while(chline[j]==' ') j++;
k=0;
while(chline[j]!=' ')
{ch[k]=chline[j];
k++;
j++;
}
m=atoi(ch);
while(chline[j]==' ') j++;
k=0;
while(chline[j]!=' ')
{ch[k]=chline[j];
k++;
j++;
}
ch[k]='\0';
m0[m-1]=atoi(ch);
while(chline[j]!=',')
{if (chline[j]==' ') j++;
else 
{k=0;
while((chline[j]!=' ')&&(chline[j]!=','))
{ch[k]=chline[j];
k++;
j++;
}
ch[k]='\0';
tp=0;
while(tpos[atoi(ch)-1][tp]!=0) tp++;
tpos[atoi(ch)-1][tp]=m;
}
}
j++;
while(chline[j]!='\0')
{if (chline[j]==' ') j++;
else 
{k=0;
while((chline[j]!=' ')&&(chline[j]!='\0'))
{ch[k]=chline[j];
k++;
j++;
}
ch[k]='\0';
tp=0;
while(tpre[atoi(ch)-1][tp]!=0) tp++;
tpre[atoi(ch)-1][tp]=m;
tp++;
}
}
}
for(i=0;i<varnum;i++)
//get infint bdd
pninit=bddtrue;
for(i=0;i<varnum;i++)
   {
    m=m0[i];
    for(j=0;j<4;j++)
        {
	 if(m%2==0) pninit=bdd_apply(pninit,bdd_not(p[i][j]),bddop_and);
	 else pninit=bdd_apply(pninit,p[i][j],bddop_and);
	 m=m/2;
	}
   }
  fprintf(fp,"The infinit pn is:\n");
  bdd_fprintset(fp,pninit);
  fprintf(fp,"\n");
  //set pairs
  bddPair *pair=bdd_newpair();
 int oldvar[varnum][4];
int newvar[varnum][4];
for(i=0;i<varnum;i++)
for(j=0;j<4;j++)
{oldvar[i][j]=i*4+j+4*varnum;
newvar[i][j]=i*4+j;
}

  //computer et[i]
  bdd det;
  for(i=0;i<tnum;i++)
      {
      et[i]=bddtrue;
      for(j=0;j<varnum;j++)
      {
       det=bddtrue;
       if(tpre[i][j]==0) break;
       for(k=0;k<4;k++)
              {
	       det=bdd_apply(det,bdd_not(p[tpre[i][j]-1][k]),bddop_and);
	      }      
     et[i]=bdd_apply(et[i],bdd_not(det),bddop_and);
     }
     }
     
     //computer   cet
  for(i=0;i<tnum;i++)
      {
      cet[i]=bddtrue;
      for(j=0;j<varnum;j++)
      {
       det=bddtrue;
       if(tpos[i][j]==0) break;
       for(k=0;k<4;k++)
              {
	       det=bdd_apply(det,bdd_not(p[tpos[i][j]-1][k]),bddop_and);
	      }      
     cet[i]=bdd_apply(cet[i],bdd_not(det),bddop_and);
     }
     }
     
     //computer add aaand  reduce mtrix
     bdd add[varnum],reduce[varnum],a[4];
     for(i=0;i<varnum;i++)
         {
	 reduce[i]=bddtrue;
	 a[0]=bdd_apply(q[i][0],p[i][0],bddop_xor);
	 a[1]=bdd_apply(p[i][1],p[i][0],bddop_biimp);
	 a[1]=bdd_apply(a[1],q[i][1],bddop_biimp);
	 a[2]=bdd_apply(bdd_not(p[i][0]),bdd_not(p[i][1]),bddop_and);
	 a[2]=bdd_apply(a[2],p[i][2],bddop_xor);
	 a[2]=bdd_apply(a[2],q[i][2],bddop_biimp);
	 a[3]=bdd_apply(bdd_not(p[i][2]),bdd_apply(bdd_not(p[i][1]),bdd_not(p[i][0]),bddop_and),bddop_and);
	 a[3]=bdd_apply(a[3],p[i][3],bddop_xor);
	 a[3]=bdd_apply(a[3],q[i][3],bddop_biimp);
	 for(j=0;j<4;j++)
	     {
	     reduce[i]=bdd_apply(reduce[i],a[j],bddop_and);
	     }
	 add[i]=bddtrue;
	 a[0]=bdd_apply(q[i][0],p[i][0],bddop_xor);
	 a[1]=bdd_apply(p[i][1],p[i][0],bddop_xor);
	 a[1]=bdd_apply(a[1],q[i][1],bddop_biimp);
	 a[2]=bdd_apply(p[i][0],p[i][1],bddop_and);
	 a[2]=bdd_apply(a[2],p[i][2],bddop_xor);
	 a[2]=bdd_apply(a[2],q[i][2],bddop_biimp);
	 a[3]=bdd_apply(p[i][2],bdd_apply(p[i][1],p[i][0],bddop_and),bddop_and);
	 a[3]=bdd_apply(a[3],p[i][3],bddop_xor);
	 a[3]=bdd_apply(a[3],q[i][3],bddop_biimp);
	 for(j=0;j<4;j++)
	     {
	     add[i]=bdd_apply(add[i],a[j],bddop_and);
	     }
	 }
  //computer pn
 pn=pnfrom=to=pninit;
 while(1)
 {
  for(i=0;i<tnum;i++)
      {
       pnnew=bdd_apply(pnfrom,et[i],bddop_and);
       if(pnnew==bddfalse) continue;
       for(j=0;j<varnum;j++)
           {
	   if(tpre[i][j]==0) break;   
	   pnnew=bdd_apply(pnnew,reduce[tpre[i][j]-1],bddop_and);
	   bdd_setpairs(pair,oldvar[tpre[i][j]-1],newvar[tpre[i][j]-1],4);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,p[tpre[i][j]-1][k]);
	   pnnew=bdd_replace(pnnew,pair);
	   }
       for(j=0;j<varnum;j++)
          {
	   if(tpos[i][j]==0) break;   
	  pnnew=bdd_apply(pnnew,add[tpos[i][j]-1],bddop_and);
	   bdd_setpairs(pair,oldvar[tpos[i][j]-1],newvar[tpos[i][j]-1],4);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,p[tpos[i][j]-1][k]);
	   pnnew=bdd_replace(pnnew,pair);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,q[tpos[i][j]-1][k]);
	  }
	  to=bdd_apply(to,pnnew,bddop_or);
      }
pnfrom=bdd_apply(to,bdd_not(pn),bddop_and);
if(pnfrom==bddfalse) break;
pn=to=bdd_apply(pn,pnfrom,bddop_or);
}

for(k=0;k<8*varnum-4*varnum;k++)
    pn=bdd_apply(pn,bdd_ithvar(k+4*varnum),bddop_and);
f=bdd_satcount(pn);
fprintf(fp,"\n pn is %f states:\n",f);

//computer deadstates
bdd pndead=pn;
bdd pnenable;
for(i=0;i<tnum;i++)
{
pnenable=bdd_apply(pndead,et[i],bddop_and);
pndead=bdd_apply(pndead,bdd_not(pnenable),bddop_and);
}

if(pndead==bddfalse)
fprintf(fp,"\nThis pn is not dead.\n");
else 
{f=bdd_satcount(pndead);
fprintf(fp,"\nThis pn is dead.The number of dead states is %f:\ndead states:\n",f);
for(k=0;k<8*varnum-4*varnum;k++)
     pndead=bdd_exist(pndead,bdd_ithvar(k+4*varnum));
bdd_fprintset(fp,pndead);
}
//computer converse pn
pngood=pnfrom=to=pninit;
 while(1)
 {
  for(i=0;i<tnum;i++)
      {
       pnnew=bdd_apply(pnfrom,cet[i],bddop_and);
       if(pnnew==bddfalse) continue;
       for(j=0;j<varnum;j++)
           {
	   if(tpos[i][j]==0) break;   
	   pnnew=bdd_apply(pnnew,reduce[tpos[i][j]-1],bddop_and);
	   bdd_setpairs(pair,oldvar[tpos[i][j]-1],newvar[tpos[i][j]-1],4);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,p[tpos[i][j]-1][k]);
	   pnnew=bdd_replace(pnnew,pair);
	   }
       for(j=0;j<varnum;j++)
          {
	   if(tpre[i][j]==0) break;   
	  pnnew=bdd_apply(pnnew,add[tpre[i][j]-1],bddop_and);
	   bdd_setpairs(pair,oldvar[tpre[i][j]-1],newvar[tpre[i][j]-1],4);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,p[tpre[i][j]-1][k]);
	   pnnew=bdd_replace(pnnew,pair);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,q[tpre[i][j]-1][k]);
	  }
	  to=bdd_apply(to,pnnew,bddop_or);
      }
pnfrom=bdd_apply(to,bdd_not(pngood),bddop_and);
if(pnfrom==bddfalse) break;
pngood=to=bdd_apply(pngood,pnfrom,bddop_or);
}
for(k=0;k<8*varnum-4*varnum;k++)
    pngood=bdd_apply(pngood,bdd_ithvar(k+4*varnum),bddop_and);
f=bdd_satcount(pngood);
fprintf(fp,"\n good states  is   %f states:\n",f);

//    computer bad states
pnbad=bdd_apply(pn,bdd_not(pngood),bddop_and);
f=bdd_satcount(pnbad);
fprintf(fp,"\npn bad states is: %f states\n",f);

//computer departion
fprintf(fp,"\n The M/T seepartion is:");
for(k=0;k<8*varnum-4*varnum;k++)
    pnbad=bdd_exist(pnbad,bdd_ithvar(k+4*varnum));
int depnum=0;                       //the sis states number/////////////
for(i=0;i<tnum;i++)
{
pnnew=bdd_apply(pnbad,cet[i],bddop_and);
if (pnnew==bddfalse)
continue;
       for(j=0;j<varnum;j++)
           {
	   if(tpos[i][j]==0) break;   
	   pnnew=bdd_apply(pnnew,reduce[tpos[i][j]-1],bddop_and);
	   bdd_setpairs(pair,oldvar[tpos[i][j]-1],newvar[tpos[i][j]-1],4);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,p[tpos[i][j]-1][k]);
	   pnnew=bdd_replace(pnnew,pair);
	   }
       for(j=0;j<varnum;j++)
          {
	   if(tpre[i][j]==0) break;   
	  pnnew=bdd_apply(pnnew,add[tpre[i][j]-1],bddop_and);
	   bdd_setpairs(pair,oldvar[tpre[i][j]-1],newvar[tpre[i][j]-1],4);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,p[tpre[i][j]-1][k]);
	   pnnew=bdd_replace(pnnew,pair);
	   for(k=0;k<4;k++)
	        pnnew=bdd_exist(pnnew,q[tpre[i][j]-1][k]);
	  }
  pnnew=bdd_apply(pnnew,pn,bddop_and);

  if (pnnew!=bddfalse)
 { fprintf(fp,"\nM/T separition states   is:  t%d\n",i+1);
   for(k=0;k<8*varnum-4*varnum;k++)
        pnnew=bdd_exist(pnnew,bdd_ithvar(k+4*varnum));
   bdd_fprintset(fp,pnnew);
   depnum++;
  }
}
fprintf(fp,"\nthe total dis (state and event)  number :   %d\n",depnum);
fprintf(fp,"All missions done!!\n");

}

tval = time(NULL);
    now = localtime(&tval);
    fprintf(fp,"现在时间: %4d年 %d月 %02d日 %d:%02d:%02d\n",  now->tm_year+1900,now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min,now->tm_sec);
    printf("Complete successfully!!\n");
bdd_done();
}
