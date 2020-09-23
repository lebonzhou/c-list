/*
* Author: Lebon <lebon.zhou@gmail.com>
* Singly Linked List Examples
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#define PR_DEBUG

#ifdef PR_DEBUG
#define pr_dbg(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define pr_dbg(fmt, ...)
#endif

#define pr_info(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define pr_err(fmt, ...) printf(fmt, ##__VA_ARGS__)

struct node {
	int data;
	struct node *next;
};

struct list_function {
	struct node *(*func)();
	char *description;
};

struct node *list_head = NULL;

struct node *list_init(unsigned int nums)
{
	unsigned int i;
	struct node *new = NULL;
	struct node *cur = NULL;
	struct node *first = NULL;

	for (i = 0; i < nums; i++) {
		new = malloc(sizeof(struct node));
		new->data = i + 1;
		new->next = NULL;

		if (first == NULL) {
			first = new;
		} else {
			cur->next = new;
		}
		cur = new;
	}
	return first;
}

void list_free(struct node *head)
{
	struct node *cur = head;
	struct node *next;
	do {
		if (cur != NULL) {
			next = cur->next;
			free(cur);
			cur = next;
		} else {
			break;
		}
	} while (1);

	return;
}

unsigned int list_get_nums(struct node *head)
{
	unsigned int nums = 1;
	while (head->next != NULL) {
		nums++;
		head = head->next;
	}

	pr_dbg("\nGet node nums:%d\n", nums);
	return nums;
}

void list_show(struct node *head, char *msg)
{
	printf("\n%s\n", msg);
	unsigned int i = 1;

	do {
		pr_info("node pos:%3d, data:%6d\n", i, head->data);

		head = head->next;
		i++;

	} while (head != NULL);
}

struct node *list_move_tail(struct node *head)
{
	struct node *prev = NULL;
	do {
		if (head->next == NULL) {
			if (prev != NULL) {
				prev->next = NULL;
			}
			return head;
		} else {
			prev = head;
			head = head->next;
		}

	} while (1);
}

struct node *list_revert_node(struct node *head)
{
	struct node *tail = NULL;
	struct node *new_head = NULL;
	struct node *curr = NULL;

	do {
		tail = list_move_tail(head);

		if (new_head == NULL) {
			new_head = tail;

		} else {
			curr->next = tail;
		}
		curr = tail;

		pr_dbg("tail data:%d\n", tail->data);

	} while (tail != head);

	return new_head;
}

struct node *list_revert_data(struct node *head)
{
	struct node *fst_half_cur = NULL;
	struct node *snd_half_cur = NULL;
	struct node *snd_half_head = NULL;
	unsigned int nums = 0;
	int half = 0;
	int data = 0;
	unsigned int i = 0;
	unsigned int j = 0;

	nums = list_get_nums(head);
	half = nums >> 1;
	snd_half_head = head;
	fst_half_cur = head;

	for (i = 0; i < half; i++) {
		snd_half_head = snd_half_head->next;
	}

	if (nums & 0x01) {
		snd_half_head = snd_half_head->next;
	}

	for (j = 0; j < half; j++) {
		snd_half_cur = snd_half_head;
		for (i = 0; i < half - j - 1; i++) {
			snd_half_cur = snd_half_cur->next;
		}
		data = fst_half_cur->data;
		fst_half_cur->data = snd_half_cur->data;
		snd_half_cur->data = data;
		fst_half_cur = fst_half_cur->next;
	}

	return head;
}

struct node *list_set_random(struct node *head)
{
	struct node *cur = head;

	while (1) {
		cur->data = (int)random() & 0xFFFF;
		if (cur->next == NULL)
			break;
		else
			cur = cur->next;
	}

	return head;
}

struct node *list_sort_data_b2s(struct node *head)
{
	unsigned int i, j;
	unsigned int nums;
	struct node *cur;
	int data;

	nums = list_get_nums(head);

	for (j = 1; j < nums; j++) {
		cur = head;
		for (i = 0; i < nums - j; i++) {
			if (cur->data < cur->next->data) {
				data = cur->data;
				cur->data = cur->next->data;
				cur->next->data = data;
			}
			cur = cur->next;
		}
	}
	return head;
}

struct node *list_swap_data(struct node *head)
{
	struct node *cur = head;
	int data;

	while (1) {
		if ((cur != NULL) && (cur->next != NULL)) {
			data = cur->data;
			cur->data = cur->next->data;
			cur->next->data = data;
			cur = cur->next->next;
		} else {
			break;
		}
	}

	return head;
}

struct node *list_swap_node(struct node *head)
{
	struct node *first = NULL;
	struct node *cur = head;
	struct node *pre = NULL;
	struct node *next = NULL;

	while (1) {
		if ((cur != NULL) && (cur->next != NULL)) {
			next = cur->next;
			if (pre != NULL) {
				pre->next = next;
			}
			cur->next = next->next;
			next->next = cur;
			pre = cur;
			cur = cur->next;
			if (first == NULL) {
				first = next;
			}
		} else {
			break;
		}
	}

	if (first == NULL) {
		first = head;
	}

	return first;
}

struct list_function function_suites[] = {

	{ list_revert_node, "After revert node......" },
	{ list_revert_data, "After revert data......" },
	{ list_swap_node, "After swap node......" },
	{ list_swap_data, "After swap data......" },
	{ list_set_random, "Set random data as:" },
	{ list_sort_data_b2s, "After sort data from big to small......" },
	{ NULL, NULL }
};

int main(int argc, char *argv[])
{
	unsigned int nums = 0;
	unsigned int i = 0;

	if (argc < 2) {
		pr_info("Please input node numbers, e.g.: %s 7\n", argv[0]);
		exit(0);
	}

	nums = (unsigned int)atoi(argv[1]);
	if (nums <= 0) {
		pr_err("Input nums value (%u) is illegal, please input value more than zero\n",
		       nums);
		exit(-1);
	}

	pr_info("\n****** Singly Linked List Examples ******\n");

	list_head = list_init(nums);
	list_show(list_head, "Set init data as:");

	i = 0;
	while (function_suites[i].func != NULL) {
		list_head = function_suites[i].func(list_head);
		list_show(list_head, function_suites[i].description);
		i++;
	}

	list_free(list_head);

	return 0;
}
