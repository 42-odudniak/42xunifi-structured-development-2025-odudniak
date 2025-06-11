#include "filesystem.h"

int compute_total_size(const FSNode *node)
{
	if (!node)
		return 0;
	if (node->size != 0)
		return node->size;

	int result = node->size;
	if (node->size == 0)
	{
		for (FSNode *child = node->children; child; child = child->sibling)
		{
			result += compute_total_size(child);
		}
	}

	return result;
}

static void print_structure_impl(const FSNode *node, int indent, int level)
{
	if (!node)
		return;
	printf("%*s", level * indent, " ");

	if (node->size == 0)
	{
		printf("📂 %s (%d)\n", node->name, compute_total_size((FSNode *)node));

		// Folder's children
		for (FSNode *child = node->children; child; child = child->sibling)
			print_structure_impl(child, indent, level + 1);
	}
	else
	{
		printf("📄 %s (%d)\n", node->name, node->size);
	}

	if (level != 0)
		return;

	// Siblings
	for (FSNode *sibling = node->sibling; sibling; sibling = sibling->sibling)
		print_structure_impl(sibling, indent, level);
}
void print_structure(const FSNode *node, int indent)
{
	print_structure_impl(node, indent, 0);
}

void free_filesystem(FSNode *node)
{
	if (!node)
		return ;

	free_filesystem(node->children);
	free_filesystem(node->sibling);
	free(node->name);
	free(node);
}

/*
int main()
{
	// L0
	FSNode *root = create_folder("/");

	// L1
	FSNode *l1_home = create_folder("home");
	FSNode *l1_bin = create_folder("bin");
	FSNode *l1_swap_img = create_file("swap.img", 512);

	add_child(root, l1_bin);
	add_child(root, l1_home);
	add_child(root, l1_swap_img);

	// L2
	FSNode *l2_ls = create_file("ls", 420);
	FSNode *l2_cat = create_file("cat", 1337);
	FSNode *l2_odudniak = create_folder("odudniak");
	FSNode *l2_who_cache = create_file("who.cache", 1024);

	add_child(l1_bin, l2_cat);
	add_child(l1_bin, l2_ls);

	add_child(l1_home, l2_odudniak);
	add_child(l1_home, l2_who_cache);

	// L3
	FSNode *l3_sasharm = create_file("sasharm", 15360);

	add_child(l2_odudniak, l3_sasharm);

	// PRINT
	print_structure(root, 4);

	free_filesystem(root);
}
*/
