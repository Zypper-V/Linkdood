import QtQuick 2.0
import com.syberos.basewidgets 2.0

Component {
    id: sendTextMessage

    Item {
        id: sendTextMessageRoot

        width: chatListView.editing ? chatListView.width - 100 : chatListView.width
        height: textMessageBg.height

        property int sendEditMessageModel: 0

        Loader {
            id: sendTextMessageHeadImageViewLoader
            anchors.right: parent.right
            anchors.rightMargin: 20
            asynchronous: false
            sourceComponent: sendTextMessageHeadImageViewComponent
        }

        Component {
            id: sendTextMessageHeadImageViewComponent

            CDoodHeaderImage {
                id: sendTextMessageHeadImageView
                width: 75
                height: 75
                name: sessionListManager.getSubName(model.modelData.name)
                headerColor: sessionListManager.getHeaderColor(model.modelData.fromId)
                iconSource: "file://"+ model.modelData.thumbAvatar

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
            id: textMessageBg
            anchors.right: sendTextMessageHeadImageViewLoader.left
            anchors.rightMargin: 10
            anchors.top: sendTextMessageHeadImageViewLoader.top

            property var textMessageWidth: textMessage.width + 55
            property var textMessageHeight: textMessage.height + 40

            width: textMessageWidth
            height: textMessageHeight
            asynchronous : true

            border { left: 15; top: 50; right: 15; bottom: 15 }

            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat

            source: "qrc:/res/send/message.png"

            MouseArea {
                anchors.fill: parent

                onPressAndHold: {
                    sendTextMessageRoot.sendEditMessageModel = 1
                }

                onPressed: {
                    sendTextMessageRoot.sendEditMessageModel = 0
                    textMessageBg.source = "qrc:/res/send/messageActive.png"
                }

                onReleased: {
                    textMessageBg.source = "qrc:/res/send/message.png"
                }

                onCanceled: {
                    textMessageBg.source = "qrc:/res/send/message.png"
                }
            }

            CEmojiLinkText {
                id: textMessage
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.top: parent.top
                anchors.topMargin: 25
                wrapMode: Text.WrapAnywhere
                lineHeight: 1.15

                color:"#333333"
                font.pixelSize: 28
                realText: model.modelData.body

                visible: true

                Component.onCompleted: {
                    if(textMessage.implicitWidth > chatDelegateRoot.maxMessageLength)
                        textMessage.width = chatDelegateRoot.maxMessageLength
                }
            }
        }

        Loader {
            id: sendFailedImageLoader
            anchors.right: textMessageBg.left
            anchors.rightMargin: 20
            anchors.verticalCenter: textMessageBg.verticalCenter

            asynchronous:  true
            sourceComponent: null
        }

        Component {
            id: sendFailedImageComponent

            Image {
                id: sendFailedImage
                sourceSize: Qt.size(50, 50)
                source: "qrc:/res/sendfailed.png"
                asynchronous: true

                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        console.log("zhangp to resend !!!")
                    }
                }
            }
        }

        Loader {
            id: textMessageLoadingLoader
            anchors.right: textMessageBg.left
            anchors.rightMargin: -5
            anchors.verticalCenter: textMessageBg.verticalCenter

            asynchronous: false
            sourceComponent: null
        }

        Component {
            id: sendTextMessageLoadingComponent

            CIndicator {
                direction: Qt.Horizontal
                textColor:"#ffffff"
                text:""
                spacing:28
                fontSize:26
            }
        }

        Behavior on width {
            NumberAnimation { duration: 100 }
        }
    }
}
