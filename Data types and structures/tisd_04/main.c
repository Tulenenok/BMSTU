#include"libr.h"

int main(void)
{
	setbuf(stdout, NULL);
	array_t arr;
	list_t list;
	arr.count = 0;
	list.count = 0;
	int choice, len;
	
	menu();
	
	while (scanf("%d", &choice) == 1)
	{
		if (choice == 0)
		{
			printf("Выход.\n");
			break;
		}
		else if (choice == 1)
		{
			if (create_stacks(&arr, &list))
				break;
		}
		else if (choice == 2)
		{
			printf("Введите кол-во элементов не более кол-ва свободных: ");
			if (scanf("%d", &len) == 1)
			{
				if (add_array(&arr, len))
					break;
				if (add_list(&list, len, &arr))
					break;
			}
			else
				printf("Стек переполнится.");
		}
		/*else if (choice == 3)
		{
			if ((rc = process_3(&mtr_1, &mtr_2, &mtr_3)) || !flag)
			{
				printf("Не введены матрицы.\n");
				break;
			}
			
			if (flag == 1)
				flag = 2;
			else
				flag = 4;
		}*/
		else if (choice == 4)
		{
			print_stack(&arr);
			//print_list(&list);
		}
		/*else if (choice == 5)
		{
			if (flag != 2 && flag != 4)
			{
				printf("Матрицы не введены или не сложены в нужном виде.\n");
				break;
			}
			printf("Исходная матрица 1:\n");
			output_matrix(&mtr_1);
			printf("Исходная матрица 2:\n");
			output_matrix(&mtr_2);
			printf("Результат:\n");
			output_matrix(&mtr_3);
		}
		else if (choice == 6)
		{
			if (flag != 3 && flag != 4)
			{
				printf("Матрицы не введены или не сложены в нужном виде.\n");
				break;
			}
			printf("Исходная матрица 1:\n");
			output_sparse(&smtr_1);
			printf("Исходная матрица 2:\n");
			output_sparse(&smtr_2);
			printf("Результат:\n");
			output_sparse(&smtr_3);
		}*/
		else
		{
			printf("Некорректный выбор в меню.\n");
			break;
		}
		
		menu();
	}
	
	free(arr.first);
	free_list(&list);
	
	return EXIT_SUCCESS;
}
