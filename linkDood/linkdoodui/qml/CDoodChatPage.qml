import QtQuick 2.0
import com.syberos.basewidgets 2.0
import org.nemomobile.time 1.0
import com.syberos.multimedia.photos 2.0

CPage {
    id: chatPage
    anchors.fill: parent
    orientationPolicy: CPageOrientation.LockPortrait

    property bool loadDataFlag:false
    //    signal prepareFinished()

    Timer{
        id:loadDataCheckTimer
        running: false
        repeat: false
        interval: 100
        onTriggered: {
            if(loadDataFlag) {
                loadDataFlag = false
                chatListView.positionViewAtEnd()
                viewToEndanimation.start()
            }
        }
    }

    Timer{
        id:viewToEndanimation
        running: false
        repeat: false
        interval: 50
        onTriggered: {
            prepareFinished()
        }
    }

    property alias wallClockCurrentTime: clock.time

    property string chatName
    property string targetid
    property string chatType
    property string icon
    property bool inputShow: false
    property bool bNeedViewToEnd: true
    property int getMessageHeight: 50
    property string myID :  loginManager.userId

    property bool pageActive
    property bool pageWindowFocus: loginManager.windowFocus


    Connections{
        target: Qt.inputMethod

        onVisibleChanged: {
            if (!Qt.inputMethod.animating) {
                inputShow = gInputContext.softwareInputPanelVisible && chatPage.active
            }
        }
    }

    Keys.onReleased: {
        if (event.key === Qt.Key_Back || event.key === Qt.Key_Escape) {
            btnEmotion.isKeyboard = true;
        }

        if(event.key === Qt.Key_Return)
        {
            console.log("dood === sendMsg !!!!")
            event.accepted = true;
        }
    }

    onActiveChanged: {
        if (active) {
            chatManager.setMessageRead(chatPage.targetid)
        }
    }

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            chatPage.pageActive = true
            chatPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(chatPage.statusBarHoldEnabled)
            chatPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        } else if (status === CPageStatus.WillHide) {
            chatListView.cancelFlick()
            chatPage.pageActive = false
            inputTextArea.focus = false
            chatManager.exitChat()
        } else if (status === CPageStatus.Show) {
            console.log("chatListView.positionViewAtEnd()")
            chatListView.positionViewAtEnd()
        }
    }

    onPageWindowFocusChanged: {
        if(chatPage.pageWindowFocus && chatPage.pageActive) {
            chatManager.entryChat(chatPage.targetid)
        } else {
            chatManager.exitChat()
        }
    }

    function sendTextMsg() {
        console.log("dood sendMsg inputTextArea.plainText() = ", inputTextArea.plainText())

        if(inputTextArea.plainText().replace(/(\s)|(\r\n)|(\r)|(\n)/g, "") !== "") {
            console.log("dood === sendMsg !!!!")
            chatManager.sendText(inputTextArea.textDocument,inputTextArea.plainText());
            chatListView.positionViewAtEnd();
        }
        inputTextArea.text = ""
    }

    function initMessage() {
        console.log("zhangp dood initMessage !!!!")
        //        chatPage.loadDataFlag = true;

        inputTextArea.text = ""
        chatManager.deleteMessageListItem()
        chatManager.initChatState()
        chatManager.entryChat(chatPage.targetid)
        chatManager.getMessages(chatPage.targetid, 20)
    }

    WallClock {
        id: clock
    }

    contentAreaItem:Item {
        Rectangle {
            id: chatPageBackground
            anchors.fill: parent
            color: "#f2f2f2"
        }
        Rectangle{
            id: titleBackground

            color:"#003953"
            width:parent.width
            height:86
            anchors{
                top:parent.top
                left:parent.left
            }
            IconButton{
                id:btnBack
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    btnEmotion.isKeyboard = true;
                    pageStack.pop();
                }
            }
            Text{
                text:chatPage.chatName
                color:"white"
                font.pixelSize: 36

                anchors.left: btnBack.right
                anchors.leftMargin: 50
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        CEditListView {
            id: chatListView
            anchors.top: parent.top

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: titleBackground.height
            anchors.bottom: functionPanelRoot.top

            property variant selectDeleteIndexList
            property bool ifSessionListAtEnd: true

            clip: true
            model: chatManager
            flickDeceleration: 3000
            cacheBuffer: chatListView.height * 2
            delegate: CDoodChatDelegate {
                Component.onCompleted: {
                    if(chatPage.loadDataFlag)
                    {
                        loadDataCheckTimer.restart()
                    }
                }
            }

            Rectangle {
                id: chatListScrollbbar
                objectName: "chatListScrollbbar"

                anchors.right: chatListView.right
                anchors.rightMargin: 5
                y: chatListView.visibleArea.yPosition * chatListView.height + 10
                width: 7
                height: chatListView.visibleArea.heightRatio * chatListView.height - 20
                color: "#d9d9d9"
                radius: 3

                visible: opacity === 0 || chatListView.count === 0 ? false : true
                opacity: 0

                onYChanged: {
                    chatListScrollbbar.opacity = 1
                    chatListScrollbbarTimer.start()
                }

                Behavior on opacity {
                    NumberAnimation { duration: 200 }
                }

                Timer {
                    id: chatListScrollbbarTimer
                    interval: 300;
                    running: false;
                    repeat: false
                    onTriggered: {
                        chatListScrollbbar.opacity = 0
                    }
                }
            }

            onMovingChanged: {
                if(!moving && chatListScrollbbar.y >=0 && chatListScrollbbar.y < chatPage.getMessageHeight * 4) {
                    chatPage.bNeedViewToEnd = false
                    // todo
                    chatManager.getMessages(chatPage.targetid, 20)
                }
                btnEmotion.isKeyboard = true;
            }

            footer: Item {
                id: refreshRoot

                width: chatListView.width
                height: chatPage.getMessageHeight
            }

            onFlickEnded: {
                chatListView.ifSessionListAtEnd = atYEnd
            }

            onDraggingChanged: {
                chatListView.ifSessionListAtEnd = atYEnd

                if (chatListView.count === 0) {
                    return;
                }

                if(dragging) {
                    inputTextArea.focus = false
                }
            }

            onCountChanged: {
                if(chatPage.loadDataFlag)
                {
                    loadDataCheckTimer.restart()
                }
            }

            onHeightChanged: {
                console.log("zhangp === onHeightChanged!!!!")
                if (inputShow) {
                    chatListView.cancelFlick()
                    if(!chatListView.editing) {
                        chatListView.positionViewAtEnd()
                    }
                }
            }
        }

        // 聊天功能面板
        Item {
            id: functionPanelRoot

            anchors.left: parent.left
            anchors.bottom: selectionAddDialog.height > 0 ? selectionAddDialog.top : parent.bottom

            width: parent.width
            height: inputMessageRoot.visible ? inputMessageRoot.height + 30 : 100
            visible: true
            clip: true

            Rectangle {
                anchors.fill: parent
                color: "#ffffff"
            }
            //表情按钮
            CToolButton{
                id:btnEmotion

                backgroundIconSource:!isKeyboard ? "qrc:/res/chatting_setmode_keyboard_btn.png": "qrc:/res/chatting_biaoqing_btn.png"
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                property bool isKeyboard: true
                visible: false
                onClicked: {

                    console.log("123xxxxxxxxxxxxxxx:"+isKeyboard)
                    if(isKeyboard){

                        isKeyboard = false;
                        inputTextArea.focus = false;
                        //btnEmotion.backgroundIconSource = "qrc:/res/chatting_setmode_keyboard_btn.png";
                    }else{
                        isKeyboard = true;
                        inputTextArea.focus = true;
                        //btnEmotion.backgroundIconSource = "qrc:/res/chatting_biaoqing_btn.png";
                    }
                }
            }

            // 输入文字信息
            Item {
                id: inputMessageRoot

                anchors.centerIn: parent
                anchors.horizontalCenterOffset: -30
                //anchors.left: parent.left
                //anchors.leftMargin: 30
                //anchors.verticalCenter: parent.verticalCenter
                width: 460
                height: inputTextArea.contentHeight < 70 ? 70 : inputTextArea.contentHeight > 218 ? 218 : inputTextArea.contentHeight

                visible: true

                Image {
                    id: inputBg
                    anchors.fill: parent
                    source: "qrc:/res/editBg.png"
                    asynchronous: true
                }
                Rectangle {
                    anchors.fill: parent
                    border.width: 2
                    border.color: "#d7d7d7"
                    anchors.centerIn: parent
                    radius: 10
                    color: "#ffffff"
                    opacity: 1
                }

                CEmojiTextArea {
                    id: inputTextArea
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10

                    property int oldLength: 0

                    verticalAlignment: TextEdit.AlignVCenter
                    textColor: "#333333"
                    font.pixelSize: 28
                    focus : false
                    maximumLength: 500
                    textMargin: 12
                    wrapMode: TextEdit.Wrap
                    textFormat:TextEdit.RichText
                    inputMethodHintExtensions: {
                        var args = {};
                        args["enterKeyText"] = "send"
                        return args;
                    }

                    onFocusChanged: {
                        console.log("zhangp onFocusChanged = ", focus)
                        if(focus) {
                            inputTextArea.cursorPosition = inputTextArea.length
                            btnEmotion.isKeyboard = true

                        } else {
                            //btnEmotion.isKeyboard = false
                        }
                    }

                    onKeyReleased: {
                        console.log("dood === onKeyReleased: key = ", key)

                        if(key === Qt.Key_Return)
                        {
                            inputTextArea.text = ""
                        }
                    }

                    onKeyPressed: {
                        console.log("dood === onKeyPressed: key = ", key)

                        if (key === Qt.Key_Return)
                        {
                            console.log("dood === Key_Return !!!!")
                            sendTextMsg()
                        }
                    }

                    onTextChanged:  {
                        oldLength = text.length
                    }
                }
            }
            Rectangle{
                id:rectSendButtunBk

                anchors.left: inputMessageRoot.right
                anchors.leftMargin: 20
                anchors.verticalCenter: inputMessageRoot.verticalCenter
                width:100
                height:inputMessageRoot.height
                radius: 10
                color:"#ffffff"
                Text{
                    id:sendBtn

                    text:qsTr("发送")
                    font.pixelSize: 30
                    color:"#333333"
                    anchors.centerIn: parent
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            sendTextMsg();
                        }
                        onReleased: {
                            rectSendButtunBk.color="#ffffff"
                            sendBtn.color = "#333333"
                        }
                        onPressed: {
                            rectSendButtunBk.color="#003953"
                            sendBtn.color = "white"
                        }
                    }
                }
            }
        }

        // 工具面板
        Item {
            id: selectionAddDialog
            anchors.bottom: parent.bottom

            width: parent.width
            visible: !btnEmotion.isKeyboard
            height: setHieght()

            Behavior on height {
                NumberAnimation { duration: 150 }
            }
            CDoodEmojiTabView{
                id: background
                anchors.fill: parent
                //width:parent.width
            }
            function setHieght(){

                console.log("softwareInputPanelRect:"+gInputContext.softwareInputPanelRect.height)
                if(!btnEmotion.isKeyboard){
                    return 480;
                }
                return gInputContext.softwareInputPanelRect.height;
            }
        }
    }

    Connections{
        target: userEmojiManager
        onSignalEmojiChanged:{
            inputTextArea.insert(inputTextArea.cursorPosition,path);
        }
    }
    Connections{
        target: userDyEmojiManager
        onSignalEmojiChanged:{
            chatManager.sendDyEmojiMsg(path);
            chatListView.positionViewAtEnd();
        }
    }
}
