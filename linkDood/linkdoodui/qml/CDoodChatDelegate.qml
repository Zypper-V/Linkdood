import QtQuick 2.0
import com.syberos.basewidgets 2.0

CEditListViewDelegate {
    id:chatDelegateRoot

    width: parent.width
    height: sessionTimeBgLoader.height + messageLoader.height + marginValue + messageTopMarginValue + bottomMarginValue

    property int marginValue: chatDelegateRoot.showMsgTime ? 10 :0
    property int messageTopMarginValue: 11
    property int leftRightMarginValue: 40

    property int bottomMarginValue: 11
    property int maxMessageLength: 418

    property string msgSendTime: model.modelData.time
    property bool showMsgTime:  false

    property Component sendTextMsgObj:  CDoodSendTextMessageCompoent{}
    property Component receiveTextMsgObj:  CDoodReceiveTextMessageCompoent{}

    function loaderComponent () {
        if(model.modelData.msgType === "2") {
            console.log("model.modelData.targetId", model.modelData.targetId)
            console.log("model.modelData.fromId", model.modelData.fromId)

            console.log("chatPage.myID", chatPage.myID)

            if(model.modelData.fromId === loginManager.userId) {
                return chatDelegateRoot.sendTextMsgObj
            } else {
                return chatDelegateRoot.receiveTextMsgObj
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

                text: Qt.formatDateTime(chatPage.wallClockCurrentTime, "yyyy") !== Qt.formatDateTime(chatDelegateRoot.msgSendTime, "yyyy") ?
                          Qt.formatDateTime(chatDelegateRoot.msgSendTime, "yyyy-MM-dd hh:mm") :
                          Qt.formatDateTime(chatPage.wallClockCurrentTime, "MM-dd") !== Qt.formatDateTime(chatDelegateRoot.msgSendTime, "MM-dd") ?
                              Qt.formatDateTime(chatDelegateRoot.msgSendTime, "MM-dd hh:mm") : Qt.formatDateTime(chatDelegateRoot.msgSendTime, "hh:mm")
            }
        }
    }

    Loader {
        id: messageLoader
        anchors.top: sessionTimeBgLoader.bottom
        anchors.topMargin: messageTopMarginValue
        asynchronous: false

        sourceComponent: chatDelegateRoot.loaderComponent()
    }

    onEditingChanged: {

    }
}
