#include "linkdoodservicethread.h"
#include <QTimer>
#include <QDebug>
#include <csystemnotification.h>
#include <csystemnotificationmanager.h>
#include <csystembadge.h>
#include <csystempowermanager.h>

LinkDoodServiceThread::LinkDoodServiceThread(QObject *parent) : QObject(parent)
{

}

LinkDoodServiceThread::~LinkDoodServiceThread()
{
    if (m_pPowerManager) {
        delete m_pPowerManager;
        m_pPowerManager = NULL;
    }
}

void LinkDoodServiceThread::bcNotify(const QString &senderId,
                                      const QString &msgType,
                                      const QString &content,
                                      const QString &msgId,
                                      const QString &sendTime,
                                      const QString &displayName,
                                      const QString &senderIconPath,
                                      const QString &sessionType,
                                      int unReadNumber)
{
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

    qDebug()<<Q_FUNC_INFO<<"1111111111111111111111111111111242335456456";
    notification.setTitle("信源豆豆");

    //    if ("0" == msgType) {
    //        notification.setSubtitle(content);
    //    } else if ("1" == msgType) {
    //        notification.setSubtitle("[语音]");
    //    } else if ("2" == msgType) {
    //        notification.setSubtitle("[图片]");
    //    } else if ("3" == msgType) {
    //        notification.setSubtitle("[视频]");
    //    }
    //    int nUnReadNumber = gGetAllUnreadMsgNum();
    notification.setUpdateId("{c4a1fd6e-fa7d-39f6-a1d9-b9d25f64135b}");

    //    notification.setAction(senderId);
    notification.setAction("showRootPage");
    notification.setMarqueeText(QString(tr("你收到了%1条即时消息")).arg(1));
    notification.setSubtitle(QString(tr("你收到了%1条即时消息")).arg(1));

    //    QString sDefaultIcon = QString::fromStdString(ReadProfile (e_Runtime, "Corp", "Portrait", "0"));
    //    notification.setIconName(sDefaultIcon);

    QString sSoundState ="1";// QString::fromStdString(ReadProfile(e_UserConfig, "msgAudio", "IsOn", ""));
    if ("1" == sSoundState /*&& "CALL" != msgType*/) {
        // bool 通知声音，默认为空
        notification.setSound("/usr/share/rings/门铃.wav");
    }

    QString sShakeState = "0";//QString::fromStdString(ReadProfile(e_UserConfig, "msgShock", "IsOn", ""));

    if ("0" == sShakeState) {
        notification.setVibrationMode(CNotification::ForceQuietMode);
    }

    notification.setSopid("com.vrv.linkDood");
    notification.setUiAppId("linkDood");

    notificationService.sendNotification(notification);

    // 桌面角标数处理：
    // gGetAllUnreadMsgNum获取到的是已经写入数据库的未读消息总数
    CSystemBadge badge;
    badge.setValue("com.vrv.linkDood", "linkDood", 1);

    QTimer::singleShot(2000, this, SLOT(releaseWakelockSlot()));
}

void LinkDoodServiceThread::releaseWakelockSlot()
{
    qDebug() << "linkDood : " << Q_FUNC_INFO;
    m_pPowerManager->releaseWakelock();
}
