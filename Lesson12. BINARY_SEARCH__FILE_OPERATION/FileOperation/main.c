#include <stdio.h>
#include <stdlib.h>

// Hàm tạo file CSV
void createCSV(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Cannot create file.csv %s.\n", filename);
        return;
    }
    fprintf(file, "ID,Name,Age\n"); // Ghi dòng tiêu đề vào file
    fclose(file);
}

// Hàm ghi dữ liệu vào file CSV
void writeDataToCSV(const char *filename, int id, const char *name, int age) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Cannot open file %s.\n", filename);
        return;
    }
    fprintf(file, "%d,%s,%d\n", id, name, age); // Ghi dữ liệu vào file
    fclose(file);
}

// Hàm đọc dữ liệu từ file CSV
void readCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file %s.\n", filename);
        return;
    }

    char line[100]; // Bộ đệm để đọc từng dòng
    printf("Data file %s:\n", filename);
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line); // In từng dòng ra màn hình
    }
    fclose(file);
}

int main() {
    const char *file = "data.csv";

    // Tạo file CSV
    createCSV(file);

    // Ghi dữ liệu vào file CSV
    writeDataToCSV(file, 5, "John", 25);
    writeDataToCSV(file, 2, "Alice", 30);
    writeDataToCSV(file, 3, "Bob", 22);

    // Đọc dữ liệu từ file CSV
    readCSV(file);

    return 0;
}