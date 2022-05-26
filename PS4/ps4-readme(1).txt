/**********************************************************************
 *  readme 
 *  DNA Sequence Alignment
 **********************************************************************/

Name: James Yakura

Hours to complete assignment: 1 (in progress)

/**********************************************************************
 * Explain which approach you decided to use when implementing
 * (either recursive with memoization, recursive without memoization,
 * dynamic programming or Hirschberg’s algorithm). Also describe why
 * you chose this approach and what its pros and cons are.
 **********************************************************************/
 Used matrix. This is easy to implement and runs in n^2 time and n^2 space. 
 The biggest drawback is that it would struggle with more complex transformations that are not part of the assignment, 
 and it cannot handle sequences as large as Hirschberg's algorithm can.




/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file? 
 * 
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/
Input:
the quick brown fox jumps over a lazy dog
thequi ckbrown  foxjump s overthe lazydog


Expected output:
the qui-ck brown- fox jump s over a- lazy dog
the-qui ck-brown  fox jump s overthe lazy-dog

What happened:
the quick brown fox jumps over a- lazy dog
the-qui ckbrown  foxjumps overthe lazy-dog

Not quite correct, but close. Seems to have found a shorter path.


/**********************************************************************
 * Look at your computer’s specs in the settings. 
 * How much RAM does your computer have and explain what this means? 
 **********************************************************************/
 8GB. This computer has a bit under 8 billion bytes available.


/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of 
 *  N. Give an answer of the form a * N^b for some constants a 
 *  and b, where b is an integer. Note chars are 2 bytes long, and 
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 8GB (billion bytes) of memory?
 **********************************************************************/
a =4
b = 2
This program uses a NxM array of integers, and two 1xN and 1xM arrays of characters. The memory used is 4(NxM)^2+2N+2M. 
Assuming N=M, memory usage is 4(N^2+N), or 4N(N+1).

largest N =44720

/**********************************************************************
 * Run valgrind if you can and attach the output file to your submission. 
 * If you cannot run it, explain why, and list all errors you’re seeing. 
 * If you can run it successfully, does the memory usage nearly match that 
 * found in the question above? 
 * Explain why or why not. 
/**********************************************************************
Can run valgrind, but no output file generated.


/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *
 *  If you get segmentation fault when allocating memory for the last
 *  two test cases (N=20000 and N=28284), note this, and skip filling
 *  out the last rows of the table.
 **********************************************************************/

data file           distance       time (seconds)     memory (MB)
------------------------------------------------------------------
ecoli2500.txt		120				3				25
ecoli5000.txt		162				14				100
ecoli7000.txt		196				29				196
ecoli10000.txt		225				59				400
ecoli20000.txt		3135			236				1600				
ecoli28284.txt		8394			492	(24.5255)	[Valgrind error]

Note: This data was obtained under Valgrind. The program runs much faster without a memory checker.

/*************************************************************************
 *  Here are sample outputs from a run on a different machine for 
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730



/**********************************************************************
 *  For this question assume M=N (which is true for the sample files 
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a 
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use 
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 * 
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/
a = 6.1501x10^-7 for Valgrind, estimated 3.066x10^-8 without
b = 2
largest N = 382675, assuming run under Valgrind. Estimated 1187074 without

Doubling N results in quadrupling time. The function is quadratic.

/
**********************************************************************
 *  Did you use the lambda expression in your assignment? If yes, where 
 * (describe a method or provide a lines numbers)
 **********************************************************************/
 Did not use lambda expression; no place where one would make sense.



**********************************************************************
 *  List whatever help (if any) you received from the course TAs,
 *  instructor, classmates, or anyone else.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/



/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

