import QtQuick 2.0
import com.syberos.basewidgets 2.0

Rectangle{
    id:myProfilePage

    property color tipTextClr: "#777777"
    color:"#F2F2F2"

    anchors.fill: parent
    Column{
        spacing: 30
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
            font.pixelSize: 36
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
                Image {
                    id: userIcon

                    source: userProfileManager.thumbAvatar !=="" ? userProfileManager.thumbAvatar: "qrc:/res/headerDefault.png"

                    anchors{
                        left: parent.left
                        leftMargin: 20
                        verticalCenter: parent.verticalCenter
                    }
                }
                Text{
                    id:userName

                    text:userProfileManager.name
                    font.pixelSize: 34
                    anchors{
                        top:userIcon.top
                        topMargin: 20
                        left:userIcon.right
                        leftMargin: 10
                    }
                }
                Text{
                    id:userDD

                    text:qsTr("圆圆号：")
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
            onPressed: rectBackground.color = "#32c2fe"
            onReleased: rectBackground.color = "white"

            onClicked: {
                console.log("dsfdfvvvvvvvvvvvvvvvvvvvvvvvvv");
                pageStack.push(Qt.resolvedUrl("CDoodSettingProfileDataPage.qml"));
            }
        }

        Rectangle{
            color:"transparent"
            height: 300
            width:parent.width
        }

        Text{
            id:loginoutTip

            text:qsTr("退出登录")
            color:tipTextClr
            font.pixelSize: 34
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
                font.pixelSize: 34
                color:"red"
                anchors.centerIn: parent
            }

            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin:20
            MouseArea{
                anchors.fill: parent
                onPressed: btnLoginout.color = "#32c2fe"
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
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
}
