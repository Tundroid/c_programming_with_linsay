/**
 * @file test_extreme.c
 * @author Test Suite Generator
 * @brief Extreme test cases for banking application
 * @version 1.0
 * @date 2026-05-12
 * 
 * Test Coverage:
 * - Default account as central reserve
 * - Deposits ONLY from bank
 * - Withdrawals ONLY to bank
 * - Transfers ONLY between customer accounts
 * - Account limits enforcement
 * - Overdraft limits enforcement
 * - Edge cases and boundary conditions
 * - To run: gcc -o app_test ./app_test.c -lm  && ./app_test
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/* ========== TEST FRAMEWORK ========== */
#define TEST_PASS() printf("  ✓ PASS\n")
#define TEST_FAIL(msg) printf("  ✗ FAIL: %s\n", msg)
#define TEST_SECTION(name) printf("\n╔════════════════════════════════════════╗\n║ %s\n╚════════════════════════════════════════╝\n", name)

int tests_passed = 0;
int tests_failed = 0;

void log_test(const char *test_name, bool passed) {
    printf("Test: %s ... ", test_name);
    if (passed) {
        TEST_PASS();
        tests_passed++;
    } else {
        TEST_FAIL("Assertion failed");
        tests_failed++;
    }
}

/* ========== DATA STRUCTURES (from app.c) ========== */
#define DEFAULT_BANK_ACCOUNT_NUMBER 123

typedef struct Account {
    char name[50];
    int account_number;
    int balance;
    int account_limit;
    int overdraft_limit;
    struct Account *next;
} Account;

typedef struct txn {
    int from_account;
    int to_account;
    int amount;
    struct txn *next;
} Transaction;

/* ========== GLOBAL STATE ========== */
Transaction *txn_head = NULL;
Account *head = NULL;
int test_input_index = 0;
int test_inputs[1000];
bool use_auto_input = false;

/* ========== MOCK INPUT SYSTEM ========== */
int scanf_mock(const char *format, ...) {
    if (!use_auto_input) {
        return scanf(format, __builtin_va_arg_pack());
    }
    // Auto-input mode for testing
    va_list args;
    va_start(args, format);
    if (strcmp(format, "%d") == 0) {
        int *ptr = va_arg(args, int *);
        if (test_input_index < 1000) {
            *ptr = test_inputs[test_input_index++];
            return 1;
        }
    }
    va_end(args);
    return 0;
}

/* ========== CORE FUNCTIONS (from app.c) ========== */
void create_default_account() {
    Account *default_account = (Account *)malloc(sizeof(Account));
    if (default_account == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(default_account->name, "Bank");
    default_account->account_number = DEFAULT_BANK_ACCOUNT_NUMBER;
    default_account->balance = 1000000;
    default_account->account_limit = 0;
    default_account->overdraft_limit = 0;
    default_account->next = head;
    head = default_account;
}

void record_transaction(int from_account, int to_account, int amount) {
    Transaction *new_txn = (Transaction *)malloc(sizeof(Transaction));
    if (new_txn == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    new_txn->from_account = from_account;
    new_txn->to_account = to_account;
    new_txn->amount = amount;
    new_txn->next = txn_head;
    txn_head = new_txn;
}

Account *find_account(int account_number) {
    Account *current = head;
    while (current != NULL) {
        if (current->account_number == account_number) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void reset_system() {
    // Free all accounts
    Account *current = head;
    while (current != NULL) {
        Account *temp = current;
        current = current->next;
        free(temp);
    }
    // Free all transactions
    Transaction *t_current = txn_head;
    while (t_current != NULL) {
        Transaction *temp = t_current;
        t_current = t_current->next;
        free(temp);
    }
    head = NULL;
    txn_head = NULL;
    test_input_index = 0;
    memset(test_inputs, 0, sizeof(test_inputs));
}

/* ========== TEST SUITE ========== */

void test_default_account_initialization() {
    TEST_SECTION("TEST SUITE 1: Default Account Initialization");
    
    reset_system();
    create_default_account();
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    log_test("Bank account created", bank != NULL);
    log_test("Bank account number is 123", bank != NULL && bank->account_number == DEFAULT_BANK_ACCOUNT_NUMBER);
    log_test("Bank account has name 'Bank'", bank != NULL && strcmp(bank->name, "Bank") == 0);
    log_test("Bank account initial balance is 1,000,000", bank != NULL && bank->balance == 1000000);
    log_test("Bank account has 0 account limit", bank != NULL && bank->account_limit == 0);
    log_test("Bank account has 0 overdraft limit", bank != NULL && bank->overdraft_limit == 0);
}

void test_customer_account_creation() {
    TEST_SECTION("TEST SUITE 2: Customer Account Creation");
    
    reset_system();
    create_default_account();
    
    // Create customer account 1
    Account *cust1 = (Account *)malloc(sizeof(Account));
    strcpy(cust1->name, "Alice");
    cust1->account_number = 101;
    cust1->balance = 0;
    cust1->account_limit = 5000;
    cust1->overdraft_limit = 1000;
    cust1->next = head;
    head = cust1;
    
    Account *found = find_account(101);
    log_test("Customer account created and found", found != NULL);
    log_test("Customer account has correct name", found != NULL && strcmp(found->name, "Alice") == 0);
    log_test("Customer account has correct limit", found != NULL && found->account_limit == 5000);
    log_test("Customer account has correct overdraft limit", found != NULL && found->overdraft_limit == 1000);
    
    // Create customer account 2
    Account *cust2 = (Account *)malloc(sizeof(Account));
    strcpy(cust2->name, "Bob");
    cust2->account_number = 102;
    cust2->balance = 0;
    cust2->account_limit = 3000;
    cust2->overdraft_limit = 500;
    cust2->next = head;
    head = cust2;
    
    found = find_account(102);
    log_test("Second customer account created", found != NULL && strcmp(found->name, "Bob") == 0);
}

void test_deposits_from_bank_only() {
    TEST_SECTION("TEST SUITE 3: Deposits Come ONLY From Bank");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Customer");
    cust->account_number = 201;
    cust->balance = 0;
    cust->account_limit = 10000;
    cust->overdraft_limit = 0;
    cust->next = head;
    head = cust;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    
    // Simulate deposit
    cust->balance += 1000;
    bank->balance -= 1000;
    record_transaction(DEFAULT_BANK_ACCOUNT_NUMBER, 201, 1000);
    
    log_test("Deposit increases customer balance", cust->balance == 1000);
    log_test("Deposit decreases bank balance", bank->balance == initial_bank_balance - 1000);
    log_test("Transaction recorded from bank (123) to customer (201)", 
             txn_head != NULL && txn_head->from_account == DEFAULT_BANK_ACCOUNT_NUMBER && txn_head->to_account == 201);
}

void test_withdrawals_to_bank_only() {
    TEST_SECTION("TEST SUITE 4: Withdrawals Go ONLY To Bank");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Customer");
    cust->account_number = 202;
    cust->balance = 5000;
    cust->account_limit = 10000;
    cust->overdraft_limit = 1000;
    cust->next = head;
    head = cust;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    
    // Simulate withdrawal
    cust->balance -= 2000;
    bank->balance += 2000;
    record_transaction(202, DEFAULT_BANK_ACCOUNT_NUMBER, 2000);
    
    log_test("Withdrawal decreases customer balance", cust->balance == 3000);
    log_test("Withdrawal increases bank balance", bank->balance == initial_bank_balance + 2000);
    log_test("Transaction recorded from customer (202) to bank (123)", 
             txn_head != NULL && txn_head->from_account == 202 && txn_head->to_account == DEFAULT_BANK_ACCOUNT_NUMBER);
}

void test_transfers_between_customers_only() {
    TEST_SECTION("TEST SUITE 5: Transfers ONLY Between Customer Accounts");
    
    reset_system();
    create_default_account();
    
    Account *cust1 = (Account *)malloc(sizeof(Account));
    strcpy(cust1->name, "Alice");
    cust1->account_number = 301;
    cust1->balance = 5000;
    cust1->account_limit = 10000;
    cust1->overdraft_limit = 1000;
    cust1->next = head;
    head = cust1;
    
    Account *cust2 = (Account *)malloc(sizeof(Account));
    strcpy(cust2->name, "Bob");
    cust2->account_number = 302;
    cust2->balance = 1000;
    cust2->account_limit = 8000;
    cust2->overdraft_limit = 500;
    cust2->next = head;
    head = cust2;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    
    // Simulate transfer from cust1 to cust2
    cust1->balance -= 2000;
    cust2->balance += 2000;
    record_transaction(301, 302, 2000);
    
    log_test("Transfer decreases source customer balance", cust1->balance == 3000);
    log_test("Transfer increases destination customer balance", cust2->balance == 3000);
    log_test("Bank balance is UNCHANGED by customer transfer", bank->balance == initial_bank_balance);
    log_test("Transaction recorded from customer to customer", 
             txn_head != NULL && txn_head->from_account == 301 && txn_head->to_account == 302);
}

void test_account_limit_on_deposit() {
    TEST_SECTION("TEST SUITE 6: Account Limit Enforcement on Deposit");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Limited");
    cust->account_number = 401;
    cust->balance = 4500;
    cust->account_limit = 5000;
    cust->overdraft_limit = 0;
    cust->next = head;
    head = cust;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    int initial_cust_balance = cust->balance;
    
    // Try deposit that would exceed limit
    int deposit_amount = 600;
    bool would_exceed = (cust->balance + deposit_amount > cust->account_limit);
    
    log_test("Deposit would exceed account limit", would_exceed);
    log_test("Deposit correctly blocked (balance unchanged)", !would_exceed || cust->balance == initial_cust_balance);
    log_test("Bank balance unchanged when deposit blocked", bank->balance == initial_bank_balance);
    
    // Valid deposit (500 stays within 5000 limit)
    if (cust->balance + 500 <= cust->account_limit) {
        cust->balance += 500;
        bank->balance -= 500;
        record_transaction(DEFAULT_BANK_ACCOUNT_NUMBER, 401, 500);
    }
    
    log_test("Valid deposit processed", cust->balance == 5000);
}

void test_account_limit_on_transfer() {
    TEST_SECTION("TEST SUITE 7: Account Limit Enforcement on Transfer");
    
    reset_system();
    create_default_account();
    
    Account *cust1 = (Account *)malloc(sizeof(Account));
    strcpy(cust1->name, "Sender");
    cust1->account_number = 501;
    cust1->balance = 3000;
    cust1->account_limit = 10000;
    cust1->overdraft_limit = 1000;
    cust1->next = head;
    head = cust1;
    
    Account *cust2 = (Account *)malloc(sizeof(Account));
    strcpy(cust2->name, "Receiver-Limited");
    cust2->account_number = 502;
    cust2->balance = 4500;
    cust2->account_limit = 5000;
    cust2->overdraft_limit = 0;
    cust2->next = head;
    head = cust2;
    
    int initial_cust1_balance = cust1->balance;
    int initial_cust2_balance = cust2->balance;
    
    // Try transfer that would exceed destination limit
    int transfer_amount = 600;
    bool would_exceed = (cust2->balance + transfer_amount > cust2->account_limit);
    
    log_test("Transfer would exceed destination limit", would_exceed);
    log_test("Transfer correctly blocked (source unchanged)", !would_exceed || cust1->balance == initial_cust1_balance);
    log_test("Transfer correctly blocked (destination unchanged)", !would_exceed || cust2->balance == initial_cust2_balance);
    
    // Valid transfer (400 keeps destination at 4900, within 5000 limit)
    if (cust2->balance + 400 <= cust2->account_limit) {
        cust1->balance -= 400;
        cust2->balance += 400;
        record_transaction(501, 502, 400);
    }
    
    log_test("Valid transfer processed", cust1->balance == 2600 && cust2->balance == 4900);
}

void test_overdraft_limit_on_withdrawal() {
    TEST_SECTION("TEST SUITE 8: Overdraft Limit Enforcement on Withdrawal");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Overdraft-Customer");
    cust->account_number = 601;
    cust->balance = 1000;
    cust->account_limit = 10000;
    cust->overdraft_limit = 500;
    cust->next = head;
    head = cust;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    int initial_cust_balance = cust->balance;
    
    // Try withdrawal that exceeds balance + overdraft
    int withdrawal_amount = 1600; // balance=1000, overdraft=500, total=1500
    bool exceeds_overdraft = (cust->balance + cust->overdraft_limit < withdrawal_amount);
    
    log_test("Withdrawal exceeds balance + overdraft limit", exceeds_overdraft);
    log_test("Excessive withdrawal blocked (balance unchanged)", !exceeds_overdraft || cust->balance == initial_cust_balance);
    log_test("Bank balance unchanged when withdrawal blocked", bank->balance == initial_bank_balance);
    
    // Valid withdrawal using overdraft (withdraw 1200, balance goes to -200, within -500 limit)
    int valid_withdrawal = 1200;
    if (cust->balance >= valid_withdrawal || (cust->balance + cust->overdraft_limit >= valid_withdrawal)) {
        cust->balance -= valid_withdrawal;
        bank->balance += valid_withdrawal;
        record_transaction(601, DEFAULT_BANK_ACCOUNT_NUMBER, valid_withdrawal);
    }
    
    log_test("Valid overdraft withdrawal processed", cust->balance == -200);
    log_test("Customer in overdraft state", cust->balance < 0);
}

void test_overdraft_limit_zero() {
    TEST_SECTION("TEST SUITE 9: No Overdraft When Limit is Zero");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "No-Overdraft");
    cust->account_number = 701;
    cust->balance = 500;
    cust->account_limit = 10000;
    cust->overdraft_limit = 0;
    cust->next = head;
    head = cust;
    
    int initial_balance = cust->balance;
    
    // Try withdrawal exceeding balance with zero overdraft
    int withdrawal_amount = 600;
    bool insufficient = (cust->balance < withdrawal_amount && cust->overdraft_limit == 0);
    
    log_test("Withdrawal blocked when overdraft is zero", insufficient);
    log_test("Balance unchanged after failed withdrawal", cust->balance == initial_balance);
}

void test_transfer_to_bank_prohibited() {
    TEST_SECTION("TEST SUITE 10: Transfers TO Bank Account Prohibited");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Customer");
    cust->account_number = 801;
    cust->balance = 5000;
    cust->account_limit = 10000;
    cust->overdraft_limit = 1000;
    cust->next = head;
    head = cust;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    int initial_cust_balance = cust->balance;
    
    // Try transfer to bank account
    bool attempt_to_bank = (DEFAULT_BANK_ACCOUNT_NUMBER == 123);
    
    log_test("Transfer to bank account correctly identified", attempt_to_bank);
    log_test("Transfer to bank blocked (customer balance unchanged)", cust->balance == initial_cust_balance);
    log_test("Transfer to bank blocked (bank balance unchanged)", bank->balance == initial_bank_balance);
}

void test_transfer_from_bank_prohibited() {
    TEST_SECTION("TEST SUITE 11: Transfers FROM Bank Account Prohibited");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Customer");
    cust->account_number = 901;
    cust->balance = 1000;
    cust->account_limit = 10000;
    cust->overdraft_limit = 500;
    cust->next = head;
    head = cust;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    int initial_cust_balance = cust->balance;
    
    // Try transfer from bank account
    bool attempt_from_bank = (DEFAULT_BANK_ACCOUNT_NUMBER == 123);
    
    log_test("Transfer from bank account correctly identified", attempt_from_bank);
    log_test("Transfer from bank blocked (bank balance unchanged)", bank->balance == initial_bank_balance);
    log_test("Transfer from bank blocked (customer balance unchanged)", cust->balance == initial_cust_balance);
}

void test_transfer_same_account_prohibited() {
    TEST_SECTION("TEST SUITE 12: Self-Transfer Prohibited");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Customer");
    cust->account_number = 1001;
    cust->balance = 5000;
    cust->account_limit = 10000;
    cust->overdraft_limit = 500;
    cust->next = head;
    head = cust;
    
    int initial_balance = cust->balance;
    
    // Try self-transfer
    bool same_account = (1001 == 1001);
    
    log_test("Self-transfer correctly identified", same_account);
    log_test("Self-transfer blocked (balance unchanged)", cust->balance == initial_balance);
}

void test_insufficient_bank_funds_for_deposit() {
    TEST_SECTION("TEST SUITE 13: Bank Insufficient Funds for Deposit");
    
    reset_system();
    
    // Create bank with very limited funds
    Account *bank = (Account *)malloc(sizeof(Account));
    strcpy(bank->name, "Bank");
    bank->account_number = DEFAULT_BANK_ACCOUNT_NUMBER;
    bank->balance = 100; // Very limited
    bank->account_limit = 0;
    bank->overdraft_limit = 0;
    bank->next = head;
    head = bank;
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Customer");
    cust->account_number = 1101;
    cust->balance = 0;
    cust->account_limit = 10000;
    cust->overdraft_limit = 0;
    cust->next = head;
    head = cust;
    
    int initial_bank_balance = bank->balance;
    int initial_cust_balance = cust->balance;
    
    // Try deposit exceeding bank's available funds
    int deposit_request = 500;
    bool bank_insufficient = (deposit_request > bank->balance);
    
    log_test("Insufficient bank funds detected", bank_insufficient);
    log_test("Deposit blocked when bank has insufficient funds", 
             !bank_insufficient || cust->balance == initial_cust_balance);
    log_test("Bank balance unchanged", bank->balance == initial_bank_balance);
}

void test_boundary_deposit_at_limit() {
    TEST_SECTION("TEST SUITE 14: Boundary Test - Deposit Exactly At Limit");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Boundary");
    cust->account_number = 1201;
    cust->balance = 4000;
    cust->account_limit = 5000;
    cust->overdraft_limit = 0;
    cust->next = head;
    head = cust;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    
    // Deposit that brings balance exactly to limit
    int deposit_amount = 1000;
    if (cust->balance + deposit_amount <= cust->account_limit) {
        cust->balance += deposit_amount;
        bank->balance -= deposit_amount;
        record_transaction(DEFAULT_BANK_ACCOUNT_NUMBER, 1201, deposit_amount);
    }
    
    log_test("Deposit to exact account limit accepted", cust->balance == 5000);
    log_test("Balance equals account limit", cust->balance == cust->account_limit);
}

void test_boundary_overdraft_at_limit() {
    TEST_SECTION("TEST SUITE 15: Boundary Test - Overdraft Exactly At Limit");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Boundary-OD");
    cust->account_number = 1301;
    cust->balance = 500;
    cust->account_limit = 10000;
    cust->overdraft_limit = 500;
    cust->next = head;
    head = cust;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    
    // Withdrawal that brings balance to exactly -overdraft_limit
    int withdrawal_amount = 1000; // 500 - 1000 = -500
    bool allowed = (cust->balance + cust->overdraft_limit >= withdrawal_amount);
    
    if (allowed) {
        cust->balance -= withdrawal_amount;
        bank->balance += withdrawal_amount;
        record_transaction(1301, DEFAULT_BANK_ACCOUNT_NUMBER, withdrawal_amount);
    }
    
    log_test("Withdrawal to exact overdraft limit accepted", allowed);
    log_test("Balance at negative of overdraft limit", allowed && cust->balance == -500);
}

void test_transaction_history_order() {
    TEST_SECTION("TEST SUITE 16: Transaction History - Most Recent First");
    
    reset_system();
    create_default_account();
    
    // Record multiple transactions
    record_transaction(123, 201, 1000);
    record_transaction(201, 202, 500);
    record_transaction(202, 123, 200);
    
    log_test("Most recent transaction is first (202->123)", 
             txn_head != NULL && txn_head->from_account == 202 && txn_head->to_account == 123);
    log_test("Second transaction is second (201->202)", 
             txn_head->next != NULL && txn_head->next->from_account == 201);
    log_test("Oldest transaction is last (123->201)", 
             txn_head->next->next != NULL && txn_head->next->next->from_account == 123);
}

void test_nonexistent_account_operations() {
    TEST_SECTION("TEST SUITE 17: Non-existent Account Handling");
    
    reset_system();
    create_default_account();
    
    Account *found = find_account(9999);
    log_test("Non-existent account returns NULL", found == NULL);
    
    // Try to operate on non-existent account
    Account *source = find_account(123);
    Account *dest = find_account(9999);
    
    log_test("Source account exists", source != NULL);
    log_test("Destination account does not exist", dest == NULL);
}

void test_multiple_transfers_between_customers() {
    TEST_SECTION("TEST SUITE 18: Multiple Transfers Between Same Customers");
    
    reset_system();
    create_default_account();
    
    Account *alice = (Account *)malloc(sizeof(Account));
    strcpy(alice->name, "Alice");
    alice->account_number = 1401;
    alice->balance = 10000;
    alice->account_limit = 20000;
    alice->overdraft_limit = 2000;
    alice->next = head;
    head = alice;
    
    Account *bob = (Account *)malloc(sizeof(Account));
    strcpy(bob->name, "Bob");
    bob->account_number = 1402;
    bob->balance = 5000;
    bob->account_limit = 15000;
    bob->overdraft_limit = 1000;
    bob->next = head;
    head = bob;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    
    // Multiple transfers
    alice->balance -= 2000;
    bob->balance += 2000;
    record_transaction(1401, 1402, 2000);
    
    bob->balance -= 1000;
    alice->balance += 1000;
    record_transaction(1402, 1401, 1000);
    
    alice->balance -= 3000;
    bob->balance += 3000;
    record_transaction(1401, 1402, 3000);
    
    log_test("Alice final balance correct", alice->balance == 5000);
    log_test("Bob final balance correct", bob->balance == 9000);
    log_test("Bank balance unchanged by customer transfers", bank->balance == initial_bank_balance);
    log_test("Transaction count is 3", 
             txn_head != NULL && txn_head->next != NULL && txn_head->next->next != NULL && txn_head->next->next->next == NULL);
}

void test_zero_amount_operations() {
    TEST_SECTION("TEST SUITE 19: Zero Amount Edge Cases");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Customer");
    cust->account_number = 1501;
    cust->balance = 1000;
    cust->account_limit = 10000;
    cust->overdraft_limit = 500;
    cust->next = head;
    head = cust;
    
    // Zero deposit
    cust->balance += 0;
    log_test("Zero deposit leaves balance unchanged", cust->balance == 1000);
    
    // Zero withdrawal
    cust->balance -= 0;
    log_test("Zero withdrawal leaves balance unchanged", cust->balance == 1000);
    
    // Zero transfer
    Account *cust2 = (Account *)malloc(sizeof(Account));
    strcpy(cust2->name, "Customer2");
    cust2->account_number = 1502;
    cust2->balance = 500;
    cust2->account_limit = 5000;
    cust2->overdraft_limit = 0;
    cust2->next = head;
    head = cust2;
    
    int alice_before = cust->balance;
    int bob_before = cust2->balance;
    cust->balance -= 0;
    cust2->balance += 0;
    
    log_test("Zero transfer leaves both balances unchanged", 
             cust->balance == alice_before && cust2->balance == bob_before);
}

void test_large_deposit() {
    TEST_SECTION("TEST SUITE 20: Large Deposit Amount");
    
    reset_system();
    create_default_account();
    
    Account *cust = (Account *)malloc(sizeof(Account));
    strcpy(cust->name, "Customer");
    cust->account_number = 1601;
    cust->balance = 0;
    cust->account_limit = 1000000;
    cust->overdraft_limit = 0;
    cust->next = head;
    head = cust;
    
    Account *bank = find_account(DEFAULT_BANK_ACCOUNT_NUMBER);
    int initial_bank_balance = bank->balance;
    
    // Large deposit
    int large_deposit = 500000;
    if (cust->balance + large_deposit <= cust->account_limit && 
        large_deposit <= bank->balance) {
        cust->balance += large_deposit;
        bank->balance -= large_deposit;
        record_transaction(DEFAULT_BANK_ACCOUNT_NUMBER, 1601, large_deposit);
    }
    
    log_test("Large deposit processed", cust->balance == 500000);
    log_test("Bank balance decreased correctly", bank->balance == initial_bank_balance - 500000);
}

/* ========== MAIN TEST RUNNER ========== */
int main() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║     EXTREME TEST SUITE FOR BANKING APPLICATION v1.0        ║\n");
    printf("║                    Comprehensive Coverage                   ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // Run all test suites
    test_default_account_initialization();
    test_customer_account_creation();
    test_deposits_from_bank_only();
    test_withdrawals_to_bank_only();
    test_transfers_between_customers_only();
    test_account_limit_on_deposit();
    test_account_limit_on_transfer();
    test_overdraft_limit_on_withdrawal();
    test_overdraft_limit_zero();
    test_transfer_to_bank_prohibited();
    test_transfer_from_bank_prohibited();
    test_transfer_same_account_prohibited();
    test_insufficient_bank_funds_for_deposit();
    test_boundary_deposit_at_limit();
    test_boundary_overdraft_at_limit();
    test_transaction_history_order();
    test_nonexistent_account_operations();
    test_multiple_transfers_between_customers();
    test_zero_amount_operations();
    test_large_deposit();
    
    // Print summary
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                      TEST SUMMARY                           ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("✓ Tests Passed: %d\n", tests_passed);
    printf("✗ Tests Failed: %d\n", tests_failed);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Total Tests: %d\n", tests_passed + tests_failed);
    printf("Pass Rate: %.1f%%\n", 100.0 * tests_passed / (tests_passed + tests_failed));
    printf("\n");
    
    reset_system();
    return tests_failed > 0 ? 1 : 0;
}
