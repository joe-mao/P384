#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHostInfo>
#include <QAbstractSocket>
#include <QList>
#include <QNetworkInterface>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol);//QHostInfo获取主机信息

private slots:
    void on_btnGetHostInfo_clicked();


    void on_btnLookup_clicked();


    void lookedUpHostInfo(const QHostInfo & host);//查找主机信息的槽函数

    void on_btnALLInterface_clicked();//QNetworkInterface::allInterfaces()函数的使用，获得程序所在主机的所有网络接口

    void on_btnDetail_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
