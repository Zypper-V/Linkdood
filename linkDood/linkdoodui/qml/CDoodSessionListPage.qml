import QtQuick 2.0
import com.syberos.basewidgets 2.0
import QtQml.Models 2.1
Item {
    id: sessionListPage
    anchors.fill: parent
    property var myChatPage

    ListView {
        id: sessionListView

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        property var selectedItem: null

        clip: true
        function unsetSelectedItem()
        {
            if (selectedItem) {
                selectedItem.toInitState();
                selectedItem = null;
            }
        }

        function setSelectedItem(item) {
            if (selectedItem !== item) {
                console.debug("overhere")
                unsetSelectedItem();
                selectedItem = item;
            }
        }

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }

        Behavior on contentY {
            NumberAnimation { duration: 200 }
        }
        model: DelegateModel {
            id: visualModel
            model: sessionListManager
            delegate: Item {
                id: rootItem

                width: parent.width/*gScreenInfo.platformWidth*/
                height: 125
                property int visualIndex: DelegateModel.itemsIndex
                SlideDelegate {
                    id: delegateRoot
                    anchors.fill: parent

                    onPositionChanged: {
                        if(!delegateRoot.pressed){
                            background.color="#FFFFFF";
                        }
                    }
                    onPressed: background.color="#CDCDCD"
                    onReleased: background.color="#FFFFFF"
                    onCanceled: background.color="#FFFFFF"
                    onClicked: {

                        var unreadCount = parseInt(model.modelData.unReadCount, 10);

                        delegateRoot.toInitState();
                        sessionListView.unsetSelectedItem();
                        sessionListManager.clickChatItem(model.modelData.id);
                        if(model.modelData.chatType !== "-5"){

                            if(unreadCount>0){

                                console.log("sdgfsdfgsdgasfsasfsf:"+unreadCount)
                                chatManager.switchToChatPage(model.modelData.id,model.modelData.name,model.modelData.chatType,model.modelData.lastMsgid,unreadCount,model.modelData.thumbAvatar);
                            }else{
                                chatManager.switchToChatPage(model.modelData.id,model.modelData.name,model.modelData.chatType,model.modelData.lastMsgid,0,model.modelData.thumbAvatar);
                                chatManager.entryChat(model.modelData.id);
                            }
                            console.log("123avater:"+model.modelData.thumbAvatar)

                        }else{//系统消息
                            sessionListManager.entrySysMsgPage();
                            sysmsgManager.getSysMessages();
                            myChatPage = pageStack.getCachedPage(Qt.resolvedUrl("CDoodSysMessagePage.qml"),"CDoodSysMessagePage");
                            pageStack.push(myChatPage);
                        }

                    }

                    onSlideFinished: {
                        sessionListView.setSelectedItem(delegateRoot);
                    }

                    _rightMenuItem: Item {
                        width: 140
                        height: delegateRoot.height

                        Rectangle {
                            anchors.fill: parent

                            color: "red"
                            Text{
                                anchors.centerIn: parent
                                text:qsTr("删除")
                                font.pixelSize: 34
                                color:"white"
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                var targetId = model.modelData.id;
                                sessionListManager.removeChatItem(targetId);
                                chatManager.removeChat(targetId);
                            }
                        }
                    }
                    property Item contentItem: Rectangle {
                        id: cellItem

                        parent:delegateRoot.slideItem

                        anchors.fill: delegateRoot.slideItem
                        anchors.margins: 1

                        color: "white"

                        Rectangle {
                            width: cellItem.width
                            height: cellItem.height

                            Rectangle {
                                id : mousePressBackgroud
                                anchors.fill: parent
                                visible: false
                                color: "white"
                            }
                            Rectangle {
                                id : background

                                anchors.fill: parent
                                anchors.topMargin: 1
                                anchors.bottomMargin: 3

                                CDoodHeaderImage {
                                    id: headPortraitImage

                                    anchors.left: parent.left
                                    anchors.leftMargin: 20
                                    anchors.verticalCenter: parent.verticalCenter
                                    width: 90
                                    height: 90
                                    radius: 6
                                    name:""
                                    iconSource: setIcon(model.modelData.chatType,model.modelData.thumbAvatar)

                                }


                                Text {
                                    id: nameText

                                    anchors.left: headPortraitImage.right
                                    anchors.leftMargin:30
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
                                    text: model.modelData.name
                                }
                                CLabel{
                                    id: contentText

                                    anchors.left: headPortraitImage.right
                                    anchors.leftMargin: 30
                                    anchors.bottom: parent.bottom
                                    anchors.bottomMargin: 10
                                    anchors.top: nameText.bottom
                                    anchors.topMargin: 24

                                    font.pixelSize: 24
                                    height: 60
                                    clip: true
                                    width:460
                                    elide: Text.ElideRight
                                    color: "#777777"
                                    text: model.modelData.lastMsg
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

                                    text: model.modelData.msgTime
                                }
                                Rectangle{
                                    id:unreadcount
                                    anchors.bottom: parent.bottom
                                    anchors.bottomMargin: 10
                                    anchors.right: parent.right
                                    anchors.rightMargin:40
                                    width: model.modelData.unReadCount==="99+"?38:36
                                    height: model.modelData.unReadCount==="99+"?38:36
                                    radius: model.modelData.unReadCount==="99+"?19:18
                                    visible: setUnread()
                                    color:"red"
                                    Text{
                                        font.pixelSize: model.modelData.unReadCount==="99+"?20:24
                                        anchors.centerIn: parent
                                        color:"white"
                                        text:model.modelData.unReadCount
                                    }
                                    function setUnread(){
                                        if( model.modelData.unReadCount==="" ||  model.modelData.unReadCount==="0"){
                                            return false;
                                        }
                                        return true;
                                    }
                                }
                            }
                        }

                        CLine {
                            width: parent.width
                            anchors.left: parent.left
                            //                            anchors.leftMargin: 150
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            z: parent.z+2
                        }
                        DropArea {
                            id: dropArea
                            anchors { fill: parent; margins: 15 }

                            onEntered: visualModel.items.move(drag.source.visualIndex, rootItem.visualIndex)
                        }
                    }
                    Component.onCompleted: {
                        // medoRecordManager.startQueryAttachments(model.modelData.id);
                    }
                }
            }
        }
        CScrollDecorator{
            flickableItem: sessionListView
        }
    }
}

