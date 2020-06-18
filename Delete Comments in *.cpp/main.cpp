#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> comment_erase(std::vector<std::string> &vec) {
    std::vector<std::string> result(vec.size());
    bool flag = false; // показывает, что сейчас "режим удаления"

    for (int j = 0; j < vec.size(); j++) {
        std::string line = vec[j];
        std::string new_line = line;
        int line_size = line.size();
        int number_marks = 0; // для подсчета кавычек
        int k = 0; // позиция текущего символа удаления
        bool fl = false; // флаг для определения ситуаций вида /***/ /***/ на одной строчке
        for (int i = 0; i < line_size; i++) {
            if (flag == false) {
                if (line[i] == '/' && line[i + 1] == '*' && (number_marks % 2 == 0)) {
                    if (fl == false) {
                        new_line.erase(i, 1);
                        k = i;
                    } else {
                        new_line.erase(k, 1);
                    }
                    flag = true;
                }
                // если "//", то просто стираем всвю строчку до конца
                if (line[i] == '/' && line[i + 1] == '/' && (number_marks % 2 == 0)) {
                    new_line.erase(i, line.size() - i);
                    break;
                }
                if (line[i] == '"' && line[i - 1] != '\\') {
                    number_marks++;
                }
                if (fl && !flag) {
                    k++;
                }
            } else {
                if (line[i] == '*' && line[i + 1] == '/') {
                    new_line.erase(k, 2);
                    i++;
                    flag = false;
                    fl = true;
                } else {
                    new_line.erase(k, 1);
                }
            }
        }
        result[j] = new_line + "\n";
    }

    return result;
}

std::string delete_all_whitespace(std::string &text, std::vector<std::string> &vec) {
    std::vector<std::string> result;

    result = comment_erase(vec);

    std::string res;
    for (const auto &i : result) {
        res += i;
    }
    return res;
}

int main() {
    std::ifstream fin("txt.txt");
    std::ofstream fout("nex_txt.txt");

    std::string text;
    std::vector<std::string> vec_string;
    while (fin) {
        std::string s;
        getline(fin, s);
        text += s + "\n";
        vec_string.push_back(s);
    }

    std::string res = delete_all_whitespace(text, vec_string);
    fout << res;

    fin.close();
    fout.close();
    return 0;
}
