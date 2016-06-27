#ifndef CDOODORGITEM_H
#define CDOODORGITEM_H

#include <QObject>

class CDoodOrgItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit CDoodOrgItem(QObject *parent = 0);

    QString id() const;
    QString setId(const QString &data);

    QString name() const;
    QString setName(const QString &data);

signals:
    void idChanged();
    void nameChanged();

private:
    QString mId;
    QString mName;
};

#endif // CDOODORGITEM_H
