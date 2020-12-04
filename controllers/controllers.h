#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../models/models.h"

Dish *createNewDish(char *name, int price, int qty){
   Dish *temp = (Dish*) malloc(sizeof(Dish));
   strcpy(temp->name, name);
   temp->price = price;
   temp->qty = qty;
   temp->next = temp->prev = NULL;

   return temp;
}

void addDish(char *name, int price, int qty){
   Dish *newDish = createNewDish(name, price, qty);

   if(!head){
      head = tail = newDish;
   }
   else{
      tail->next = newDish;
      newDish->prev = tail;
      tail = newDish;
   }
   tail->next = NULL;
}

void popHead(){
   if(head && head == tail){
      head = tail = NULL;
      free(head);
   }
   else{
      Dish *newHead = head->next;
      head->next = head->prev = NULL;
      free(head);
      head = newHead;
   }
}

void popTail(){
   if(head && head == tail){
      head = tail = NULL;
      free(head);
   }
   else{
      Dish *newTail = tail->prev;
      tail->prev = tail->next = NULL;
      free(tail);
      tail = newTail;
   }
}

void removeDish(char *name){
   if(!head) return;
   else if(strcmp(head->name, name) == 0) popHead();
   else if(strcmp(tail->name, name) == 0) popTail();
   else{
      curr = head;
      while(curr && strcmp(curr->name, name) != 0){
         curr = curr->next;
      }
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      curr->next = curr->prev = NULL;
      free(curr);
   }
   return;
}

int searchDish(char *name){
   curr = head;
   while(curr && strcmp(curr->name, name) != 0){
      curr = curr->next;
   }
   if(!curr) return -1;
   else return curr->qty;
}

void viewDish(){
   printf("\t\tBude's Menu\n");
   printf("===================================================\n");
   printf("| %-3s | %-15s | %-10s | %-10s |\n", "No.", "Name", "Quantity", "Price");
   curr = head;
   int ctr = 1;
   while(curr){
      printf("| %-3d | %-15s | %-10d | Rp%-8d |\n", ctr, curr->name, curr->qty, curr->price);
      curr = curr->next;
      ctr++;
   }
   printf("===================================================\n");
}

const int size = 30;
struct Customer *table[size] = {NULL};

unsigned long hash(char *str) {
   unsigned long hash = 5381;
   int c;
   while ((c = *str++))
      hash = ((hash << 5) + hash) + c;
   
   return hash%size;
}

struct Customer *createNewCust(char *name){
   struct Customer *temp = (Customer *) malloc(sizeof(Customer));
   strcpy(temp->name, name);
   strcpy(temp->order[0].name, "anggepkosongplis");
   temp->ctr = 0;
   temp->next = NULL;

   return temp;
}

void addCust(char *name){
   Customer *temp = createNewCust(name);
   int index = hash(temp->name);

   if(!table[index]){
      table[index] = temp;
   }
   else{
      Customer *current = table[index];
      while(current->next){
         current = current->next;
      }
      current->next = temp;
   }
}

int searchCust(char *name){
   int index = hash(name);
   if(table[index]){
      Customer *current = table[index]->next;
      //mis 2 4 5 6 
      while(current && strcmp(current->name, name) != 0){
         current = current->next;
      }
      if(!current) return index;
      else return -1;
   }
   else{
      return -1;
   }  
}

void viewCust(){
   for(int i=0; i<26; i++){
      if(table[i]){
         printf("%d. ", i);
         Customer *curr = table[i];
         while(curr){
            if(!curr->next){
               printf("%s\n", curr->name);
            }
            else{
               printf("%s --> ", curr->name);
            }
            curr = curr->next;
         }
      }
   }
}

void popCust(char *name){
   int idx = hash(name);

   if(table[idx] != NULL){
      Customer *current = table[idx];
      if(strcmp(table[idx]->name, name) == 0){
         Customer *temp = current;
         current = current->next;
         free(temp);
         table[idx] = current;
      }
      else{
         // misal kesya kenzie kezia
         //       curr
         while(current->next && strcmp(current->next->name, name) != 0){
            current = current->next;
         }
         if(current->next){
            Customer *temp = current->next;
            current->next = current->next->next;
            free(temp);
         }
      }
   }
   return;
}

void order(char *custName, char *dishName, int qty){
   int index = hash(custName);
   
   curr = head;
   while(curr){
      if(strcmp(curr->name, dishName) == 0){
         break;
      }
      curr = curr->next;
   }

   Dish newOrder = {.price = curr->price, .qty = qty};
   strcpy(newOrder.name, dishName);
   Customer *temp = table[index];
   temp->order[temp->ctr] = newOrder;
   temp->ctr++;

   curr->qty -= qty;
   if(curr->qty <= 0){
      removeDish(curr->name);
   }

   return;
}