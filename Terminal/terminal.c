#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../Card/card.h"
#include "terminal.h"

/*Get Transaction Date function*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) 
{
	printf("=======================================================\n");
	printf("Please enter transaction date in the form of \"dd/mm/yyyy\" \n");
	scanf_s(" %[^\n]s", termData->transactionDate, 11);
	if (termData->transactionDate == NULL)
	{
		return WRONG_DATE;
	}
	for (int i = 0; i < 10; i++) /*iterate over the array to check the input*/
	{
		if (i != 2 && i != 5) /*check all inputs except '/'*/
		{
			if (termData->transactionDate[i] < '0' || termData->transactionDate[i] > '9') /*check input type that is number*/
			{
				return WRONG_DATE;
			}
		}
		else if (i == 2 || i == 5) /*check the '/' only*/
		{
			if (termData->transactionDate[i] != '/') /*check to see if the slash is inputed correctly */
			{
				return WRONG_DATE;
			}
		}
	}
	return TERMINAL_OK;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Is Card Expired function*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) 
{
	/* check if they have the same year*/
	if ((cardData->cardExpirationDate[3] == termData->transactionDate[8]) && (cardData->cardExpirationDate[4] == termData->transactionDate[9]))
	{
		if (cardData->cardExpirationDate[0] < termData->transactionDate[3]) /* compare the tenth digit of the month*/
		{
			return EXPIRED_CARD;
		}
		/* compare the unit digit of the month*/
		else if (cardData->cardExpirationDate[1] < termData->transactionDate[4] && cardData->cardExpirationDate[0] == termData->transactionDate[3]) 
		{
			return EXPIRED_CARD;
		}
		else
		{
			return TERMINAL_OK;
		}
	}
	else /* if they have different year */
	{
		if (cardData->cardExpirationDate[3] < termData->transactionDate[8]) /* compare the tenth digit of the year */
		{
			return EXPIRED_CARD;
		}
		else if (cardData->cardExpirationDate[4] < termData->transactionDate[9]) /* compare the unit digit of the year*/
		{
			return EXPIRED_CARD;
		}
		else
		{
			return TERMINAL_OK;
		}
	}
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Get Transaction Amount function*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("=======================================================\n");
	printf("Please enter the transaction amount: \n");
	scanf_s(" %f", &termData->transAmount);
	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	return TERMINAL_OK;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Is Below Max Amount function*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Set Max Amount function*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Please enter the maximum allowed amount: \n");
	scanf_s(" %f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

