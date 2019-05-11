#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btnGetHostInfo_clicked()
{
    //QHostInfo获取主机信息
    QString hostName = QHostInfo::localHostName();//本地主机名
    this->ui->plainTextEdit->appendPlainText("本地主机名：" + hostName + "\n");

    QHostInfo hostInfo = QHostInfo::fromName(hostName);//本机IP地址
    QList<QHostAddress> addList = hostInfo.addresses();//IP地址列表
    if(!addList.isEmpty()){
        for(int i = 0; i < addList.count(); i++){
            QHostAddress aHost = addList.at(i);//每一项是一个QHostAddress
            bool show = this->ui->chkOnlyIPv4->isChecked();//只显示IPv4
            if(show){
                show = (QAbstractSocket::IPv4Protocol == aHost.protocol());//IPv4协议，返回当前IP地址的类型
            }else{
                show = true;
            }
            if(show){
                this->ui->plainTextEdit->appendPlainText("协议:" + protocolName(aHost.protocol()));
                this->ui->plainTextEdit->appendPlainText("本机IP地址：" + aHost.toString());//返回Ip地址的字符串
                this->ui->plainTextEdit->appendPlainText("");
            }
        }
    }
}

QString Dialog::protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
{
    //通过协议类型，返回协议名称字符串
    switch(protocol){
    case QAbstractSocket::IPv4Protocol:
        return "IPv4 Protocol";
    case QAbstractSocket::IPv6Protocol:
        return "IPv6 Protocol";
    case QAbstractSocket::AnyIPProtocol:
        return "Any IP Protocol";
    default:
        return "Unknown Network Layer Protocol";
    }
}

void Dialog::on_btnLookup_clicked()
{
    //查找主机信息（可以根据主机名，域名，IP地址）
    QString hostname = this->ui->editHost->text();//获取主机名，域名或者IP地址
    this->ui->plainTextEdit->appendPlainText("正在查找主机信息：" + hostname);
    QHostInfo::lookupHost(hostname, this, SLOT(lookedUpHostInfo(QHostInfo)));
}

void Dialog::lookedUpHostInfo(const QHostInfo & host){
    //查找主机信息的槽函数
    QList<QHostAddress> addList = host.addresses();
    if(!addList.isEmpty()){
        for(int i = 0; i < addList.count(); i++){
            QHostAddress aHost = addList.at(i);
            bool show = ui->chkOnlyIPv4->isChecked();//只显示IPv4
            if(show){
                show = (QAbstractSocket::IPv4Protocol == aHost.protocol());
            }else{
                show = true;
            }
            if(show){
                this->ui->plainTextEdit->appendPlainText("协议：" + protocolName(aHost.protocol()));
                this->ui->plainTextEdit->appendPlainText(aHost.toString());
            }
        }
    }
}

void Dialog::on_btnALLInterface_clicked()
{
    //QNetworkInterface::allInterfaces()函数的使用，获得程序所在主机的所有网络接口
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for(int i = 0; i < list.count(); i++){
        QNetworkInterface aInterface = list.at(i);
        if(!aInterface.isValid()){
            continue;
        }
        this->ui->plainTextEdit->appendPlainText("设备名称:" + aInterface.humanReadableName());
        this->ui->plainTextEdit->appendPlainText("硬件地址:" + aInterface.hardwareAddress());//MAC地址
        QList<QNetworkAddressEntry> entryList = aInterface.addressEntries();
        for(int j = 0; j < entryList.count(); j++){
            QNetworkAddressEntry aEntry = entryList.at(j);
            this->ui->plainTextEdit->appendPlainText("IP地址：" + aEntry.ip().toString());
            this->ui->plainTextEdit->appendPlainText("子网掩码：" + aEntry.netmask().toString());
            this->ui->plainTextEdit->appendPlainText("广播地址：" + aEntry.broadcast().toString() + "\n");
        }
        this->ui->plainTextEdit->appendPlainText("\n");
    }
}

void Dialog::on_btnDetail_clicked()
{
    //QNetworkInterface::allAddresses()的使用
    QList<QHostAddress> addList = QNetworkInterface::allAddresses();
    if(!addList.isEmpty()){
        for(int i = 0; i < addList.count(); i++){
            QHostAddress aHost = addList.at(i);
            bool show = this->ui->chkOnlyIPv4->isChecked();//只显示IPv4
            if(show){
                show = (QAbstractSocket::IPv4Protocol == aHost.protocol());
            }else{
                show = true;
            }
            if(show){
                this->ui->plainTextEdit->appendPlainText("协议：" + protocolName(aHost.protocol()));
                this->ui->plainTextEdit->appendPlainText("IP地址：" + aHost.toString());
                this->ui->plainTextEdit->appendPlainText("");
            }
        }
    }
}
