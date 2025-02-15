
// Hàm in ra giá trị các điểm ảnh của ảnh img thành một bảng
void printImage(const Image& img) {
    for (int i = 0; i < img.height; ++i) {
        for (int j = 0; j < img.width; ++j) {
            std::cout << img.pixels[i * img.width + j] << " ";
        }
        std::cout << "\n";
    }
}

// Hàm trả về một ảnh mới có kích thước mỗi chiều bằng một nửa ảnh đầu vào
Image halve(const Image& img) {
    int newWidth = (img.width+1) /2;
    int newHeight = (img.height+1) / 2;
    int *newPixels = new int[newWidth * newHeight];

    for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {
            newPixels[i * newWidth + j] = img.pixels[(2 * i) * img.width + (2 * j)];
        }
    }

    Image halvedImg = { newPixels, newWidth, newHeight };
    return halvedImg;
}