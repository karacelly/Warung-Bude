#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../controllers/controllers.h"

//alphabet only validation
bool alphabetOnly(char *name){
   int len = strlen(name);
   for(int i=0; i<len; i++){
      if((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9')){
         return false;
      }
   }
   return true;
}

//validation for unique name consists of alphabets only
bool isValidName(char *name){
   curr = head;
   while(curr && strcmp(curr->name, name) != 0){
      curr = curr->next;
   }
   if(curr) return false;

   if(!alphabetOnly(name)) return false;
   return true;
}

//prompt new dish to the menu
void menuAddDish(){
   char name[255];
   do{
      printf("Insert the name of the dish [Lowercase letters]: ");
      scanf("%[^\n]", name); getchar();
   }while(!isValidName(name));

   int price;
   do{
      printf("Insert the price of dish [1000..50000]: ");
      scanf("%d", &price); getchar();
   }while(price < 1000 || price > 50000);

   int qty;
   do{
      printf("Input the quantity of the dish [1..999]: ");
      scanf("%d", &qty); getchar();
   }while(qty < 1 || qty > 999);

   addDish(name, price, qty);
   printf("The dish has been added!\n");
   printf("Press enter to continue...");
   getchar();
   return;
}

//prompt dish that user wanted to remove
void menuRemoveDish(){
   if(!head){
      printf("Please input dish first!"); getchar();
      return;
   }
   viewDish();
   
   char name[255];
   do{
      printf("Insert dish's name to be deleted: ");
      scanf("%[^\n]", name); getchar();
   }while(!alphabetOnly(name) || searchDish(name) == -1);

   removeDish(name);
   puts("The dish has been removed!");
   printf("Press enter to continue..."); getchar();
}

//validation for cust's name
bool isValidCustName(char *name){
   for(int i=0; i<strlen(name); i++){
      if(name[i] == ' ' || (name[i] >= '0' && name[i] <= '9')){
         return false;
      }
   }
   return true;
}

//prompt new customer info to add
void menuAddCustomer(){
   char name[255];
   do{
      printf("Insert customer's name [Without space]: ");
      scanf("%[^\n]", name); getchar();
   }while(!isValidCustName(name));

   addCust(name);
   printf("Customer has been added!\n");
   printf("Press enter to continue..."); getchar();
}

//prompt customer name to be search
void menuSearchCust(){
   char name[255];
   do{
      printf("Insert the customer's name to be searched: ");
      scanf("%[^\n]", name); getchar();
   }while(!isValidCustName(name));

   if(searchCust(name) == -1){
      printf("%s is not present\n", name);
   }
   else{
      printf("%s is present\n", name);
   }
   printf("Press enter to continue..."); getchar();
   return;
}

//view customer's list
void menuViewWarteg(){
   puts("Customer's List");
   viewCust();
   printf("\nPress enter to continue..."); getchar();
   return;
}

//prompt cust's name to order menu
void menuOrder(){
   char custName[255];
   do{
      printf("Insert the customer's name: ");
      scanf("%[^\n]", custName); getchar();
      if(searchCust(custName) == -1) puts("No such customer!");
   }while(searchCust(custName) == -1);

   system("clear||cls");
   viewDish();
   int n;
   printf("Insert the amount of dish: ");
   scanf("%d", &n); getchar();

   char dishName[255];
   int qty, maxqty;
   for(int i=1; i<=n; i++){
      do{
         printf("[%d] Insert the dish's name and quantity: ", i);
         scanf("%[^x]x%d", dishName, &qty); getchar();
         int len = strlen(dishName);
         dishName[len-1] = '\0';
         maxqty = searchDish(dishName);
      }while(maxqty == -1 || qty < 0 || qty > maxqty);
      order(custName, dishName, qty);
   }
   printf("Order success!");
   printf("\nPress enter to continue..."); getchar();
}

//prompt cust index to proceed payment
void menuPayment(){
   int idx;
   printf("Insert the customer's index: ");
   scanf("%d", &idx); getchar();
   if(searchCust(table[idx]->name) == -1){
      puts("Wrong index!"); getchar();
      return;
   }

   if(strcmp(table[idx]->order[0].name, "anggepkosongplis") == 0){
      printf("This customer doesn't have any order!");
      getchar();
      return;
   }

   //display and compute total price
   printf("%s\n", table[idx]->name);
   int max = table[idx]->ctr;
   int total = 0;
   for(int i=0; i<max; i++){
      printf("[%d] %s x%d\n", i+1, table[idx]->order[i].name, table[idx]->order[i].qty);
      total += (table[idx]->order[i].price * table[idx]->order[i].qty);
   }
   printf("Total: Rp%d\n", total);
   popCust(table[idx]->name);
   printf("Press enter to continue..."); getchar();
   return;
}

//function to display splash screen
void splashScreen(){
   puts("Please expand your terminal to full screen!");
   printf("Press enter to continue..."); getchar();

   system("clear||cls");
   char line[255];
   FILE *fp = fopen("splash-screen.txt", "r");
   if(!fp) puts("Failed to open file :(");
   while(!feof(fp)){
      fgets(line, 100, fp);
      printf("%s", line);
   }
   fclose(fp);
}

//detecting OS to display
const char* detectOS() {
   #ifdef _WIN32
   return "Windows 32-bit";
   #elif _WIN64
   return "Windows 64-bit";
   #elif __APPLE__ || __MACH__
   return "Mac OSX";
   #elif __linux__
   return "Linux";
   #elif __FreeBSD__
   return "FreeBSD";
   #elif __unix || __unix__
   return "Unix";
   #else
   return "Other";
   #endif
}

int main(){
   int pil = -1;
   do{
      system("clear||cls");
      //display os
      printf("System: %s\n", detectOS());

      //display time
      time_t t;
      time(&t);
      printf("%s\n", ctime(&t));

      //display menu
      puts("1. Add Dish");
      puts("2. Remove Dish");
      puts("3. Add Customer");
      puts("4. Search Customer");
      puts("5. View Warteg");
      puts("6. Order");
      puts("7. Payment");
      puts("8. Exit Warteg");
      scanf("%d", &pil); getchar();
      if(pil == 1){
         system("clear||cls");
         menuAddDish();
      }
      else if(pil == 2){
         system("clear||cls");
         menuRemoveDish();
      }
      else if(pil == 3){
         system("clear||cls");
         menuAddCustomer();
      }
      else if(pil == 4){
         system("clear||cls");
         menuSearchCust();
      }
      else if(pil == 5){
         system("clear||cls");
         menuViewWarteg();
      }
      else if(pil == 6){
         system("clear||cls");
         menuOrder();
      }
      else if(pil == 7){
         system("clear||cls");
         menuPayment();
      }
      else if(pil == 8){
         system("clear||cls");
         splashScreen();
      }
   }while(pil != 8);

   return 0;
}
