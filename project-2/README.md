# ECE 36800 Project 2: Huffman Coding

## Description
In this project, you will utilize your knowledge about queues and trees to design our own simple version of a file compression and decompression utility (similar to zip and unzip). You will base your utilities on the widely used algorithmic technique of Huffman coding. In case you did not know it, Huffman coding is used in JPEG compression as well as in MP3 audio compression. Let us see how the procedure of coding works.

## Functions

### The program huff.c
The program should accept one command line argument, which will be the name of an input file. The program should compress the input file using Huffman coding and write out the compressed output to a file that has the same name as the input file with a “.huff” appended to it. For example, if “example.txt” is the name of an input file, the output file should be “example.txt.huff”. 

### The program unhuff.c
The program should accept one command line argument, which will be the name of an input file. The program should de-compress the input file and write out the de-compressed output to a file that has the same name as the input file with an “.unhuff” appended to it. For example, if “example.txt.huff” is the name of an input file, the output file should be “example.txt.huff.unhuff”.

## Testing
Test your huff.c and unhuff.c by compiling them with the following command:
```
gcc -Werror -Wall -O3 huff.c -o huff
```
```
gcc -Werror -Wall -O3 unhuff.c -o unhuff
```
