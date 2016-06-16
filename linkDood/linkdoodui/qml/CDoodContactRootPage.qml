import QtQuick 2.0
import com.syberos.basewidgets 2.0

Item {
    id: contactRootPage
    anchors.fill: parent

    Rectangle{
        id:contactRootTitleBar

        anchors.top: parent.top
        anchors.left: parent.left

        width:parent.width
        height: 110
        color:"#1c1b21"
        Text{
            id:titleText

            anchors.centerIn: parent

            text:qsTr("信源豆豆")
            color:"white"
            font.pixelSize: 36
        }
    }

    Rectangle {
        anchors.top: contactRootTitleBar.bottom
        anchors.left: parent.left

        width:parent.width
        height: parent.height

        color: "#f2f2f2"
        z:parent.z-1
    }
}
