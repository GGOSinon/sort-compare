#include<stdio.h>
#include<algorithm>
using namespace std;

int a[1000005];

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

int R[1000000];
 
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
    //for(i=s;i<=e;i++)printf("%d ", a[i]);
    //printf("Pivot1 = %d, Pivot2 = %d\n", a[p1], a[p2]);
    while(true){
       while(a[l]<=a[p1]&&l<=e-1){l++;}
       while(a[r]>=a[p1]&&r>=s+1){
           //printf("%d %d %d %d %d\n", r, a[r], a[p2], sr, er);
           if(a[r]<a[p2]){R[er++] = r;}//printf("New point : %d\n", r);}
           else if(sr<er){//&&a[r-1]<a[p2]){
               swap(a[R[sr++]], a[r]);
               R[er++]=r;
               //printf("->\n");
               //for(i=s;i<=e;i++)printf("%d ", a[i]);
               //printf("\n");
           }
           r--;
       }
       if(l>=r)break; 
       swap(a[l], a[r]);
       //printf("->\n");
       //for(i=s;i<=e;i++)printf("%d ", a[i]);
       //printf("\n");
    }
    //printf("%d %d\n", sr, er);  
    if(er==0)pr = r+1;
    else pr = R[sr]+1;
    swap(a[p2], a[pr]);
    swap(a[p1], a[r]);
    //for(i=s;i<=e;i++)printf("%d ", a[i]);
    //printf("\n");
    //printf("(%d %d %d %d)\n\n", s, e, r, pr);
    quick_sort2(s, r-1);
    quick_sort2(r+1, pr-1);   
    quick_sort2(pr+1, e);
    //for(i=s;i<=e;i++)printf("%d ", a[i]);
    //printf("Pivot : %d", subpivot);
    //printf("\n");
}

int r[1000005];

void make_random(int n)
{
    int i;
    FILE* F = fopen("input.txt", "w");
    fprintf(F, "%d\n", n);
    for(i=1;i<=n;i++)r[i] = a[i] = abs(rand()%(1<<24));
    sort(r+1, r+n+1);
    for(i=1;i<=n;i++){
        a[i] = lower_bound(r+1, r+n+1, a[i])-r;
        fprintf(F, "%d ", a[i]);
    }
    fclose(F);
}

int main()
{
    int n, i;
    //freopen("input.txt", "r", stdin);
    //make_random(50);
    scanf("%d", &n);
    for(i=1;i<=n;i++)scanf("%d", &a[i]);
    quick_sort2(1, n);
    for(i=1;i<=n;i++)printf("%d ", a[i]);
    for(i=2;i<=n;i++)if(a[i-1]>a[i])break;
    //if(i==n+1)printf("\nSUCCESS");
    //else printf("\nNO..");
}
