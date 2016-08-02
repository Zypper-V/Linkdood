import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: groupListPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            groupListPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(groupListPage.statusBarHoldEnabled)
            groupListPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    //    Connections {
    //        target: memberManager
    //        onGetMemberListResult: {
    //            loadingDialog.hide();
    //            if(result=="获取成员列表失败"){
    //                gToast.requestToast(result,"","");
    //            }
    //            else{
    //                pageStack.push(Qt.resolvedUrl("CDoodGroupSetPage.qml"));
    ////            pageStack.push(Qt.resolvedUrl("CDoodMemberListPage.qml"));
    //            }
    //        }
    //    }
    //    Connections {
    //        target: groupManager
    //        onGetGroupInfoResult: {
    //        loadingDialog.hide();
    //        groupManager.getMemberList(groupManager.id);
    //        pageStack.push(Qt.resolvedUrl("CDoodGroupSetPage.qml"));
    //            //            var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodChatPage.qml"),"CDoodChatPage");
    //        }
    //    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: userdataBackground
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
                    pageStack.pop();
                }
            }
            Text{
                text:qsTr("群")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
        }
        Rectangle{
            anchors.top: titleBackground.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            color:"#F2F2F2"

            ListView {
                id: orgListView
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom



                clip: true
                model: groupManager
                section.property: "modelData.sectionKey"
                section.criteria: ViewSection.FullString
                section.delegate: Rectangle {
                    width: groupListPage.width
                    height: 35
                    color: "#F2F2F2"

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 25
                        anchors.verticalCenter: parent.verticalCenter
                        text: section
                        font.pixelSize: 22
                        color: "#333333"
                        onTextChanged: {
                            console.log("xxxxxx:"+text)
                        }
                    }
                }

                delegate:Item {
                    id:contactListDelegate

                    width: parent.width
                    height: 100

                    MouseArea {
                        anchors.fill: parent

                        onPressed: {
                            background.color = "#cdcdcd"

                        }

                        onReleased: {
                            background.color = "white"
                            memberManager.clearMemberList();
                            chatManager.switchToChatPage(model.modelData.id,model.modelData.name,"2",0,"");
                            //                            loadingDialog.show();
                            console.log(model.modelData.id,"lixinlixin");

                        }

                        onCanceled: {
                            background.color = "white"
                        }
                    }

                    Rectangle {
                        width: contactListDelegate.width
                        height: contactListDelegate.height
                        color:"white"
                        Rectangle {
                            id : background
                            anchors.fill: parent
                            color:"white"
                            CDoodHeaderImage{
                                id: headPortraitImage
                                anchors.left: parent.left
                                anchors.leftMargin: 25
                                anchors.topMargin: 16
                                anchors.verticalCenter: parent.verticalCenter
                                width: 90
                                height: 90
                                radius: 6

                                iconSource:setIcon("2",model.modelData.thumbAvatar)

                            }
                            Text {
                                id: nameText
                                anchors.left: headPortraitImage.right
                                anchors.leftMargin: 30
                                anchors.rightMargin: 20
                                anchors.top: parent.top
                                anchors.topMargin: 20
                                font.pixelSize: 26
                                height: 26
                                clip: true
                                width:550
                                elide: Text.ElideRight
                                color: "black"
                                verticalAlignment: Text.AlignVCenter

                                text: model.modelData.name
                            }
                            CLine {
                                //                            width: parent.width
                                width: 1
                                anchors.left: parent.left
                                //                                color:"#cdcdcd"
                                //                        anchors.leftMargin: 150
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                                z: parent.z
                            }
                        }
                    }
                }
            }
        }
    }
    CIndicatorDialog {
        id:loadingDialog
        messageText: os.i18n.ctr(qsTr("正在获取中..."))
    }
}

