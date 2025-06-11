#include "recipe_generator.h"

struct Recipe *safe_error_return(
	struct Ingredients *ingredients,
	struct TasteProfile *taste_profile)
{
	if (ingredients)
		free_ingredients(ingredients);
	if (taste_profile)
		free_taste_profile(taste_profile);
	return NULL;
}

struct Recipe *create_custom_recipe(void)
{
	struct Ingredients *ingredients = get_current_ingredients();
	if (!ingredients)
		return NULL;

	struct TasteProfile *taste_profile = get_user_taste_profile();
	if (!taste_profile)
		return safe_error_return(ingredients, NULL);

	struct Recipe *recipe = NULL;
	do
	{
		if (recipe)
			free_recipe(recipe);
		recipe = create_recipe(ingredients, taste_profile);
		if (!recipe)
			return safe_error_return(ingredients, taste_profile);
	} while (get_user_approval(recipe) == 0);

	free_ingredients(ingredients);
	free_taste_profile(taste_profile);

	return recipe;
}
