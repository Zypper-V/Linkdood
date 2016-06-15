#ifndef SYSMSGCONTROLER_H
#define SYSMSGCONTROLER_H

#endif // SYSMSGCONTROLER_H
#include<ISysMsgObserver.h>
class SysMsgControler:public ISysMsgObserver
{
    SysMsgControler();
    ~SysMsgControler();
    void onSysMessageNotice(SysMsg& msg);
};
