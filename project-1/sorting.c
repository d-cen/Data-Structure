#include <stdio.h>
#include "sorting.h"

long *Load_File(char *Filename, int *Size)
{
	FILE *fp = fopen(Filename, "r");
	fscanf(fp, "%d", Size);
	long *Array = malloc(sizeof(long) * (*Size));
        int i;
	for(i = 0; i < *Size; i++)
	{
		fscanf(fp, "%ld", Array + i);
	}
	fclose(fp);
	return Array;
}

int Save_File(char *Filename, long *Array, int Size)
{
    FILE *fp = fopen(Filename, "w");
    int count = 0;
    fprintf(fp, "%d\n", Size);
    int i;
    for(i = 0; i < Size; i++)
    {
        fprintf(fp, "%ld\n", Array[i]);
        count++;
    }
    fclose(fp);
    return count;
}

int *Gen_Seq1(int *Size, int N)
{
    int *seq = malloc(sizeof(int) * N);
    int i = 1, ptr2 = 0, ptr3 = 0, ptr2Val, ptr3Val;
    seq[0] = 1;
    while(seq[i - 1] < N)
    {
        ptr2Val = seq[ptr2] * 2;
        ptr3Val = seq[ptr3] * 3;
        if(ptr2Val == seq[i - 1])
        {
            ptr2++;
        }
        if(ptr3Val == seq[i - 1])
        {
            ptr3++;
        }
        ptr2Val = seq[ptr2] * 2;
        ptr3Val = seq[ptr3] * 3;
        if(ptr2Val < ptr3Val)
        {
            ptr2++;
            seq[i] = ptr2Val;
        }
        else
        {
            ptr3++;
            seq[i] = ptr3Val;
        }
        i++;
    }
    *Size = i - 1;
    return seq;
}

int *Gen_Seq2(int *Size, int N)
{
    int *seq = malloc(sizeof(int) * N);
    int i = 0;
    do{
        N /= 1.3;
        if(N == 9 || N == 10)
        {
            N = 11;
        }
        seq[i] = N;
        i++;
    } while(seq[i - 1] != 1);
    *Size = i - 1;
    return seq;
}

void Save_Seq1(char *Filename, int N)
{
    int Size;
    int *seq = Gen_Seq1(&Size, N);
    FILE *fp = fopen(Filename, "w");
    fprintf(fp, "%d\n", N);
    int i;
    for(i = 0; i < Size; i++)
    {
        fprintf(fp, "%d\n", seq[i]);
    }
    fclose(fp);
}

void Save_Seq2(char *Filename, int N)
{
    int Size;
    int *seq = Gen_Seq2(&Size, N);
    FILE *fp = fopen(Filename, "w");
    fprintf(fp, "%d\n", N);
    int i;
    for(i = Size; i >= 0; i--)
    {
        fprintf(fp, "%d\n", seq[i]);
    }
    fclose(fp);
}

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
    int seqSize, i, gap, j, k, comp = 0, move = 0;
    long key;
    int *seq = Gen_Seq1(&seqSize, Size);
    for(i = (seqSize - 1); i >= 0; i--)
    {
        gap = seq[i];
        for(j = gap; j < Size; j++)
        {
            key = Array[j];
            for(k = j; k >= gap && Array[k - gap] > key; k -= gap)
            {
                Array[k] = Array[k - gap];
                move++;
                comp++;
            }
            Array[k] = key;
            move++;
        }
    }
    *N_Comp = comp;
    *N_Move = move;
}

void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
    int seqSize, i, j, k, gap, comp = 0, move = 0;
    int *seq = Gen_Seq2(&seqSize, Size);
    for(i = 0; i < (seqSize + 1); i++)
    {
        gap = seq[i];
        for(j = gap; j < Size; j++)
        {
            for(k = j; k >= gap && Array[k - gap] > Array[k]; k -= gap)
            {
                Swap(&Array[k], &Array[k - gap]);
                move += 3;
                comp++;
            }
        }
    }
    *N_Comp = comp;
    *N_Move = move;
}

void Swap(long *x, long *y)
{
    long temp = *x;
    *x = *y;
    *y = temp;
}

