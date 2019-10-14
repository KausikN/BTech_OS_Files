#include <bits/stdc++.h> 
using namespace std; 

int arr[1000];
  
struct data
{
    int beg;
    int end;
};

int run_size;

struct MinHeapNode 
{ 
    int element; 

    int i; 
}; 

void swap(MinHeapNode* x, MinHeapNode* y); 
 
class MinHeap 
{ 
    MinHeapNode* harr;
    int heap_size; 
  
public: 
    MinHeap(MinHeapNode a[], int size); 

    void MinHeapify(int); 
 
    int left(int i) { return (2 * i + 1); } 

    int right(int i) { return (2 * i + 2); } 

    MinHeapNode getMin() {  return harr[0]; } 

    void replaceMin(MinHeapNode x) 
    { 
        harr[0] = x; 
        MinHeapify(0); 
    } 
}; 

MinHeap::MinHeap(MinHeapNode a[], int size) 
{ 
    heap_size = size; 
    harr = a;
    int i = (heap_size - 1) / 2; 
    while (i >= 0) 
    { 
        MinHeapify(i); 
        i--; 
    } 
} 

void MinHeap::MinHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < heap_size && harr[l].element < harr[i].element) 
        smallest = l; 
    if (r < heap_size && harr[r].element < harr[smallest].element) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&harr[i], &harr[smallest]); 
        MinHeapify(smallest); 
    } 
} 

void swap(MinHeapNode* x, MinHeapNode* y) 
{ 
    MinHeapNode temp = *x; 
    *x = *y; 
    *y = temp; 
} 

int partition(int beg,int end){
    int pivot=arr[beg];
    int i=beg;
    int j=end;
    while(i<j){ 
        
        while(arr[i]<=pivot && i<end)
            i++;
            
        while(arr[j]>pivot && j>beg)
            j--;
            
        if(i<j){
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    

    int temp=arr[beg];
    arr[beg]=arr[j];
    arr[j]=temp;


return j;
}

void * quickSort(void *param)
{ 
    struct data *DQ = (struct data *)param;
    int l= DQ->beg;
    int r= DQ->end;

    // for(int i=0; i<run_size; i++)
    //     arr[i]=DQ->arr[i];

    if (l < r) 
    { 
        int j;
        j=partition(l,r);

        struct data QLeft,QRight;
        QLeft.beg = l;
        QLeft.end = j-1;
        
        // for(int i=0; i<run_size; i++){
        //     QLeft.arr[i]=arr[i];
        //     QRight.arr[i] =arr[i];
        // }

        QRight.beg = j+1;
        QRight.end = r;
       

        pthread_t tid[2];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        pthread_create(&tid[0],&attr,quickSort,&QLeft);
        pthread_create(&tid[1],&attr,quickSort,&QRight);
        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);

        // quickSort(arr, l, m); 
        // quickSort(arr, m + 1, r); 
  
    }
    pthread_exit(0); 

} 
  
FILE* openFile(char* fileName, char* mode) 
{ 
    FILE* fp = fopen(fileName, mode); 
    if (fp == NULL) 
    { 
        perror("Error while opening the file.\n"); 
        exit(EXIT_FAILURE); 
    } 
    return fp; 
} 

void mergeFiles(char *output_file, int n, int k) 
{ 
    FILE* in[k]; 
    for (int i = 0; i < k; i++) 
    { 
        char fileName[2]; 

        snprintf(fileName, sizeof(fileName), "%d", i); 
 
        in[i] = openFile(fileName, "r"); 
    } 

    FILE *out = openFile(output_file, "w"); 

    MinHeapNode* harr = new MinHeapNode[k]; 
    int i; 
    for (i = 0; i < k; i++) 
    { 
        if (fscanf(in[i], "%d ", &harr[i].element) != 1) 
            break; 
  
        harr[i].i = i;
    } 
    MinHeap hp(harr, i);
  
    int count = 0; 
 
    while (count != i) 
    { 
        MinHeapNode root = hp.getMin(); 
        fprintf(out, "%d ", root.element); 

        if (fscanf(in[root.i], "%d ", &root.element) != 1 ) 
        { 
            root.element = INT_MAX; 
            count++; 
        } 

        hp.replaceMin(root); 
    } 

    for (int i = 0; i < k; i++) 
        fclose(in[i]); 
  
    fclose(out); 
} 

void createInitialRuns(char *input_file, int num_ways) 
{ 
    FILE *in = openFile(input_file, "r"); 

    FILE* out[num_ways]; 
    char fileName[2]; 
    for (int i = 0; i < num_ways; i++) 
    { 
        snprintf(fileName, sizeof(fileName), "%d", i); 

        out[i] = openFile(fileName, "w"); 
    } 

    // int* arr = (int*)malloc(run_size * sizeof(int)); 
  
    bool more_input = true; 
    int next_output_file = 0; 
  
    int i; 
    while (more_input) 
    { 
        for (i = 0; i < run_size; i++) 
        { 
            if (fscanf(in, "%d ", &arr[i]) != 1) 
            { 
                more_input = false; 
                break; 
            } 
        } 

        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init (&attr);

        struct data StQ;
        StQ.beg = 0;
        StQ.end = i-1;
        // for(int i=0;i<run_size;i++)
        //     StQ.arr[i] = arr[i];

        pthread_create(&tid,&attr,quickSort,&StQ);
        pthread_join(tid,NULL);

        for (int j = 0; j < i; j++) 
            fprintf(out[next_output_file], "%d ", arr[j]); 
  
        next_output_file++; 
    } 

    for (int i = 0; i < num_ways; i++) 
        fclose(out[i]); 
  
    fclose(in); 
} 

void externalSort(char* input_file,  char *output_file, 
                  int num_ways) 
{ 
    createInitialRuns(input_file, num_ways); 

    mergeFiles(output_file, run_size, num_ways); 
} 


int main() 
{ 
	char input_file[] = "input.txt"; 
    char output_file[] = "output.txt"; 

    cout<<"Enter input file name: ";
    cin>>input_file;
    cout<<"Enter output file name: ";
    cin>>output_file;

    int num_ways = 10;
    cout<<"Enter number of splits: ";
    cin>>num_ways;

    run_size = 1000;
    cout<<"Enter run size: ";
    cin>>run_size;
  
    FILE* in = openFile(input_file, "w"); 
  
    srand(time(NULL)); 
    
    for (int i = 0; i < num_ways * run_size; i++) 
        fprintf(in, "%d ", rand()%100); 
  
    fclose(in); 
  
    externalSort(input_file, output_file, num_ways); 
  
    return 0; 
} 

