#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);	// Set up user interface
    m_message=nullptr;	// EString is null until User clicks encryptButton
    // User may not edit output text browser
    ui->textBrowser->setReadOnly(true);
    ui->warning_label->hide();
}

MainWindow::~MainWindow()
{
    delete ui;	// Reclaim memory from user interface
    // If m_message is not null, reclaim memory
    if(m_message!=nullptr) delete m_message;
}

void MainWindow::on_encryptButton_clicked()
{
    // Get user input from lineEdit widget
    QString input=ui->input_lineEdit->text();
    if(input.isEmpty() || input.isNull()) ui->warning_label->show();
    else
    {
        ui->warning_label->hide();

        // If m_message has been initialized, reclaim memory to start fresh
        if(m_message!=nullptr) delete m_message;
        // Create a new EString from user input and assign to m_message
        m_message=new EString(input);

        // Display m_message in output text browser
        ui->textBrowser->setText(m_message->as_text());
    }
}

void MainWindow::on_decryptButton_clicked()
{
   if(m_message==nullptr)
       return;
   else {
       m_message->unscramble();
        ui->textBrowser->setText(m_message->as_text());
   }
}
