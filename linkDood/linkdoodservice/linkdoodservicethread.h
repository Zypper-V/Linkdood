#ifndef LINKDOODSERVICETHREAD_H
#define LINKDOODSERVICETHREAD_H

#include <QObject>

class CSystemPowerManager;
class LinkDoodServiceThread : public QObject
{
    Q_OBJECT
public:
    explicit LinkDoodServiceThread(QObject *parent = 0);
    ~LinkDoodServiceThread();

signals:

public:
    void bcNotify(const QString &senderId="1242",
                  const QString &msgType="2",
                  const QString &content="24234",
                  const QString &msgId="2424",
                  const QString &sendTime="",
                  const QString &displayName="rwre",
                  const QString &senderIconPath="",
                  const QString &sessionType="rerer",
                  int unReadNumber=3);
private slots:
    void releaseWakelockSlot();

private:
    CSystemPowerManager * m_pPowerManager;
};

#endif // LINKDOODSERVICETHREAD_H
