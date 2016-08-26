import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: userdataPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            userdataPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(userdataPage.statusBarHoldEnabled)
            userdataPage.statusBarHoldItemColor = "#edf0f0"
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
                text:qsTr("添加好友")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
        }

        Rectangle{
            id:rectid

            height: 80
            width: parent.width - 40
            radius: 10
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: titleBackground.height + 20
            CLineEdit {
                id: serachContactId
                height: parent.height
                width: parent.width
                anchors.top: parent.top
                anchors.centerIn: parent
                searchLabelLeftMargin: 20
                searchLabelRightMargin: 20
                searchLabelEnabled:true
                readOnly: true

                textColor:"#787777"
                font.pixelSize: 30
                placeholderText:os.i18n.ctr(qsTr("圆圆ID/名称"))
                inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                         pageStack.push(Qt.resolvedUrl("CDoodSearchContactPage.qml"))
                    }
                }
            }
        }

    }
}
