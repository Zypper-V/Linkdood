import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: welcomePage

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
        Rectangle{
            RotationAnimation on rotation {
                loops: Animation.Infinite
                from: 0
                to: 360
            }
            id:imagebackground
            anchors.fill: parent
            color:"white"
            Image{
                id:image
                anchors.horizontalCenter:parent.horizontalCenter
                anchors.top:parent.top
                anchors.topMargin: 300
                source: "qrc:/res/logo.png"
//                SequentialAnimation {
//                    PropertyAction { target: image; property: "opacity"; value: .5 }
//                    NumberAnimation { target: image; property: "width"; to: 300; duration: 10000 }
//                    PropertyAction { target: image; property: "opacity"; value: 1 }
//                }
            }

        }
    }
    Component.onCompleted: {

        pageStack.replace(Qt.resolvedUrl("CDoodLoginPage.qml"), "", true);
    }
}
