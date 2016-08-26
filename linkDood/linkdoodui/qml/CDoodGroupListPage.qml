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
    Connections {
        target: groupManager
        onRemoveGroupResult: {
            loadingDialog.hide();
            gToast.requestToast(result,"","");
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
                        onPressAndHold: {
                          if(model.modelData.isLeader){
                              menu1.groupid=model.modelData.id;
                              menu1.groupname=model.modelData.name;
                              menu1.isLeader="1";
                              menu1.show();
                          }
                          else{
                              menu1.groupid=model.modelData.id;
                              menu1.groupname=model.modelData.name;
                              menu1.isLeader="";
                              menu1.show();
                          }
                        }

                        onPressed: {
                            background.color = "#cdcdcd"

                        }
                        onClicked: {
                            chatManager.switchToChatPage(model.modelData.id,model.modelData.name,"2","0",0,"");
                            //                            loadingDialog.show();
                            console.log(model.modelData.id,"lixinlixin");

                        }

                        onReleased: {
                            background.color = "white"

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
                                anchors.rightMargin: 50
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
                            Image {
                                id: leader
                                anchors.right: parent.right
                                anchors.top: parent.top
                                anchors.topMargin: 20
                                anchors.rightMargin: 20
                                visible: model.modelData.isLeader
                                source: "qrc:/res/lv_crown.png"
                            }
                            CLine {
                                //                            width: parent.width
                                width: 1
                                anchors.left: parent.left
                                //                                color:"#cdcdcd"
                                anchors.leftMargin: 25
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
    CDialog {
        property string tip: ""
        property string operate: ""
        property string groupid: ""
        id: alertDialog

        titleText: qsTr("提示")
        messageText: alertDialog.tip
        onAccepted: {
            groupManager.removeGroup(alertDialog.operate,alertDialog.groupid);
            loadingDialog.show();
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
    CDoodPopWndLayer{
        id:menu1
        property string groupname: ""
        property string groupid: ""
        property string isLeader: ""
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
                leftText: menu1.isLeader===""?"退出该群":"解散该群"
                radius: 4

                anchors.top: line1.bottom
                anchors.topMargin: 10
                showLine:false
                onClicked: {
                    menu1.hide();
                    alertDialog.groupid=menu1.groupid;
                    if(menu1.isLeader===""){
                        alertDialog.tip="是否退出群:"+menu1.groupname;
                        alertDialog.operate="2";
                    }
                    else{
                        alertDialog.tip="是否解散群:"+menu1.groupname;
                        alertDialog.operate="1";
                    }

                    alertDialog.show();
                }
            }
        }
        onBackKeyReleased: {
            console.log("11111111111111111111111111111111111")
            menu1.hide();
        }
        onOutAreaClicked: {
            console.log("222222222222222222222222222222")
            menu1.hide();
        }
    }
    CIndicatorDialog {
        id:loadingDialog
        messageText: os.i18n.ctr(qsTr("正在操作中..."))
        onBackKeyReleased: {
            loadingDialog.hide();
        }
    }
}

