import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: sysMsgPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            sysMsgPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(sysMsgPage.statusBarHoldEnabled)
            sysMsgPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }else if(status === CPageStatus.Hide){
            console.log("2222222222222:hide")
            sysmsgManager.clearListView();
            sessionListManager.exitSysMsgPage();
        }
    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: sysMsgBackground
            anchors.fill: parent
            color: "#f2f2f2"
        }
        Rectangle{
            id: titleBackground

            color:"#003953"
            width:parent.width
            height:86
            anchors{
                top:parent.top
                left:parent.left
            }
            IconButton{
                id:btnBack
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    sysmsgManager.clearListView();
                    sessionListManager.exitSysMsgPage();
                    pageStack.pop();
                }
            }
            Text{
                text:qsTr("系统消息")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
            CButton{
                id:surbutton
                anchors.right:parent.right
                anchors.rightMargin: 5
                visible: sysmsgManager.isSysMsg
                width: 200
                anchors.verticalCenter: parent.verticalCenter
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#003953"
                    radius: 10
                }
                onClicked: {
                    alertDialog.show();
                }
                Text{
                    text:qsTr("清空")
                    color:"white"
                    font.pixelSize: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                }
            }
        }
        Rectangle{
            anchors.top: titleBackground.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            color:"#F2F2F2"
            ListView {
                id: sysMsgListView
                clip: true
                model: sysmsgManager
                spacing:20

                anchors.fill: parent
                anchors.topMargin: 30

                delegate:Item {
                    id:sysMsgListDelegate

                    width: parent.width
                    height: 180

                    MouseArea {
                        anchors.fill: parent
                        onPressAndHold: {
                            menu.id=model.modelData.msgid;
                            menu.msgtype=model.modelData.msgType;
                              menu.show();
                        }
                        onPressed: {
                            delegateBk.color = "#cdcdcd"
                        }
                        onReleased: {
                            delegateBk.color = "white"
                        }
                        onCanceled: {
                            delegateBk.color = "white"
                        }
                        onClicked: {
                            gToast.requestToast(model.modelData.info,"","");
                        }
                    }

                    Rectangle {
                        id:delegateBk

                        width: sysMsgListDelegate.width - 40
                        height: sysMsgListDelegate.height
                        radius: 10
                        color:"white"

                        anchors.centerIn: parent

                        Rectangle {
                            id : background

                            color:"transparent"
                            anchors.fill: parent
                            anchors.margins: 20

                            Text{
                                id:msgText
                                text:model.modelData.msgtypeText
                                font.pixelSize: 30
                                color:"#777777"

                                anchors.top: parent.top
                                anchors.left: parent.left
                            }
                            Text{
                                id:msgTime
                                text:model.modelData.time
                                font.pixelSize: 30
                                color:"#777777"

                                anchors.top: parent.top
                                anchors.right: parent.right
                            }
                            CLine{
                                id:line
                                anchors.top: msgText.bottom
                                anchors.topMargin: 8
                            }

                            Text{
                                id:msgIsReaded
                                text:model.modelData.respons
                                font.pixelSize: 28
                                color:"#777777"

                                anchors.verticalCenter: parent.verticalCenter
                                anchors.right: parent.right
                            }

                            CDoodHeaderImage {
                                id: headPortraitImage

                                width: 90
                                height: 90
                                radius: 6
                                name:""
                                iconSource: setIcon(getType(),model.modelData.thumbAvatar);//"qrc:/res/group_icon.png"/*"file://"+ model.modelData.thumbAvatar*/

                                anchors.left: parent.left
                                anchors.top:line.bottom
                                anchors.topMargin: 10
                                function getType(){
                                    if(model.modelData.msgType===1 ||model.modelData.msgType===2){
                                        return "1";
                                    }else{
                                        return "2";
                                    }
                                }
                            }
                            Text{
                                id:msgUserName
                                text:model.modelData.name
                                font.pixelSize: 30

                                anchors.left: headPortraitImage.right
                                anchors.leftMargin: 20
                                anchors.right: parent.right
                                elide: Text.ElideRight
                                anchors.top: headPortraitImage.top
                                anchors.topMargin: 10
                            }
                            Text{
                                id:msgUserInfo
                                text:model.modelData.info
                                font.pixelSize: 26
                                color:"#777777"
                                elide: Text.ElideRight

                                anchors.left: headPortraitImage.right
                                anchors.leftMargin: 20
                                anchors.right: parent.right
                                anchors.top: msgUserName.bottom
                                anchors.topMargin: 10
                            }

                            CButton {
                                id: btnAgree

                                height:50
                                width:70

                                text:os.i18n.ctr(qsTr("同意"))
                                textColor:  "#ffffff"
                                visible: model.modelData.isShowButton

                                anchors.right: parent.right
                                anchors.top: msgUserName.top
                                anchors.topMargin: 10
                                backgroundComponent: Rectangle {
                                    anchors.fill: parent
                                    color:"#32c2fe"
                                    radius: 10
                                    opacity : !btnAgree.pressed ? 1: 0.5
                                }
                                Behavior on opacity {
                                    PropertyAnimation { duration: 200 }
                                }
                                onClicked: {
                                    sysmsgManager.clickItem(model.modelData.msgid,true);
                                }
                            }
                            CButton {
                                id: btnIg

                                height:btnAgree.height
                                width:btnAgree.width

                                text:os.i18n.ctr(qsTr("拒绝"))
                                textColor:  "#ffffff"
                                visible: model.modelData.isShowButton

                                anchors.right: btnAgree.left
                                anchors.rightMargin: 20
                                anchors.top: msgUserName.top
                                anchors.topMargin: 10
                                backgroundComponent: Rectangle {
                                    anchors.fill: parent
                                    color:"#32c2fe"
                                    radius: 10
                                    opacity : !btnIg.pressed ? 1: 0.5
                                }
                                Behavior on opacity {
                                    PropertyAnimation { duration: 200 }
                                }
                                onClicked: {
                                    sysmsgManager.clickItem(model.modelData.msgid,false);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    CDoodPopWndLayer{
        id:menu
        property string id: ""
        property string msgtype: ""
        contentItemBackGroundOpacity:0.73
        contentItem:Rectangle{

            color: "white"
            radius: 10
            width:489
            height: 190
            Text{
                id:title1

                text:qsTr("提示")
                font.pixelSize: 36
                color:"#333333"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
            }
            CLine{
                id:line1

                anchors.top:title1.bottom
                anchors.topMargin: 10
                height: 2
            }
            UserProfileButton{
                id:btntran1

                width:parent.width
                height: 100
                leftText: "删除此系统消息"
                radius: 4

                anchors.top: line1.bottom
                anchors.topMargin: 10
                showLine:false
                onClicked: {
                    menu.hide();
                    sysmsgManager.removeSysMessage(menu.msgtype,menu.id);
                }
            }
        }
        onBackKeyReleased: {
            console.log("11111111111111111111111111111111111")
            menu.hide();
        }
        onOutAreaClicked: {
            console.log("222222222222222222222222222222")
            menu.hide();
        }
    }
    CDialog {
        id: alertDialog

        titleText: qsTr("提示")
        messageText: "是否删除所有系统消息"
        onAccepted: {
           sysmsgManager.removeSysMessage("0","123");
            alertDialog.hide();
        }
        onCanceled: {
            alertDialog.hide();
            console.log("onCanceled")
        }
    }
}

