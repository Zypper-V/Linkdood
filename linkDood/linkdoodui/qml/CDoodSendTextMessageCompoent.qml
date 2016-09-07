import com.syberos.basewidgets 2.0
import QtQuick 2.3

Component {
    id: sendTextMessage

    Item {
        id: sendTextMessageRoot

        signal showMenu()

        function copy(){

            //chatManager.isTextOnClipboard();
            if(chatManager.isTextOnly(textMessage.text)){
                textMessage.selectAll();
                textMessage.copy();
                gToast.requestToast("已经复制","","");
            }else{
                gToast.requestToast("本版本仅支持纯文本复制","","");
            }

            console.log("copy text:"+ textMessage.text+":"+textMessage.canPaste)
        }
        function documentText(){
            return textMessage.textDocument;
        }

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
                width: 90
                height: 90
                radius: 6
                name:""
                headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                iconSource:setIcon("1", model.modelData.contactThumbAvatar)
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

            TextEdit{
                id: textMessage
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.top: parent.top
                anchors.topMargin: 25

                wrapMode: Text.Wrap
                textFormat: model.modelData.textFormat
                renderType: Text.NativeRendering
                readOnly:true
                selectionColor: "transparent"
                selectedTextColor: "#333333"
                verticalAlignment: TextEdit.AlignVCenter

                color:"#333333"
                font.pixelSize: 28
                text: model.modelData.body

                visible: true

                Component.onCompleted: {
                    if(textMessage.implicitWidth > chatDelegateRoot.maxMessageLength)
                        textMessage.width = chatDelegateRoot.maxMessageLength
                }
                onLinkHovered: {
                    console.log("onLinkHovered")
                }
            }

            MouseArea {
                anchors.fill: parent

                onPressAndHold: {
                    sendTextMessageRoot.sendEditMessageModel = 1
                    emit: showMenu();
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
                visible:model.modelData.loading
            }
        }

        Behavior on width {
            NumberAnimation { duration: 100 }
        }
    }
}
