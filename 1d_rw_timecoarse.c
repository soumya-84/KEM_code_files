#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"ran2.c"
#define L 1000
float expd(void);
long sd=-993178333;
main()
{
  int i,j,k,count2,iw,count,n,NRUN=10000,t,TMAX=1000000,ii,jj,ni,nj,id,xl,yl,M,tt,flag,ratio,RELAX=10000,counti,countj,delta,idelta,inorm,clg_list[51],nr,a,used[51],before,after,*stat,*flip,count0,count1,value,temp;
  float sum,r,p,*op,tot_sum,*s_op,*time_avg,zero,tot_flip,tot_zero,*norm,*prob_del,total_factor=0.,tot_op,new_sum,*per,*per1,*per0,*op0,ent,n_ent,limit=0.1,win,tot_ent,battle,*noise;
  int spin_per_block,*super_spin,total_flip,new_total,part_sum,part_sum_flip,size,old_total,index,x,y,mu,dur,avc=0,rw,prev;
  float dist[100000];
  FILE *fpt1,*fpt2,*fpt3;

 ////////////////////////////can change NRUN depending on run-time



  M=50;
  spin_per_block=L/M;
  ratio=L/M;
 //   norm=(float *)calloc(LARGE, sizeof(float));
//  prob_del=(float *)calloc(LARGE, sizeof(float));
  
//  fpt3=fopen("elec_clg_list_3","r");
//  fpt1=fopen("mag_L30_p0.12n","w");
//  fpt2=fopen("flip_prob_L30_p0.12n","w");
 
 //  p=0.9;

     stat = (int *)calloc(L, sizeof(int));
     super_spin = (int *)calloc(M, sizeof(int));
     noise = (float *)calloc(L, sizeof(float));
     flip = (int *)calloc(L,sizeof(int));
     op = (float *)calloc(TMAX,sizeof(float));
     op0 = (float *)calloc(TMAX,sizeof(float));
     s_op=(float *)calloc(TMAX,sizeof(float));
     time_avg=(float *)calloc(TMAX,sizeof(float));
     per=(float *)calloc(TMAX,sizeof(float));
     per0=(float *)calloc(TMAX,sizeof(float));
     per1=(float *)calloc(TMAX,sizeof(float));
 //    super_spin = (int **)calloc(M,sizeof(int*));


//  for(i=0;i<51;i++) {fscanf(fpt3,"%d %d\n",&clg_list[i],&a); }

  for(i=0;i<100000;i++) {dist[i]=0;}


 p=0.99;
/// for(p=0;p<1;p=p+0.01)
 {

  win=0; tot_ent=0;
  for(n=0;n<NRUN;n++)
  {
  
    rw=0;

    dur=0;
    for(t=0;t<TMAX;t++)
    {
       prev=rw;
       if(ran2(&sd)<.5) {rw++;}
       else {rw--;}

       if(prev*rw<=0 /*&& t%500 == 0*/)
       {
         if(dur<100000) {dist[dur]++; avc++;}
          dur=0;
       }
       else {dur++;}

    }
 
//  printf("%d %d %d %f\n",old_total,new_total,total_flip,n_ent);



  }
//end of realisation loop

  for(i=0;i<100000;i++) {printf("%d %f\n",i,dist[i]/avc);}


 ///////////// printf("%f %f %f\n",p,win/NRUN,tot_ent/NRUN);
 }
//end of p loop

}


float expd(void)
{

   float lam, x,y,z;
  
   lam=0.01; 

   z=ran2(&sd);
   x=log(1-z)/(-1*lam);
 
   return(x);
}







