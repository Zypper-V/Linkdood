#ifndef CDOODCONTACTMANAGER_H
#define CDOODCONTACTMANAGER_H

#include <QObject>

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"

class CDoodContactItem;
class CDoodContactManager : public CDoodListModel
{

    Q_OBJECT

public:
    explicit CDoodContactManager(LinkDoodClient *client = 0, QObject *parent = 0);
    void getContactInforFromList(QString id,QString& name,QString& avater);
    ~CDoodContactManager();
    //获取会话列表
    Q_INVOKABLE void getContactList();
    //清空列表
    Q_INVOKABLE void clearChatList();
    Q_INVOKABLE void getContactInfo(QString userId);

    Q_INVOKABLE bool isFriend(QString id);
    Q_INVOKABLE QString findName(QString userId);
    //更新联系人信息
    Q_INVOKABLE void updateContactInfo(QString userId,QString operStar,QString remark="");
    //删除联系人
    Q_INVOKABLE void removeContact(QString userid);

    Q_INVOKABLE void selectMember(QString id);

    Q_INVOKABLE void clearMember();

    CDoodContactItem* itemById(QString id);
signals:
    void contactListChanged(int oper,ContactList contacts);
    void updateContactInfoResult(int code);
    void removeContactResult(int code);
    void addContactReslut(QString userId);
    void removeContactOper(QString id);
    void contactInfoChanged();
private slots:
    void onAvatarChanged(QString userid, QString avatar);
    void onContactListChanged(int oper,ContactList contacts);
    //联系人信息更新
    void onContactInfoChanged(int oper,Contact user);
    //监听联系人信息更新
    void onContactOnlineChanged(QString id,QString deviceText);
    //更新联系人信息返回
    void onUpdateContactInfo(int code);
    //删除联系人返回
    void onRemoveContact(int code);

private:

    void initConnect();
    int  indexOfSection(QString sectnion);//从map开头找第一个section相同item位置
    QMap<QString, CDoodContactItem*> otherListMap;
    QMap<QString, CDoodContactItem*> contactListMap;
    QMap<QString, CDoodContactItem*> starContactListMap;//v标好友
    QMap<QString, CDoodContactItem*> appListMap;
    std::vector<QString> m_member;

    int indexofTeam(QString team);

    LinkDoodClient *m_pClient;

    void addContact(Contact user,bool isInit=true);
    void modifyContact(Contact user);
    void removeContact(Contact user);
};
bool CmpByTeam(CDoodContactItem * first, CDoodContactItem * second);
#endif // CDOODCONTACTMANAGER_H
