import QtQuick 2.0
import com.syberos.basewidgets 2.0
//import QtQuick.Layouts 1.2
//import QtQuick.Controls 1.4

CPage {
    id: chatManagerPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
           // loginPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(loginPage.statusBarHoldEnabled)
            loginPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
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
            id:titleBackground

            anchors.top: parent.top
            anchors.left: parent.left

            width:parent.width
            height: 110
            color:"#1c1b21"
            Text{
                id:titleText

                anchors.centerIn: parent

                text:chatManager.name
                color:"white"
                font.pixelSize: 36
            }
            CButton{
                id:backbutton

                anchors.left:parent.left
                anchors.top:parent.top
                anchors.leftMargin:20
                anchors.verticalCenter: parent.verticalCenter
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"#1c1b21"
                }
                text:os.i18n.ctr(qsTr("<返回"))
                textColor:"white"
                onClicked: {
                    pageStack.replace(Qt.resolvedUrl("CDoodRootTabView.qml"), "", true);
                }
            }
        }

        Item{
            id:chatLayout

            anchors{
                top:titleBackground.bottom
                left: parent.left
            }
            width:parent.width
            height: parent.height - titleBackground.height

            CLineEdit{
                id:inputField

                width:parent.width
                height:300

                anchors.centerIn: parent
            }

            CButton{
                id:sendmessage

                anchors{
                    bottom: parent.bottom
                    bottomMargin: 10
                    left:parent.left
                }

                width: parent.width
                height: 83
                backgroundComponent: Rectangle {
                    anchors.fill: parent
                    color:"white"
                }
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    color:"blue"
                    font.pixelSize: 32
                    text:qsTr("发送")
                }
                onClicked: {
                    chatManager.sendText(loginManager.userId,inputField.text);
                }
            }

        }
    }

}
