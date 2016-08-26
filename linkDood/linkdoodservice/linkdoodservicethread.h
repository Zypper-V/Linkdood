#ifndef LINKDOODSERVICETHREAD_H
#define LINKDOODSERVICETHREAD_H

#include <QObject>
#include <QMap>
class CSystemPowerManager;
class LinkDoodServiceThread : public QObject
{
    Q_OBJECT
public:
    explicit LinkDoodServiceThread(QObject *parent = 0);
    ~LinkDoodServiceThread();

signals:

public slots:
    void bcNotify(const QString senderId,
                  const QString msgType,
                  const QString content,
                  const QString msgId,
                  const QString sendTime,
                  const QString displayName,
                  const QString senderIconPath="",
                  const QString sessionType="",
                  int unReadNumber=1);
private slots:
    void releaseWakelockSlot();
   // void onRemoveNotification(const QString &updateId);
private:
    CSystemPowerManager * m_pPowerManager;
    QMap<QString,QString> mMapUppdateId;
};

#endif // LINKDOODSERVICETHREAD_H
