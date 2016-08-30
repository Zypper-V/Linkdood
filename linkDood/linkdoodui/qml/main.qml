import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPageStackWindow {
    id: mainPageView
    inputFactor: 0
    keyHandle:false

    onBackKey:{
        if(clearFocus()){
            event.accepted =true
            return
        }
        if(mainPageView.pageStack.depth > 1) {
            mainPageView.pageStack.pop();

        } else {
            winHide()
        }
    }

    Connections {
        target: gScreenInfo

        onMinimizedChanged: {
            loginManager.setWindowFocus(!gScreenInfo.minimized)
        }
    }

    Keys.onReleased:{
        if (event.key === Qt.Key_Home) {
            winHide();
        }
    }

    initialPage:CPage{
        id: startPage
        anchors.fill: parent
        orientationLock: CPageOrientation.LockPortrait

        onStateChanged: {
            if (status == CPageStatus.WillShow) {
                gScreenInfo.setWindowProperty("STATUSBAR_VISIBLE",true)
                gScreenInfo.setWindowProperty("STATUSBAR_STYLE","transBlack")
            } else if (status == CPageStatus.Show) {
            }
        }
    }

    Component.onCompleted: {
        //loginManager.getLoginHistory();
        pageStack.replace(Qt.resolvedUrl("CDoodWelcomePage.qml"), "", true);
    }
    Connections{
        target: userProfileManager
        onConnectChanged:{
            if(flag === ""){
               loadingDialog.hide();
            }
            else{
                var code = loginManager.getAppLoginStatus();
                if(code ===1){
                    loadingDialog.flag=flag;
                    loadingDialog.show();
                }


            }
        }
    }
    Connections{
        target: loginManager
        onTextPareams:{
            //gToast.requestToast(param,"","");
        }

        onSwitchLoginByUrl:{
            //gToast.requestToast("switchto B","","");
            pageStack.push(Qt.resolvedUrl("CDoodWelcomePage.qml"));
            loginManager.logout();
        }
        onSwitchChatPageByUrl:{
            sessionListManager.getChatList();
            contactManager.getContactList();
            userProfileManager.getAccountInfo();
            groupManager.getGroupList();
            enterpriseManager.setFarOrg();
            orgManager.resetOrgList();
            chatManager.clearList();
            pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
        }

        onSiwtchLoginout:{
            loadingDialog.hide();
            //var tmp ="loginout:"+loginManager.isStartupByUrl()+"->:"+loginManager.loginInfoByUrl();
            //gToast.requestToast(tmp,"","");
            resetUiModelData();
            gToast.requestToast("正在登录","","");
            loginManager.loginByUrl();
        }
        onElsewhereLogin: {
            console.log("main.qml  onElsewhereLogin !!!")
            resetUiModelData();
            pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
            menu1.show();
        }
        onServiceRestart:{

            if(loginManager.isStartupByUrl() === false){
                loginManager.getLoginHistory();
                pageStack.replace(Qt.resolvedUrl("CDoodWelcomePage.qml"), "", true);
            }
        }
        onLoginSucceeded: {
            console.log("onLoginSuccess !!!!")
            if(loginManager.isStartupByUrl()){
                sessionListManager.getChatList();
                enterpriseManager.setFarOrg();
                orgManager.resetOrgList();
                pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
                loginManager.setIsStartupByUrl(false);
            }
        }
        onLoginFailed: {
            console.log("onLoginFailed !!!!")
            if(loginManager.isStartupByUrl()){
                gToast.requestToast(err,"","");
                if(err==="首次登录，请激活帐号")
                {
                    pageStack.replace(Qt.resolvedUrl("CDoodActivateAccountPage.qml"), "", true);
                }else if(err==="输入错误次数过多,请输入验证码")
                {
                    pageStack.replace(Qt.resolvedUrl("CDoodVerifyImgPage.qml"), "", true);
                }else{
                    loginManager.setIsStartupByUrl(false);
                    pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
                }
            }
        }
    }
    function resetUiModelData(){
        contactManager.clearChatList();
        sessionListManager.clearChatList();
        loginManager.setAppLoginStatus(0);
        enterpriseManager.setFarOrg();
        orgManager.resetOrgList();
        chatManager.clearList()
        userProfileManager.clearData();
    }

    CDoodPopWndLayer{
        id:menu1
        contentItemBackGroundOpacity:0.73
        contentItem:Rectangle{

            color: "white"
            radius: 10
            width:489
            height: 260
            Text{
                id:title1

                text:qsTr("提 示")
                font.pixelSize: 24
                color:"#cdcdcd"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
                height: 40
            }
            CLine{
                id:line1

                anchors.top:title1.bottom
                height: 2
            }
            Text{
                id:title2

                text:qsTr("您的帐号已经在别处登陆!")
                font.pixelSize: 36
                color:"#cdcdcd"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: line1.bottom
                anchors.topMargin: 20
                height: 90
            }
            CLine{
                id:line2

                anchors.top:title2.bottom
                height: 2
            }
            Rectangle{
                id:sure
                anchors.top: line2.bottom
                width: 480
                anchors.horizontalCenter: parent.horizontalCenter
                height:60
                Text{
                    font.pixelSize:28
                    color:"#cdcdcd"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    text:qsTr("确  定")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        menu1.hide();
                    }
                }
            }
        }
    }
    CIndicatorDialog {
        id:loadingDialog

//        canceledOnBackKeyReleased:true
        property string flag: ""
        messageText: os.i18n.ctr(flag)
    }
}
