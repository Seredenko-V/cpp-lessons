/*******************************************************************************
    Работа с динамической памятью

    Небольшая корректировка домашки. Дописал создание динамических двумерных
    массивов для корректной передачи в функцию SumArr. 
    Остальные ошибки постарайся найти сама, места где нужно посмотреть отметил
*******************************************************************************/

#include <iostream> 
using namespace std;

int** FillTArr(int str, int stolb)
{
    int** arr = new int* [str];
    for (int i = 0; i < str; ++i)
    {
        arr[i] = new int[stolb];
    }
    return arr;
}

void Print(int** arr, int str, int stolb)
{
    for (int i = 0; i < str; ++i)
    {
        for (int j = 0; j < stolb; ++j)
        {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}

int** SumArr(int str, int stolb, int size_1, int size_2, int** arr_first, int** arr_second)
{
    int** arr = FillTArr(str, stolb);
    for (int i = 0; i < size_1; ++i)
    {
        for (int j = 0; j < size_2; ++j)
        {
            arr[i][j] = arr_first[i][j] + arr_second[i][j];
            //cout << arr[i][j] << ' ';
        }
        //cout << endl;
    }
    return arr;
}

void DelArr(int** arr, int str, int stolb)
{
    for (int i = 0; i < str; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main()
{
    // посмотри внимательнее на переменные ниже
    int str = 5;
    int stolb = 7;
    const int size_1 = 2;
    const int size_2 = 2;

    int arr_first[size_1][size_2] = {
        {1,2},
        {2,9}
    };
    int arr_second[size_1][size_2] = {
        {9,8},
        {8,1}
    };


    // Это делается для того, чтобы передать двумерный массив в функцию
    int** dinamic_arr_first = FillTArr(size_1, size_2);
    for (int i = 0; i < size_1; ++i) {
        for (int j = 0; j < size_1; ++j) {
            dinamic_arr_first[i][j] = arr_first[i][j];
        }
    }
    int** dinamic_arr_second = FillTArr(size_1, size_2);
    for (int i = 0; i < size_1; ++i) {
        for (int j = 0; j < size_1; ++j) {
            dinamic_arr_second[i][j] = arr_second[i][j];
        }
    }

    // и вот тут подумай какие из переменных тебе не нужно передавать
    int** sum = SumArr(str, stolb, size_1, size_2, dinamic_arr_first, dinamic_arr_second);
    Print(sum, str, stolb);
    DelArr(sum, str, stolb);
    
    DelArr(dinamic_arr_first, str, stolb);
    DelArr(dinamic_arr_second, str, stolb);

    return 0;
}