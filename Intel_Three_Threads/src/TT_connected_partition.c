#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

typedef struct 
{
    int x;
    int y;
    int z;
}Point;

struct node
{                               
    Point *key;
    int id;
    struct node *next;
};

struct node **hashMap; //hashmap(key=node,index);
int hashSize;
int *parent;
int *rank;

int isequal(Point *a,Point *b);

int find_root(int x);
void Union(int x,int y);

void init_hashMap(int n);
int getHashIndex(Point *p);
void hashPut(Point *point,int index);
int hashGet(Point *point);

int main(int argc, char *argv[])
{
    int n,i;
    FILE *op = fopen("temp_algo_time.txt", "w");

    int num_thread=4;               //number of threads
    char s[1];  
    n = atoi(argv[1]);
    Point *points = (Point *)malloc(n*sizeof(Point));
    parent = (int *)malloc(n*sizeof(int));
    rank = (int *)malloc(n*sizeof(int));
    double starttime,endtime;
    omp_set_num_threads(num_thread);
    int *arr=(int*)malloc(sizeof(int)*n);
    int *ans=(int*)malloc(sizeof(int)*n);

    for(i=0;i<n;i++)
    {
        scanf("%d",&points[i].x);
        scanf("%c",s);
        scanf("%d",&points[i].y);
        scanf("%c",s);
        scanf("%d",&points[i].z);
    }

    starttime=omp_get_wtime();  //application time starts
    init_hashMap(n);        //initilize the hashMap

    #pragma omp parallel
    {
        #pragma omp for private(i)
        for (i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i]=0;
            #pragma omp critical
            {
                int temp=hashGet(&points[i]);
                if(temp>=0){
                parent[i]=temp;
                rank[temp]++;
                }
                hashPut(&points[i],i);
            } 
        }
        #pragma omp for private(i)
        for(i=0;i<n;i++)                                                
        {
            Point temp;
            int id;
            int x=points[i].x;
            int y=points[i].y;
            int z=points[i].z;
            temp = points[i];

            temp.x = x + 1;     // changing x 
            id = hashGet(&temp);
            if(id >i )
            {
                Union(i,id);
            }
            temp.x = x - 1;     // changing x 
            id = hashGet(&temp);
            if(id >i )
            {
                Union(i,id);
            }
            temp.x=x;           //reset x

            temp.y = y + 1;     // changing y 
            id = hashGet(&temp);
            if(id >i )
            {
                Union(i,id);

            }
            temp.y = y - 1;     // changing y 
            id = hashGet(&temp);
            if(id >i )
            {
                Union(i,id);
            }
            temp.y=y;           //reset y

            temp.z = z + 1;     // changing z        
            id = hashGet(&temp);
            if(id >i )
            {
                Union(i,id);
            }
            temp.z =z - 1;      // changing z 
            id = hashGet(&temp);
            if(id >i )                                                                      
            {
                Union(i,id);
            }
        }
        #pragma omp for private(i)
        for(i=0;i<n;i++){
            arr[i] = 0;
        }
    }

    int count=1;
    int x;
    for(i=0;i<n;i++){
        x=find_root(i);
        if(arr[x]==0){
            arr[x]=count;
            count++;
        }
        ans[i]=arr[x];   
    }
    endtime=omp_get_wtime();        //application time ends

    for (i = 0; i < n; i++)
    {
        printf("%d\n", ans[i]);
    }
    fprintf(op,"%.0lf\n", (endtime-starttime)*1000000); // print application time in micro seconds
    fclose(op);
}

int isequal(Point *a,Point *b)
{
    return (a->x==b->x && a->y==b->y && a->z==b->z);
}

int find_root(int x)    //find root with path comprassion
{
    int a;
    if(parent[x]!=x){
        parent[x]=find_root(parent[x]);
    }
    return parent[x];
}
void Union(int x,int y)     //union by rank
{
    int i,j;
    #pragma omp critical
    {
        i = find_root(x);
        j = find_root(y);
        if(i!=j){
            if(rank[i]<rank[j]){
                parent[i]=parent[j]; 
            }
            else if(rank[i]>rank[j]){
                parent[j]=parent[i];
            }
            else{
                parent[j]=parent[i];
                rank[i]++;
            }
        }
        
    }
    
}

void init_hashMap(int n)
{
    int i;
    hashSize = n;
    hashMap = (struct node **)malloc(n*sizeof(struct node *));
    #pragma omp parallel for private(i)
    for(i=0;i<n;i++)                                                   
    {
        hashMap[i] = NULL;
    }
}
int getHashIndex(Point *p)
{
    int index = (p->x*997*638669 + p->y*638669 + p->z);  //using two large primes to compute hash function
    index = index&0x7FFFFFFF;
    return index%hashSize;
}
void hashPut(Point *point,int id)
{
    int hashIndex = getHashIndex(point);
    struct node *head = hashMap[hashIndex];
    hashMap[hashIndex] = (struct node *)malloc(sizeof(struct node ));
    hashMap[hashIndex]->next =  head;
    hashMap[hashIndex]->key = point;
    hashMap[hashIndex]->id = id;
}
int hashGet(Point *point)
{
    int hashIndex = getHashIndex(point);
    struct node *head = hashMap[hashIndex];
    while(head!=NULL)
    {
        if (isequal(head->key,point))
            return head->id;                                         
        head = head -> next ;
    }
    return -1;
}