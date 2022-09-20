#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	for (int i = 0; i < 255; i++) /*Loop to iterate on all account DB*/
	{
		if (!(strcmp(cardData->primaryAccountNumber , accountRefrence[i].primaryAccountNumber))) /* compare the two PAN*/
		{
			reference = i; /* Global variable used as a refrence*/
			return SERVER_OK;
		}
	}
		return ACCOUNT_NOT_FOUND;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (termData->transAmount > accountRefrence->balance) /*compare transaction amount with account balance*/
	{
		return LOW_BALANCE;
	}
	return SERVER_OK;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	int server_working = 0; /*flage used to check if transData is stored in Transaction DB*/
	int is_valid = isValidAccount(&transData->cardHolderData, accountsDB);
	if (is_valid == SERVER_OK) /*Check if the transData PAN is in the account DB*/
	{
		if (accountsDB[reference].state == BLOCKED) /*Check the state of the transData*/
		{
			return DECLINED_STOLEN_CARD;
		}
		int is_amount = isAmountAvailable(&transData->terminalData, &accountsDB[reference]);
		if (is_amount != SERVER_OK) /* Check if the account balance is sufficent for the transaction*/
		{
			return DECLINED_INSUFFECIENT_FUND;
		}
	}

	for (int i = 0; i < 255; i++)
	{
		/* Check if the transData is stored in the transaction DB by comparing PAN*/
		if (!(strcmp(transData->cardHolderData.primaryAccountNumber, transactionDB[i].cardHolderData.primaryAccountNumber)))
		{
			server_working = 1;
		}
	}
	if (is_valid != SERVER_OK)
	{
		return FRAUD_CARD;
	}
	else if (server_working == 0)
	{
		return INTERNAL_SERVER_ERROR;
	}	
	else
	{
		return APPROVED;
	}
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	for (int i = 0; i < 225; i++)
	{
		if (transactionSequenceNumber == transactionDB[i].transactionSequenceNumber)
		{
			transaction_data = i; /* Global variable used as a refrence*/
			return SERVER_OK;
		}
	}
	return TRANSACTION_NOT_FOUND;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	static int transactionSequenceNumber = 0;
	int check_transaction = getTransaction(transactionSequenceNumber, transactionDB); /* Check the last sequence number*/
	if (check_transaction == SERVER_OK)
	{
		transactionSequenceNumber++;
		transData->transactionSequenceNumber == transactionSequenceNumber;
		transactionDB[transaction_data + 1] = *transData; /* Store in the data base*/
		int state = recieveTransactionData(transData); /* finds and print the state of the transaction*/
		if (state == APPROVED)
		{
			printf("State: APPROVED\n");
		}
		else if (state == DECLINED_STOLEN_CARD)
		{
			printf("State: DECLINED_STOLEN_CARD\n");
		}
		else if (state == DECLINED_INSUFFECIENT_FUND)
		{
			printf("State: DECLINED_INSUFFECIENT_FUND\n");
		}
		else if (state == FRAUD_CARD)
		{
			printf("State: DECLINED_FRAUD_CARD\n");
		}
		else if (state == INTERNAL_SERVER_ERROR)
		{
			printf("Transaction NOT Saved!\n");
			return SAVING_FAILED;
		}
	}
	check_transaction = getTransaction(transData->transactionSequenceNumber, transactionDB); /* Check if transaction is stored*/
	if (check_transaction == SERVER_OK)
	{
		printf("Transaction Saved\n");
		return SERVER_OK;
	}
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/




