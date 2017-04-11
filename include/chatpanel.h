#include <QWidget>
#include <QLineEdit> 
#include <QPushButton> 
#include <QListWidget>

class ChatPanel : public QWidget {
    Q_OBJECT

public:
    explicit ChatPanel(QString name, QWidget *parent = 0);
    
public slots:
    void writeMessage(QString sender, QString message);

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
