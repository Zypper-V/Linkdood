import com.syberos.basewidgets 2.0
import QtQuick 2.3

Component {
    id: sendPictrueMessage

    Item {
        id: sendpictrueMessageRoot

        width: chatListView.editing ? chatListView.width - 100 : chatListView.width
        height: pictrueMessageBg.height
        signal showMenu()
        property int sendEditMessageModel: 0
        property var myChatPage
        Loader {
            id: sendpictrueMessageHeadImageViewLoader
            anchors.right: parent.right
            anchors.rightMargin: 20
            asynchronous: false
            sourceComponent: sendpictrueMessageHeadImageViewComponent
        }

        Component {
            id: sendpictrueMessageHeadImageViewComponent

            CDoodHeaderImage {
                id: sendpictrueMessageHeadImageView
                width: 90
                height: 90
                radius: 6
                name:""
                headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                iconSource: setIcon("1", model.modelData.contactThumbAvatar)
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

        BorderImage {
            id: pictrueMessageBg
            anchors.right: sendpictrueMessageHeadImageViewLoader.left
            anchors.rightMargin: 10
            anchors.top: sendpictrueMessageHeadImageViewLoader.top

            property var pictrueMessageWidth: pictrueMessage.width + 55
            property var pictrueMessageHeight: pictrueMessage.height + 40

            width: pictrueMessageWidth
            height: pictrueMessageHeight
            asynchronous : true

            border { left: 15; top: 50; right: 15; bottom: 15 }

            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat

            source: "qrc:/res/send/message.png"

            MouseArea {
                anchors.fill: parent

                onPressAndHold: {
                    sendpictrueMessageRoot.sendEditMessageModel = 1
                    emit: showMenu();
                }

                onPressed: {
                    sendpictrueMessageRoot.sendEditMessageModel = 0
                    pictrueMessageBg.source = "qrc:/res/send/messageActive.png"
                }

                onReleased: {
                    pictrueMessageBg.source = "qrc:/res/send/message.png"
                }

                onCanceled: {
                    pictrueMessageBg.source = "qrc:/res/send/message.png"
                }
                onClicked: {

                    chatManager.downloadMainImage(model.modelData.bodyBig,model.modelData.encrypt_key,model.modelData.targetId);
                    myChatPage = pageStack.getCachedPage(Qt.resolvedUrl("CDoodViewImage.qml"),"CDoodViewImage");
                    myChatPage.imageSource = model.modelData.body;
                    myChatPage.tip="(图片加载中...)";
                    myChatPage.url=model.modelData.bodyBig
                    pageStack.push(myChatPage);
                }
            }

            Image{
                id: pictrueMessage

                property bool bChange:model.modelData.isImageChange
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.top: parent.top
                anchors.topMargin: 25
                source: model.modelData.body
                visible: true
                asynchronous:true
                onBChangeChanged: {
                    width = bChange?width+1:width-1;
                    console.log("imag:"+width)
                }
                Component.onCompleted: {
                    if(pictrueMessage.implicitWidth > chatDelegateRoot.maxMessageLength)
                        pictrueMessage.width = chatDelegateRoot.maxMessageLength
                }

                Text{
                    font.pixelSize: 36
                    color:"white"
                    text:model.modelData.progress+"%"
                    visible: model.modelData.loading

                    anchors.centerIn: parent
                }
            }
        }

        Loader {
            id: sendFailedImageLoader
            anchors.right: pictrueMessageBg.left
            anchors.rightMargin: 20
            anchors.verticalCenter: pictrueMessageBg.verticalCenter

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
                        console.log("zhangp to resend 1111111111111111111111111111111!!!")
                        chatManager.resendMessage(model.modelData.localId);
                    }
                }
            }
        }

        Loader {
            id: pictrueMessageLoadingLoader
            anchors.right: pictrueMessageBg.left
            anchors.rightMargin: -5
            anchors.verticalCenter: pictrueMessageBg.verticalCenter

            asynchronous: false
            sourceComponent: sendpictrueMessageLoadingComponent
        }

        Component {
            id: sendpictrueMessageLoadingComponent

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
