import QtQuick 2.0
import com.syberos.basewidgets 2.0

CEditListViewDelegate {
    id:chatDelegateRoot

    width: parent.width
    height: sessionTimeBgLoader.height + messageLoader.height + marginValue +
            messageTopMarginValue + bottomMarginValue + (isSender ? 0 : 40)

    property bool  isSender: model.modelData.fromId === loginManager.userId
    property int marginValue: chatDelegateRoot.showMsgTime ? 10 :0
    property int messageTopMarginValue: 11
    property int leftRightMarginValue: 40

    property int bottomMarginValue: 11
    property int maxMessageLength: 418

    property string msgSendTime: model.modelData.timeText
    property bool showMsgTime:  model.modelData.showTime

    property Component sendTextMsgObj:  CDoodSendTextMessageCompoent{}
    property Component receiveTextMsgObj:  CDoodReceiveTextMessageCompoent{}

    property Component sendDyEmojiMsgObj:CDoodSendDynamicExpressionMessageCompoent{}
    property Component receiveDyEmojiMsgObj:CDoodReceiveDynamicExpressionMessageCompoent{}

    property Component sendImageMsgObj:CDoodSendPicturetMessageCompoent{}
    property Component receiveImageMsgObj:CDoodReceivePictureMessageCompoent{}

    property Component sendFileMsgObj:CDoodSendFileMessageCompoent{}
    property Component receiveFileMsgObj:CDoodReceiveFileMessageCompoent{}
    property Component sendTipMsgObj:CDoodTipMessageCompoent{}


    function loadRigthUi(){

        if(chatManagerModel.chatType === "6"){
            if(model.modelData.contactThumbAvatar ==="qrc:/res/icon_pc.png"){
                return false;
            }else{
                return true;
            }
        }else if(model.modelData.fromId === loginManager.userId){
            return true;
        }
        else{
            return false;
        }
    }

    function loaderComponent () {
        if(model.modelData.msgType === "2") {
            if(loadRigthUi()) {
                return chatDelegateRoot.sendTextMsgObj
            } else {
                return chatDelegateRoot.receiveTextMsgObj
            }
        }else if(model.modelData.msgType === "19"){
            if(loadRigthUi()) {
                return chatDelegateRoot.sendDyEmojiMsgObj
            } else {
                return chatDelegateRoot.receiveDyEmojiMsgObj
            }
        }else if(model.modelData.msgType === "5"){
            if(loadRigthUi()) {
                return chatDelegateRoot.sendImageMsgObj
            } else {
                return chatDelegateRoot.receiveImageMsgObj
            }
        }else if(model.modelData.msgType === "8" ||model.modelData.msgType === "100"){
            return chatDelegateRoot.sendTipMsgObj
        }else{
            //TODO
        }
        if(model.modelData.msgType === "6"){

            if(loadRigthUi()) {
                return chatDelegateRoot.sendFileMsgObj
            } else {
                return chatDelegateRoot.receiveFileMsgObj
            }
        }
    }

    editLabelComponent:CCheckBox {
        checkedColor: "#00afee"
        checked: chatDelegateRoot.checked
        enabled: false
    }

    editLabelSize: Qt.size(40, 40)
    editLabelRightMargin: 40

    MouseArea {
        anchors.fill: parent
        enabled: !editing
        onPressed: {
        }
    }

    Loader {
        id: sessionTimeBgLoader
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: chatDelegateRoot.marginValue
        asynchronous: false

        Component.onCompleted: {
            if(showMsgTime) {
                sessionTimeBgLoader.sourceComponent = sessionTimeBgComponent
            }
        }
    }

    Component {
        id: sessionTimeBgComponent

        Rectangle {
            id: sessionTimeBg

            height: sessionTime.implicitHeight + 14
            width: sessionTime.width + 30
            radius: 10
            color: "#ced1d1"

            Text {
                id: sessionTime
                anchors.centerIn: parent

                color:"#ffffff"
                font.pixelSize: 20

                text:chatDelegateRoot.msgSendTime /*Qt.formatDateTime(chatPage.wallClockCurrentTime, "yyyy") !== Qt.formatDateTime(chatDelegateRoot.msgSendTime, "yyyy") ?
                          Qt.formatDateTime(chatDelegateRoot.msgSendTime, "yyyy-MM-dd hh:mm") :
                          Qt.formatDateTime(chatPage.wallClockCurrentTime, "MM-dd") !== Qt.formatDateTime(chatDelegateRoot.msgSendTime, "MM-dd") ?
                              Qt.formatDateTime(chatDelegateRoot.msgSendTime, "MM-dd hh:mm") : Qt.formatDateTime(chatDelegateRoot.msgSendTime, "hh:mm")*/
            }
        }
    }

    CDialog {
        id: alertDialog

        titleText: qsTr("提示")
        messageText: qsTr("确定要删除此消息吗？")
        property string id
        property string msgId
        onAccepted: {
            chatManager.deleteMessage(id,msgId);
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }

    CDoodChatMessageOption{
        id:msgOptions
        onInerClicked: {
            console.log("you select:"+index)
            if(msgOptions.index == 0){
                messageLoader.item.copy();
            }else if(msgOptions.index == 1){
                alertDialog.id = chatManagerModel.id;
                alertDialog.msgId = msgOptions.id;
                alertDialog.show();
            }else if(msgOptions.index == 2){

                if(model.modelData.msgType ==="2"){
                    var tmp = chatManager.handleEmojiText(messageLoader.item.documentText());
                    model.modelData.setTextMsg(tmp);
                }

                var compoment = pageStack.getCachedPage(Qt.resolvedUrl("CDoodGroupAddMainPage.qml"),"CDoodGroupAddMainPage");
                pageStack.push(compoment,{localId:msgOptions.id,isTransMessage:true});
            }
            msgOptions.hide();
        }
    }

    Loader {
        id: messageLoader
        anchors.top: sessionTimeBgLoader.bottom
        anchors.topMargin: messageTopMarginValue
        asynchronous: false
        width: parent.width
        sourceComponent: chatDelegateRoot.loaderComponent()
    }
    onEditingChanged: {

    }

    Connections{
        target: messageLoader.item
        onShowMenu:{

            msgOptions.id = model.modelData.localId;
            msgOptions.index = -1;
            if(model.modelData.msgType === "2"){
                console.log("msgOptions.isVisibleCopy:true");
                msgOptions.isVisibleCopy = true;
            }else{
                msgOptions.isVisibleCopy = false;
                console.log("msgOptions.isVisibleCopy:false");
            }
            if(model.modelData.msgType === "8"){
                msgOptions.isCanTrans = false;
            }else{
                msgOptions.isCanTrans = true;
            }

            msgOptions.show();
        }
    }
}
