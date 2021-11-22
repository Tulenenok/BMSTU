#include"libr.h"

void menu(void)
{
	printf("Выберите пункт меню от 0 до 6:\n");
	printf("0 - выход;\n");
	printf("1 - создать стеки;\n");
	printf("2 - добавить элемент;\n");
	printf("3 - удалить элемент;\n");
	printf("4 - вывести стек;\n");
	printf("5 - вывести адреса удалённых элементов списка;\n");
	printf("6 - сложить числа в стеке и вывести статистику.\n");
}

int create_stacks(array_t *arr, list_t *list)
{
	if (arr->count)
	{
		printf("Стеки уже существуют.\n");
		return EXIT_SUCCESS;
	}
	int len;
	printf("Введите целочисленную длину стеков от 1 до 1000: ");
	
	if (scanf("%d", &len) != 1 || len < 1 || len > 1000)
	{
		printf("Некорректный ввод.\n");
		return EXIT_FAILURE;
	}
	arr->first = malloc(sizeof(int) * len);
	
	if (!arr->first)
	{
		printf("Ошибка выделения памяти.");
		return EXIT_FAILURE;
	}
	
	arr->count = len;
	list->first = malloc(sizeof(list_t));
	
	if (!list->first)
	{
		printf("Ошибка выделения памяти.");
		return EXIT_FAILURE;
	}
	
	int el = rand() % 100 - 50;
	elem_t *str = list->first;
	list->first->elem = el;
	*(arr->first) = el;
	list->count = len;

	for (int i = 1; i < len; i++)
	{
		str->next = malloc(sizeof(list_t));
		
		if (!list->first)
		{
			printf("Ошибка выделения памяти.");
			return EXIT_FAILURE;
		}
		
		str = str->next;
		
		el = rand() % 100 - 50;
		*(arr->first + i) = el;
		str->elem = el;
	}
	
	str->next = NULL;
	
	return EXIT_SUCCESS;
}

void free_list(list_t *list)
{
	elem_t *x = list->first;
	elem_t *y;
	
	while (x)
	{
		y = x->next;
		free(x);
		x = y;
	}
}

void print_stack(array_t *arr)
{
	for (int i = 0; i < arr->count; i++)
	{
		if (*(arr->first + i) > 0)
			printf("+%d\n", *(arr->first + i));
		else
			printf("%d\n", *(arr->first + i));
	}
	printf("Свободных мест: %d\n", 1000 - arr->count);
}

void print_list(list_t *list)
{
	elem_t *x = list->first;
	
	while (x)
	{
		if (x->elem > 0)
			printf("+%d\n", x->elem);
		else
			printf("%d\n", x->elem);
		x = x->next;
	}
}

int add_array(array_t * arr, int len)
{
	arr->first = realloc(arr->first, sizeof(int) * (len + arr->count));
	
	if (!arr->first)
	{
		printf("Ошибка выделения памяти.");
		return EXIT_FAILURE;
	}
	
	arr->count += len;
	
	for (int i = arr->count - 1; i >= 0; i--)
		*(arr->first + len + i) = *(arr->first + i);
	
	for (int i = 0; i < len; i++)
		*(arr->first + i) = rand() % 100 - 50;
	
	return EXIT_SUCCESS;
}

int add_list(list_t *list, int len, array_t *arr)
{
	elem_t *x = list->first;
	elem_t *y;
	list->count = arr->count;

	for (int i = 0; i < len; i++)
	{
		printf("%zu\n", sizeof(elem_t));
		y = malloc(sizeof(elem_t));
		printf("AAA\n");
		if (!y)
		{
			printf("Ошибка выделения памяти.");
			return EXIT_FAILURE;
		}
		
		y->elem = *(arr->first + len - 1 - i);
		y->next = x;
		x = y;
	}
	
	return EXIT_SUCCESS;
}
