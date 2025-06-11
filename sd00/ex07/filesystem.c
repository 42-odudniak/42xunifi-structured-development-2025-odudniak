#include "filesystem.h"

FSNode *create_file(const char *name, int size)
{

	FSNode *result = (FSNode *)malloc(sizeof(FSNode));

	if (!result)
		return (NULL);

	result->name = strdup(name);
	result->size = size;
	result->children = NULL;
	result->sibling = NULL;
	return (result);
}

FSNode *create_folder(const char *name)
{
	return (create_file(name, 0));
}

void add_child(FSNode *parent, FSNode *child)
{
	if (!child || !parent || parent->size != 0)
		return;
	if (!parent->children)
	{
		parent->children = child;
		return;
	}

	FSNode *last_child = parent->children;
	while (last_child->sibling)
		last_child = last_child->sibling;
	last_child->sibling = child;
}

FSNode *get_children(const FSNode *parent)
{
	return (parent->children);
}

FSNode *get_sibling(const FSNode *node)
{
	return (node->sibling);
}
