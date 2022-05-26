/**********************************************************************
 *  readme.txt template                                                   
 *  Markov Model
 **********************************************************************/

Name: James Yakura

Hours to complete assignment: 4
/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
 This is a Markov chain that takes in text and uses it to generate similar text.




  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
This program makes use of map<string, map<char, int>> to store information about the next character.




/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/

 Basic Markov chain: Read in a string, use k-grams to determine the frequencies of the next character.
 Frequency: Look up a k-gram in the next-characters map, or look up a character within a single k-gram's frequency table.
 Generate: Using the current k-gram, look up the next possible characters and then randomly decide one.



/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
 Basic Markov model completed. Did not test.



/**********************************************************************
 *  Does your implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/




 /**********************************************************************
 *  Describe where you used exceptions. 
 *  Provide files and lines of the code.
 ***********************************************************************/
 Code throws an exception if there is no next value for the current k-gram.




 /**********************************************************************
 *  Describe where you used lambda expression if any
 *  Provide files and lines of the code.
 ***********************************************************************/



/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
 Some difficulty in setting up operator.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

