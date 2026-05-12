/**
 * @file app.c
 * @author MOLeCULE Soft (felix@moleculesoft.net)
 * @brief A simple banking application that allows users to create accounts,
 *        deposit and withdraw money, and check their balance using linked lists.
 * @version 1.0
 * @date 2024-06-01
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULT_BANK_ACCOUNT_NUMBER 123
typedef struct Account
{
    char name[50];
    int account_number;
    int balance;
    int account_limit;
    int overdraft_limit;
    struct Account *next;
} Account;

typedef struct txn
{
    int from_account;
    int to_account;
    int amount;
    struct txn *next;
} Transaction;

/** Head pointer for the transaction linked list. */
Transaction *txn_head = NULL; // or struct txn *txn_head = NULL;

/** Head pointer for the account linked list. */
Account *head = NULL;

/**
 * @brief Creates the system-owned bank account used as the source/sink of funds.
 *
 * This account is inserted at the head of the account linked list and initialized
 * with a large starting balance so regular customer operations can be simulated.
 */
void create_default_account()
{
    Account *default_account = (Account *)malloc(sizeof(Account));
    if (default_account == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(default_account->name, "Bank");
    default_account->account_number = DEFAULT_BANK_ACCOUNT_NUMBER;
    default_account->balance = 1000000.0;
    default_account->account_limit = 0;
    default_account->overdraft_limit = 0;
    /* Push-front insertion for O(1) linked-list insert. */
    default_account->next = head;
    head = default_account;
}

/**
 * @brief Records a money movement in the transaction history.
 * @param from_account Source account number.
 * @param to_account Destination account number.
 * @param amount Amount transferred.
 */
void record_transaction(int from_account, int to_account, float amount)
{
    Transaction *new_txn = (Transaction *)malloc(sizeof(Transaction));
    if (new_txn == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    new_txn->from_account = from_account;
    new_txn->to_account = to_account;
    new_txn->amount = amount;
    /* Newest transaction is stored first for quick insertion and recent-first listing. */
    new_txn->next = txn_head;
    txn_head = new_txn;
}

/**
 * @brief Finds an account by account number.
 * @param account_number Account number to search for.
 * @return Pointer to matching account, or NULL if not found.
 */
Account *find_account(int account_number)
{
    Account *current = head;
    while (current != NULL)
    {
        if (current->account_number == account_number)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Creates a new customer account and adds it to the account list.
 */
void create_account()
{
    Account *new_account = (Account *)malloc(sizeof(Account));
    if (new_account == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &new_account->account_number);

    Account *check = find_account(new_account->account_number);
    if (check != NULL)
    {
        printf("Account number %d already exists!\n", new_account->account_number);
        free(new_account);
        return;
    }

    printf("Enter account holder's name: ");
    scanf("%s", new_account->name);
    printf("Enter account limit: ");
    scanf("%d", &new_account->account_limit);
    printf("Enter overdraft limit: ");
    scanf("%d", &new_account->overdraft_limit);

    new_account->balance = 0.0;
    /* Insert new account at head to avoid traversing the entire list. */
    new_account->next = head;
    head = new_account;

    printf("Account created successfully!\n");
}

/**
 * @brief Deposits funds into a customer account from the bank account.
 */
void deposit()
{
    int account_number;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &account_number);
    printf("Enter amount to deposit: ");
    scanf("%d", &amount);
    Account *cus_account = find_account(account_number);

    if (cus_account == NULL)
    {
        printf("Account number %d not found!\n", account_number);

        return;
    }
    /* The bank account acts as central liquidity for deposits/withdrawals. */
    Account *default_account = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    if (cus_account->balance + amount > cus_account->account_limit)
    {
        printf("Deposit failed! Account limit exceeded.\n");
        return;
    }
    else if (amount > default_account->balance)
    {
        printf("Bank does not have enough funds to complete this deposit!\n");
        return;
    }

    cus_account->balance += amount;
    default_account->balance -= amount;
    record_transaction(DEFAULT_BANK_ACCOUNT_NUMBER, account_number, amount);
    printf("Deposit successful! New balance: %d\n", cus_account->balance);
}

/**
 * @brief Withdraws funds from a customer account back to the bank account.
 */
void withdraw()
{
    int account_number;
    float amount;
    bool overdraft_used = false;

    printf("Ent-er account number: ");
    scanf("%d", &account_number);
    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);

    Account *cus_account = find_account(account_number);
    if (cus_account == NULL)
    {
        printf("Account number %d not found!\n", account_number);
        return;
    }
    else if (cus_account->balance < amount)
    {
        if (cus_account->overdraft_limit == 0)
        {
            printf("Withdrawal failed! Balance is insufficient.\n");
            return;
        }
        else if (cus_account->balance + cus_account->overdraft_limit < amount)
        {
            printf("Withdrawal failed! Overdraft limit exceeded.\n");
            return;
        }
        overdraft_used = true;
    }

    Account *default_account = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);

    cus_account->balance -= amount;
    default_account->balance += amount;
    record_transaction(account_number, DEFAULT_BANK_ACCOUNT_NUMBER, amount);
    printf("Withdrawal successful! New balance: %d\n", cus_account->balance);
    if (overdraft_used)
    {
        printf("Note: Overdraft used! Current overdraft used: %d\n", -cus_account->balance);
    }
}

/**
 * @brief Displays the account details and current balance for one account.
 */
void check_balance()
{
    int account_number;

    printf("Enter account number: ");
    scanf("%d", &account_number);

    Account *cus_account = find_account(account_number);

    if (cus_account == NULL)
    {
        printf("Account number %d not found!\n", account_number);
        return;
    }

    printf("Account holder: %s\n", cus_account->name);
    printf("Account number: %d\n", cus_account->account_number);
    printf("Balance: %d\n", cus_account->balance);
}

/**
 * @brief Transfers funds between two customer accounts.
 */
void transfer()
{
    int from_account, to_account;
    float amount;

    printf("Enter source account number: ");
    scanf("%d", &from_account);
    printf("Enter destination account number: ");
    scanf("%d", &to_account);
    printf("Enter amount to transfer: ");
    scanf("%d", &amount);

    Account *src_account = find_account(from_account);
    Account *dest_account = find_account(to_account);

    /*
     * Validation order short-circuits as early as possible:
     * 1) both accounts must exist,
     * 2) accounts must be different,
     * 3) bank account cannot participate,
     * 4) source must have enough funds.
     */
    if (src_account == NULL)
    {
        printf("Source account number %d not found!\n", from_account);
        return;
    }
    else if (dest_account == NULL)
    {
        printf("Destination account number %d not found!\n", to_account);
        return;
    }
    else if (from_account == to_account)
    {
        printf("Source and destination accounts cannot be the same!\n");
        return;
    }
    else if (from_account == DEFAULT_BANK_ACCOUNT_NUMBER)
    {
        printf("Transfers from the bank's account are not allowed!\n");
        return;
    }
    else if (to_account == DEFAULT_BANK_ACCOUNT_NUMBER)
    {
        printf("Transfers to the bank's account are not allowed!\n");
        return;
    }
    else if (src_account->balance < amount)
    {
        if (src_account->overdraft_limit == 0)
        {
            printf("Transfer failed! Balance is insufficient for source account number %d!\n", from_account);
            return;
        }
        else if(src_account->balance + src_account->overdraft_limit < amount)
        {
            printf("Transfer failed! Overdraft limit exceeded for source account number %d!\n", from_account);
            return;
        }
    }
    else if (dest_account->balance + amount > dest_account->account_limit)
    {
        printf("Transfer failed! Account limit exceeded for destination account number %d!\n", to_account);
        return;
    }

    src_account->balance -= amount;
    dest_account->balance += amount;
    record_transaction(from_account, to_account, amount);
    printf("Transfer successful! New balance of source account: %d\n", src_account->balance);
    printf("New balance of destination account: %d\n", dest_account->balance);
}

/**
 * @brief Prints every recorded transaction in the history list.
 */
void list_all_transactions()
{
    Transaction *current = txn_head;
    printf("\n--- All Transactions ---\n");
    while (current != NULL)
    {
        printf("From Account: %d | To Account: %d | Amount: %d\n",
               current->from_account, current->to_account, current->amount);
        current = current->next;
    }
}

/**
 * @brief Prints transactions where the given account is sender or receiver.
 */
void list_transactions_for_account()
{
    int account_number;
    printf("Enter account number to view transactions: ");
    scanf("%d", &account_number);

    Account *cus_account = find_account(account_number);
    if (cus_account == NULL)
    {
        printf("Account number %d not found!\n", account_number);
        return;
    }

    Transaction *current = txn_head;
    printf("\n--- Transactions for Account %d ---\n", account_number);
    while (current != NULL)
    {
        if (current->from_account == account_number || current->to_account == account_number)
        {
            printf("From Account: %d | To Account: %d | Amount: %d\n",
                   current->from_account, current->to_account, current->amount);
        }
        current = current->next;
    }
}

/**
 * @brief Displays the interactive menu options.
 */
void display_menu()
{
    printf("\n--- Banking Application Menu ---\n");
    printf("Please select an option:\n");
    printf("1. Create Account\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Check Balance\n");
    printf("5. Transfer\n");
    printf("6. List Accounts\n");
    printf("7. List All Transactions\n");
    printf("8. List Transactions for an Account\n");
    printf("9. Exit\n");
}

/**
 * @brief Lists all accounts currently stored in the account linked list.
 */
void show_accounts()
{
    Account *current = head;
    printf("\n--- Account List ---\n");
    while (current != NULL)
    {
        printf("Account Holder: %20s | Account Number: %5d | Balance: %d | Overdraft Limit: %d | Account Limit: %d\n",
               current->name, current->account_number, current->balance, current->overdraft_limit, current->account_limit);
        current = current->next;
    }
}

/**
 * @brief Frees all dynamically allocated account nodes.
 */
void free_memory()
{
    Account *current = head;
    while (current != NULL)
    {
        Account *temp = current;
        current = current->next;
        free(temp);
    }
}

/**
 * @brief Performs cleanup and terminates the program.
 */
void exit_application()
{
    free_memory();
    printf("Exiting the application. Goodbye!\n");
    exit(0);
}

/**
 * @brief Program entry point.
 * @return 0 on normal termination.
 */
int main()
{
    int choice;

    create_default_account(); // Create a default account for the bank

    /* Menu loop continues until the user selects exit. */
    do
    {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            check_balance();
            break;
        case 5:
            transfer();
            break;
        case 6:
            show_accounts();
            break;

        case 7:
            list_all_transactions();
            break;
        case 8:
            list_transactions_for_account();
            break;
        case 9:
            exit_application();
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}
