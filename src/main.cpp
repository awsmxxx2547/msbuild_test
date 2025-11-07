#include <xlsxio_write.h>
#include <cstdio>

int main() {
    // Создаём новый Excel-файл
    xlsxiowriter xlsx;
    xlsx = xlsxiowrite_open("example.xlsx", "MySheet");
    if (!xlsx) {
        printf("Ошибка при создании файла Excel\n");
        return 1;
    }

    // Добавляем строку заголовков
    xlsxiowrite_add_cell_string(xlsx, "Имя");
    xlsxiowrite_add_cell_string(xlsx, "Возраст");
    xlsxiowrite_next_row(xlsx);

    // Добавляем первую строку данных
    xlsxiowrite_add_cell_string(xlsx, "Иван");
    xlsxiowrite_add_cell_int(xlsx, 25);
    xlsxiowrite_next_row(xlsx);

    // Добавляем вторую строку данных
    xlsxiowrite_add_cell_string(xlsx, "Мария");
    xlsxiowrite_add_cell_int(xlsx, 30);
    xlsxiowrite_next_row(xlsx);

    // Закрываем файл
    xlsxiowrite_close(xlsx);

    printf("Excel файл 'example.xlsx' создан!\n");
    return 0;
}

