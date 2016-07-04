#ifndef CDOODEMOJIITEM_H
#define CDOODEMOJIITEM_H

#include <QObject>

class CDoodEmojiItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:
    explicit CDoodEmojiItem(QObject *parent = 0);

    QString name() const;
    QString setName(const QString &data);

    QString path() const;
    QString setPath(const QString &data);

signals:
      void nameChanged();
      void pathChanged();

public slots:
private:
    QString mName;
    QString mPath;
};

#endif // CDOODEMOJIITEM_H
