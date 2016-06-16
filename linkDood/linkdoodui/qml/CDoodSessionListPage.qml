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

    CEditListView {
        id: sessionListView
        anchors.top: sessionListTitleBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        editable:false
        clip: true
        model: sessionListManager

        editing: false

        delegate:CEditListViewDelegate {
            id:sessionListDelegate

            width: sessionListView.width
            height: 125

            onClicked: {
                console.log("model.modelData.link = ", model.modelData.last_msg)
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
                width: sessionListDelegate.width
                height: sessionListDelegate.height


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
                    //                    radius: 10

                    Rectangle {
                        id: headPortraitImage
                        anchors.left: parent.left
                        anchors.leftMargin: 40
                        anchors.verticalCenter: parent.verticalCenter
                        width: 80
                        height: headPortraitImage.width
                        radius: headPortraitImage.width/2
                        color: sessionListManager.getHeaderColor(model.modelData.NID)
                        Text {
                            anchors.centerIn: parent
                            font.pixelSize: headPortraitImage.height/3
                            color: "#ffffff"
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                            font.bold: true
                            text: sessionListManager.getSubName(model.modelData.MgsFromName)
                        }
                    }

                    Text {
                        id: nameText
                        anchors.left: headPortraitImage.right
                        anchors.leftMargin: 30
                        anchors.right: timeText.left
                        anchors.rightMargin: 20
                        anchors.top: parent.top
                        anchors.topMargin: 25
                        font.pixelSize: 30
                        height: 33
                        clip: true
                        color: "#333333"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                        text: model.modelData.MgsFromDept
                    }

                    Item {
                        id: atTextRoot
                        anchors.left: nameText.left
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 25
                        height: 28
                        width: 0

                        clip: true
                        visible: width === 0 ? false : true

                        Text {
                            id: atText
                            font.pixelSize: 24
                            color: "red"
                            elide: Text.ElideMiddle;
                            text: os.i18n.ctr(qsTr("[You were mentioned]")) // qsTr("[有人@你] ")
                        }
                    }
                    Text {
                        id: contentText
                        anchors.left: atTextRoot.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        anchors.right: notDisTurb.left
                        anchors.rightMargin: 15
                        font.pixelSize: 24
                        height: 40
                        clip: true
                        color: "#777777"
                        elide: Text.ElideRight
                        text: model.modelData.Title
                    }

                    Text {
                        id: timeText
                        anchors.right: parent.right
                        anchors.rightMargin: sessionListView.editing ? 100 : 40
                        anchors.top: nameText.top
                        height: nameText.height
                        verticalAlignment: Text.AlignVCenter

                        font.pixelSize: 22
                        color: "#999999"

                        text: model.modelData.SentTime
                    }

                    Image {
                        id: badgeImage
                        anchors.right: parent.right
                        anchors.rightMargin: sessionListView.editing ? 100 : 40
                        anchors.top: timeText.bottom
                        anchors.topMargin: 12
                        fillMode: Image.PreserveAspectFit
                        width: 64
                        height: 30
                        visible: false

                        Text {
                            id: badgeText
                            anchors.centerIn: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter

                            font.pixelSize: 24
                            color: "#ffffff"
                        }
                    }

                    Image {
                        id: badge0Image
                        anchors.right: parent.right
                        anchors.rightMargin: sessionListView.editing ? 100 : 40
                        anchors.top: timeText.bottom
                        anchors.topMargin: 12
                        fillMode: Image.PreserveAspectFit
                        width: 16
                        height: 16
                        visible: false
                    }

                    Image {
                        id: notDisTurb
                        anchors.right: badgeImage.visible ? badgeImage.left : badge0Image.left
                        anchors.rightMargin: 16
                        anchors.top: timeText.bottom
                        anchors.topMargin: 12

                        width: 25
                        height: 25
                        sourceSize: Qt.size(25, 25)
                        smooth: true
                        cache: false
                        asynchronous: true
                        visible: false
                    }
                }
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
        CScrollDecorator{
            flickableItem: sessionListView
        }
    }

    Component.onCompleted: {
    }
}
