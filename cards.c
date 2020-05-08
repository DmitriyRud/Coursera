/*
   C for Everyone: Structured programming
   Week 2 Honors Assignment: 
   Use a struct to define a card as an enumerated member that is its suit value and a short that is its pips value.
   Write a function that randomly shuffles the deck.
   Then deal out 7 card hands and evaluate the probability that a hand has no pair, one pair,
   two pair, three of a kind, full house and 4 of a kind.
   This is a Monte Carlo method to get an approximation to these probabilities.
   Use at least 1 million randomly generated hands.

   Author: Dmitriy Rudakov
   Date: May 7, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum suits {heart, diamond, club, spade} suits;

typedef struct	card {
	suits	suit;
	short	pips;
}				card;

void swap_cards(card *card1, card *card2)
/* Function which swaps two cards in a deck */
{
	card tmp;

	tmp = *card1;
	*card1 = *card2;
	*card2 = tmp;
}

void shuffle_deck(card *cards, int rand_num)
/* Function which randomly shuffles the deck */
{
	int	rounds;

	srand(time(NULL));								/* Making randomizer more random :) */
	rounds =  10 + rand() % 50;						/* We will swap cards "round" times */
	for (int i = 0; i < rounds; ++i)
	{
		srand(rand_num / (i + 1));
		short card1 = rand() % 51;
		short card2 = rand() % 51;
		swap_cards(&cards[card1], &cards[card2]);   /* Swapping two random cards */
	}
}

void fill_deck(card *cards)
/* Function which fills the deck of 52 cards with data */
{
	int card_number = 0;

	for (int suit_number = 0; suit_number < 4; ++suit_number)
	{
		for (int pips_number = 2; pips_number <= 14; ++pips_number)
		{
			cards[card_number].pips = pips_number;
			cards[card_number++].suit = suit_number;
		}
	}
}

void check_combinations(card *card_hands, int combinations[10])
/* Function which check if combinations we're looking for are in the hands */
{
	int	one_suit = 1;
	int straight = 1;
	int four_of_a_kind = 0;
	int three = 0;
	int pairs = 0;
	int ace = 0;
	int i, j;
	int kind[15] = {0};

	/* Sorting the hand in accending order to calculate the straights correctly */
	for (j = 0; j < 5; ++j)
		for (i = 0; i < 4; ++i)
			if (card_hands[i].pips > card_hands[i + 1].pips)
				swap_cards(&card_hands[i], &card_hands[i + 1]);

	for (i = 0; i < 4; ++i)
	{
		/* Checking if cards in a hand have one suit */
		if (card_hands[i].suit != card_hands[i + 1].suit)
		{
			one_suit = 0;
			break;
		}
	}

	for (i = 0; i < 5; ++i)
	/* Checking how many aces are in the hand */
		if (card_hands[i].pips == 14)
			++ace;

	/* Checking if cards forming a straight */
	if (ace == 0)
		for (i = 0; i < 4; ++i)
		{
			if (card_hands[i + 1].pips != card_hands[i].pips + 1)
				straight = 0;
		}
	else if (ace == 1)
		for (i = 0; i < 3; ++i)
		{
			if (card_hands[i + 1].pips != card_hands[i].pips + 1)
				straight = 0;
		}
	else if (ace == 2)
		for (i = 1; i < 3; ++i)
		{
			if (card_hands[i + 1].pips != card_hands[i].pips + 1)
				straight = 0;
		}
	else
		straight = 0;

	for (i = 0; i < 5; ++i)
	{
		/* Checking how many cards in a hand have the same value */
		++kind[card_hands[i].pips];
	}
	for (i = 0; i < 15; ++i)
	{
		/* Checking how many... */
		if (kind[i] > 3)
			four_of_a_kind = 1;                    /* ...fours values */
		if (kind[i] > 2)
			three = 1;							   /* ...three values */
		else if (kind[i] > 1)
			++pairs;							   /* ...pairs */
	}
	if (one_suit == 1 && card_hands[0].pips == 10 && straight == 1)
		++combinations[0];    /* Means Royal Flush */
	else if (one_suit == 1 && straight == 1)
		++combinations[1];    /* Means Straight Flush */
	else if (four_of_a_kind == 1)
		++combinations[2];    /* Means Four of a kind */
	else if (three > 0  && pairs > 0)
		++combinations[3]; 	  /* Means Full House */
	else if (one_suit == 1 && straight == 0)
		++combinations[4]; 	  /* Means Flush */
	else if (straight == 1 && one_suit == 0)
		++combinations[5]; 	  /* Means Straight */
	else if (three == 1)
		++combinations[6]; 	  /* Means Three of a kind */
	else if (pairs > 1)
		++combinations[7];    /* Means two pairs */
	else if (pairs > 0)
		++combinations[8];    /* Means one pair */
	else if (ace == 1)
		++combinations[9];    /* Ace high or less */
}

int main(void)
{
	card	cards[52];
	card	card_hands[7][5];
	int		combinations[10] = {0};
	int		total;
	int		card_count;
	
	printf("Generating the million hands, please wait...\n\n");
	fill_deck(cards);

	/* We need to check 1 million shuffles */
	for (int i = 0; i < 1000000; ++i)
	{
		shuffle_deck(cards, i);
		card_count = 0;
		/* and in each shuffle we need to analyze 7 hands */
		for (int hand = 0; hand < 7; ++hand)
		{
			for (int hands = 0; hands < 5; ++hands)
				card_hands[hand][hands] = cards[card_count++];
			check_combinations(card_hands[hand], combinations);
		}
	}

	/* Now let's calculate the total and probabilities and print the results */
	for (int i = 0; i < 10; ++i)
		total += combinations[i];
	printf("Hand              Combinations           Probabilities\n");
	printf("--------------------------------------------------------------\n");
	printf("Royal flush       %-10d             %f\n", combinations[0], (double)combinations[0] / total);
	printf("Straight flush    %-10d             %f\n", combinations[1], (double)combinations[1] / total);
	printf("Four of a kind    %-10d             %f\n", combinations[2], (double)combinations[2] / total);
	printf("Full house        %-10d             %f\n", combinations[3], (double)combinations[3] / total);
	printf("Flush             %-10d             %f\n", combinations[4], (double)combinations[4] / total);
	printf("Straight          %-10d             %f\n", combinations[5], (double)combinations[5] / total);
	printf("Three of a kind   %-10d             %f\n", combinations[6], (double)combinations[6] / total);
	printf("Two pair          %-10d             %f\n", combinations[7], (double)combinations[7] / total);
	printf("Pair              %-10d             %f\n", combinations[8], (double)combinations[8] / total);
	printf("Ace high or less  %-10d             %f\n", combinations[9], (double)combinations[9] / total);
	printf("Total             %-10d\n", total);
	return (0);
}
