import QtQuick 2.0
import com.syberos.basewidgets 2.0

Item {
    id: sessionListPage
    anchors.fill: parent

    Rectangle {
        anchors.fill: parent
        color: "#ffffff"
        z:parent.z-1
    }

    Rectangle{
        id:sessionListTitleBar

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
}
