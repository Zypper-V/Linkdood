#include<sysmsgcontroler.h>
#include<iostream>
#include<QDebug>


SysMsgControler::SysMsgControler()
{

}

SysMsgControler::~SysMsgControler()
{

}

void SysMsgControler::onSysMessageNotice(SysMsg &msg)
{
    qDebug() << Q_FUNC_INFO;
}
