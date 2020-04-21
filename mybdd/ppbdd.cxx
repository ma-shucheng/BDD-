#include <bdd.h>
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include<fstream>
#include<ctype.h>
#define varnum 49
#define tnum 35
 main(void )
{
 using namespace std ;



int i,j,k,bddnodenum;
double f;
 bdd pn,pninit,pnfrom,pnnew,to,pnbad,pngood;
 bdd p[varnum],et[tnum],cet[tnum];
 bdd_init(100000,10000);
bdd_setvarnum(varnum);
//define M0 ,  transion mix //////////
char ch[4],chline[80];
int pt,m,tp;
int m0[varnum];
int tpre[tnum][varnum];
int tpos[tnum][varnum];

ifstream input;
input.open("pp7.pnt");
if(!input.is_open()) printf("open failed!\n");
else  {input.getline(chline,sizeof(chline));
for(i=0;i<tnum;i++)
{input.getline(chline,sizeof(chline));
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
m0[m-1]=atoi(ch);
tp=0;
while(chline[j]!=',')
{if (chline[j]==' ') j++;
else 
{k=0;
while((chline[j]!=' ')||(chline[j]!=','))
{ch[k]=chline[j];
k++;
j++;
}
tpre[m-1][tp]=atoi(ch);
tp++;
}
}
j++;
tp=0;
while(chline[j]!='\0')
{if (chline[j]==' ') j++;
else 
{k=0;
while(chline[j]!=' ')
{ch[k]=chline[j];
k++;
j++;
}
tpos[m-1][tp]=atoi(ch);
tp++;
}
}
}
}

 FILE *fp=fopen("ppbdd7.txt","wb");
time_t tval;
struct tm *now;
	//显示当前时间
    tval = time(NULL);
    now = localtime(&tval);
    fprintf(fp,"现在时间: %4d年 %d月 %02d日 %d:%02d:%02d\n",  now->tm_year+1900,now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min,now->tm_sec);
//computer the pninit,et,cet/////
for(i=0;i<varnum;i++)
{
p[i]=bdd_ithvar(i); 
}
pninit=bddtrue;
for(i=0;i<varnum;i++)
{if(m0[i]==1)
pninit=bdd_apply(pninit,bdd_ithvar(i),bddop_and);
else pninit=bdd_apply(pninit,bdd_nithvar(i),bddop_and);
}
fprintf(fp,"The init state is :\n");
bdd_fprintset(fp,pninit);

for(i=0;i<tnum;i++)
{
et[i]=bddtrue;
cet[i]=bddtrue;
for(j=0;j<varnum;j++)
{
if(tpre[i][j]==0) break;
et[i]=bdd_apply(et[i],bdd_ithvar(tpre[i][j]-1),bddop_and);
}
for(j=0;j<varnum;j++)
{if(tpos[i][j]==0) break;
cet[i]=bdd_apply(cet[i],bdd_ithvar(tpos[i][j]-1),bddop_and);
}
}
pn=pninit;
to=pninit;
pnfrom=pninit;
k=0;
while(pnfrom!=bddfalse)
{

for(i=0;i<tnum;i++)
{
pnnew=bdd_apply(pnfrom,et[i],bddop_and);
if (pnnew==bddfalse) continue;
for(j=0;j<varnum;j++)
{
 if (tpre[i][j]==0) break;
 pnnew=bdd_exist(pnnew,bdd_ithvar(tpre[i][j]-1));
 pnnew=bdd_apply(pnnew,bdd_nithvar(tpre[i][j]-1),bddop_and);
 }
 for(j=0;j<varnum;j++)
  {
  if (tpos[i][j]==0) break;
  pnnew=bdd_exist(pnnew,bdd_ithvar(tpos[i][j]-1));
  pnnew=bdd_apply(pnnew,bdd_ithvar(tpos[i][j]-1),bddop_and);
  }
  to=bdd_apply(to,pnnew,bddop_or);
  }
  pnfrom=bdd_apply(to,bdd_not(pn),bddop_and);
  pn=to;
  k++;
}
f=bdd_satcount(pn);
bddnodenum=bdd_nodecount(pn);
fprintf(fp,"\nPn complete successfully!  The result is :\nCirculs number  is: %d\npn is:   %f states %d nodes \n",k,f,bddnodenum);
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
bdd_fprintset(fp,pndead);
}

to=pninit;
pnfrom=pninit;
pngood=pninit;
k=0;
while(pnfrom!=bddfalse)
{

for(i=0;i<tnum;i++)
{
pnnew=bdd_apply(pnfrom,cet[i],bddop_and);
if (pnnew==bddfalse) continue;
for(j=0;j<varnum;j++)
{
 if (tpos[i][j]==0) break;
 pnnew=bdd_exist(pnnew,bdd_ithvar(tpos[i][j]-1));
 pnnew=bdd_apply(pnnew,bdd_nithvar(tpos[i][j]-1),bddop_and);
 }
 for(j=0;j<varnum;j++)
  {
  if (tpre[i][j]==0) break;
  pnnew=bdd_exist(pnnew,bdd_ithvar(tpre[i][j]-1));
  pnnew=bdd_apply(pnnew,bdd_ithvar(tpre[i][j]-1),bddop_and);
  }
  to=bdd_apply(to,pnnew,bddop_or);
  }
  pnfrom=bdd_apply(to,bdd_not(pngood),bddop_and);
  pngood=to;
  k++;
}
pngood=bdd_apply(pn,pngood,bddop_and);
f=bdd_satcount(pngood);
fprintf(fp,"\n\nConverse pn complete successfully!\nCirculs number is%d\npngood is:  %f states\n",k,f);
pnbad=bdd_apply(pn,bdd_not(pngood),bddop_and);
f=bdd_satcount(pnbad);
fprintf(fp,"\npn bad states is: %f states\n",f);
bdd_fprintset(fp,pnbad);

// *find event dis*//
fprintf(fp,"\n The dis state and event:");
k=0;                       //the sis states number/////////////
for(i=0;i<tnum;i++)
{
pnnew=bdd_apply(pnbad,cet[i],bddop_and);
if (pnnew==bddfalse)
continue;
for(j=0;j<varnum;j++)
{if (tpos[i][j]==0) break;
 pnnew=bdd_exist(pnnew,bdd_ithvar(tpos[i][j]-1));
  pnnew=bdd_apply(pnnew,bdd_nithvar(tpos[i][j]-1),bddop_and);
  }
  for(j=0;j<varnum;j++)
 {if (tpre[i][j]==0) break;
  pnnew=bdd_exist(pnnew,bdd_ithvar(tpre[i][j]-1));
  pnnew=bdd_apply(pnnew,bdd_ithvar(tpre[i][j]-1),bddop_and);
  }
  pnnew=bdd_apply(pnnew,pn,bddop_and);

  if (pnnew!=bddfalse)
 { fprintf(fp,"\ndis states   is:  t%d\n",i+1);
  bdd_fprintset(fp,pnnew);
  k++;
  }
}
fprintf(fp,"\nthe total dis (state and event)  number :   %d\n",k);
fprintf(fp,"All missions done!!\n");
    tval = time(NULL);
    now = localtime(&tval);
    fprintf(fp,"现在时间: %4d年 %d月 %02d日 %d:%02d:%02d\n",  now->tm_year+1900,now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min,now->tm_sec);
    printf("Complete successfully!!\n");
bdd_done();
}
