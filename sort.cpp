#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
using namespace std;

int res[1000005], a[1000005], r[1000005];

int h[2000005];
int n;

double heap_sort(int n) //Heap sort
{
    int i, time1, time2;
    double tot_time;
    int k=1;
    time1 = clock();
    for(i=1;i<=n;i++)h[k++]=a[i], push_heap(h+1, h+k);
    for(i=1;i<=n;i++){
        res[i]=h[0];
        pop_heap(h+1, h+k);
        k--;
    }
    time2 = clock();
    tot_time = (double)(time2-time1)/CLOCKS_PER_SEC;
    printf("heap: %lf\n", tot_time);
    return tot_time;
}

void q_sort(int s, int e) //Quick sort implementation
{
    int l = s+1, r = e, p = s;
    if(s>=e)return;
    while(true){
       while(a[l]<=a[p]&&l<=e)l++;
       while(a[r]>=a[p]&&r>=s+1)r--;
       if(l>=r)break;
       swap(a[l], a[r]);
    }
    swap(a[p], a[r]);
    q_sort(s, r-1);
    q_sort(r+1, e);
}

double quick_sort(int n) //Quick sort
{
    int deltaTime = 1*CLOCKS_PER_SEC, time1, time2;
    double tot_time;
    time1 = clock();
    q_sort(1, n);
    time2 = clock();
    tot_time = (double)(time2-time1)/CLOCKS_PER_SEC;
    printf("quick: %lf\n", tot_time);
    return tot_time;
}

double select_sort(int);
const int K=5;
int c[(1<<K)][1000005];

double select2_sort(int s, int e) //Selection sort
{
    int i, j, time1, time2, time_t;
    int p;
    for(i=s;i<=e;i++){
        p = i;
        for(j=i+1;j<=e;j++){
           if(a[j]<a[p])p = j;
        }
        if(i!=p)swap(a[i], a[p]);
    }
}

int R[1000005];

void quick_sort2(int s, int e)
{
    int l = s+1, r = e-1, p1 = s, p2 = e, i, sr = 0, er = 0, pr = -1, subpivot;
    if(s>=e)return;
    if(s>=e){
        select2_sort(s, e);
        return;
    }
    if(a[p1] > a[p2])swap(a[p1], a[p2]);
    subpivot = a[p2];
    while(true){
       while(a[l]<=a[p1]&&l<=e-1){l++;}
       while(a[r]>=a[p1]&&r>=s+1){
           if(a[r]<a[p2]){R[er++] = r;}
           else if(sr<er){//&&a[r-1]<a[p2]){
               swap(a[R[sr++]], a[r]);
               R[er++]=r;
           }
           r--;
       }
       if(l>=r)break; 
       swap(a[l], a[r]);
    }
    if(er==0)pr = r+1;
    else pr = R[sr]+1;
    swap(a[p2], a[pr]);
    swap(a[p1], a[r]);
    quick_sort2(s, r-1);
    quick_sort2(r+1, pr-1);   
    quick_sort2(pr+1, e);
}

double my_sort2(int n)
{
   int time1, time2;
   double tot_time;
   time1 = clock();
   quick_sort2(1, n);
   time2 = clock();
   tot_time = (double)(time2-time1)/CLOCKS_PER_SEC;
   printf("mysort2: %lf\n", tot_time);
   return tot_time;
}

double my_sort(int n) //New sort(Radix sort + Selection sort)
{
    int k[(1<<K)],i,j,l,t,bit;
    int time1, time2;
    double tot_time;
    time1 = clock();
    if(n<=30)return select_sort(n);
    for(i=0,bit=(1<<K)-1;i<31/K;i++,bit<<=K){
        for(j=0;j<(1<<K);j++)k[j]=0;
        for(j=1;j<=n;j++){
            t = (a[j]&bit)>>(K*i);
            //printf("%d %d %d %d\n", a[j], bit, a[j]&bit, t);
            c[t][k[t]++]=a[j];
        }
        n = 0;
        for(j=0;j<(1<<K);j++){
            for(l=0;l<k[j];l++)a[++n]=c[j][l];
            k[j]=0;
        }
        //for(j=1;j<=10;j++)printf("%d ", (a[j]&bit)>>(4*i));	
    }
    time2=clock();
    tot_time = (double)(time2-time1)/CLOCKS_PER_SEC;
    printf("mysort: %lf\n", tot_time);
    return tot_time;
}

bool cmp(int x, int y)
{
    return a[x]<a[y];
}

void mid_q_sort(int s, int e) //Quick sort implementation
{
    int l = s, r = e, p, P[3], i;
    if(s>=e)return;
    for(i=0;i<3;i++)P[i] = rand()%(e-s+1)+s;
    if(P[0]<P[2]){
        if(P[0]<P[1]&&P[1]<P[2])p=P[1];
        if(P[1]>=P[2])p=P[2];
        if(P[1]<=P[0])p=P[0];
    }
    else{
        if(P[2]<P[1]&&P[1]<P[0])p=P[1];
        if(P[1]>=P[0])p=P[0];
        if(P[1]<=P[2])p=P[2];
    }
    while(true){
       while(a[l]<=a[p]&&l<=e)l++;
       while(a[r]>=a[p]&&r>=s+1)r--;
       if(l>=r)break;
       swap(a[l], a[r]);
    }
    swap(a[p], a[r]);
    mid_q_sort(s, r-1);
    mid_q_sort(r+1, e);
}

double mid_quick_sort(int n) //Quick sort
{
    int time1, time2;
    double tot_time;
    time1 = clock();
    mid_q_sort(1, n);
    time2 = clock();
    tot_time = (double)(time2-time1)/CLOCKS_PER_SEC;
    return tot_time;
    printf("mid_quick: %lf\n", tot_time);
}

double select_sort(int n) //Selection sort
{
    int i, j, time1, time2, time_t;
    int deltaTime = 1*CLOCKS_PER_SEC;
    double tot_time;
    int p;
    time1 = clock();
    for(i=1;i<=n;i++){
        p = i;
        time_t = clock();
        if(time_t>time1+deltaTime){
           if(a[j] < a[p]){
            printf("selection: LOL\n");
            return 1.0;
        }
        for(j=i+1;j<=n;j++){
               p = j;
           } 
        }
        if(i!=p)swap(a[i], a[p]);
    }
    time2 = clock();
    tot_time = (double)(time2-time1)/CLOCKS_PER_SEC;
    printf("selection: %lf\n", tot_time);
    return tot_time;
}

double insert_sort(int n) //Insertion sort
{
    int i, j, time1, time2, time_t;
    int deltaTime = 1*CLOCKS_PER_SEC;
    double tot_time;
    int p;
    time1 = clock();
    for(i=1;i<=n;i++){
        p = i;
        time_t = clock();
        if(time_t>time1+deltaTime){
            printf("insertion: LOL\n");
            return 1.0;
        }
        for(j=i+1;j<=n;j++){
           if(a[j] < a[j-1]){
               swap(a[j], a[j-1]);
           }
        }
    }
    time2 = clock();
    tot_time = (double)(time2-time1)/CLOCKS_PER_SEC;
    printf("insertion: %lf\n", tot_time);
    return tot_time;
}

double bubble_sort(int n) //Bubble sort
{
    int i, j, time1, time2, time_t;
    int deltaTime = 1*CLOCKS_PER_SEC;
    double tot_time;
    int p;
    time1 = clock();
    for(j=0;j<n;j++){
        time_t = clock();
        if(time_t>time1+deltaTime){
            printf("bubble:LOL\n");
            return 1.0;
        }
        for(i=2;i<=n;i++){
            if(a[i-1]>a[i]){
                swap(a[i-1], a[i]);
            }
        }
    }
    time2 = clock();
    tot_time = (double)(time2-time1)/CLOCKS_PER_SEC;
    printf("bubble: %lf\n", tot_time);
    return tot_time;
}

double std_sort(int n) //std::sort
{
    int i, j, time1, time2;
    double tot_time;
    time1 = clock();
    sort(a+1,a+n+1);
    time2 = clock();
    tot_time = (double)(time2-time1)/CLOCKS_PER_SEC;
    printf("std: %lf\n", tot_time);
    return tot_time;
}

int abs(int x)
{
    if(x<0)return -x;
    return x;
}

void make_random(int n)
{
    int i;
    for(i=1;i<=n;i++){
        r[i] = abs(rand()%(1<<24));
        //printf("%d ", r[i]);
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    int T, n, i, j, k;
    double avg_heap = 0, avg_quick = 0, avg_select = 0, avg_bubble = 0, avg_std = 0, avg_insert = 0, avg_quick_mid = 0, avg_mine = 0; 
    FILE* F = fopen("data.txt", "w");
    for(i=1;i<=100000;i<10?i++:i<100?i+=10:i<1000?i+=100:i+=1000){
        T = 10;
        n = 10*i;
        avg_heap = 0, avg_quick = 0, avg_select = 0, avg_bubble = 0, avg_std = 0, avg_insert = 0, avg_quick_mid = 0, avg_mine = 0;
        printf("n = %d\n\n", n);
        for(j=0;j<T;j++){
            make_random(n);
            for(k=1;k<=n;k++)a[k]=r[k];
            //avg_heap+=heap_sort(n);
            for(k=1;k<=n;k++)a[k]=r[k];
            avg_quick+=quick_sort(n);
            for(k=1;k<=n;k++)a[k]=r[k];
            //avg_quick_mid+=mid_quick_sort(n);
            for(k=1;k<=n;k++)a[k]=r[k];
            avg_mine+=my_sort2(n);
            for(k=1;k<=20;k++)printf("%d ", a[k]);
            printf("\n");
            for(k=1;k<=n;k++)a[k]=r[k];
            //avg_select+=select_sort(n);
            for(k=1;k<=n;k++)a[k]=r[k];
            //avg_insert+=insert_sort(n);
            for(k=1;k<=n;k++)a[k]=r[k];
            //avg_bubble+=bubble_sort(n);
            for(k=1;k<=n;k++)a[k]=r[k];
            avg_std+=std_sort(n);
        }
        avg_heap /= T, avg_quick /= T, avg_select /= T, avg_bubble /= T, avg_std /= T;
        //fprintf(F, "%d %.3lf %.3lf %.3lf %.3lf %.3lf\n", n, avg_heap, avg_quick, avg_select, avg_bubble, avg_std);
        //fprintf(F, "%d %.3lf %.3lf %.3lf\n", n, avg_heap, avg_quick, avg_std);
        fprintf(F, "%d %.3lf %.3lf %.3lf\n", n, avg_std, avg_quick, avg_mine);
        //fprintf(F, "%d %.3lf %.3lf %.3lf\n", n, avg_select, avg_insert, avg_bubble);
    }
    fclose(F);
    return 0;
}
