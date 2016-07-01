import QtQuick 2.0
import com.syberos.basewidgets 2.0

CDoodPopWndLayer{
    id:root
    property color  messageTextColor: "#333333"
    property int    messageTextPixelSize: 26
    property string messageText: ""

    contentItem:Rectangle{

        color: "white"
        radius: 10
        implicitHeight: 90
        implicitWidth: 480

        CCollisionIndicator{
            id: indicator

            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            running: root.visible
        }

        Text{
            id: indicatorTxt

            anchors.left: indicator.right
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.Wrap
            color: root.messageTextColor
            font.pixelSize: root.messageTextPixelSize
            text: root.messageText
        }
    }
}
