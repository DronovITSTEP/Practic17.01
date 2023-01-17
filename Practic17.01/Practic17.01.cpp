#include <iostream>

using namespace std;

/*
Пользователь вводит данные о своих расходах в долларах 
за неделю (каждый день). Написать программу, которая
вычисляет:
■ среднюю (за неделю) потраченную сумму;
■ общую сумму, потраченную пользователем за неделю;
■ количество дней и их названия (например, «вторник»),
когда сумма расхода (в день) превысила 100 долларов.
*/
char week[7][15]{
    "Понедельник",
    "Вторник",
    "Среда",
    "Четверг",
    "Пятница",
    "Суббота",
    "Воскресенье" };
void HomeTask1() {
    int moneyOfWeek[7];
    int sum = 0;
    int count = 0;
    int* temp = new int[7];
    cout << "Введите траты за неделю\n";
    for (int i = 0, j = 0; i < 7; i++) {
        cout << week[i] << ": "; cin >> moneyOfWeek[i];
        sum += moneyOfWeek[i];
        if (moneyOfWeek[i] <= 100) {
            temp[j++] = i;
            count++;
        }
    }
    cout << "Сумма за неделю -> " << sum << endl
        << "Средняя сумма -> " << sum / 7 << endl;
    cout << "Кол-во дней, сумма которых < 100 ->" << count << endl;
    for (int i = 0; i < count; i++) {
        cout << week[temp[i]] << " ";
    }

}

/*
Известны данные курса валют (курс доллара по отношению
к евро) за все месяцы года и начисленные проценты за каждый 
месяц на депозитном счету в евро. Все данные вводятся
пользователем, в том числе и сумма на депозите в евро.
Написать программу, которая по запросу пользователя
(номер месяца) выводит в консоль размер допустимой суммы,
которую он может обналичить, при условии, что у него долларовая 
карта, обналичить можно не более 50% от начисленной
суммы в том случае, если начисленная сумма в этот месяц
составляет не менее 500$.
*/
void HomeTask2() {
    const double rate = 12.0;
    double exchangeRates[12]
    {1.5, 0.9, 1, 1.1, 0.8, 1, 1.8, 2, 2.1, 1.5, 1.1, 1}; // курс валют за каждый месяц
    double deposit = 7500; // первоначальная сумма денег
    double allSum; // вся сумма за год
    double amountMonth[12]; // сумма начисления в месяц (за каждый месяц)

    //cout << "Введите первоначальную сумму денег на счету: "; cin >> deposit;
    //cout << "Введите курс доллара к евро";
    //for (int i = 0; i < 12; i++) {
    //    cin >> exchangeRates[i];
    //}
    allSum = deposit;
    for (int i = 0; i < 12; i++) {
        amountMonth[i] = allSum * (rate / 100);
        cout << amountMonth[i] << " - ";
        allSum += amountMonth[i];
        cout << allSum << endl;
    }
    cout << endl;
    int m;
    do
    {
        cout << "введите месяц(1-12): "; cin >> m;
        if (amountMonth[m - 1] >= 500) {
            int temp = deposit;
            for (int i = 0; i < m; i++) {
                temp += amountMonth[i];
            }
            cout << "Можно обналичить "
                << ((temp - deposit) / 2) / exchangeRates[m - 1]
                << "$\n";

        }
        else
        {
            cout << "Можно снять 0$\n";
        }
    } while (m != 0);
}

/*
Написать программу, которая сравнивает число перестановок 
элементов при использовании сортировки «пузырьком» 
(усовершенствованная версия задания 2) и методом
выбора. Выполнить ее тестирование на разных 10 массивах,
содержащих 1000 случайных элементов, вычислить среднее
число перестановок для каждого метода после тестирования.
*/
int SortBubble(int* arr, int s) {
    int temp, count = 0;
    for (int i = 0; i < s; i++) {
        temp = 0;
        for (int j = 0; j < s - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);              
                temp++;
                count++;
            }
        }
        if (temp == 0) return count;
    }
}
int SortChoice(int* arr, int s) {
    int count = 0;
    int min_index;
    for (int i = 0; i < s; i++) {
        min_index = i;
        for (int j = i + 1; j < s; j++) {
            if (arr[j] < arr[min_index]) min_index = j;
            if (i != min_index) {
                swap(arr[i], arr[min_index]);
                count++;
            }
        }
    }
    return count;
}
void CreateArr(int* arr) {
    srand(time(0));
    for (int i = 0; i < 1000; i++) {
        arr[i] = rand() % 100;
    }
}
void HomeTask3() {
    int countBubble = 0, countChoice = 0;
    int* arr = new int[1000];
    for (int i = 0; i < 10; i++) {
        CreateArr(arr);
        countBubble += SortBubble(arr, 1000);
        CreateArr(arr);
        countChoice += SortChoice(arr, 1000);
        
    }
    cout << "Кол-во пузырьком = " << countBubble
         << "\nКол-во выбором = " << countChoice << endl;
    if (countBubble / 10 > countChoice / 10) 
        cout << "сортировка выбором эффективнее\n";
    else cout << "сортировка пузырьком эффективнее\n";
}

/*
Создайте двухмерный массив. Заполните его
случайными числами и покажите на экран. Пользователь
выбирает количество сдвигов и положение (влево, вправо, вверх, вниз).
Выполнить сдвиг массива и показать на
экран полученный результат. Сдвиг циклический.
Например, если мы имеем следующий массив
1 2 0 4 5 3
4 5 3 9 0 1
и пользователь выбрал сдвиг на 2 разряда вправо, то мы получим
5 3 1 2 0 4
0 1 4 5 3 9.
*/
void ShiftLeft(int arr[][4], int s) {
    for (int shift = 0; shift < s; shift++) {
        for (int i = 0; i < 4; i++) {
            int temp = arr[i][0];
            for (int j = 0; j < 4 ; j++) {
                arr[i][j] = arr[i][j + 1];
            }
            arr[i][3] = temp;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
void HomeTask4() {
    srand(time(0));
    int arr[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arr[i][j] = rand() % 10;
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    ShiftLeft(arr, 2);

}

int main()
{
    setlocale(LC_ALL, "");
    //HomeTask1();
    //HomeTask2();
    //HomeTask3();
    HomeTask4();
}
