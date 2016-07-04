import QtQuick 2.0
import com.syberos.basewidgets 2.0
Item {
    id: contactEnterprise
    anchors.fill: parent

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left

        width:parent.width
        height: parent.height

        color: "white"
        //z:parent.z-1
    }
    Rectangle{
        id:orgTitleListViewbackground
        anchors.top: parent.top
        anchors.left: parent.left
        width: parent.width
        height: 101
        color:"#F2F2F2"
        ListView{
            id: orgTitleListView
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 47
            //        anchors.topMargin: 21
            width: parent.width
            height: 101
            orientation:ListView.Horizontal
            spacing: -25
            model: orgManager
            Rectangle{
                anchors.fill: parent
                color:"#F2F2F2"
                z:parent.z -1
            }

            delegate: Rectangle{
                width: name.contentWidth+80
                height: 50
                anchors.top:parent.top
                color:"#F2F2F2"
                anchors.topMargin: 21
                BorderImage{
                    width: parent.width
                    height: parent.height
                    border.left: 25
                    border.right: 25
                    anchors.top:parent.top
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: -25
                    source: model.modelData.select===""?"qrc:/res/unselected.png":"qrc:/res/selected.png"
                    visible: index !== (orgTitleListView.count)
                    z:parent.z+10
                    Text {
                        id: name
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: model.modelData.name
                        font.pixelSize: 26
                        color:"#333333"
                    }

                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        orgManager.selectOrg(model.modelData.id)
                        enterpriseManager.getSonOrgs(model.modelData.id)
                    }
                }
            }
        }
    }

    ListView {
        id: orgListView
        anchors.top: orgTitleListViewbackground.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        clip: true
        model: enterpriseManager

        delegate:Item {
            id:contactListDelegate

            width: orgTitleListView.width
            height: 113

            MouseArea {
                anchors.fill: parent

                onPressed: {
                    if(mousePressBackgroud.visible){
                        background.color = "white"
                        mousePressBackgroud.visible = false
                    }else{
                        background.color = "#cdcdcd"
                        mousePressBackgroud.visible = true
                    }
                }

                onReleased: {
                    //                    userdataManager.setName(model.modelData.name);
                    //                    userdataManager.setGender(model.modelData.gender);
                    //                    userdataManager.setThumbAvatar(model.modelData.thumbAvatar);
                    //                    userdataManager.setId(model.modelData.id);

                    background.color = "white"
                    mousePressBackgroud.visible = false
                    console.log(" model.modelData.id: ",model.modelData.id)
                    console.log(" model.modelData.name: ",model.modelData.name)
                    orgManager.addOrg(model.modelData.id, model.modelData.name);

                    enterpriseManager.getSonOrgs(model.modelData.id)
                    //pageStack.push(Qt.resolvedUrl("CDoodUserDataPage.qml"));
                }

                onCanceled: {
                    background.color = "white"
                    mousePressBackgroud.visible = false
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
                        width: 90
                        height: 90
                        radius: 6
                        name:""
                        headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                        iconSource: "qrc:/res/headerDefault.png"/*"file://"+ model.modelData.thumbAvatar*/
                        visible: !model.modelData.isOrg
                    }
                    Text {
                        id: nameText
                        anchors.left: headPortraitImage.right
                        anchors.leftMargin: 30
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
                        //                        anchors.leftMargin: 150
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        z: parent.z+2
                    }
                }
            }
        }
    }
}

