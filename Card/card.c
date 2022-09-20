#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "card.h"

/*Get Card Holder Name function*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("=======================================================\n");
	printf("Please enter cardholder's name: \n");
	scanf_s(" %[^\n]s", cardData->cardHolderName, 25); /* using safe scan already will reject if name is more than 24 char*/
	fflush(stdin);
	if (cardData->cardHolderName == NULL || strlen(cardData->cardHolderName) < 20) /* check condition if name is NULL or less than 20 char*/
	{
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Get Card Expirey Date function*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) 
{
	printf("=======================================================\n");
	printf("Enter card expirey date in the form of \"MM/YY\" : \n");
	scanf_s(" %[^\n]s", cardData->cardExpirationDate, 6); /* using safe scan already will reject if input is more than 5 char*/
	if (cardData->cardExpirationDate == NULL)
	{
		return WRONG_EXP_DATE;
	}
	for (int i = 0; i < 5; i++) /*iterate over the array to check the input*/
	{
		if (i != 2) /*check all inputs except '/'*/
		{
			if (cardData->cardExpirationDate[i] < '0' || cardData->cardExpirationDate[i] > '9') /*check input type that is number*/
		{
			return WRONG_EXP_DATE;
		}
		}
		else if (i == 2) /*check the '/' only*/
		{
			if (cardData->cardExpirationDate[i] != '/') /*check to see if the slash is inputed correctly */
			{
				return WRONG_EXP_DATE;
			}
		}
	}
	return CARD_OK;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Get Card PAN function*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData) 
{
	printf("=======================================================\n");
	printf("Enter card primary account number (PAN): \n");
	scanf_s(" %[^\n]s", cardData->primaryAccountNumber, 20); /* using safe scan already will reject if input is more than 19 char*/
	if (cardData->primaryAccountNumber == NULL || strlen(cardData->primaryAccountNumber) < 16) /* check condition if PAN is NULL or less than 16 char*/
	{
		return WRONG_PAN;
	}
	return CARD_OK;
}

