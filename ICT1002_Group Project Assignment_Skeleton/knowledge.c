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

  char line[MAX_ENTITY + 1 + MAX_RESPONSE + 1] = "";
  size_t n = 1;
  char *intent;
  char *entity;
  char *response;
  int result;

  if (f == NULL) {
    printf("Could not open file\n");
    return 1;
  }
  else {
    while (!feof(f)) {
      while (fgets(line, MAX_ENTITY + 1 + MAX_RESPONSE + 1, f)) {
        size_t length = strlen(line);

        if (length) { //if is not empty line
          //if there is occurrence of \n in the line
          if (strchr(line, '\n') != NULL) {
            //printf("newline found");
            *strchr(line, '\n') = '\0';
          }

          //if there is occurrence of \r in the line
          else if (strchr(line, '\r') != NULL) {
            *strchr(line, '\r') = '\0';
          }
          
          //if the line is an intent with square brackets
          if (strchr(line, '[') != NULL && strchr(line, ']') != NULL) { 
            //if it is, then check which intent is it under
            if (compare_token(line, "[what]") == 0) {
              intent = "what";
              continue;
            }
            else if (compare_token(line, "[where]") == 0) {
              intent = "where";
              continue;
            }
            else if (compare_token(line, "[who]") == 0) {
              intent = "who";
              continue;
            }
            else {
              //if not what/where/who, it is invalid intent
              intent = NULL;
            }
          }
          //if not intent
          
          //check if the intent is valid first
          if (intent != NULL) {
            //check if it is entity-response pair with =
            if (strchr(line, '=') != NULL) {
              entity = strtok(line, "=");
              response = strtok(NULL, "=");
              result = knowledge_put(intent, entity, response);
              if (result == KB_FOUND) {
                n++;
                printf("%zu", n);
              }
            } 
          }
        }
      }
    }
  }

	return n;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {

if (who_head != NULL){

	    while (who_head != NULL) { 
		points = who_head;       
        who_head = who_head->next; 
        free(points);
		}
}
if (what_head != NULL){

	    while (what_head != NULL) { 
		points = what_head;       
        what_head = what_head->next; 
        free(points);
		}
}

if (where_head != NULL){

	    while (where_head != NULL) { 
		points = where_head;       
        where_head = where_head->next; 
        free(points);
		}
	}
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {

	if (who_head != NULL){
    fprintf(f, "[who]\n");
	  while (who_head != NULL) { 
      fprintf(f, "%s=%s\n", who_head->entity, who_head->response);
		}
  }

  if (what_head != NULL){
    fprintf(f, "[what]\n");
	  while (what_head != NULL) { 
      fprintf(f, "%s=%s\n", what_head->entity, what_head->response);
		}
  }

  if (where_head != NULL){
    fprintf(f, "[where]\n");
	  while (where_head != NULL) { 
      fprintf(f, "%s=%s\n", where_head->entity, where_head->response);
		}
  }

}
