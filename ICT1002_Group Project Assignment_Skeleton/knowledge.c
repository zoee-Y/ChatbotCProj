/*
 * ICT1002 (C Language) Group Project.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * knowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n) {
  /* Refer to chat1002.h for information about "points" and "head" */

  if (compare_token(intent, "who") == 0) {  /*If Intent is who.*/
    points = who_head; /* Moves points to Who Linked list starting node */
    do{/* points will look for the entity to check whether it exists*/   
      if (compare_token(entity, points->entity) == 0){
        /* strncpy function: strncpy(char *dest, const char *src, size_t n)*/
        strncpy(response, points->response, n); /* strcpy it to the response */
        return KB_OK;
        }
      points=points->next; /* Moves "points" to the next node to look for entity */ 
    }while (compare_token(intent, "who") == 0); /* points will terminate once intent is not "who" in the node */

    return KB_NOTFOUND;/* Points did not find the entity */

  }else if (compare_token(intent, "what") == 0) { /*If Intent is what.*/
    points = what_head;
    do{/* points will look for the entity to check whether it exists*/  
      if (compare_token(entity, points->entity) == 0){
        strncpy(response, points->response, n); /* strcpy it to the response */
        return KB_OK;
        }
    }while (compare_token(intent, "what") == 0); /* points will terminate once intent is not "what" in the node */

    return KB_NOTFOUND;/* Points did not find the entity */

  }else if (compare_token(intent, "where") == 0) { /*If Intent is where.*/
    points = what_head; 
    do{/* points will look for the entity to check whether it exists*/  
      if (compare_token(entity, points->entity) == 0){
        strncpy(response, points->response, n); /* strcpy it to the response */
        return KB_OK;
        }
    }while (compare_token(intent, "where") == 0); /* points will terminate once intent is not "where" in the node */

    return KB_NOTFOUND; /* Points did not find the entity */

  } else { /* Intent is not who,what,where */
    return KB_INVALID; 
  }
}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response) {

	/* to be implemented */

	return KB_INVALID;

}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE *f) {

	/* to be implemented */

	return 0;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {

	/* to be implemented */

}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {

	/* to be implemented */

}
