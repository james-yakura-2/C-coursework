/**********************************************************************
 *  readme.txt template                                                   
 *  PS6 Kronos 
 **********************************************************************/

Name: James Yakura


Hours to complete assignment: 10


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
Assignment completed successfully.



/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each ones does.
 **********************************************************************/
\(log\.c\.166\) server started																Check for the startup log.
oejs\.AbstractConnector:Started SelectChannelConnector@0\.0\.0\.0:9080						Check for the startup-successful log
^$																							Check for a blank line
^(\d+-\d+-\d+)																				Capture datestamp
(\d+:\d+:\d+(?:\.\d+))																		Capture timestamp

/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/
 Read in each line. When reaching a server-started line, fail any existing pairs and start a new pair. When reaching a start-successful line, pass any existing pairs.



/**********************************************************************
 *  Did you use lambda expression? If yes describe there.
 **********************************************************************/
 Did not use lambda expression; nowhere that one would make sense




/**********************************************************************
 *  List whatever help (if any) you received from TAs,
 *  classmates, or anyone else.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
 Needed to use regex_search instead of regex_match. Suggest using regex_search in stdin_boost.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/


