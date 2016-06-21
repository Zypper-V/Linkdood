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

public slots:
    void bcNotify(const QString &senderId,
                  const QString &msgType,
                  const QString &content,
                  const QString &msgId,
                  const QString &sendTime,
                  const QString &displayName,
                  const QString &senderIconPath,
                  const QString &sessionType,
                  int unReadNumber);
private slots:
    void releaseWakelockSlot();

private:
    CSystemPowerManager * m_pPowerManager;
};

#endif // LINKDOODSERVICETHREAD_H
