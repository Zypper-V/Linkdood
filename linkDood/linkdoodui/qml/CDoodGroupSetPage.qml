import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: groupSetPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            groupSetPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(groupSetPage.statusBarHoldEnabled)
            groupSetPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    Connections {
        target: groupManager
        onRemoveGroupResult: {
            loadingDialog.hide();
            gToast.requestToast(result,"","");
            pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
            //           pageStack.pop();
        }
        onGetGroupFileListResult:{
            loadingDialog.hide();
            pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
        }
    }
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
                    memberManager.clearMemberList();
                    pageStack.pop();
                }
            }
            Text{
                text:qsTr("群设置")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
        }

        Rectangle{
            id:groupIcon
            anchors.left:parent.left
            anchors.top:titleBackground.bottom
            anchors.topMargin: 30
            anchors.leftMargin: 40
            width: 90
            height: 90
            border.width: 1
            radius: 20
            MouseArea{
                anchors.fill: parent
                onPressed: {
                    console.log(groupManager.thumbAvatar);
                    groupManager.getGroupFileList(groupManager.id);
                }
            }

            Image{

                anchors.fill: parent

//                anchors.centerIn: parent
//                width: parent.width-1
//                height: parent.height-1
                source: groupManager.thumbAvatar===""?"qrc:/res/group_icon.png":"file:///data/data/com.vrv.linkDood/public/head/"+groupManager.thumbAvatar
            }
        }

        Text{
            id:groupName
            font.pixelSize: 32
            anchors.left:groupIcon.right
            anchors.leftMargin: 30
            anchors.top:titleBackground.bottom
            anchors.topMargin: 40
            color:"black"
            width:500
            elide: Text.ElideRight
            text:groupManager.name
        }
        Text{
            id:groupId
            font.pixelSize: 22
            anchors.left:groupIcon.right
            anchors.leftMargin: 30
            anchors.top:groupName.bottom
            anchors.topMargin: 15
            color:"black"
            text:groupManager.id
        }
        Rectangle {
            id:bascicBackground

            color:"white"
            border.width: 1
            border.color: "#cdcdcd"
            radius: 30
            height: 195

            anchors.top: parent.top
            anchors.topMargin: 225
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20

            UserProfileButton{
                id:allMember
                height: 90
                leftText: qsTr("群成员列表")
                editable:true
                anchors.top:parent.top
                anchors.topMargin: 7
                anchors.left:parent.left
                anchors.right: parent.right
                anchors.rightMargin: 7
                anchors.leftMargin: 7
                onClicked: {
                    memberManager.clearMemberList();
                    groupManager.getMemberList(groupManager.id);
                    pageStack.push(Qt.resolvedUrl("CDoodMemberListPage.qml"));
                    //                    loadingDialog.show();
                }
            }
            UserProfileButton{
                id:inviteMember
                height: 90
                leftText: qsTr("邀请群成员")
                anchors.left:parent.left
                anchors.right: parent.right
                anchors.rightMargin: 7
                anchors.leftMargin: 7
                editable:true
                showLine:false
                anchors.top: allMember.bottom
                onClicked: {
                    groupManager.setIsCreateGroup(false);
                    pageStack.push(Qt.resolvedUrl("CDoodGroupAddMemberPage.qml"));
                }
            }
        }
        Rectangle {
            id:groupinfoBackground

            color:"white"
            border.width: 1
            border.color: "#cdcdcd"
            radius: 30
            height: 382

            anchors.top: bascicBackground.bottom
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20

            UserProfileButton{
                id:group_name
                height: 90

                leftText: qsTr("群名称")
                editable:true
                rigthText:groupManager.name
                anchors.top:parent.top
                anchors.topMargin: 7
                anchors.left:parent.left
                anchors.right: parent.right
                anchors.rightMargin: 7
                anchors.leftMargin: 7
//                width:400
                onClicked: {
                    // TODO:
                }
            }
            UserProfileButton{
                id:groupbrief
                height: 90
                leftText: qsTr("群简介")
                rigthText: groupManager.brief===""?qsTr("未添加群简介"):groupManager.brief
                anchors.left:parent.left
                anchors.right: parent.right
                anchors.rightMargin: 7
                anchors.leftMargin: 7
                editable:true
                //                showLine:false
                anchors.top: group_name.bottom
                onClicked: {

                }
            }
            UserProfileButton{
                id:groupbull
                height: 90
                leftText: qsTr("群公告")
                rigthText:groupManager.bulletin===""?qsTr("未添加群公告"):groupManager.bulletin
                anchors.left:parent.left
                anchors.right: parent.right
                anchors.rightMargin: 7
                anchors.leftMargin: 7
                editable:true
//                showLine:false
                anchors.top: groupbrief.bottom
                onClicked: {

                }
            }
            UserProfileButton{
                id:groupFileList
                height: 90
                leftText: qsTr("查看群文件")
                anchors.left:parent.left
                anchors.right: parent.right
                anchors.rightMargin: 7
                anchors.leftMargin: 7
                editable:true
                showLine:false
                anchors.top: groupbull.bottom
                onClicked: {
                  groupManager.getGroupFileList(groupManager.id);
                    IndicatorDialog.show();
                }
            }
        }
        Rectangle{
            id:deletegroup

            border.width: 1
            border.color: "#777777"
            radius: 10
            color:"white"
            height: 100

            Text{
                text:groupManager.isGroupLeader===true?qsTr("解散该群"):qsTr("退出该群")
                font.pixelSize: 34
                color:"red"
                anchors.centerIn: parent
            }
            anchors.top:groupinfoBackground.bottom
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin:20
            MouseArea{
                anchors.fill: parent
                onPressed: deletegroup.color = "#cdcdcd"
                onReleased: deletegroup.color = "white"
                onClicked: {
//                    groupManager.removeGroup(groupManager.id);
                    if(groupManager.isGroupLeader){
                    alertDialog.operate="是否解散该群";
                    }
                    else{
                        alertDialog.operate="是否退出该群";
                    }

                    alertDialog.show();
                }
            }
        }
    }
    CIndicatorDialog {
        id:loadingDialog
        messageText: os.i18n.ctr(qsTr("正在操作中..."))
    }
    CDialog {
        property string operate: ""
        id: alertDialog

        titleText: qsTr("提示")
        messageText: alertDialog.operate
        onAccepted: {
           groupManager.removeGroup(groupManager.id);
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
}

