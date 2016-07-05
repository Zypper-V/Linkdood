#ifndef CDOODEMOJIMANAGER_H
#define CDOODEMOJIMANAGER_H

#include "cdoodlistmodel.h"
#include "linkdoodclient.h"


class CDoodEmojiItem;
class CDoodEmojiManager : public CDoodListModel
{
    Q_OBJECT
public:
    CDoodEmojiManager(LinkDoodClient *client = 0, int type = 0, QObject *parent = 0);
    Q_INVOKABLE void itemClicked(QString path);

signals:
    void signalEmojiChanged(QString path);

private:
    void loadEmoji(QString path);
    void clearData();
    int mType;
    LinkDoodClient *m_pClient;
    QMap<QString, QString>         mEmojiExplain;
    QMap<QString, CDoodEmojiItem*> mEmojiListMap;
    void initEmojiExplainMap();
};

#define		BAOBAO_DYNAMIC          QString::fromLocal8Bit("抱抱")
#define		CENGCENG_DYNAMIC	    QString::fromLocal8Bit("蹭蹭")
#define		CHIFAN_DYNAMIC		    QString::fromLocal8Bit("吃饭")
#define		DAKU_DYNAMIC	    	QString::fromLocal8Bit("大哭")
#define		HENG_DYNAMIC		    QString::fromLocal8Bit("哼")
#define		JIAYOU_DYNAMIC		    QString::fromLocal8Bit("加油")
#define		KOUBI_DYNAMIC		    QString::fromLocal8Bit("抠鼻")
#define		LIEPI_DYNAMIC	    	QString::fromLocal8Bit("雷劈")
#define		QINQIN_DYNAMIC		    QString::fromLocal8Bit("亲亲")
#define		SHUQIAN_DYNAMIC		    QString::fromLocal8Bit("数钱")

#define		SHUIJIAO_DYNAMIC	    QString::fromLocal8Bit("睡觉")
#define		WULIAO_DYNAMIC		    QString::fromLocal8Bit("无聊")
#define		XIEXIE_DYNAMIC		    QString::fromLocal8Bit("谢谢")
#define		ZAIJI_DYNAMIC		    QString::fromLocal8Bit("再见")
#define		ZHUAKUANG_DYNAMIC       QString::fromLocal8Bit("抓狂")
#define		CHOUMEI_DYNAMIC	    	QString::fromLocal8Bit("臭美")
#define		DAXIAO_DYNAMIC	     	QString::fromLocal8Bit("大笑")
#define		DIANTOU_DYNAMIC		    QString::fromLocal8Bit("点头")
#define		FEIJIALOU_DYNAMIC		QString::fromLocal8Bit("肥家喽")
#define		GANBEI_DYNAMIC		    QString::fromLocal8Bit("干杯")

#define		JICHENGGOU_DYNAMIC		QString::fromLocal8Bit("挤成狗")
#define		JIABANLOU_DYNAMIC		QString::fromLocal8Bit("加班啦")
#define		KAIHUILA_DYNAMIC		QString::fromLocal8Bit("开会啦")
#define		LAOTIANBAOYOU_DYNAMIC	QString::fromLocal8Bit("老天保佑")
#define		QIANDAO_DYNAMIC		    QString::fromLocal8Bit("签到")
#define		XINGHUI_DYNAMIC		    QString::fromLocal8Bit("幸会")
#define		YALISHANDA_DYNAMIC		QString::fromLocal8Bit("鸭梨山大")
#define		ZAN_DYNAMIC		        QString::fromLocal8Bit("赞")
#define		GUZHANG_DYNAMIC		    QString::fromLocal8Bit("鼓掌")

#endif // CDOODEMOJIMANAGER_H
