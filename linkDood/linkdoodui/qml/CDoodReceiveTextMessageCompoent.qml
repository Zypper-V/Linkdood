import QtQuick 2.0
import com.syberos.basewidgets 2.0

Component {
    id: receiveTextMessage

    Item {
        id: receiveTextMessageRoot
        x: 0

        width: parent.width
        height: textMessageBg.height

        Loader {
            id: textNameRootLoader
            anchors.top: parent.top
            anchors.left: textMessageBg.left
            asynchronous: false
            sourceComponent: null
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
//                    "qrc:/res/headerDefault.png"/*"file://"+ model.modelData.thumbAvatar*/

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        console.log("todo show Info Page !!!")
                        console.log(model.modelData.name)

                        if (chatListView.editing)
                            return;
                    }

                    onPressAndHold: {
                        console.log("todo @ !!!")
                    }
                }
            }
        }

        Text{
            id:userName

            font.pixelSize: 26
            text:model.modelData.name
            color:"#333333"

            anchors.left: receiveTextMsgHeadImageViewLoader.right
            anchors.top: receiveTextMsgHeadImageViewLoader.top
            anchors.leftMargin: 10
        }
        BorderImage {
            id: textMessageBg
            anchors.left: receiveTextMsgHeadImageViewLoader.right
            anchors.leftMargin: 10
            anchors.top: userName.bottom
            anchors.topMargin: 10

            property var textMessageWidth: textMessage.width + 55
            property var textMessageHeight: textMessage.height + 40

            width: textMessageWidth
            height: textMessageHeight
            asynchronous : true

            border { left: 15; top: 50; right: 15; bottom: 15 }

            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat

            source: "qrc:/res/receive/message.png"

            MouseArea {
                anchors.fill: parent

                onPressAndHold: {

                }

                onPressed: {
                    textMessageBg.source = "qrc:/res/receive/messageActive.png"
                }

                onReleased: {
                    textMessageBg.source = "qrc:/res/receive/message.png"
                }

                onCanceled: {
                    textMessageBg.source = "qrc:/res/receive/message.png"
                }
            }

            TextEdit{
                id: textMessage
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.top: parent.top
                anchors.topMargin: 25

                wrapMode: Text.WrapAnywhere
                textFormat:TextEdit.RichText
                readOnly:true
                verticalAlignment: TextEdit.AlignVCenter

                color:"#333333"
                font.pixelSize: 28
                text: model.modelData.body

                visible: true

                Component.onCompleted: {
                    if(textMessage.implicitWidth > chatDelegateRoot.maxMessageLength)
                        textMessage.width = chatDelegateRoot.maxMessageLength
                }
            }
        }

        Loader {
            id: reciveFailedImageLoader
            anchors.left: textMessageBg.right
            anchors.leftMargin: 20
            anchors.verticalCenter: textMessageBg.verticalCenter
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
            id:  receiveTextMessageLoadingLoader

            anchors.left: textMessageBg.right
            anchors.leftMargin: 15
            anchors.verticalCenter: textMessageBg.verticalCenter

            asynchronous: false
            sourceComponent: null
        }

        Component {
            id: receiveTextMessageLoadingComponent

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

