import QtQuick 2.0
import com.syberos.basewidgets 2.0

Component {
    id: receivePictrueMessage

    Item {
        id: receivePictrueMessageRoot
        x: 0
        signal showMenu
        width: parent.width
        height: pictrueMessageBg.height
        Loader {
            id: textNameRootLoader
            anchors.top: parent.top
            anchors.left: pictrueMessageBg.left
            asynchronous: false
            sourceComponent: textNameRootComponent
        }

        Component {
            id: textNameRootComponent

            Item {
                id: textNameRoot
                height: textNameText.implicitHeight + 6
                width: chatDelegateRoot.maxMessageLength
                z: 100
                clip:  true

                Text {
                    id: textNameText
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5

                    color:"#999999"
                    font.pixelSize: 20
                    elide: Text.ElideRight;
                    text: model.modelData.name
                }
            }
        }

        Loader {
            id: receiveTextMsgHeadImageViewLoader
            anchors.top: textNameRootLoader.bottom

            anchors.left: parent.left
            anchors.leftMargin: 20
            asynchronous: false
            sourceComponent: receiveTextMsgHeadImageViewComponent
        }

        Component {
            id: receiveTextMsgHeadImageViewComponent

            CDoodHeaderImage {
                id: receiveTextMsgHeadImageView
                width: 90
                height: 90
                radius: 6
                name:""
                headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                iconSource: setIcon("1", model.modelData.contactThumbAvatar)
                //                MouseArea {
                //                    anchors.fill: parent

                //                    onClicked: {
                //                        console.log("todo show Info Page !!!")
                //                        console.log(model.modelData.name)

                //                        if (chatListView.editing)
                //                            return;
                //                    }

                //                    onPressAndHold: {
                //                        console.log("todo @ !!!")
                //                    }
                //                }
            }
        }

        BorderImage {
            id: pictrueMessageBg
            anchors.left: receiveTextMsgHeadImageViewLoader.right
            anchors.leftMargin: 10
            anchors.top: receiveTextMsgHeadImageViewLoader.top

            property var pictrueMessageWidth: pictrueMessage.width + 55
            property var pictrueMessageHeight: pictrueMessage.height + 40

            width: pictrueMessageWidth
            height: pictrueMessageHeight
            asynchronous : true

            border { left: 15; top: 50; right: 15; bottom: 15 }

            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat

            source: "qrc:/res/receive/message.png"

            MouseArea {
                anchors.fill: parent

                onPressAndHold: {
                    emit: showMenu();
                }

                onPressed: {
                    pictrueMessageBg.source = "qrc:/res/receive/messageActive.png"
                }

                onReleased: {
                    pictrueMessageBg.source = "qrc:/res/receive/message.png"
                }

                onCanceled: {
                    pictrueMessageBg.source = "qrc:/res/receive/message.png"
                }
                onClicked: {
                    fileViewManager.showFilePage(model.modelData.localId,
                                                 model.modelData.textMsg,
                                                 model.modelData.thumbAvatar,
                                                 model.modelData.body,
                                                 model.modelData.fileSize,
                                                 model.modelData.tar_thumbAvatar);
                    var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodFileViewPage.qml"),"CDoodFileViewPage");
                    pageStack.push(component);
                }
            }

            Rectangle{
                id: pictrueMessage
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.top: parent.top
                anchors.topMargin: 25

                visible: true

                implicitWidth: chatDelegateRoot.maxMessageLength
//                implicitHeight: icon.height+40
                implicitHeight: fileName.height + 40
                Image{
                    id:icon
                    source: chatManager.judgeFileFromat(model.modelData.textMsg)

                    anchors.left: parent.left
                    anchors.leftMargin: 10
//                    anchors.verticalCenter: parent.verticalCenter
                    anchors.topMargin: 20
                }
                Text{
                    id:fileName

                    text:model.modelData.textMsg
                    font.pixelSize: 30
                    height: 40 * lineCount
                    width: parent.width
                    wrapMode: TextInput.WrapAnywhere

                    anchors.top:icon.top
                    anchors.left: icon.right
                    anchors.leftMargin: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                }
                Text{
                    id:fileSize
                    text:getSizeStr(model.modelData.fileSize)

                    anchors.top:fileName.bottom
                    anchors.left: icon.right
                    anchors.leftMargin: 10

                    function getSizeStr(bytes) {
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
                    if(pictrueMessage.implicitWidth > chatDelegateRoot.maxMessageLength)
                        pictrueMessage.width = chatDelegateRoot.maxMessageLength
                }
            }
        }

        Loader {
            id: reciveFailedImageLoader
            anchors.left: pictrueMessageBg.right
            anchors.leftMargin: 20
            anchors.verticalCenter: pictrueMessageBg.verticalCenter
            asynchronous: true
            sourceComponent: null
        }

        Component {
            id: reciveFailedImageComponent

            Image {
                id: reciveFailedImage
                sourceSize: Qt.size(50, 50)
                visible: false
                source: "qrc:/res/sendfailed.png"
            }
        }

        Loader {
            id:  receivePictrueMessageLoadingLoader

            anchors.left: pictrueMessageBg.right
            anchors.leftMargin: 15
            anchors.verticalCenter: pictrueMessageBg.verticalCenter

            asynchronous: false
            sourceComponent: null
        }

        Component {
            id: receivePictrueMessageLoadingComponent

            CIndicator {
                direction: Qt.Horizontal
                textColor:"#ffffff"
                text:""
                spacing:28
                fontSize:26
            }
        }

        Behavior on x {
            NumberAnimation { duration: 100 }
        }
    }
}

