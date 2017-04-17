#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit> 
#include <QPushButton> 
#include <QListWidget>
#include <QSize>

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

signals:
    void newMessage(QString chatname, QString message);

private:
    QString chatName;
    QListWidget *chat;
    QPushButton *btn;
    QLineEdit *txt;
};
