#include <QWidget>
#include <QLineEdit> 
#include <QPushButton> 
#include <QListWidget>

class ChatPanel : public QWidget {
    Q_OBJECT

public:
    explicit ChatPanel(QWidget *parent = 0);
    
public slots:
    void writeMessage(QString sender, QString message);

private slots:
    void sendMessage();

private:
    QListWidget *chat;
    QPushButton *btn;
    QLineEdit *txt;
};
