import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: fileViewPage
    onStatusChanged: {
//        if (status === CPageStatus.WillShow) {
//            sysMsgPage.statusBarHoldEnabled = true
//            gScreenInfo.setStatusBar(sysMsgPage.statusBarHoldEnabled)
//            sysMsgPage.statusBarHoldItemColor = "#edf0f0"
//            gScreenInfo.setStatusBarStyle("black")
//        }
    }
    Connections {
        target: groupManager
        onAddGroupResult: {
            console.log("!!!!")
           gToast.requestToast(result,"","");
            pageStack.replace(Qt.resolvedUrl("CDoodGroupListPage.qml"), "", true);
        }
    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: addGroupBackGround
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
                text:qsTr("群资料")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
        }
        Rectangle{
            color: "transparent"
            id: groupdatapic
            anchors.top:titleBackground.bottom
            anchors.left:parent.left
            height:200
            width: parent.width
            CDoodHeaderImage {
                id:groupHeadImage
                anchors.top:parent.top
                anchors.left:parent.left
                anchors.margins: 26
                width:140
                height: 140
                radius:20
                z:100
//                anchors{
//                    topMargin: 36
//                    leftMargin:36
//                }
                name:""
                //TODO
                iconSource:setIcon("2",userdataManager.thumbAvatar)
//                    userdataManager.thumbAvatar===""?"qrc:/res/headerDefault.png":userdataManager.thumbAvatar
            }
            Text{
                anchors{
                    left:groupHeadImage.right
                    leftMargin:29
                    verticalCenter: parent.verticalCenter
                    verticalCenterOffset: -30
                }
                //TODO
                    text:userdataManager.name
                    font.pixelSize: 30
            }
        }

        Rectangle{
            id: groupinfomation
            anchors.top:groupdatapic.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 40
            border.width: 1
            height: 90
            radius:10
            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 26
                font.pixelSize: 30
                text: os.i18n.ctr(qsTr("群名称"))
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 26
                font.pixelSize: 30
                anchors.right: parent.right
                //TODO:
                text: os.i18n.ctr(userdataManager.name)
            }
        }
        CButton{
            id:applyJoinIn

            anchors.top:groupinfomation.bottom
            anchors.topMargin: 47
            anchors.horizontalCenter: parent.horizontalCenter

            width: parent.width - 40
            height: 90
            opacity : pressed ? 1: 0.7
            text:os.i18n.ctr(qsTr("申请加入"))
            textColor:  "#ffffff"
            pixelSize:34
            backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#32c2fe"
                    radius: 10
                }
            onClicked: {
                //TODO: handle group-adding management
                groupManager.addGroup(userdataManager.id,"我是"+userProfileManager.name);
                }
            }

    }
}
