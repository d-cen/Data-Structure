# ECE 36800 Project 1: Improved Sorting Algorithms

## Description
The goal of this project is to understand how Shell Sort improves the performance of Insertion Sort and to apply a similar optimization to Bubble Sort. In order to successfully complete this project, you will need to implement and compare the performance of Shell Sort (using Insertion Sort) and your Improved Sort (using Bubble Sort).

Shell Sort creates logical sub-arrays of elements that are spaced “gap” positions from each other in the given array. It then sorts each of these sub-arrays using Insertion Sort. The entire procedure is repeated using smaller and smaller values of “gap” till eventually gap=1, which will result in a sorted array. The chosen values of gap (called the gap sequence) are a very important aspect of Shell Sort. For this project, you will use the following sequence for implementing Shell sort:
```
{2p′3q′, ..., 2p3q, ..., 16, 12, 9, 8, 6, 4, 3, 2, 1}, where 2p′3q′ is the largest integer smaller than N (the size of the array to be sorted). We shall refer to this sequence as Seq1. 
```

You can envision a similar modification to improve Bubble Sort. Your task is to design and implement this modification. For your improved version of Bubble Sort, use the following gap sequence:
```
{N1=N/1.3, N2=N1/1.3, N3=N2/1.3, …, 1}, where N is the size of the array to be sorted. In other words, the next value in the gap sequence is the floor value of the previous integer gap divided by 1.3. However, if any value in this sequence becomes 9 or 10, it is replaced by a value of 11. We shall refer to this sequence as Seq2. Note that since the gap value has to be an integer, you will need to take the floor of the gap value computed above. 
```

## Functions
All the functions mentioned below and their support functions, if any, must reside in a program file named sorting.c. The first two functions Load_File and Save_File, are not for sorting, but are needed to transfer the integers to be sorted to and from the disk.

```
long *Load_File (char *Filename, int *Size)
```
The input file contains N+1 integers, one in each line. The first line of the file indicates the number of integers to be sorted, i.e., N. *Size should be assigned the value of N at the end of the routine. The subsequent lines contain (long) integers.

```
int Save_File (char *Filename, long *Array, int Size)
```
The function saves Array to an external file specified by Filename. The output file should have the same format as the input file. Return the count of integers that have been successfully saved; that is, if everything goes well, the return value should equal the argument Size. 

```
void Shell_Insertion_Sort (long *Array, int Size, double *NComp, double *NMove)
```
```
void Improved_Bubble_Sort (long *Array, int Size, double *NComp, double *NMove)
```
These functions take in an array of long integers (stored in Array) and sort them in ascending order. Size specifies the number of integers to be sorted, and *NComp and *NMove contain the number of comparisons and the number of moves involving items in Array. The Shell Insertion Sort function should use the sequence Seq1, and the Improved Bubble Sort should use the sequence Seq2.

A comparison that involves an item in Array, e.g., temp < Array[i] or Array[i] < temp, corresponds to one comparison. A comparison that involves two items in Array, e.g., Array[i] < Array[i-1], also corresponds to one comparison. A move is defined in a similar fashion. Therefore, a swap, which involves temp = Array[i]; Array[i] = Array[j]; Array[j] = temp, corresponds to three moves. Also note that a memcpy or memmove call involving n elements incurs n moves.

```
void Save_Seq1 (char *Filename, int N)
```
```
void Save_Seq2 (char *Filename, int N)
```
The function should generate Seq1 that is identical to the one used in your sorting code, and write Seq1, in ascending order, to an external file specified by Filename. The format of the file should follow what has been used in Save_File(). N is the size of the array to be sorted, NOT the size of Seq1.

## Testing
To compile, use the following command (add optimization flag -O3):
```
gcc -Werror -Wall -O3 sorting.c sorting_main.c -o proj1
```

To generate a sample input file, use this command:
```
random_file output_filename num_of_integers random_seed
```

