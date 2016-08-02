import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: activateaccountPage

    property string  server
    property string  name
    property string  password


    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            activateaccountPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(activateaccountPage.statusBarHoldEnabled)
            activateaccountPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }

    Connections {
        target: loginManager

        //        onInputRootTabView: {
        //            console.log("onInputRootTabView !!!!")
        //            pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
        //        }

        onChangePasswordResult: {
            console.log("onChangePasswordResult !!!!")
            gToast.requestToast(result,"","");
            loadingDialog.hide();
            if(result==="修改成功")
            {
                pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
            }
        }
    }

    contentAreaItem: Item {
        anchors.fill :parent
        Rectangle {
            id: loginBackground
            anchors.fill: parent
            color: "#f2f2f2"
        }

        Flickable{
            id: filckableInput
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            contentHeight: parent.height

            Connections {
                target: gInputContext
                onSoftwareInputPanelVisibleChanged: {
                    if(gInputContext.softwareInputPanelVisible) {
                        filckableInput.contentHeight = filckableInput.parent.height + 200
                    } else {
                        filckableInput.contentHeight = filckableInput.parent.height
                    }
                }
            }

            Rectangle{
                id:titleBackground

                anchors.top: parent.top
                anchors.left: parent.left

                width:parent.width
                height: 86
                color:"#003658"
                Text{
                    id:titleText

                    anchors.centerIn: parent

                    text:qsTr("激活帐号")
                    color:"white"
                    font.pixelSize: 36
                }
            }

            Rectangle {
                id: inputBackGround

                anchors.top: titleBackground.bottom
                height: 303
                anchors.topMargin: 16
                anchors.left: parent.left
                anchors.right:parent.right
                anchors.leftMargin: 16
                anchors.rightMargin:16
                border.color: "#777777"
                border.width: 1
                radius:10
                color: "#ffffff"
            }
            Text{
                id:srvTip

                anchors{
                    left:inputBackGround.left
                    leftMargin: 25
                    verticalCenter: srvLineEdit.verticalCenter
                }
                width:100
                text:qsTr("旧密码")
                font.pixelSize: 30
            }

            CLineEdit {
                id: srvLineEdit
                anchors.top: inputBackGround.top
                anchors.left: srvTip.right
                anchors.right:inputBackGround.right
                anchors.leftMargin: 50/*srvLineEdit.text ==="" ? 50 : 0*/

                height: 101
                passwordLabelEnabled: false
                textLeftMargin: 50
                clip: true

                //              horizontalAlignment: srvLineEdit.text ==="" ? TextInput.AlignLeft: TextInput.AlignHCenter
                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入旧密码"))

                inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/

                onTextChanged: {
                    passWordEdit.text = ""

                    if(activateaccountPage.state !== "hidden") {
                        activateaccountPage.state = "hidden"
                    }
                }
            }
            CLine {
                width: inputBackGround.width
                anchors.top: srvLineEdit.bottom
                anchors.left:inputBackGround.left
                z: parent.z+2
            }
            Text{
                id:userTip

                anchors{
                    left:inputBackGround.left
                    leftMargin: 25
                    verticalCenter: userLineEdit.verticalCenter
                }
                width:100
                text:qsTr("新密码")
                font.pixelSize: 30
            }

            CLineEdit {
                id: userLineEdit
                anchors.top: srvLineEdit.bottom
                anchors.left: userTip.right
                anchors.right:inputBackGround.right
                anchors.leftMargin: 50/*srvLineEdit.text ==="" ? 50 : 0*/

                height: 101
                passwordLabelEnabled: false
                echoMode: TextInput.Password
                textLeftMargin: 50
                clip: true

                //              horizontalAlignment: srvLineEdit.text ==="" ? TextInput.AlignLeft: TextInput.AlignHCenter
                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入新密码"))

                inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/

                onTextChanged: {
                    passWordEdit.text = ""

                    if(activateaccountPage.state !== "hidden") {
                        activateaccountPage.state = "hidden"
                    }
                }
            }
            CLine {
                width: inputBackGround.width
                anchors.top: userLineEdit.bottom
                anchors.left:inputBackGround.left
                z: parent.z+2
            }

            Text{
                id:srvPwd

                anchors{
                    left:inputBackGround.left
                    leftMargin: 25
                    verticalCenter: passWordEdit.verticalCenter
                }
                width: 100
                text:qsTr("确认新密码")
                font.pixelSize: 30
            }

            CLineEdit {
                id: passWordEdit
                anchors.top: userLineEdit.bottom
                anchors.left: srvPwd.right
                anchors.right:inputBackGround.right
                anchors.leftMargin: 50/*srvLineEdit.text ==="" ? 50 : 0*/

                height: 101
                passwordLabelEnabled: false
                echoMode: TextInput.Password
                textLeftMargin: 50
                clip: true

                //              horizontalAlignment: srvLineEdit.text ==="" ? TextInput.AlignLeft: TextInput.AlignHCenter
                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("请输入新密码"))

                inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/
                //                text: "111111"
            }

            CButton {
                id: loginButton

                anchors.top: inputBackGround.bottom
                anchors.topMargin: 19
                anchors.horizontalCenter: parent.horizontalCenter
                height:121
                width:680

                opacity : pressed ? 1: (userLineEdit.text .trim()==="" || passWordEdit.text.trim() ==="" ? 0.5 : 1)
                text:os.i18n.ctr(qsTr("激活帐号"))
                textColor:  "#ffffff"

                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#32c2fe"
                    radius: 10
                }

                onClicked: {
                    console.log("login onClicked !!!")
                    if(userLineEdit.text ==="" || passWordEdit.text ==="")
                        return;
                    if(userLineEdit.text!==passWordEdit.text) {
                        gToast.requestToast("两次输入的新密码不一致","","");
                        return
                    }

                    if(userLineEdit.text === "") {
                        userLineEdit.focus = true
                        gToast.requestToast("旧密码不能为空","","");

                    } else if(passWordEdit.text === "") {
                        passWordEdit.focus = true
                        gToast.requestToast("新密码不能为空","","");
                    } else {
                        loadingDialog.show();
                        console.log("changepassword onClicked !!!")
                        loginManager.changepassword(srvLineEdit.text, userLineEdit.text);
                    }
                }

                Behavior on opacity {
                    PropertyAnimation { duration: 200 }
                }
            }

            CIndicatorDialog {
                id:loadingDialog
                //            indicatorDirection: Qt.Horizontal
                messageText: os.i18n.ctr(qsTr("正在处理中..."))
            }

        }
    }
}


