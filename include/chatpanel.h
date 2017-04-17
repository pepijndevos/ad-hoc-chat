#pragma once

#include <QDebug>
#include <QWidget>
#include <QLineEdit> 
#include <QPushButton> 
#include <QListWidget>
#include <QSize>
#include <QFileDialog>
#include <QDir>

class ChatPanel : public QWidget {
    Q_OBJECT

public:
    explicit ChatPanel(QString name, QWidget *parent = 0);
    
public slots:
    void writeMessage(QString sender, QString message);
    void displayImage(QString sender, QIcon image, QString caption);
    void setIconSize(QSize size);

private slots:
    void sendMessage();
    void selectFile();

signals:
    void newMessage(QString chatname, QString message);
    void sendFile(QString chatname, QString filename);

private:
    QString chatName;
    QListWidget *chat;
    QPushButton *btn;
    QPushButton *file_btn;
    QLineEdit *txt;
};
