#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "estring.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // Returns true if user input can be converted to an EString

private slots:
    void on_encryptButton_clicked();

    void on_decryptButton_clicked();

private:
    Ui::MainWindow *ui;
    EString* m_message;
};

#endif // MAINWINDOW_H
