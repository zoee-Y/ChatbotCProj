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
    if (who_head != NULL){/* Check Whether linked list exists*/   
    points = who_head; /* Moves points to Who Linked list starting node */
    
    do{/* points will look for the entity to check whether it exists*/  
      if (compare_token(points->entity, entity ) == 0){
        /* strncpy function: strncpy(char *dest, const char *src, size_t n)*/
        strncpy(response, points->response, n); /* strcpy it to the response */
        return KB_OK;
        }
      points=points->next; /* Moves "points" to the next node to look for entity */ 
    }while (compare_token(intent, "who") == 0); /* points will terminate once intent is not "who" in the node */
    }
    else{
      return KB_NOTFOUND;/* Points did not find the entity */
    }
  }else if (compare_token(intent, "what") == 0) { /*If Intent is what.*/
    if (what_head != NULL){/* Check Whether linked list exists*/ 
    points = what_head;
    do{/* points will look for the entity to check whether it exists*/  
      if (compare_token(points->entity, entity ) == 0){
        strncpy(response, points->response, n); /* strcpy it to the response */
        return KB_OK;
        }      
    points=points->next; /* Moves "points" to the next node to look for entity */ 
    }while (compare_token(intent, "what") == 0); /* points will terminate once intent is not "what" in the node */
    }
    else{
      return KB_NOTFOUND;/* Points did not find the entity */
    }
  }else if (compare_token(intent, "where") == 0) { /*If Intent is where.*/
    if (where_head != NULL){/* Check Whether linked list exists*/ 
    points = what_head; 
    do{/* points will look for the entity to check whether it exists*/  
      if (compare_token(points->entity, entity ) == 0){
        strncpy(response, points->response, n); /* strcpy it to the response */
        return KB_OK;
        }
    points=points->next; /* Moves "points" to the next node to look for entity */ 
    }while (compare_token(intent, "where") == 0); /* points will terminate once intent is not "where" in the node */
    }
    else{
      return KB_NOTFOUND;/* Points did not find the entity */
    }
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
	if (compare_token(intent, "who") == 0){ /*If Intent is who.*/
		points = who_head; /* Moves points to Who Linked list starting node */
		question_node *new_node = (question_node *)calloc(3, sizeof(question_node)); /* assign memory for new_node */
		if (new_node == NULL){ /* if new_node is null, there was a memory allocation failure */
			return KB_NOMEM;
		}
		//new_node->intent = intent; /* put all the data into this new_node */
		strcpy(new_node->intent, intent);
		//new_node->response = response;
		strcpy(new_node->response, response);
		//new_node->entity = entity;
		strcpy(new_node->entity, entity);
      		if (strlen(points->intent) == 0){ /* if there is no intent for "who" in the database, assign all the data from new_node to points */
			points = new_node;
			return KB_FOUND;
		} else {
			do{ /* points will look for the entity to check whether it exists*/   
      				if (points->entity == NULL){ /* if there is no entity in the Who Linked list, then add in the entity and response */
        				//points->entity = new_node->entity;
						strcpy(points->entity, new_node->entity);
					//points->response = new_node->response;
					strcpy(points->response, new_node->response);
					return KB_FOUND;
				} else if (compare_token(entity, points->entity) == 0) { /* if there is a match to the entity in the Who Linked list, 
				then add/change the response */
					//points->response = new_node->response;
					strcpy(points->response, new_node->response);
					return KB_FOUND;
				} else {
      					break; /* Break out of the if-else statement to find the next entity */
				}
				points = points->next; /* Moves "points" to the next node to look for entity */
    			}while (compare_token(intent, "who") == 0); /* points will terminate once intent is not "who" in the node */
		}
	} else if (compare_token(intent, "what") == 0){ /*If Intent is what.*/
		points = what_head; /* Moves points to What Linked list starting node */
		question_node *new_node = (question_node *)calloc(3, sizeof(question_node)); /* assign memory for new_node */
		if (new_node == NULL){ /* if new_node is null, there was a memory allocation failure */
			return KB_NOMEM;
		}
		//new_node->intent = intent; /* put all the data into this new_node */
		strcpy(new_node->intent, intent);
		//new_node->response = response;
		strcpy(new_node->response, response);
		//new_node->entity = entity; 
		strcpy(new_node->entity, entity);
      		if (strlen(points->intent) == 0){ /* if there is no intent for "what" in the database, assign all the data from new_node to points */
			points = new_node;
			return KB_FOUND;
		} else {
			do{ /* points will look for the entity to check whether it exists*/   
      				if (points->entity == NULL){ /* if there is no entity in the What Linked list, then add in the entity and response */
        				//points->entity = new_node->entity;
						strcpy(points->entity, new_node->entity);
					//points->response = new_node->response;
					strcpy(points->response, new_node->response);
					return KB_FOUND;
				} else if (compare_token(entity, points->entity) == 0) { /* if there is a match to the entity in the What Linked list, 
				then add/change the response */
					//points->response = new_node->response;
					strcpy(points->response, new_node->response);
					return KB_FOUND;
				} else {
      					break; /* Break out of the if-else statement to find the next entity */
				}
				points = points->next; /* Moves "points" to the next node to look for entity */
    			}while (compare_token(intent, "who") == 0); /* points will terminate once intent is not "what" in the node */
		}
	} else if (compare_token(intent, "where") == 0){ /*If Intent is where.*/
		points = where_head; /* Moves points to Where Linked list starting node */
		question_node *new_node = (question_node *)calloc(3, sizeof(question_node)); /* assign memory for new_node */
		if (new_node == NULL){ /* if new_node is null, there was a memory allocation failure */
			return KB_NOMEM;
		}
		//new_node->intent = intent; /* put all the data into this new_node */
		strcpy(new_node->intent, intent);
		//new_node->response = response;
		strcpy(new_node->response, response);
		//new_node->entity = entity;
		strcpy(new_node->entity, entity);
      		if (strlen(points->intent) == 0){ /* if there is no intent for "where" in the database, assign all the data from new_node to points */
			points = new_node;
			return KB_FOUND;
		} else {
			do{ /* points will look for the entity to check whether it exists*/   
      				if (points->entity == NULL){ /* if there is no entity in the Where Linked list, then add in the entity and response */
        				//points->entity = new_node->entity;
						strcpy(points->entity, new_node->entity);
					//points->response = new_node->response;
					strcpy(points->response, new_node->response);
					return KB_FOUND;
				} else if (compare_token(entity, points->entity) == 0) { /* if there is a match to the entity in the Where Linked list, 
				then add/change the response */
					//points->response = new_node->response;
					strcpy(points->response, new_node->response);
					return KB_FOUND;
				} else {
      					break; /* Break out of the if-else statement to find the next entity */
				}
				points = points->next; /* Moves "points" to the next node to look for entity */
    			}while (compare_token(intent, "who") == 0); /* points will terminate once intent is not "where" in the node */
		}
	} else {
		return KB_INVALID; /* Intent is not who,what,where */
	}
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
