#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARDS 52
#define HAND_SIZE 7
#define NUM_RANKS 13
#define NUM_SIMULATIONS 1000000

// declaring variables for keeping count of poker hands
long long int num_no_pair , num_one_pair , num_two_pair , num_three_of_a_kind , num_four_of_a_kind , num_full_house ;

// defining the member suit of the card
typedef enum suits {spade,heart,club,diamond} suits;

// defining the Cards
typedef struct Cards {
	suits suit;
	short pips;
} Cards;

// a function to swap the cards
void swap(Cards *a , Cards *b) ;

// a function to initiate the deck
void init_deck(Cards deck[]);

// a function to shuffle the deck
void shuffle_deck(Cards deck[]);

// a function to deal out 7 cards and count the number of poker hands
void deal_and_check(Cards shuffled_deck[]);

int main(void){
	Cards deck[NUM_CARDS]; // creating a deck for the cards
	init_deck(deck); // initializing the deck with standard poker cards 
	for ( int i = 0 ; i < NUM_SIMULATIONS ; i++){
		shuffle_deck(deck);
	       deal_and_check(deck);	
	}
	double p_no_pair , p_one_pair , p_two_pair , p_three_of_a_kind , p_four_of_a_kind , p_full_house ;
	p_no_pair = (double)num_no_pair/NUM_SIMULATIONS;
	p_one_pair = (double)num_one_pair/NUM_SIMULATIONS;
	p_two_pair = (double)num_two_pair/NUM_SIMULATIONS;
	p_three_of_a_kind = (double)num_three_of_a_kind/NUM_SIMULATIONS;
	p_four_of_a_kind = (double)num_four_of_a_kind/NUM_SIMULATIONS;
	p_full_house = (double)num_full_house/NUM_SIMULATIONS;

	printf("Number of silumations made : %d\n",NUM_SIMULATIONS);
	printf("The probability of no pair is : %lf\n",p_no_pair);
	printf("The probability of one pair is : %lf\n",p_one_pair);
	printf("The probability of two pair is : %lf\n",p_two_pair);
	printf("The probability of three of a kind is : %lf\n",p_three_of_a_kind);
	printf("The probability of four of a kind is : %lf\n",p_four_of_a_kind);
	printf("The probability of fullhouse is : %lf\n",p_full_house);


}

// defining the swap function
void swap (Cards *a , Cards *b) {
	Cards temp = *a;
	*a = *b;
	*b = temp;
}

// defining the init function 
void init_deck(Cards deck[]){
	suits s;
	int i , index = 0 ;
	for ( s = spade ; s <= diamond ; s++){
		for ( i = 1 ; i<= NUM_RANKS ; i++ ){
			deck[index].suit = s ;
			deck[index].pips = i ;
			index++;
		}
	}
}

// defining the shuffle function
void shuffle_deck(Cards deck[]){
	srand(time(NULL));
	int i , j ;
	for ( i = NUM_CARDS - 1 ; i > 0 ; i-- ){
		j = rand()%(i+1);
		swap(&deck[i],&deck[j]);

	}


}

// defining the function for dealing out seven cards and counting the number of poker hands
void deal_and_check(Cards shuffled_deck[]){
	int pips_count[NUM_RANKS] = {0} , i , counter = 0 , Pair = 0 , threeOfaKind = 0 ;
	for(i = 0 ; i < HAND_SIZE ; i++){
		pips_count[shuffled_deck[i].pips]++;
	}
	for(i = 0 ; i < NUM_RANKS ; i++){
		if (pips_count[i]==4){
		       	num_four_of_a_kind++;  // checking for four of a kind
			return;
		}
		if (pips_count[i]==3) threeOfaKind++;        // checking for three of a kind
		if (pips_count[i]==2) Pair++;             // checking for the pairs
		if (pips_count[i]==1) counter++;             // checking for noPair condition
	}
	if (threeOfaKind && Pair) num_full_house++;
	else if (threeOfaKind) num_three_of_a_kind++;
	else if (Pair > 1 ) num_two_pair++;
	else if (Pair == 1) num_one_pair++;
        else if (counter == 7 ) num_no_pair++;	
}




