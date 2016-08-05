#include "linkdoodservicethread.h"
#include <QTimer>
#include <QDebug>
#include <csystemnotification.h>
#include <csystemnotificationmanager.h>
#include <csystembadge.h>
#include <csystempowermanager.h>
#include <QDateTime>
#include <QUuid>

LinkDoodServiceThread::LinkDoodServiceThread(QObject *parent) : QObject(parent)
{
    m_pPowerManager = new CSystemPowerManager(this);
}

LinkDoodServiceThread::~LinkDoodServiceThread()
{
    if (m_pPowerManager) {
        delete m_pPowerManager;
        m_pPowerManager = NULL;
    }
}

void LinkDoodServiceThread::bcNotify(const QString senderId,
                                     const QString msgType,
                                     const QString content,
                                     const QString msgId,
                                     const QString sendTime,
                                     const QString displayName,
                                     const QString senderIconPath,
                                     const QString sessionType,
                                     int unReadNumber)
{
    qDebug()<<Q_FUNC_INFO<<"bcNotify content:"<<content;
    Q_UNUSED(sendTime);
    Q_UNUSED(msgId);
    Q_UNUSED(sessionType);
    Q_UNUSED(senderId);
    Q_UNUSED(content);
    Q_UNUSED(displayName);
    Q_UNUSED(senderIconPath);
    m_pPowerManager->accquireWakelock();

    CSystemNotificationManager notificationService;
    CSystemNotification notification;

    if(displayName == ""){
        notification.setTitle("天工圆圆");
    }else{
        notification.setTitle(displayName);
    }
    QString updateId = mMapUppdateId.value(senderId,"");
    if(updateId == ""){
        QUuid id = QUuid::createUuid();
        updateId = id.toString();
        mMapUppdateId[senderId] = updateId;
    }
    notification.setUpdateId(updateId);
    notification.setAction(senderId);
    notification.setMarqueeText(QString(tr("你收到了%1条即时消息")).arg(unReadNumber));
    notification.setSubtitle(content);
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(sendTime.toLongLong());
    notification.setDisplayTime(dateTime);
    if(senderIconPath != ""){
        notification.setIcon("file:://"+senderIconPath);
        qDebug()<<Q_FUNC_INFO<<senderIconPath;
    }
    //gGetAllUnreadMsgNum();
    //    QString sDefaultIcon = QString::fromStdString(ReadProfile (e_Runtime, "Corp", "Portrait", "0"));
    //    notification.setIconName(sDefaultIcon);

    QString sSoundState ="1";// QString::fromStdString(ReadProfile(e_UserConfig, "msgAudio", "IsOn", ""));
    if ("1" == sSoundState && "CALL" != msgType) {
        // bool 通知声音，默认为空
        notification.setSound("/usr/share/rings/门铃.wav");
    }

    QString sShakeState = "0";//QString::fromStdString(ReadProfile(e_UserConfig, "msgShock", "IsOn", ""));

    if ("0" == sShakeState) {
        notification.setVibrationMode(CNotification::ForceQuietMode);
    }

    notification.setSopid("com.vrv.linkDood");
    notification.setUiAppId("linkdoodui");

    notificationService.sendNotification(notification);

    // 桌面角标数处理：
    // gGetAllUnreadMsgNum获取到的是已经写入数据库的未读消息总数
    //CSystemBadge badge;
    //badge.setValue("com.vrv.linkDood", "linkdoodui", unReadNumber);

    QTimer::singleShot(2000, this, SLOT(releaseWakelockSlot()));
}

void LinkDoodServiceThread::releaseWakelockSlot()
{
    qDebug() << "linkDood : " << Q_FUNC_INFO;
    m_pPowerManager->releaseWakelock();
}
