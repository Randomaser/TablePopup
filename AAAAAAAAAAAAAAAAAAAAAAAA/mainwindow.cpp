#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Глобальные переменные для определения ячейки таблицы, где был совершён клик

int rowIndClick = 0; // Отслеживание строки ячейки клика
int colIndClick = 0; // Отслеживание столбца ячейки клика

// Слот при событии клика ПКМ (есть другой более гибкий способ, но более сложный, в данном примере лучше использовать это)
void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    // Создаём переменные для отслеживания различных параметров высоты

    QList<int> rowsHeight; // Отслеживание высоты каждой строки
    int Height = 0; // Отслеживание итоговой высоты всей таблицы
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) // Пробегаемся по всем строкам
    {
        rowsHeight.append(ui->tableWidget->rowHeight(row)); // Заполнение массива высот строк
        Height += rowsHeight.last(); // Увеличение итоговой высоты
        if (Height < pos.y()) // Если координата высоты клика не в получившемся отрезке (от начала таблицы до нынешней итоговой высоты),
            rowIndClick++;    // то прибавляем счётчик строк
    }

    // Создаём переменные для отслеживания различных параметров ширины

    QList<int> columnsWidth; // Отслеживание ширины каждой строки
    int Width = 0; // Отслеживание итоговой ширины всей таблицы
    for (int col = 0; col < ui->tableWidget->columnCount(); col++) // Пробегаемся по всем столбцам
    {
        columnsWidth.append(ui->tableWidget->columnWidth(col)); // Заполнение массива ширин столбцов
        Width += columnsWidth.last(); // Увеличение итоговой ширины
        if (Width < pos.x()) // Если координата ширины клика не в получившемся отрезке (от начала таблицы до нынешней итоговой ширины),
            colIndClick++;   // то прибавляем счётчик столбцов
    }

    // Переводим значения ширины и длины в точку с глобальными координатами
    QPoint maxPoint = ui->tableWidget->viewport()->mapToGlobal(QPoint(Width, Height));
    // А также переводим точку клика в точку с глобальными координатами
    QPoint pointClick = ui->tableWidget->viewport()->mapToGlobal(pos);

    if (maxPoint.x() >= pointClick.x() && maxPoint.y() >= pointClick.y()) // Проверка попадания клика во всю таблицу
    {
        //Создаём меню
        QMenu *menu = new QMenu(this);

        //Настраиваем необходимые функции
        QAction *clear = new QAction("Сбросить");
        connect(clear, SIGNAL(triggered()), this, SLOT(SlotClearCell())); // Связываем нужный сигнал с нужным слотом (по идее можно и без этого, но там как-то у меня не сильно получилось)

        //Добавляем в меню все пункты
        menu->addAction(clear);

        //Определяем, что это контекстное меню при нажатии ПКМ (popup)
        menu->popup(pointClick);
    }
}

// Слот, в котором происходит что-то (В данном случае лучше использовать лямбда-выражение, но у меня не получилось с ними) :(
void MainWindow::SlotClearCell()
{
    // Основные действия с ячейкой (в данном случае её очистка)
    ui->tableWidget->setItem(rowIndClick, colIndClick, new QTableWidgetItem(""));
}
