# ECE 368 Project 2: Huffman Coding

## Introduction
In this project, you will utilize your knowledge about queues and trees to design our own simple version of a file compression and decompression utility (similar to zip and unzip). You will base your utilities on the widely used algorithmic technique of Huffman coding. In case you did not know it, Huffman coding is used in JPEG compression as well as in MP3 audio compression. Let us see how the procedure of coding works.

### ASCII coding
Many programming languages use ASCII (which stands for American Standard Code for Information Interchange) coding to represent characters. In ASCII coding, every character is encoded (represented) with the same number of bits (8-bits) per character. Since there are 256 different values that can be represented with 8-bits, there are potentially 256 different characters in the ASCII character set. For your reference, the ASCII character table is available at http://www.asciitable.com/. 

Note that you must assume that all possible ASCII values may appear in the input text file. 

Let us now look at a simple example of ASCII encoding of characters. We'll look at how the string "go go gophers" is encoded in ASCII. Using ASCII encoding (8 bits per character) the 13-character string "go go gophers" requires 13 * 8 = 104 bits. The table below shows how the coding works.

Character
ASCII code 
8-bit binary value
g
103
1100111
o
111
1101111
p
112
1110000
h
104
1101000
e
101
1100101
r
114
1110010
s
115
1110011
Space
32
1000000


