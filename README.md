# wordsearch
Wordsearch program as assigned for Bryant York's NB Theory II course at Portland State University. 

Version one is a barely modified and commented version of Chong Kim's code for the same program. 
https://github.com/chongkim/wordsearch/blob/master/c/wordsearch.c
https://www.youtube.com/watch?v=Gjiwgnpv-5s

Version two will be more strongly modified. 

Assignment: 
New Beginnings Theory II
Fall 2016
Programming Assignment 3
Professor York
Due Date: 11/02/2016 17:00 PT
There is a familiar old game called the “Word Search Game”. It is often played with pencil and
paper by young children. The gamer is provided with a rectangular array of letters followed by a
collection of words. The goal is to find all occurrences of each word in the rectangular array. A
word may appear horizontally, vertically, and diagonally running in either direction, thus giving
8 possible directions.
See the following website for the rules and examples.
http://www.gmpuzzles.com/blog/word-search-rules-and-info/
Your task in this programming assignment is as follows:
1. Think about how you would design and code a wordsearch algorithm in the C language.
2. View the following video by Chong Kim from December 2013:
https://www.youtube.com/watch?v=Gjiwgnpv-5s
3. Pause the video and copy his code into a file.
4. Insert comments into the code to describe what he is doing at significant places in the
program.
5. Compile and run his code on the provided input files (Input1.txt and Input2.txt).
a. In your makefile be sure to use the: -gnu99 switch of gcc
6. In a single sentence describe any anomalies that you notice. Does his program adhere to
the rules of the wordsearch game?
7. How would you fix any anomalies.
8. How would you change the code to read just the array of letters from a file and to accept
search words interactively?
9. Provide a simpler design and code based on two new important details about the input:
a. The input array is SQUARE.
b. The number of rows in the input square array is provided as an integer n
(4 < n < 25) in the first line of the file, followed by a blank line, followed by n
rows of n characters each. The characters are all upper case and drawn from A-Z.
c. The search words must be provided interactively.
Submission requirements:
1. Your submission must consist of a zip or 7z file that contains two source files ws1.c and
ws2.c, a makefile that allows for each program (ws1.c and ws2.c) to be compiled and run
on ada.cs.pdx.edu and a file named design.txt. ws1.c should contain the copy of Kim’s
code. Ws2.c should be the code developed by you.
2. The name of the zip file must be PA3_<yourlastname> with extension .zip or .7z
3. Within the files ws1.c and ws2.c there must be a banner:
<your first name> <your last name>
<date submitted>
NEW EGINNINGS Theory II
Programming Assignment 3
4. The file ws1.c must have a comment line in the banner indicating that the code was taken
from Chong Kim video and used for educational purposes.
5. The zip file for this assignment must be uploaded to D2L by 17:00 PT on 11/02/2016.
