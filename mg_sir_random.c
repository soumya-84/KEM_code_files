#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"ran2.c"
#define L 160
#define N 300
#define PI2 6.2832
long sd=-987896584;
main() 
{
  int SIR[L][L],SIR_copy[L][L],duration[L][L],flip[L][L],i,j,k,n,NRUN=10,t,TMAX=500,ni,nj,mi,mj,x,y,ii,jj,count2,in,flag,flag1;
  float diff[TMAX],sum,delta,p,thr,W,S,sum1,sum2,T,diss,mix,in0,in1,in2,beta;
  int agent,temp,r1,r2,max_duration,nei,z,nr,sus,inf,rec,max_move,t_start,t_end,t_period,n_avc,m_avc; 
  float sus_t[TMAX],inf_t[TMAX],rec_t[TMAX],moved[TMAX],didntmove[TMAX];
  float moved_infected, unmoved_infected, sum4,sum5,sum6,sum7,q;
  
  n_avc=0; m_avc=0;
 
  max_duration=15;
  beta=1-0.98; 
  q=0.0;


 // max_move=1;
//  mix=0.125;


  for(i=0;i<TMAX;i++) {sus_t[i]=0; inf_t[i]=0; rec_t[i]=0;}





  for(n=0;n<NRUN;n++)
  {
     for(i=0;i<L;i++) {for(j=0;j<L;j++) {SIR[i][j]=-1; flip[i][j]=0; duration[i][j]=0;}}
////////////random assignments//////////////
     for(i=0;i<10000;)
     {
         ni=ran2(&sd)*L; nj=ran2(&sd)*L;
         if(SIR[ni][nj]==-1)
         {
           SIR[ni][nj]=0;
        //   move[ni][nj]=max_move;
           duration[ni][nj]=0;
           i++;
         }
     }     
///////////////////////////////////////////////
///////////////SIR initialization//////////////
     

     for(i=0;i<=15;)
     {
       ni=ran2(&sd)*L; nj=ran2(&sd)*L;
       if(SIR[ni][nj]==0)
       {
          SIR[ni][nj]=1;
          duration[ni][nj]=ran2(&sd)*max_duration;
          i++;
       }
       
     }

     for(i=0;i<400;)
     {
       ni=ran2(&sd)*L; nj=ran2(&sd)*L;
       if(SIR[ni][nj]!=-1)
       {
          flip[ni][nj]=1; i++;
       }
     }
    
///////////////////////////////////////////////

     for(t=0;t<TMAX;t++)
     {
        
///////////////SIR dynamics//////////////////////////////////////////
        for(i=0;i<L;i++) {for(j=0;j<L;j++) {SIR_copy[i][j]=SIR[i][j];}}         
        for(i=0;i<L;i++) 
        {
           for(j=0;j<L;j++)
           {
              if(SIR[i][j]==0)
              {
                 flag=1;
                 ni=i+1; nj=j;
                 if(ni<L && flag==1)
                 {
                    if(SIR[ni][nj]==1)
                    {
                        if(ran2(&sd)>beta) 
                        {
                           SIR_copy[i][j]=1;
                           flag=0; 
                        }
                    }
                 }
                 ni=i-1; nj=j;
                 if(ni>=0 && flag==1)
                 {
                    if(SIR[ni][nj]==1)
                    {
                        if(ran2(&sd)>beta) 
                        {
                           SIR_copy[i][j]=1; 
                           flag=0;
                        }
                    }
                 }
                 ni=i; nj=j-1;
                 if(nj>=0 && flag==1)
                 {
                    if(SIR[ni][nj]==1)
                    {
                        if(ran2(&sd)>beta) 
                        {
                           SIR_copy[i][j]=1; 
                           flag=0;
                        }
                    }
                 }
                 ni=i; nj=j+1;
                 if(nj<L && flag==1)
                 {
                    if(SIR[ni][nj]==1)
                    {
                        if(ran2(&sd)>beta) 
                        {
                           SIR_copy[i][j]=1; 
                           flag=0;
                        }
                    }
                 }

                 ni=i+1; nj=j+1;
                 if(ni<L && nj<L && flag==1)
                 {
                    if(SIR[ni][nj]==1)
                    {
                        if(ran2(&sd)>beta) 
                        {
                           SIR_copy[i][j]=1; 
                           flag=0;
                        }
                    }
                 }

                 ni=i-1; nj=j-1;
                 if(ni>=0 && nj>=0 && flag==1)
                 {
                    if(SIR[ni][nj]==1)
                    {
                        if(ran2(&sd)>beta) 
                        {
                           SIR_copy[i][j]=1; 
                           flag=0;
                        }
                    }
                 }
                  
                 ni=i+1; nj=j-1;
                 if(ni<L && nj>=0 && flag==1)
                 {
                    if(SIR[ni][nj]==1)
                    {
                        if(ran2(&sd)>beta) 
                        {
                           SIR_copy[i][j]=1; 
                           flag=0;
                        }
                    }
                 }

                 ni=i-1; nj=j+1;
                 if(ni>=0 && nj<L && flag==1)
                 {
                    if(SIR[ni][nj]==1)
                    {
                        if(ran2(&sd)>beta) 
                        {
                           SIR_copy[i][j]=1; 
                           flag=0;
                        }
                    }
                 }
                  
              }        
              if(SIR[i][j]==1)
              {
                 duration[i][j]++; 
                 if(duration[i][j]==max_duration) {SIR_copy[i][j]=2;}
              }

           }
        }

        sus=0; inf=0; rec=0;
        for(i=0;i<L;i++)
        {
           for(j=0;j<L;j++)
           {
              SIR[i][j]=SIR_copy[i][j];
              if(SIR[i][j]==0) {sus++;}
              if(SIR[i][j]==1) {inf++;}
              if(SIR[i][j]==2) {rec++;}
           }
        }

        sus_t[t]+=sus; inf_t[t]+=inf; rec_t[t]+=rec;
/////////////////////////////////////////////////////////////////////

/////////////////////movement////////////////////////////////////////
       for(i=0;i<L;i++)
       {
          for(j=0;j<L;j++)
          {
             ni=ran2(&sd)*L; nj=ran2(&sd)*L;

             if(flip[ni][nj]==1)
             {
               flag1=1;
                while(flag1==1)
                {
                   mi=ran2(&sd)*L; mj=ran2(&sd)*L;
                   if(SIR[mi][mj]==-1)
                   {
                      flag1=0;
                      if(ran2(&sd)<q)
                      {
                         SIR[mi][mj]=SIR[ni][nj];   SIR[ni][nj]=-1;
                         duration[mi][mj]=duration[ni][nj]; duration[ni][nj]=0;
                         flip[mi][mj]=flip[ni][nj];     flip[ni][nj]=0;
                      }
                   }
                }
             }

          }     
       }  

//////////////////////////////////////////////////////////////////////
     }      
// end of time loop

  
  }
//end of realisation loop
   sum1=0; sum2=0;
  
 //  tot_recov=(t_rec0[TMAX-1]+t_rec1[TMAX-1]+t_rec2[TMAX-1])/NRUN;

 /// printf("%d %f %f %f\n",t_start,tot_recov/N,moved_infected/NRUN, unmoved_infected/NRUN);

  for(i=0;i<TMAX;i++)
  {
   //  printf("%d %f\n",i,dist_m[i]);
     printf("%d %f %f %f\n",i,sus_t[i]/NRUN,inf_t[i]/NRUN,rec_t[i]/NRUN);
  } 
 // printf("%f %f\n",mix,diff[TMAX-1]/NRUN);

 //  for(i=0;i<L;i++) {printf("%d ",population[i]);}
 //  printf("\n");




// free(stat); free(stati); free(force); free(forcei); free(thr);
}
