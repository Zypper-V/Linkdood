#ifndef CDOODSYSMSGMANAGER_H
#define CDOODSYSMSGMANAGER_H

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"
#include "cdoodsysmsgitem.h"

class CDoodSysMsgManager : public CDoodListModel
{
    Q_OBJECT
    Q_PROPERTY(bool isSysMsg READ isSysMsg WRITE setIsSysMsg NOTIFY isSysMsgChanged)

public:
    CDoodSysMsgManager(LinkDoodClient *client = 0, QObject *parent = 0);
    bool isSysMsg() const;
    Q_INVOKABLE bool setIsSysMsg(const bool &data);

    //清空列表
    Q_INVOKABLE void clickItem(QString id,bool isAgree);
    Q_INVOKABLE void clearListView();
    Q_INVOKABLE void getSysMessages(int type=0,int count=1000,QString msgid="0",int flag=1);
    Q_INVOKABLE void setSysMessagRead(int type, QString msg);
                void response(IMSysMsgRespInfo info);
    Q_INVOKABLE void removeSysMessage(QString type,QString msgid);

signals:
    void sysMessageNotice(IMSysMsg sysMsg);
    void isSysMsgChanged();
    void removeSysMsg(QString type,QString id);
//    void getSysMessagesResult(int code, IMSysMsgList sysmsgList);
private slots:
    //系统消息推送
    void onSysMessageNotice(IMSysMsg sysMsg);
    void onRemoveSysMessageResult(QString result);
    void onGetSysMessages(int code, IMSysMsgList sysmsgList);
private:
    void initConnect();
    QString m_msgid;
    QString m_msgtype;
    bool mIsSysMsg;

    LinkDoodClient *m_pClient;
    QMap<QString, CDoodSysmsgItem*> m_contactListMap;

    void addItemToListView(IMSysMsg sysMsg);
    void modifyItemToListView(IMSysMsg sysMsg);
};

#endif // CDOODSYSMSGMANAGER_H
