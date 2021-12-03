#include <stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Element_str{
    char text[50];
    struct Element_str* next;
}Element_str;

typedef struct Taste_Stack{
    Element_str* l_tastes;
}Taste_Stack;

typedef struct Cake{
    struct Element_str* order;
    struct Taste_Stack* s_tastes;
}Cake;

Taste_Stack *init_taste()
{
    //Create a new stack
    Taste_Stack *Taste_Stack = malloc(sizeof(*Taste_Stack));
    Taste_Stack->l_tastes = NULL;
    return Taste_Stack;
}
void add_taste(Taste_Stack *pile, char *text)
{
    Element_str *new = malloc(sizeof(*new));//Create a new element
    if (pile == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }
    strcpy(new->text, text);//Setup the new element with the content (text)
    new->next = pile->l_tastes;//Setup the new element

    pile->l_tastes = new;
}
char remove_taste(Taste_Stack *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    char nombreDepile[25];
    Element_str *elementDepile = pile->l_tastes;

    if (pile->l_tastes != NULL)
    {
//        nombreDepile = elementDepile->text;
        strcpy(nombreDepile,elementDepile->text);
        pile->l_tastes = elementDepile->next;
        free(elementDepile);
    }

    return nombreDepile;
}
void print_taste(Taste_Stack *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element_str *actuel = pile->l_tastes;

    while (actuel != NULL)
    {
        printf("%s\n", actuel->text);
        actuel = actuel->next;
    }

    printf("\n");
}
char* convert_initial_to_taste(char text){

    switch(text){
        case 'C': return "Chocolate";break;
        case 'V': return "Vanilla";break;
        case 'S': return "Strawberry";break;
        case 'O': return "Orange";break;
        case 'A': return "Apple";break;
        case 'B': return "Banana";break;
        case 'F': return "Fudge";break;
        default:
            printf("Error with the order, taste isn't available");break;
    }
}




void build_Cake(Cake* cake,Element_str* l_i_tastes){
    int i,nbr_of_taste_in_cake=5;
    char initial;
    Taste_Stack* list_taste = init_taste(); //Create a new empty stack of taste

    for(i=0;i<nbr_of_taste_in_cake;i++){ //Loop to add taste
        initial = *((l_i_tastes->text)+i); //Cut out the word of the order to retrieve the initial of the desired taste
        add_taste(list_taste,convert_initial_to_taste(initial)); //The function convert_initial_to_taste is used to convert the initial of the order to a real word like C to Chocolate
    }
    cake->order = l_i_tastes; //Assign the order to the cake
    cake->s_tastes = list_taste;//Assign the stack of taste to the cake

}
Cake* create_cake(Element_str* order){
    Cake* new_cake = malloc(sizeof(*new_cake)); //Create a new empty cake
    if (new_cake == NULL)
    {exit(EXIT_FAILURE);}

    build_Cake(new_cake,order); //Launch build cake
    return new_cake;
}




typedef struct Element_cake{
    struct Cake* cake;
    struct Element_cake* next;
}Element_cake;

typedef struct Tasting_Queue{
    Element_cake* q_tasting;
}Tasting_Queue;



Tasting_Queue* init_tasting_queue()
{
    Tasting_Queue* Tasting_Queue = malloc(sizeof(*Tasting_Queue));
    Tasting_Queue->q_tasting = NULL;
    return Tasting_Queue;
}
int remove_queue(Tasting_Queue *queue)
{
    if (queue == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDefile = 0;

    /* On vérifie s'il y a quelque chose à défiler */
    if (queue->q_tasting != NULL)
    {
        Element_cake *elementDefile = queue->q_tasting;

        nombreDefile = elementDefile->cake;
        queue->q_tasting = elementDefile->next;
        free(elementDefile);
    }

    return nombreDefile;
}
void enqueue(Tasting_Queue *queue, Cake *cake)
{
    //Create a new element, with initialisation
    Element_cake* new_el = malloc(sizeof(*new_el));
    new_el->cake = cake;
    new_el->next = NULL;

    if (queue->q_tasting == NULL) /* Queue is empty, the new element is now first */
    {
        queue->q_tasting = new_el;
    }
    else /* Queue isnt empty */
    {
        /* We go to the last position and we add the new element*/
        Element_cake* temp = queue->q_tasting;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_el;
    }
}
void print_queue(Tasting_Queue *queue){
    if (queue == NULL){
        exit(EXIT_FAILURE);
    }
    Element_cake *temp = queue->q_tasting;
    while(temp != NULL){
        printf("%s\n",temp->cake->order->text);
        temp = temp->next;
    }
}



void deliver(Cake* cake, Tasting_Queue* queue_cake){
    enqueue(queue_cake,cake);//Add to the tasting queue
}

void tasting(Tasting_Queue* q_tasting, int nb_parts){

}
int main() {

    Tasting_Queue* queue_cake = init_tasting_queue();//Launch the creation of the tasting queue


    //Create an order manually
    Element_str* new_order = malloc(sizeof(*new_order));
    if (new_order == NULL)
    {exit(EXIT_FAILURE);}
    strcpy(new_order->text,"CBVAB");
    new_order->next = NULL;

    Cake* new_cake = create_cake(new_order);//Launch the creation of the cake with the order
    deliver(new_cake,queue_cake);//Deliver the cake in the tasting queue

    //Create an order manually
    Element_str* new_order2 = malloc(sizeof(*new_order));
    if (new_order2 == NULL)
    {exit(EXIT_FAILURE);}
    strcpy(new_order2->text,"FOOVA");
    new_order2->next = NULL;

    Cake* new_cake2 = create_cake(new_order2);//Launch the creation of the cake with the order
    deliver(new_cake2,queue_cake);//Deliver the cake in the tasting queue

    print_queue(queue_cake); //Print the tasting queue to verify


    return 1;
}