struct Dish{
   char name[255];
   int price;
   int qty;
   Dish *next, *prev;
}*head, *curr, *tail;

struct Customer{
   char name[255];
   Dish order[100];
   int ctr;
   Customer *next;
};

