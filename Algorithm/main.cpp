#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>

void print(std::vector<int> &vec) {
    for (auto &i: vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 1) Создайте последовательность П1 целых чисел от 1 до 10
    std::vector<int> succession = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "1: "; print(succession);
    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(succession));
    // 2) Добавте ещё несколько чисел в конец П1 из cin

    std::cout << "2: "; print(succession);

    // 3) Перемешайте П1 случайным образом
    std::default_random_engine dre;
    std::shuffle (succession.begin(), succession.end(), dre);
    std::cout << "3: "; print(succession);

    // 4) Удалите дубликаты из П1
    sort(succession.begin(), succession.end());
    auto last = unique(succession.begin(), succession.end());
    succession.erase(last, succession.end());
    std::cout << "4: "; print(succession);

    // 5) Подсчитайте количество нечетных чисел в П1
    int even = count_if(succession.begin(), succession.end(), [](int i){return i % 2 == 0;});
    std::cout << "6: " << even << std::endl;

    // 6) Определите минимальное и максимальное значение в П1
    auto mm =  minmax_element(succession.begin(), succession.end());
    std::cout << "6: " << *mm.first << " " << *mm.second << std::endl;

    // 7) Попробуйте найти хотя бы одно просто число в П1
    auto simpleIter = find_if(succession.begin(), succession.end(), [](auto x) {
       for (int i = 2; i < sqrt(x); i++) {
           if (!(x % i)) {
               return false;
           }
       }
        return true;
    });
    std::cout << "7: ";
    if (simpleIter != succession.end()) {
        std::cout << *simpleIter << std::endl;
    } else {
        std::cout << "Don't find simple value" << std::endl;
    }


    // 8) Заменить все числа в П1 их квадратами
    int x;
    transform(succession.begin(), succession.end(), succession.begin(), [](auto x) { return x*x;});
    std::cout << "8: "; print(succession);

    // 9) Создайте последовательность П2 из N случайных чисел, где N - длина П1
    std::uniform_int_distribution<int> di(1,200);
    std::vector<int> succession_2;
    std::generate_n(std::back_inserter(succession_2), succession.size(), [&di, &dre](){
        auto t = di(dre);
        return t;
    });
    std::cout << "9: "; print(succession_2);

    // 10) Вычислите сумму чисел в П2
    std::cout << "10: " << accumulate(succession_2.begin(), succession_2.end(), 0) << std::endl;

    // 11) Замените первым первые несколько чисел в П2 числом 1

    std::fill_n(succession_2.begin(), 5, 1);
    std::cout << "11: "; print(succession_2);

    // 12) Создайте последовательност П3, как разность П1 и П2
    std::vector<int> succession_3;
    transform(succession.begin(), succession.end(), succession_2.begin(), back_inserter(succession_3),
            [](auto x, auto y) { return x - y;});
    std::cout << "12: "; print(succession_3);

    // 13) Замените каждый отрицательный элемент в П3 нулем
    replace_if(succession_3.begin(), succession_3.end(), [](auto x) { return x < 0;}, 0);
    std::cout << "13: "; print(succession_3);

    // 14) Удалите полностью все нулевые элементы из П3
    succession_3.erase(remove_if(succession_3.begin(), succession_3.end(), [](auto x) {
        return x == 0;
    }), succession_3.end());
    std::cout << "14: "; print(succession_3);

    // 15) измените порядок следования элементов в П3 на обратный
    reverse(succession_3.begin(), succession_3.end());
    std::cout << "15: "; print(succession_3);

    // 16) определите быстро топ-3 наибольших элемента в П3
    nth_element(succession_3.begin(), next(succession_3.begin(), 2), succession_3.end(), std::greater<int>());
    std::cout << "16: " << succession_3[0] << " " << succession_3[1] << " " << succession_3[2] << std::endl;

    // 17) отсортируйте полностью П1 и П2 по возростанию
    sort(succession.begin(), succession.end());
    sort(succession_2.begin(), succession_2.end());
    std::cout << "17: " << std::endl;
    print(succession);
    print(succession_2);

    // 18) создайте последовательность П4 как слияние П1 и П2
    std::vector<int>succession_4;
    merge(succession.begin(), succession.end(), succession_2.begin(), succession_2.end(), back_inserter(succession_4));
    std::cout << "18: "; print(succession_4);

    // 19) определите диапазон упорядоченной вставки числа 1 в П4
    auto range = equal_range(succession_4.begin(), succession_4.end(), 1);
    std::cout << "19: Range between value: " << *range.first << " and " << *range.second << std::endl;

    // 20) выведите все последовательности в cout
    std::cout << "20: " << std::endl;
    std::copy(succession.begin(), succession.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::copy(succession_2.begin(), succession_2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::copy(succession_3.begin(), succession_3.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::copy(succession_4.begin(), succession_4.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    return 0;
}