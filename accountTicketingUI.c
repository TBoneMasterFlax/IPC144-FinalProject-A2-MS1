/*
    ==================================================
    Assignment #2 Milestone #1:
    ==================================================
    Name   : Tuan Nguyen
    ID     : 109062166
    Email  : tnguyen140@myseneca.ca
    Section: NFF
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "accountTicketingUI.h"
#include "account.h"
#include "commonHelpers.h"
#include <string.h>
#include <stdlib.h>

void displayAccountSummaryHeader(void)
{
    printf("Acct# Acct.Type Birth\n");
    printf("----- --------- -----\n");
}

void displayAccountDetailHeader(void)
{
    printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* account)
{
    char accountType[] = "CUSTOMER";
    if (account->account_type == 'A')
    {
        strcpy(accountType, "AGENT");
    }
    printf("%05d %-9s %5d\n", account->account_number, accountType, account->demographic.birth_year);
}

void displayAccountDetailRecord(const struct Account* account)
{
    char accountType[] = "CUSTOMER";
    if (account->account_type == 'A')
    {
        strcpy(accountType, "AGENT");
    }
    char hiddenPassword[9];
    strcpy(hiddenPassword, account->user_login.password);
    int passwordLength = strlen(hiddenPassword);
    int i;
    for (i = 0; i < passwordLength; i++)
    {
        if (i % 2 != 0)
        {
            hiddenPassword[i] = '*';
        }
    }
    printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", account->account_number, accountType, account->demographic.birth_year, account->demographic.income, account->demographic.country, account->user_login.display_name, account->user_login.login_name, hiddenPassword);
}

void applicationStartup(struct AccountTicketingData* accountsAndTickets)
{
    int userIndex = -1;
    int flag = 1;
    do
    {
        userIndex = menuLogin(accountsAndTickets);
        if (userIndex < 0)
        {
            flag = 0;
        }
    } while (flag);
}

int menuLogin(struct AccountTicketingData* accountsAndTickets)
{
    int userIndex;
    int selection, flag = 1;
    int accountNumber, i = 0, firstEmptyIndex = -1;
    char exit;
    do
    {
        userIndex = -1;
        printf("==============================================\n");
        printf("Account Ticketing System - Login\n");
        printf("==============================================\n");
        printf("1) Login to the system\n");
        printf("0) Exit application\n");
        printf("----------------------------------------------\n\n");
        printf("Selection: ");
        for (i = 0; i < accountsAndTickets->ACCOUNT_MAX_SIZE; i++)
        {
            if (accountsAndTickets->accounts[i].account_number <= 0)
            {
                firstEmptyIndex = i;
                break;
            }
            else
            {
                firstEmptyIndex = -1;
            }
        }
        selection = getIntFromRange(0, 1);
        switch (selection)
        {
        case 0:
            printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
            exit = getCharOption("yYnN");
            putchar('\n');
            if (exit == 'y' || exit == 'Y')
            {
                printf("==============================================\n");
                printf("Account Ticketing System - Terminated\n");
                printf("==============================================\n");
            }
            else
            {
                userIndex = menuLogin(accountsAndTickets);
            }
            flag = 0;
            break;
        case 1:
            printf("\nEnter your account#: ");
            scanf("%d", &accountNumber);
            clearStandardInputBuffer();
            for (i = 0; i < firstEmptyIndex; i++)
            {
                if (accountNumber == accountsAndTickets->accounts[i].account_number)
                {
                    userIndex = i;
                }
            }
            if (userIndex < 0)
            {
                printf("\nERROR:  Access Denied.\n\n");
                pauseExecution();
            }
            else
            {
                if (accountsAndTickets->accounts[userIndex].account_type == 'A')
                {
                    putchar('\n');
                    menuAgent(accountsAndTickets, &accountsAndTickets->accounts[userIndex]);
                    flag = 0;
                }
                else
                {
                    putchar('\n');
                    menuCustomer(accountsAndTickets, &accountsAndTickets->accounts[userIndex]);
                    flag = 0;
                }
            }
            break;
        default:
            break;
        }
    } while (flag);
    return userIndex;
}

void menuAgent(struct AccountTicketingData* accountsAndTickets, const struct Account* userAccount)
{
    const int userAccountNumber = userAccount->account_number;
    int selection, flag = 1;
    int accountNumber, i = 0;
    int userIndex = -1, firstEmptyIndex = -1, arrayIndex = -1;
    int highestNumber = 0;
    char removeAccount;
    do
    {
        for (i = 0; i < accountsAndTickets->ACCOUNT_MAX_SIZE; i++)
        {
            if (accountsAndTickets->accounts[i].account_number <= 0)
            {
                firstEmptyIndex = i;
                break;
            }
            else
            {
                firstEmptyIndex = -1;
            }
        }
        for (i = 0; i < firstEmptyIndex; i++)
        {
            if (accountsAndTickets->accounts[i].account_number == userAccountNumber)
            {
                userIndex = i;
            }
        }
        printf("AGENT: %s (%d)\n", accountsAndTickets->accounts[userIndex].user_login.display_name, accountsAndTickets->accounts[userIndex].account_number);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf("1) Add a new account\n");
        printf("2) Modify an existing account\n");
        printf("3) Remove an account\n");
        printf("4) List accounts: summary view\n");
        printf("5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf("6) List new tickets\n");
        printf("7) List active tickets\n");
        printf("8) Manage a ticket\n");
        printf("9) Archive closed tickets\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 9);
        switch (selection)
        {
        case 0:
            printf("\n### LOGGED OUT ###\n\n");
            flag = 0;
            break;
        case 1:
            if (firstEmptyIndex < 0)
            {
                printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
                pauseExecution();
            }
            else
            {
                for (i = 0; i < accountsAndTickets->ACCOUNT_MAX_SIZE; i++)
                {
                    if (highestNumber < accountsAndTickets->accounts[i].account_number)
                    {
                        highestNumber = accountsAndTickets->accounts[i].account_number + 1;
                    }
                }
                getAccount(&accountsAndTickets->accounts[firstEmptyIndex], highestNumber);
                getUserLogin(&accountsAndTickets->accounts[firstEmptyIndex].user_login);
                getDemographic(&accountsAndTickets->accounts[firstEmptyIndex].demographic);
                printf("*** New account added! ***\n\n");
                pauseExecution();
            }
            break;
        case 2:
            arrayIndex = -1;
            printf("\nEnter your account#: ");
            scanf("%d", &accountNumber);
            clearStandardInputBuffer();
            for (i = 0; i < firstEmptyIndex; i++)
            {
                if (accountNumber == accountsAndTickets->accounts[i].account_number)
                {
                    arrayIndex = i;
                }
            }
            if (arrayIndex < 0)
            {
                printf("\nERROR:  Access Denied.\n\n");
                pauseExecution();
            }
            else
            {
                updateAccount(&accountsAndTickets->accounts[arrayIndex]);
            }
            putchar('\n');
            break;
        case 3:
            arrayIndex = -1;
            printf("\nEnter your account#: ");
            scanf("%d", &accountNumber);
            clearStandardInputBuffer();
            for (i = 0; i < firstEmptyIndex; i++)
            {
                if (accountNumber == accountsAndTickets->accounts[i].account_number)
                {
                    arrayIndex = i;
                }
            }
            if (arrayIndex < 0)
            {
                printf("\nERROR:  Access Denied.\n\n");
                pauseExecution();
            }
            else
            {
                if (accountsAndTickets->accounts[arrayIndex].account_number == userAccount->account_number)
                {
                    printf("\nERROR: You can't remove your own account!\n\n");
                    pauseExecution();
                }
                else
                {
                    displayAccountDetailHeader();
                    displayAccountDetailRecord(&accountsAndTickets->accounts[arrayIndex]);
                    printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
                    removeAccount = getCharOption("YN");
                    if (removeAccount == 'Y')
                    {
                        struct Account tmp[50];
                        int validAccounts = 0;
                        for (i = 0; i < 50; i++)
                        {
                            tmp[i] = accountsAndTickets->accounts[i];
                        }
                        tmp[arrayIndex].account_number = 0;
                        for (i = 0; i < 50; i++)
                        {
                            if (tmp[i].account_number > 0)
                            {
                                accountsAndTickets->accounts[validAccounts] = tmp[i];
                                validAccounts++;
                            }
                        }
                        for (i = validAccounts; i < accountsAndTickets->ACCOUNT_MAX_SIZE; i++)
                        {
                            accountsAndTickets->accounts[i].account_number = 0;
                        }
                        printf("\n*** Account Removed! ***\n\n");
                        pauseExecution();
                    }
                    else
                    {
                        printf("\n*** No changes made! ***\n\n");
                        pauseExecution();
                    }
                    putchar('\n');
                }
            }
            break;
        case 4:
            putchar('\n');
            displayAllAccountSummaryRecords(accountsAndTickets->accounts, accountsAndTickets->ACCOUNT_MAX_SIZE);
            putchar('\n');
            pauseExecution();
            break;
        case 5:
            putchar('\n');
            displayAllAccountDetailRecords(accountsAndTickets->accounts, accountsAndTickets->ACCOUNT_MAX_SIZE);
            putchar('\n');
            pauseExecution();
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            printf("\nFeature #%d currently unavailable!\n\n", selection);
            pauseExecution();
            break;
        default:
            break;
        }
    } while (flag);
}

void menuCustomer(struct AccountTicketingData* accountsAndTickets, const struct Account* userAccount)
{
    const int userAccountNumber = userAccount->account_number;
    int selection, flag = 1;
    int i = 0;
    int userIndex = -1, firstEmptyIndex = -1;
    do
    {
        for (i = 0; i < accountsAndTickets->ACCOUNT_MAX_SIZE; i++)
        {
            if (accountsAndTickets->accounts[i].account_number <= 0)
            {
                firstEmptyIndex = i;
                break;
            }
            else
            {
                firstEmptyIndex = -1;
            }
        }
        for (i = 0; i < firstEmptyIndex; i++)
        {
            if (accountsAndTickets->accounts[i].account_number == userAccountNumber)
            {
                userIndex = i;
            }
        }
        printf("CUSTOMER: %s (%d)\n", accountsAndTickets->accounts[userIndex].user_login.display_name, accountsAndTickets->accounts[userIndex].account_number);
        printf("==============================================\n");
        printf("Customer Main Menu\n");
        printf("==============================================\n");
        printf("1) View your account detail\n");
        printf("2) List my tickets\n");
        printf("3) Create a new ticket\n");
        printf("4) Manage a ticket\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 9);
        switch (selection)
        {
        case 0:
            printf("\n### LOGGED OUT ###\n\n");
            flag = 0;
            break;
        case 1:
            putchar('\n');
            displayAccountDetailHeader();
            displayAccountDetailRecord(&accountsAndTickets->accounts[userIndex]);
            putchar('\n');
            pauseExecution();
            break;
        case 2:
        case 3:
        case 4:
            printf("\nFeature #%d currently unavailable!\n\n", selection);
            pauseExecution();
            break;
        default:
            break;
        }
    } while (flag);
}

int findAccountIndexByAcctNum(int accountNumber, const struct Account accounts[], int size, int prompt)
{
    return 0;
}

void displayAllAccountSummaryRecords(const struct Account accounts[], int size)
{
    int i = 0, firstEmptyIndex = -1;
    for (i = 0; i < size; i++)
    {
        if (accounts[i].account_number <= 0)
        {
            firstEmptyIndex = i;
            break;
        }
        else
        {
            firstEmptyIndex = size;
        }
    }
    displayAccountSummaryHeader();
    for (i = 0; i < firstEmptyIndex; i++)
    {
        displayAccountSummaryRecord(&accounts[i]);
    }
}

void displayAllAccountDetailRecords(const struct Account accounts[], int size)
{
    int i = 0, firstEmptyIndex = -1;
    for (i = 0; i < size; i++)
    {
        if (accounts[i].account_number <= 0)
        {
            firstEmptyIndex = i;
            break;
        }
        else
        {
            firstEmptyIndex = size;
        }
    }
    displayAccountDetailHeader();
    for (i = 0; i < firstEmptyIndex; i++)
    {
        displayAccountDetailRecord(&accounts[i]);
    }
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    putchar('\n');
}