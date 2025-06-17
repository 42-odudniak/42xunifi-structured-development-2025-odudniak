#include "food_order.h"

int process_food_order(struct OrderRequest *request)
{
	const bool is_opened = check_restaurant_status(request) == 1;

	struct OrderConfirmation *confirmation = NULL;
	if (!is_opened)
		confirmation = create_preorder_confirmation();
	else
		confirmation = create_standard_confirmation();

	if (!confirmation)
		return 0;

	send_confirmation_notification(confirmation);

	return 1;
}
