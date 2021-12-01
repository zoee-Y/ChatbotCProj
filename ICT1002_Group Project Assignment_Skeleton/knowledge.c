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
    who_points = who_head; /* Moves points to Who Linked list starting node */
    
    do{/* points will look for the entity to check whether it exists*/ 
        if (compare_token(who_points->entity, entity ) == 0){
          /* strncpy function: strncpy(char *dest, const char *src, size_t n)*/
          strncpy(response, who_points->response, n); /* strcpy it to the response buffer */
          return KB_OK;
          }
        who_points = who_points->next; /* Moves "points" to the next node to look for entity */
      
    }while (who_points != NULL); /* loop will terminate when there is no more nodes in the "who" linked list */
    return KB_NOTFOUND;
    }
    else{
      return KB_NOTFOUND;/* Points did not find the entity */
    }
  }else if (compare_token(intent, "what") == 0) { /*If Intent is what.*/
    if (what_head != NULL){/* Check Whether linked list exists*/ 
    what_points = what_head;
    do{/* points will look for the entity to check whether it exists*/  
      if (compare_token(what_points->entity, entity ) == 0){
        strncpy(response, what_points->response, n); /* strcpy it to the response buffer */
        return KB_OK;
      }
    what_points = what_points->next; /* Moves "points" to the next node to look for entity */
    
    }while (what_points != NULL); /* loop will terminate when there is no more nodes in the "what" linked list */
    return KB_NOTFOUND;
    }
    else{
      return KB_NOTFOUND;/* Points did not find the entity */
    }
  }else if (compare_token(intent, "where") == 0) { /*If Intent is where.*/
    if (where_head != NULL){/* Check Whether linked list exists*/ 
    where_points = where_head; //zoe: changed from what_head to where_head
    do{/* points will look for the entity to check whether it exists*/  
        if (compare_token(where_points->entity, entity ) == 0){
          strncpy(response, where_points->response, n); /* strcpy it to the response buffer */
          return KB_OK;
          }
            where_points = where_points->next; /* Moves "points" to the next node to look for entity */
      
    }while (where_points != NULL); /* loop will terminate when there is no more nodes in the "where" linked list */
    return KB_NOTFOUND;
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
  char temp_response[MAX_RESPONSE]; /* Declare a temporary variable for response */
  int get_knowledge; /* Declare the variable to store the return value of knowledge_get */
  get_knowledge = knowledge_get(intent, entity, temp_response, MAX_RESPONSE); /* Call the function knowledge_get in order to check if there exists an intent-entity pair in the linked lists */
  get_knowledge *= -1; /* This makes sure that all integer values from the return value of knowledge_get is a positive number */
  if (get_knowledge == 2){ /* If the intent is not a valid question word, return KB_INVALID */
    return KB_INVALID;
  } else {
    if (compare_token(intent, "who") == 0){ /* First check if the intent is "who" */
      if (get_knowledge == 0){ /* If the intent is "who" and the intent-entity pair exists */
        who_points = who_head; /* appoint the "who" pointer to "who" head which is the start of the "who" Linked List */
        do{
          if (compare_token(who_points->entity, "entity") == 0){ /* if statement to check if the entity in the parameters and the entity in that particular node are the same */
            strncpy(who_points->response, response, MAX_RESPONSE); /* Copy the response to the node's response, it would overwrite any exisiting response in that node */
            return KB_FOUND; 
          }
          who_points = who_points->next; /* If cannot find the entity, then go to the next node in the "who" Linked List */
        } while(who_points != NULL); /* do-while loop that searches through all not null nodes in the "who" Linked List */
      } else if (get_knowledge == 1){  /* If the intent is "who", but the intent-entity pair does not exists */
        question_node *new_node = (question_node *) malloc(sizeof(question_node));
        if (new_node == NULL){ /* memory allocation failure */
          return KB_NOMEM;
        } else { /* If no memory allocation failure, copy the intent, entity & response to the new_node and insert the new_node into the beginning of the "who" Linked List */
          strcpy(new_node->intent, intent);
          strcpy(new_node->entity, entity);
          strcpy(new_node->response, response);
          new_node->next = who_head;
          who_head = new_node;
          return KB_FOUND;
        }
      }
    } else if (compare_token(intent, "what") == 0){ /* First check if the intent is "what" */
      if (get_knowledge == 0){ /* If the intent is "what" and the intent-entity pair exists */
        what_points = what_head; /* appoint the "what" pointer to "what" head which is the start of the "what" Linked List */
        do{
          if (compare_token(what_points->entity, "entity") == 0){ /* if statement to check if the entity in the parameters and the entity in that particular node are the same */
            strncpy(what_points->response, response, MAX_RESPONSE); /* Copy the response to the node's response, it would overwrite any exisiting response in that node */
            return KB_FOUND;
          }
          what_points = what_points->next; /* If cannot find the entity, then go to the next node in the "what" Linked List */
        } while(what_points != NULL); /* do-while loop that searches through all not null nodes in the "what" Linked List */
      } else if (get_knowledge == 1){ /* If the intent is "what", but the intent-entity pair does not exists */
        question_node *new_node = (question_node *) malloc(sizeof(question_node));
        if (new_node == NULL){ /* memory allocation failure */
          return KB_NOMEM;
        } else { /* If no memory allocation failure, copy the intent, entity & response to the new_node and insert the new_node into the beginning of the "what" Linked List */
          strcpy(new_node->intent, intent);
          strcpy(new_node->entity, entity);
          strcpy(new_node->response, response);
          new_node->next = what_head;
          what_head = new_node;
          return KB_FOUND;
        }
      }
    } else if (compare_token(intent, "where") == 0){ /* First check if the intent is "where" */
      if (get_knowledge == 0){ /* If the intent is "where" and the intent-entity pair exists */
        where_points = where_head; /* appoint the "where" pointer to "where" head which is the start of the "where" Linked List */
        do{
          if (compare_token(where_points->entity, "entity") == 0){ /* if statement to check if the entity in the parameters and the entity in that particular node are the same */
            strncpy(where_points->response, response, MAX_RESPONSE); /* Copy the response to the node's response, it would overwrite any exisiting response in that node */
            return KB_FOUND;
          }
          where_points = where_points->next; /* If cannot find the entity, then go to the next node in the "where" Linked List */
        } while(where_points != NULL); /* do-while loop that searches through all not null nodes in the "where" Linked List */
      } else if (get_knowledge == 1){ /* If the intent is "where", but the intent-entity pair does not exists */
        question_node *new_node = (question_node *) malloc(sizeof(question_node));
        if (new_node == NULL){ /* memory allocation failure */
          return KB_NOMEM;
        } else { /* If no memory allocation failure, copy the intent, entity & response to the new_node and insert the new_node into the beginning of the "where" Linked List */
          strcpy(new_node->intent, intent);
          strcpy(new_node->entity, entity);
          strcpy(new_node->response, response);
          new_node->next = where_head;
          where_head = new_node;
          return KB_FOUND;
        }
      }
    }
  }
  return 0;
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
  size_t n = 0;
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
              //printf("----In file:----\nIntent: %s\nLine : %s=%s\n", intent, entity, response);
              //printf("%s\n", response);
              result = knowledge_put(intent, entity, response);
              if (result == KB_FOUND) {
                n++;
                //printf("line no: %zu\n", n);
                //printf("----Found:----\nIntent: %s\nLine %zu : %s=%s\n", intent, n, entity, response);
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
		  who_points = who_head;       
      who_head = who_head->next; 
      free(who_points);
		}
  }
  if (what_head != NULL){

    while (what_head != NULL) { 
		  what_points = what_head;       
      what_head = what_head->next; 
      free(what_points);
		}
  }

  if (where_head != NULL){

    while (where_head != NULL) { 
      where_points = where_head;       
      where_head = where_head->next; 
      free(where_points);
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
      who_head = who_head->next;
		}
  }

  if (what_head != NULL){
    fprintf(f, "[what]\n");
	  while (what_head != NULL) { 
      fprintf(f, "%s=%s\n", what_head->entity, what_head->response);
      what_head = what_head->next;
		}
  }

  if (where_head != NULL){
    fprintf(f, "[where]\n");
	  while (where_head != NULL) { 
      fprintf(f, "%s=%s\n", where_head->entity, where_head->response);
      where_head = where_head->next;
		}
  }

}
