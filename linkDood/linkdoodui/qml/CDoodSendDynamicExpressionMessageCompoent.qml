import com.syberos.basewidgets 2.0
import QtQuick 2.3

Component {
    id: sendTextMessage

    Item {
        id: sendTextMessageRoot

        width: chatListView.editing ? chatListView.width - 100 : chatListView.width
        height: textMessageBg.height

        property int sendEditMessageModel: 0
        signal showMenu()

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
                width: 90
                height: 90
                radius: 6
                name:""
                headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                iconSource:setIcon("1", model.modelData.contactThumbAvatar)
//                    "qrc:/res/headerDefault.png"/*"file://"+ model.modelData.thumbAvatar*/

//                MouseArea {
//                    anchors.fill: parent

//                    onClicked: {
//                        console.log("todo show MyInfo Pagesssssssssss !!!")
//                        console.log(model.modelData.name)
//                        console.log(model.modelData.fromId)
//                        if (chatListView.editing)
//                            return;
//                    }
//                }
            }
        }

        Rectangle {
            id: textMessageBg
            anchors.right: sendTextMessageHeadImageViewLoader.left
            anchors.rightMargin: 10
            anchors.top: sendTextMessageHeadImageViewLoader.top

            property var textMessageWidth: textMessage.width + 55
            property var textMessageHeight: textMessage.height + 40

            width: textMessageWidth
            height: textMessageHeight
            color:"transparent"
            AnimatedImage{
                id: textMessage
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.top: parent.top
                anchors.topMargin: 25

                source: model.modelData.body
                visible: true
                asynchronous:true

                Component.onCompleted: {
                    if(textMessage.implicitWidth > chatDelegateRoot.maxMessageLength)
                        textMessage.width = chatDelegateRoot.maxMessageLength
                }
            }
            MouseArea{
                anchors.fill: parent
                onPressAndHold: {
                    emit: showMenu();
                }
            }
        }

        Loader {
            id: sendFailedImageLoader
            anchors.right: textMessageBg.left
            anchors.rightMargin: 20
            anchors.verticalCenter: textMessageBg.verticalCenter

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
                        chatManager.resendMessage(model.modelData.localId);
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
            sourceComponent: sendTextMessageLoadingComponent
        }

        Component {
            id: sendTextMessageLoadingComponent

            CIndicator {
                direction: Qt.Horizontal
                textColor:"#ffffff"
                text:""
                spacing:28
                fontSize:26
                visible: model.modelData.loading
            }
        }

        Behavior on width {
            NumberAnimation { duration: 100 }
        }
    }
}
