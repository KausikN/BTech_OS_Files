#include<stdio.h>
#include<unistd.h>
#include<string.h>
//#include<process.h>

/*
1. The position of next number is calculated by decrementing row number of previous number by 1, and incrementing the column number of previous number by 1. At any time, if the calculated row position becomes -1, it will wrap around to n-1. Similarly, if the calculated column position becomes n, it will wrap around to 0.

2. If the magic square already contains a number at the calculated position, calculated column position will be decremented by 2, and calculated row position will be incremented by 1.

3. If the calculated row position is -1 & calculated column position is n, the new position would be: (0, n-2).
*/
// -----------------------------------------------------------

int MagicSquare[100][100];

void GenerateSquare(int n)  
{    
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            MagicSquare[i][j] = 0;
        }
    }

    int i = n/2;  
    int j = n-1;  
  
    int num = 1;
    while(num <= n*n)  
    {  
        if (i == -1 && j == n) //case 3
        {  
            j = n-2;  
            i = 0;  
        }  
        else
        {
            if (j == n)  
                j = 0;  
  
            if (i < 0)  
                i = n-1;  
        }  
        if (MagicSquare[i][j]) //case 2
        {  
            j = j-2;  
            i++;  
            continue;  
        }  
        else
            MagicSquare[i][j] = num++;
  
        i--;
        j++;  //case 1 
    }  
  
    // Print 
    printf("The Magic Square for n=%d:\nSum of "
    "each row or column %d:\n\n", n, n*(n*n+1)/2);  
    for (i = 0; i < n; i++)  
    {  
        for (j = 0; j < n; j++)
        {
            printf("%d ", MagicSquare[i][j]);  
        }
        printf("\n");
    }  
}

int CheckSquare(int n)
{
    int sum = -1;

    for(int i=0;i<n;i++)
    {
        int rsum = 0, csum = 0;
        for(int j=0;j<n;j++)
        {
            rsum = rsum + MagicSquare[i][j];
            csum = csum + MagicSquare[j][i];
        }
        if(sum == -1) sum = rsum;
        else if(rsum != sum || csum != sum)
        {
            return 0;
        }
    }
    return 1;
}

// -----------------------------------------------------------


int main()
{
    printf("------------------------------------ MAGIC SQUARE GEN --------------------------------------\n");

    int side_size;

    while(1)
    {
        
        printf("Enter the side size of square: ");
        scanf("%d", &side_size);

        int pid = vfork();

        if(pid == 0)
        {
            GenerateSquare(side_size);
            exit(0);
            //return 0;
        }
        else if(pid > 0)
        {
            wait(NULL);

            printf("\n\n");

            int square_valid = CheckSquare(side_size);
            if(square_valid == 1) printf("Square is a Magic square.\n");
            else printf("Square is NOT a Magic square.\n");
        }

        printf("\n\n");

        int exit = 0;
        printf("Do you want to exit: ");
        scanf("%d", &exit);
        if(exit == 1)
        {
            printf("\n------------------------------------ MAGIC SQUARE GEN --------------------------------------\n");
            return 0;
        }

            

    }
}
