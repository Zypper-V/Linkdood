import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: verifycodePage



    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            verifycodePage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(verifycodePage.statusBarHoldEnabled)
            verifycodePage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }

    Connections {
        target: loginManager
        onGetVerifyImgResult: {
            console.log("onChangePasswordResult !!!!")
            if(result!=""){
            gToast.requestToast(result,"","");
            }
            loadingDialog.hide();
            if(judge==="")
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
                IconButton{
                    id:btnBack
                    anchors.left: parent.left
                    anchors.leftMargin: 30
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        pageStack.replace(Qt.resolvedUrl("CDoodMailLoginPage.qml"), "", true);
                    }
                }
                Text{
                    id:titleText

                    anchors.centerIn: parent

                    text:qsTr("验证码")
                    color:"white"
                    font.pixelSize: 36
                }
            }

            Rectangle {
                id: inputBackGround

                anchors.top: titleBackground.bottom
                height: 404
                anchors.topMargin: 150
                anchors.left: parent.left
                anchors.right:parent.right
                anchors.leftMargin: 16
                anchors.rightMargin:16
                border.color: "#777777"
                border.width: 1
                radius:10
                color: "#ffffff"
            }
            Image{
                id:verifyimg
                property int nCount: loginManager.nVerifyImgCount
                anchors.top:inputBackGround.top
                anchors.left: inputBackGround.left
                anchors.leftMargin: 120
                anchors.topMargin: 100
                height:150
                width: 150+loginManager.nVerifyImgCount
                sourceSize.width: 150+loginManager.nVerifyImgCount
                sourceSize.height:150
                source:loginManager.verifyImg
            }
            CButton{
                id:cantsee
                anchors.verticalCenter:verifyimg.verticalCenter
                anchors.rightMargin: 20
                anchors.right: inputBackGround.right
                height:50
                width:200
                text:os.i18n.ctr(qsTr("看不清,下一张"))
                textColor:  "#32c2fe"
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#f2f2f2"
                    radius: 10
                }
                onClicked: {
                    loadingDialog.show();
                    loginManager.getVerifyImg("","");
                }
            }
            CLine {
                id:line
                width: inputBackGround.width
                anchors.bottom: inputBackGround.bottom
                anchors.bottomMargin: 100
                anchors.left: inputBackGround.left
                z: parent.z+2
            }

            Text{
                id:verifycodetip

                anchors{
                    top:line.bottom
                    topMargin: 40
                    left:inputBackGround.left
                    leftMargin: 20
                }
                width: 100
                text:qsTr("输入验证码:")
                font.pixelSize: 30
            }
            CLineEdit {
                id: verifycodeEdit
                anchors.top:line.bottom
                anchors.topMargin: 18
                anchors.left: verifycodetip.right
                anchors.leftMargin: 65
                width: 350
                passwordLabelEnabled: false
                //                textLeftMargin: 50
                clip: true
                textColor:"#787777"
                font.pixelSize: 32
                //                inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/
                //                text: "111111"
            }
            CButton{
                id:verify
                anchors.top:line.bottom
                anchors.topMargin: 30
                anchors.rightMargin: 20
                anchors.right: inputBackGround.right
                height:50
                width:200
                text:os.i18n.ctr(qsTr("验证"))
                textColor:  "#32c2fe"
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#f2f2f2"
                    radius: 10
                }
                onClicked: {
                    if(verifycodeEdit.text==""){
                        gToast.requestToast("请输入验证码","","");
                    }
                    else{
                        loadingDialog.show();
                        loginManager.getVerifyImg("",verifycodeEdit.text);
                    }
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
