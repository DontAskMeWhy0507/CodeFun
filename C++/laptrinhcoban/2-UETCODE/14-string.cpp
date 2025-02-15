#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::string alphabet;
    std::cin >> alphabet; // Đọc bảng chữ cái của ngôn ngữ X

    std::vector<std::string> words;

    // Tạo tất cả các từ có độ dài 2
    for (char i : alphabet) {
        for (char j : alphabet) {
            words.push_back(std::string(1, i) + j);         // std::string(1, i) tạo ra một chuỗi có một ký tự i  (ví dụ: std::string(1, 'a') tạo ra chuỗi "a")
        }
    }

    // Tạo tất cả các từ có độ dài 3
    for (char i : alphabet) {
        for (char j : alphabet) {
            for (char k : alphabet) {
                words.push_back(std::string(1, i) + j + k);
            }
        }
    }

    // Sắp xếp từ theo thứ tự từ điển của ngôn ngữ X
    std::sort(words.begin(), words.end(), [&alphabet](const std::string &a, const std::string &b) {
        for (size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
            if (a[i] != b[i]) return alphabet.find(a[i]) < alphabet.find(b[i]);
        }
        return a.size() < b.size();
    });

    // In tất cả các từ
    for (const std::string &word : words) {
        std::cout << word << '\n';
    }

    return 0;
}