import com.syberos.basewidgets 2.0
import QtQuick 2.3

Component {
    id: sendfileMessage

    Item {
        id: sendfileMessageRoot

        width: chatListView.editing ? chatListView.width - 100 : chatListView.width
        height: fileMessageBg.height

        property int sendEditMessageModel: 0

        Loader {
            id: sendfileMessageHeadImageViewLoader
            anchors.right: parent.right
            anchors.rightMargin: 20
            asynchronous: false
            sourceComponent: sendfileMessageHeadImageViewComponent
        }

        Component {
            id: sendfileMessageHeadImageViewComponent

            CDoodHeaderImage {
                id: sendfileMessageHeadImageView
                width: 90
                height: 90
                radius: 6
                name:""
                headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                iconSource: setIcon("1", model.modelData.contactThumbAvatar)
                //                    "qrc:/res/headerDefault.png"/*"file://"+ model.modelData.thumbAvatar*/

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        console.log("todo show MyInfo Pagesssssssssss !!!")
                        console.log(model.modelData.name)
                        console.log(model.modelData.fromId)
                        if (chatListView.editing)
                            return;
                    }
                }
            }
        }

        BorderImage {
            id: fileMessageBg
            anchors.right: sendfileMessageHeadImageViewLoader.left
            anchors.rightMargin: 10
            anchors.top: sendfileMessageHeadImageViewLoader.top

            property var fileMessageWidth: fileMessage.width + 55
            property var fileMessageHeight: fileMessage.height + 40

            width: fileMessageWidth
            height: fileMessageHeight
            asynchronous : true

            border { left: 15; top: 50; right: 15; bottom: 15 }

            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat

            source: "qrc:/res/send/message.png"

            MouseArea {
                anchors.fill: parent

                onPressAndHold: {
                    sendfileMessageRoot.sendEditMessageModel = 1
                }

                onPressed: {
                    sendfileMessageRoot.sendEditMessageModel = 0
                    fileMessageBg.source = "qrc:/res/send/messageActive.png"
                }

                onReleased: {
                    fileMessageBg.source = "qrc:/res/send/message.png"
                }

                onCanceled: {
                    fileMessageBg.source = "qrc:/res/send/message.png"
                }
                onClicked: {
                    fileViewManager.showFilePage(model.modelData.localId,
                                                 model.modelData.filePath,
                                                 "",
                                                 "",
                                                 model.modelData.fileSize,
                                                 "");
                    var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodFileViewPage.qml"),"CDoodFileViewPage");
                    pageStack.push(component);
                }
            }

            Rectangle{
                id: fileMessage

                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.top: parent.top
                anchors.topMargin: 25
                implicitWidth: chatDelegateRoot.maxMessageLength
                implicitHeight: icon.height+40
                Image{
                    id:icon
                    source: chatManager.judgeFileFromat(model.modelData.textMsg)

                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text{
                    id:fileName

                    text:model.modelData.textMsg
                    font.pixelSize: 30
                    height: 40
                    elide:Text.ElideRight

                    anchors.top:icon.top
                    anchors.left: icon.right
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                }
                CProgressBar{
                    id:progressBar

                    minimum: 0
                    maximum: 100
                    value: model.modelData.progress
                    visible: model.modelData.loading

                    anchors.top:fileName.bottom
                    anchors.topMargin: 30
                    anchors.left: icon.right
                    anchors.leftMargin: 10
                    anchors.right: fileMessage.right
                    anchors.rightMargin: 10
                }

                Text{
                    id:fileSize

                    text:getSizeStr(model.modelData.fileSize)
                    font.pixelSize: 30
                    height: 40
                    visible:!progressBar.visible
                    anchors.top:fileName.bottom
                    anchors.topMargin: 15
                    anchors.left: icon.right
                    anchors.leftMargin: 10
                    anchors.right: fileMessage.right
                    anchors.rightMargin: 10
                    function getSizeStr(bytes) {
                        console.log("_________________________________filesize:" + bytes)
                        var unit = ["B", "KB", "MB", "GB", "TB"]
                        var i = 0
                        var str = bytes + unit[0]
                        while(bytes > 1024 && i<unit.length) {
                            bytes /= 1024.0
                            i++
                            str = Number(bytes).toPrecision(3) + unit[i]
                        }
                        return str
                    }

                }
                Component.onCompleted: {
                    if(fileMessage.implicitWidth > chatDelegateRoot.maxMessageLength)
                        fileMessage.width = chatDelegateRoot.maxMessageLength
                }
            }
        }

        Loader {
            id: sendFailedImageLoader
            anchors.right: fileMessageBg.left
            anchors.rightMargin: 20
            anchors.verticalCenter: fileMessageBg.verticalCenter

            asynchronous:  true
            sourceComponent: sendFailedImageComponent
        }

        Component {
            id: sendFailedImageComponent

            Image {
                id: sendFailedImage
                sourceSize: Qt.size(50, 50)
                source: "qrc:/res/sendfailed.png"
                asynchronous: true
                visible: !model.modelData.status
                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        console.log("zhangp to resend !!!")
                        chatManager.resendMessage(model.modelData.msgId);
                    }
                }
            }
        }

        Loader {
            id: fileMessageLoadingLoader
            anchors.right: fileMessageBg.left
            anchors.rightMargin: -5
            anchors.verticalCenter: fileMessageBg.verticalCenter

            asynchronous: false
            sourceComponent: sendfileMessageLoadingComponent
        }

        Component {
            id: sendfileMessageLoadingComponent

            CIndicator {
                direction: Qt.Horizontal
                textColor:"#ffffff"
                text:""
                spacing:28
                fontSize:26
                visible:model.modelData.loading
            }
        }

        Behavior on width {
            NumberAnimation { duration: 100 }
        }
    }
}
