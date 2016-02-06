#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int **arr;

int Calculator(int base, int free_cube);

int main()
{
	int cube_count = 0;
	cin >> cube_count;
	arr = new int*[cube_count];
	for (int i = 0; i < cube_count; i++)
	{
		arr[i] = new int[cube_count];
	}
	for (int i = 0; i < cube_count; i++)
		for (int j = 0; j < cube_count; j++)
			arr[i][j] = -1;
	cout << Calculator(cube_count, cube_count);
	for (int i = 0; i < cube_count; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

int Calculator(int base, int free_cube)
{
	//заполнять не больше текущей бызы все свободные кубики
	int count = 0;
	int current = 0;
	bool full_base = false;
	while (current < base && current < free_cube){	
		current++;	
	}
	//если база кончилась, а свободные кубики еще остались, то
	if (current == base && current < free_cube)
	{
		if (arr[base][free_cube - current] == -1){
			arr[base][free_cube - current] = Calculator(base, free_cube - current);
		}
		count += arr[base][free_cube - current];
		full_base = true;
	}
	//если кубики кончились, то считаем текущее количество базой и уменьшаем ее по единичке
	if (current == free_cube || full_base)
	{
		if (!full_base)
			count++;
		int i = free_cube - current;
		int t0 = 0, t1 = 0;
		while (current > 1){
			t0 = --current;
			t1 = ++i;
			if (arr[t0][t1] == -1){
				arr[t0][t1] = Calculator(t0, t1);
			}
			count += arr[t0][t1] = Calculator(t0, t1);
		}
	}

	return count;
}