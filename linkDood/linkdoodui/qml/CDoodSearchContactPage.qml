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
            id:inputBox

            anchors.top: parent.top
            width:parent.width
            height:120
            color:"#CDCDCD"

            Rectangle{
                id:searchContactId

                height: 80
                width: parent.width - 120
                radius: 10
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.verticalCenter: parent.verticalCenter
                CLineEdit {
                    id: editContactId
                    height: 80
                    width: parent.width
                    anchors.centerIn: parent
                    searchLabelEnabled:true
                    focus: true

                    textColor:"#787777"
                    font.pixelSize: 30
                    placeholderText:os.i18n.ctr(qsTr("圆圆ID/名称"))
                    inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/
                    inputMethodHintExtensions: {
                        var args = {};
                        args["enterKeyText"] = "search"
                        return args;
                    }
                    onKeyPressed: {
                        console.log("dood === onKeyPressed: key = ", key)

                        if (key === Qt.Key_Return)
                        {
                            if(editContactId.text === ""){
                                gToast.requestToast("请输入关键字","","");
                                return ;
                            }
                            addContactManager.searchFromNet(editContactId.text)
                        }
                    }
                }

            }
            Rectangle {
                id: cancelId
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                height:parent.height
                color:"transparent"
                width:70
                Text{
                    color: "green"
                    font.pixelSize: 30
                    anchors.centerIn: parent
                    text: qsTr("取消")
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        pageStack.pop()
                        addContactManager.contactListClear();

                    }
                }
            }
        }
        ListView {
            id: contactListView

            anchors.top: inputBox.bottom
            anchors.bottom: parent.bottom
            width:parent.width
            height: 200

            clip: true
            model: addContactManager

            delegate:Item {
                id:contactListDelegate

                width: contactListView.width
                height: 104

                MouseArea {
                    id:mouse

                    anchors.fill: parent
                    onPressed: {
                        if(mousePressBackgroud.visible){
                            background.color = "#ffffff"
                            mousePressBackgroud.visible = false
                        }else{
                            background.color = "#cdcdcd"
                            mousePressBackgroud.visible = true
                        }
                    }
                    onReleased: {
                        background.color = "#ffffff"
                        mousePressBackgroud.visible = false
                        if("1" === model.modelData.userOrGroup){

                            userdataManager.clearData();

                            userdataManager.setName(model.modelData.name);
                            userdataManager.setGender(model.modelData.gender);
                            userdataManager.setThumbAvatar(model.modelData.thumbAvatar);
                            userdataManager.setId(model.modelData.id);

                            console.log(userdataManager.name);
                            userdataManager.setIsFriend(contactManager.isFriend(model.modelData.id));
                            pageStack.push(Qt.resolvedUrl("CDoodUserDataPage.qml"));
                        }else{
                            userdataManager.setName(model.modelData.name);
                            userdataManager.setId(model.modelData.id);
                            userdataManager.setThumbAvatar(model.modelData.thumbAvatar);
                            pageStack.push(Qt.resolvedUrl("CDoodAddGroupPage.qml"));
                        }

                    }
                    onCanceled: {
                        background.color = "#ffffff"
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
                            anchors.verticalCenter: parent.verticalCenter
                            width: 90
                            height: 90
                            radius: 6
                            name:""
                            headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                            iconSource: setIcon( model.modelData.userOrGroup,model.modelData.thumbAvatar)
                            //                            iconSource: ("" !== model.modelData.thumbAvatar) ? model.modelData.thumbAvatar : (("1" === model.modelData.userOrGroup) ? "qrc:/res/headerDefault.png" : "qrc:/res/group_icon.png")

                            //                            iconSource: "qrc:/res/headerDefault.png"/*"file://"+ model.modelData.thumbAvatar*/
                        }
                        Text {
                            id: nameText
                            anchors.left: headPortraitImage.right
                            anchors.leftMargin: 30
                            anchors.rightMargin: 20
                            anchors.top: headPortraitImage.top
                            anchors.topMargin: 10
                            font.pixelSize: 24
                            clip: true
                            color: "#333333"
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                            text: model.modelData.name
                        }
                        CLine {
                            width: parent.width
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
    Connections{
        target: addContactManager
        onSearchFromNetResult:{
            if(size <=0){
                gToast.requestToast("未搜索到联系人","","");
            }
        }
    }
}

