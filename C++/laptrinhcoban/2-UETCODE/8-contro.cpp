/*
Viết hàm lọc ký tự phía bên phải xâu dùng con trỏ void rFilter(char *s).
Lọc các ký tự không nằm trong bảng chữ cái tiếng Anh (a-zA-Z) nằm ngoài cùng bên phải xâu, chuyển thành '_'.
*/

#include <cstring>

void rFilter(char *s) {
    char *right = s + strlen(s) - 1;  // Con trỏ trỏ tới ký tự cuối cùng của xâu

    while (right >= s && !((*right >= 'a' && *right <= 'z') || (*right >= 'A' && *right <= 'Z'))) {
        *right = '_';  // Thay thế ký tự không nằm trong bảng chữ cái
        right--;  // Di chuyển con trỏ về bên trái
    }
}

