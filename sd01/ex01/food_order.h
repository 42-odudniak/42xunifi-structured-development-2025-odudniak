#ifndef FOOD_ORDER_H
#define FOOD_ORDER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Checks if the restaurant is open based on the order. Returns 1 if open, 0 if closed.
int check_restaurant_status(struct OrderRequest *request);
// Creates a confirmation for an immediate order. Returns NULL on failure.
struct OrderConfirmation *create_standard_confirmation(void);
// Creates a confirmation for a future (pre-order). Returns NULL on failure.
struct OrderConfirmation *create_preorder_confirmation(void);
// Sends the confirmation to the user.
void send_confirmation_notification(struct OrderConfirmation *confirmation);

int process_food_order(struct OrderRequest *request);

#endif
