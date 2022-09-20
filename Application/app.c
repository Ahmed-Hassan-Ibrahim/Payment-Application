#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"


void appStart(void)
{
	ST_cardData_t card_test = { NULL, NULL, NULL }; // initilaize card data
	ST_terminalData_t term_test = { 0.0, 0.0, NULL }; // initilaize terminal data
	int flag = NULL; 
	setMaxAmount(&term_test); // setting transaction maximum amount
		
	flag = getCardHolderName(&card_test); // enter card holder name
	if (flag == CARD_OK) // if data entered corectly procssed
	{
		flag = getCardExpiryDate(&card_test); // enter card expirey date 
	}
	if (flag == CARD_OK) // if data entered corectly procssed
	{
		flag = getCardPAN(&card_test); // enter card PAN
	}
	if (flag == CARD_OK) // if data entered corectly procssed
	{
		flag = getTransactionDate(&term_test); // enter transaction date
	}
	if (flag == TERMINAL_OK) // if data entered corectly procssed
	{
		flag = isCardExpired(&card_test, &term_test); // check if card is expired
	}
	if (flag == EXPIRED_CARD)
	{
		printf("Declined: Expired Card!\n");
		return;
	}
	flag = getTransactionAmount(&term_test); // enter transaction amount
	if (flag == TERMINAL_OK)
	{
		flag = isBelowMaxAmount(&term_test); // check if transation is below maximum amount
	}
	if (flag == EXCEED_MAX_AMOUNT)
	{
		printf("Declined: Amount Exceeding Limit!");
		return;
	}
	ST_transaction_t trans_test = { card_test, term_test, RUNNING, NULL }; // initilaize transaction data
	flag = isValidAccount(&trans_test.cardHolderData, accountsDB); // check if it is valid account
	if (flag == FRAUD_CARD)
	{
		printf("Declined: Invalid Card!\n");
		return;
	}
	flag = isAmountAvailable(&trans_test.terminalData, &accountsDB[reference]); // check if amount is available
	if (flag == LOW_BALANCE)
	{
		printf("Declined: Insuffecient Fund!\n");
		return;
	}
	accountsDB[reference].balance -= term_test.transAmount; // update account balance
	saveTransaction(&trans_test); // save transaction
	return;
}



