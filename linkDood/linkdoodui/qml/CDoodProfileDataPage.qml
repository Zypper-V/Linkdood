import QtQuick 2.0
import com.syberos.basewidgets 2.0

Rectangle{
    id:myProfilePage

    property color tipTextClr: "#777777"
    color:"#F2F2F2"

    anchors.fill: parent
    Column{
        spacing: 20
        width:parent.width
        Rectangle{
            width:parent.width
            height: 20
            color:"#F2F2F2"
        }
        Text{
            id:myProfileTip

            text:qsTr("个人信息")
            color:tipTextClr
            font.pixelSize: 30
            anchors{
                left:parent.left
                leftMargin: 30
            }
        }
        MouseArea{
            id:myProfileButton

            height: 180

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin:20

            Rectangle {
                id:rectBackground

                anchors.fill: parent
                color:"white"
                border.width: 1
                border.color: "#777777"
                radius: 10
                CDoodHeaderImage {
                    id: userIcon

                    anchors{
                        left: parent.left
                        leftMargin: 20
                        verticalCenter: parent.verticalCenter
                    }
                    width: 120
                    height: 120
                    radius: 10
                    headerColor: "white"
                    iconSource: userProfileManager.thumbAvatar !=="" ? "file://"+userProfileManager.thumbAvatar: "qrc:/res/headerDefault.png"

                }
                Text{
                    id:userName

                    text:userProfileManager.name
                    font.pixelSize: 30
                    anchors{
                        top:userIcon.top
                        topMargin: 20
                        left:userIcon.right
                        leftMargin: 10
                    }
                }
                Text{
                    id:userDD

                    text:qsTr("圆圆号：")+userProfileManager.nickId
                    font.pixelSize: 24
                    anchors{
                        bottom: parent.bottom
                        bottomMargin: 40
                        left:userIcon.right
                        leftMargin: 10
                    }
                }
                Image {
                    id: arrowTip

                    source: "qrc:/res/arrow_icon.png"
                    anchors{
                        right: parent.right
                        rightMargin: 20
                        verticalCenter: parent.verticalCenter
                    }
                }
            }
            onPressed: rectBackground.color = "#cdcdcd"
            onReleased: rectBackground.color = "white"

            onClicked: {
                console.log("dsfdfvvvvvvvvvvvvvvvvvvvvvvvvv");
                pageStack.push(Qt.resolvedUrl("CDoodSettingProfileDataPage.qml"));
            }
        }

        //        Rectangle{
        //            color:"transparent"
        //            height: 150
        //            width:parent.width
        //        }

        Text{
            id:changepswTip

            text:qsTr("操作")
            color:tipTextClr
            font.pixelSize: 30
            anchors{
                left:parent.left
                leftMargin: 30
            }
        }
        Rectangle{
            id:changepsw

            border.width: 1
            border.color: "#777777"
            radius: 10
            color:"white"
            height: 100

            Text{
                text:qsTr("修改密码")
                font.pixelSize: 30
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: settingIcon.right
                anchors.leftMargin: 25
            }

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin:20
            Image {
                id: settingIcon
                source: "qrc:/res/personal_setting.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 30
            }

            Image {
                id: settingArrow
                source: "qrc:/res/arrow_icon.png"
                anchors{
                    right: parent.right
                    rightMargin: 20
                    verticalCenter: parent.verticalCenter
                }
            }
            MouseArea{
                anchors.fill: parent
                onPressed: changepsw.color = "#cdcdcd"
                onReleased: changepsw.color = "white"
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("CDoodChangePasswordPage.qml"));
                    console.log("setting clicked")
                }
            }
        }
        Rectangle{
            id: friendVeri

            border.width: 1
            border.color: "#777777"
            radius: 10
            color:"white"
            height: 100

            Text{
                text:qsTr("好友验证")
                font.pixelSize: 30
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: verifyIcon.right
                anchors.leftMargin: 25
            }
            Text {
                id: verifyMethodText
                text: verify()
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: verifyArrow.left
                anchors.rightMargin: 30
                font.pixelSize: 24
                function verify(){
                    if(userProfileManager.verifytype === 1)
                        return "需要验证信息";
                    else if(userProfileManager.verifytype === 2)
                        return "不允许任何人添加";
                    else if(userProfileManager.verifytype === 3)
                        return "允许任何人添加";
                }
            }

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin:20
            Image {
                id: verifyIcon
                source: "qrc:/res/personal_setting.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 30
            }

            Image {
                id: verifyArrow
                source: "qrc:/res/arrow_icon.png"
                anchors{
                    right: parent.right
                    rightMargin: 20
                    verticalCenter: parent.verticalCenter
                }
            }
            MouseArea{
                anchors.fill: parent
                onPressed: friendVeri.color = "#cdcdcd"
                onReleased: friendVeri.color = "white"
                onClicked: {
                    sexListDialog.select(sexListDialog.initSelect(),true);
                    sexListDialog.show();
                }
            }
        }
        Rectangle{
            id:rectVer

            border.width: 1
            border.color: "#777777"
            radius: 10
            color:"white"
            height: 100

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin:20
            Image {
                id: verifyTip
                source: "qrc:/res/personal_setting.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 30
            }
            Text{
                anchors.left: verifyTip.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter

                font.pixelSize: 30
                text:qsTr("版本")
            }
            Text{
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 30

                text:userProfileManager.appVer;
            }
        }

        Text{
            id:loginoutTip

            text:qsTr("退出登录")
            color:tipTextClr
            font.pixelSize: 30
            anchors{
                left:parent.left
                leftMargin: 30
            }
        }
        Rectangle{
            id:btnLoginout

            border.width: 1
            border.color: "#777777"
            radius: 10
            color:"white"
            height: 100

            Text{
                text:qsTr("退出登录")
                font.pixelSize: 30
                color:"red"
                anchors.centerIn: parent
            }

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin:20
            MouseArea{
                anchors.fill: parent
                onPressed: btnLoginout.color = "#cdcdcd"
                onReleased: btnLoginout.color = "white"
                onClicked: {
                    alertDialog.show();
                    console.log("sdddddddddddddddddddddddddddd")
                }
            }
        }
    }

    CDialog {
        id: alertDialog

        titleText: qsTr("提示")
        messageText: qsTr("是否确认注销用户")+userProfileManager.name+"？"
        onAccepted: {
            console.log("ok")
            loginManager.logout();
            loadingDialog.show();
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
    CIndicatorDialog {
        id:loadingDialog
        messageText: os.i18n.ctr(qsTr("正在注销..."))
    }
    Connections {
        target: loginManager
        onLoginoutRelust:{
            loadingDialog.hide();
            if(!loginManager.isStartupByUrl()){
                resetUiModelData();
                pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
            }
        }
    }

    CDoodListDialog{
        id: sexListDialog

        property  int  currentIndex: 0
        titleText: qsTr("验证方式")
        onNotifySelectedItems:{
            console.log("xxxxxxxxx:"+model[curIndex]);
            userProfileManager.setPrivateSettingVerify(curIndex+1);
            sexListDialog.currentIndex = curIndex;
        }
        Component.onCompleted: {
            model = [qsTr("需要验证信息"),qsTr("不允许任何人添加"),qsTr("允许任何人添加")]
        }
        function initSelect(){

            return userProfileManager.verifytype-1;
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
}
