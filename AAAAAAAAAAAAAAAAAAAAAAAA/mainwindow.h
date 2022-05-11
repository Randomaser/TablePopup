#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слот при событии клика ПКМ (есть другой более гибкий способ, но более сложный, в данном примере лучше использовать это)
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);
    // Слот, в котором происходит что-то (В данном случае лучше использовать лямбда-выражение, но у меня не получилось с ними) :(
    void SlotClearCell();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
