#include <bdd.h>
#include <time.h>
#include <stdlib.h>

#define varnum 14
#define tnum 10
 main(void )
{
 FILE *fp=fopen("result.txt","wb");
time_t tval;
struct tm *now;
	//显示当前时间
    tval = time(NULL);
    now = localtime(&tval);
    fprintf(fp,"现在时间: %4d年 %d月 %02d日 %d:%02d:%02d\n",  now->tm_year+1900,now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min,now->tm_sec);


int i,j,k,bddnodenum;
double f;
 bdd pn,pninit,pnfrom,pnnew,to,pnbad,pngood;
 bdd p[14],et[10],cet[10];
 bdd_init(100000,10000);
bdd_setvarnum(14);
//define M0 ,  transion mix //////////
int m0[varnum]={1,0,0,0,0,0,1,0,0,0,0,0,1,1};
int dat[tnum][varnum]={{0,1,1,2,2,2,2,2,2,2,2,2,2,2},
                      {2,0,2,1,2,2,2,2,2,2,2,2,0,2},
		      {2,2,0,2,1,2,2,2,2,2,2,2,2,0},
		      {2,2,2,0,0,1,2,2,2,2,2,2,2,2},
		      {1,2,2,2,2,0,2,2,2,2,2,2,1,1},
		      {2,2,2,2,2,2,0,1,1,2,2,2,2,2},
		      {2,2,2,2,2,2,2,0,2,1,2,2,2,0},
		      {2,2,2,2,2,2,2,2,0,2,1,2,0,2},
		      {2,2,2,2,2,2,2,2,2,0,0,1,2,2},
		      {2,2,2,2,2,2,1,2,2,2,2,0,1,1}};
//computer the pninit,et,cet/////
for(i=0;i<14;i++)
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
if(dat[i][j]==0)
et[i]=bdd_apply(et[i],bdd_ithvar(j),bddop_and);
else if(dat[i][j]==1)
cet[i]=bdd_apply(cet[i],bdd_ithvar(j),bddop_and);
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
 if (dat[i][j]==0)
 {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_nithvar(j),bddop_and);
  }
  else if (dat[i][j]==1)
  {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_ithvar(j),bddop_and);
  }
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
bdd_fprintset(fp,pn);
bdd pndead=pn;
bdd pnenable;
for(i=0;i<tnum;i++)
{
pnenable=bdd_apply(pndead,bdd_not(et[i]),bddop_and);
}

if(pndead==bddfalse)
fprintf(fp,"This pn is not dead.\n");
else 
{f=bdd_satcount(pndead);
fprintf(fp,"This pn is dead.The number of dead states is %f:\ndead states:\n",f);
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
{if (dat[i][j]==1)
 {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_nithvar(j),bddop_and);
  }
  else if (dat[i][j]==0)
  {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_ithvar(j),bddop_and);
  }
  }
  to=bdd_apply(to,pnnew,bddop_or);
  }
  pnfrom=bdd_apply(to,bdd_not(pngood),bddop_and);
  pngood=to;
    f=bdd_satcount(to);
  k++;
}
pngood=bdd_apply(pn,pngood,bddop_and);
f=bdd_satcount(pngood);
fprintf(fp,"\n\nConverse pn complete successfully!\nCirculs number is%d\npngood is:  %f states\n",k,f);
bdd_fprintset(fp,pngood);
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
{if (dat[i][j]==1)
 {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_nithvar(j),bddop_and);
  }
  else if (dat[i][j]==0)
  {pnnew=bdd_exist(pnnew,bdd_ithvar(j));
  pnnew=bdd_apply(pnnew,bdd_ithvar(j),bddop_and);
  }
  }
  pnnew=bdd_apply(pnnew,pn,bddop_and);

  if (pnnew!=bddfalse)
 { fprintf(fp,"\ndis states   is:  t%d\n",i);
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
