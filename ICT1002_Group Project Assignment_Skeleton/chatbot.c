/*
 * ICT1002 (C Language) Group Project.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#include <stdio.h>
#include <string.h>
#include "chat1002.h"


/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return "Chatbot";

}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "User";

}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {

	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}

	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_smalltalk(inv[0]))
		return chatbot_do_smalltalk(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {

	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;

}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {

	snprintf(response, n, "Goodbye!");

	return 1;

}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {
	
	if (compare_token(intent, "load") == 0){
		return 1;
	} else {
		return 0;
	}
}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {

	
	char filename[MAX_INPUT];
	FILE *file_check;
	int responses = 0;
	
	// To load the file
	if (compare_token(inv[1], "from") == 0) 
	{
		strcpy(filename,inv[2]);
	}
	
	else
	{
		strcpy(filename,inv[1]);
	}
	
	// Open the file in read format
	file_check = fopen(filename,"r");
	
	// check if the file exist
	if (file_check != NULL)
	{
		// File exist and would read the number of responses in it
		responses = knowledge_read(file_check);
		fclose(file_check);
		printf("There are %d reponses in %s.",responses,file_check);
	}
	else
	{
		// File does not exist and an error message would pop out
		printf("There is an error in loading the knowledge %s.",file_check);
	}
		       
	return 0;

}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {

	return( compare_token(intent, "what") == 0 || compare_token(intent, "where") == 0 || compare_token(intent,"who") == 0);

	return 0;

}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {
	char *intent = inv[0];
	char entity[MAX_ENTITY];
    char ignore[MAX_ENTITY];			
    char * ignorelist[] = {"is","are"};  

	
	getEntity(inc, inv, ignorelist, 2, entity, ignore);

	if (knowledge_get(intent, entity, response, n ) == KB_NOTFOUND){
		char answer[MAX_RESPONSE];
		prompt_user(answer, n, "I Don't Know. %s%s%s", intent, ignore, entity);
	
	char *fliter = trim (answer);
	if(strlen(fliter) != 0){
		knowledge_put(intent,entity,fliter);
		snprintf(response, n, "Thank You. ");
		}
	else{
		snprintf(response, n, ":-(");
	}
				
	}
	return 0;

	

}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {

	if (compare_token(intent, "reset") == 0){
		return 1;
	} else {
		return 0;
	}

	return 0;

}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {

	knowledge_reset();
	snprintf(response, n,"%s resetted", chatbot_botname());
	
	return 0;

}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {
	if (compare_token(intent, "save") == 0){
		return 1;
	} else {
		return 0;
	}

	return 0;

}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {

	char filename[MAX_INPUT];
	FILE *file_check;
	
	// Checking to see if it is "save to" or "save as"
	
	if (compare_token(inv[1],"to") == 0 || compare_token(inv[1],"as") == 0)
	    {
		    strcpy(filename,inv[2]);
	    }
	    
	else 
	    {
		strcpy(filename,inv[1]);
	    }
	    
	// opening the file in write mode 
	file_check = fopen(filename,"w");
	
	// To check whether if the file have been created 
	if (file_check != NULL) 
	    { 
		    // if filename is created, it would write and save the knowedge in
		    knowledge_write(file_check);
		    fclose(file_check);
		    printf("The new knowledge have been successfully saved to %s.",filename);
	    }
	
	else
	    { 
		    // if filename is not created, thee would be an error message which would show up
		    printf("There seem to have some error in saving the new knowledge to %s.",filename);
	    }
	

	return 0;

}


/*
 * Determine which an intent is smalltalk.
 *
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is the first word of one of the smalltalk phrases
 *  0, otherwise
 */
int chatbot_is_smalltalk(const char *intent) {

	// if intent is hi/hello/goodbye
	return compare_token(intent, "hi") == 0 || compare_token(intent, "hello") == 0 || compare_token(intent, "goodbye") == 0 || compare_token(intent, "it's") == 0 || compare_token(intent, "It's") == 0 || compare_token(intent, "its") == 0 || compare_token(intent, "Its") == 0;
}


/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop chatting (e.g. the smalltalk was "goodbye" etc.)
 */
int chatbot_do_smalltalk(int inc, char *inv[], char *response, int n) {

	// check if user said goodbye
	if (compare_token(*inv, "goodbye") == 0) {
		snprintf(response, n, "Goodbye!");
		//stop the conversation
		return 1;
	}
  	if (compare_token(*inv, "its") == 0 ||compare_token(*inv, "it's") == 0 || compare_token(*inv, "It's") == 0) {
		snprintf(response, n, "Indeed it is.");
		//stop the conversation
		return 0;
	}
	if (compare_token(*inv, "joke") == 0) {
		snprintf(response, n, "Indeed it is");
		//stop the conversation
		return 0;
	}
	
	//if its not goodbye, respond hi
	if (compare_token(*inv, "hi") == 0) {
		snprintf(response, n, "Hi!");
		//stop the conversation
		return 0;
	}
	return 1;
}
	  
	    
	    
// To ignore inv[1] if the word is 'is' or 'are'  
	    
int compare_ignorelist(char * word, char * ignorelist[], int ignorelistsize){
    
    for(int i = 0; i < ignorelistsize; i++ ){    // Loop through each word in the ignore list
        // Insensitively check
        if(compare_token(word, ignorelist[i]) == 0){
            // Return true
            return 1;
        }
    }
    // Return false
    return 0;
}

	    

	    
// Get entity from user's input 
	    
void getEntity(int inc, char *inv[], char * ignorelist[], int ignorelistsize, char entity[], char removed[]){
	
    int entity_length = 0;		// Index to insert the next word

    							
	for(int i = 1; i<inc; i++){
        
		if(i == 1){
            
            if(compare_ignorelist(inv[i], ignorelist, ignorelistsize)){                							// Check if first word is inside in the ignorelist
                
				snprintf(removed, MAX_ENTITY, " %s ", inv[i]);													//Store ignored word in between spaces
				
				entity_length += snprintf(entity+entity_length, MAX_ENTITY-entity_length, "%s", "");			//Change entity to blank
			}
			else{
				
				snprintf(removed, MAX_ENTITY, "%s", " ");														// remove spacing
				
				entity_length += snprintf(entity+entity_length, MAX_ENTITY-entity_length, "%s", inv[i]);		//change entity to first word
			}
		}
		else
		{
		
			if(strcmp(entity, "") != 0){
				entity_length += snprintf(entity + entity_length, MAX_ENTITY-entity_length," %s", inv[i]);	//2nd words onwards are accumulated
			}
			else {
				entity_length += snprintf(entity + entity_length, MAX_ENTITY-entity_length,"%s", inv[i]);
			}
		}
	}
}
