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
    CEditListView {
        id: contactListView
        anchors.top: contactRootTitleBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        editable:false
        clip: true
        model: contactManager

        editing: false

        delegate:CEditListViewDelegate {
            id:contactListDelegate

            width: contactListView.width
            height: 113

            onClicked: {
                console.log("model.modelData.link = ", model.modelData.name)
            }

            onPressedChanged:{
                if(mousePressBackgroud.visible){
                    background.color = "#ffffff"
                    mousePressBackgroud.visible = false
                }else{
                    background.color = "#cdcdcd"
                    mousePressBackgroud.visible = true
                }

            }

            Rectangle {
                width: contactListDelegate.width
                height: contactListDelegate.height


                Rectangle {
                    id : mousePressBackgroud
                    anchors.fill: parent
                    visible: false
                    color: "#cdcdcd"
                }

                Rectangle {
                    id : background
                    anchors.fill: parent
                    anchors.topMargin: 1
                    anchors.bottomMargin: 3
                    anchors.leftMargin: 2
                    anchors.rightMargin:  2

                    CDoodHeaderImage {
                        id: headPortraitImage
                        anchors.left: parent.left
                        anchors.leftMargin: 25
                        anchors.topMargin: 16
                        anchors.verticalCenter: parent.verticalCenter
                        width: 72
                        height: 72

                        name: sessionListManager.getSubName(model.modelData.name)
                        headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                        iconSource: "file://"+ model.modelData.thumbAvatar
                    }
                    Text {
                        id: nameText
                        anchors.left: headPortraitImage.right
                        anchors.leftMargin: 30
                        anchors.right: timeText.left
                        anchors.rightMargin: 20
                        anchors.top: parent.top
                        anchors.topMargin: 25
                        font.pixelSize: 32
                        height: 33
                        clip: true
                        color: "#333333"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                        text: model.modelData.name
                    }
                    CLine {
                        width: parent.width
                        anchors.left: parent.left
                        anchors.leftMargin: 150
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        z: parent.z+2
                    }

                }
            }
        }
        CScrollDecorator{
            flickableItem: contactListView
        }
    }
}
