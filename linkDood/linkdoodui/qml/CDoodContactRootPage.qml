import QtQuick 2.0
import com.syberos.basewidgets 2.0
Item {
    id: contactRootPage
    anchors.fill: parent
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left

        width:parent.width
        height: parent.height

        color: "white"
        z:parent.z-1
    }
    ListView {
        id: contactListView

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        clip: true
        model: contactManager

        // todo 缺少sectionKey字段
        section.property: "modelData.sectionKey"
        section.criteria: ViewSection.FullString
        section.delegate: Rectangle {
            width: contactRootPage.width
            height: textSection.text !=="" ? 38 :0
            color: "#F2F2F2"
            Text {
                id:textSection

                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.verticalCenter: parent.verticalCenter
                text: (section !== "app" ? section:"")
                font.pixelSize: 26
                color: "#333333"
                onTextChanged: {
                    console.log("xxxxxx:"+text)
                }
            }
        }

        delegate:Item {
            id:contactListDelegate

            width: contactListView.width
            height: 100

            Timer {
                id:pressTimer

                interval: 700
                repeat: false
                onTriggered:{
                    if(mouse.bPress && !mouse.bMove){
                        menu.id = model.modelData.id;
                        menu.isStar= model.modelData.isStar;
                        menu.name  = model.modelData.name;
                        menu.show();
                    }
                    pressTimer.stop();
                }
            }
            MouseArea {
                id:mouse

                anchors.fill: parent

                property bool bPress
                property bool bMove
                onPressed: {
                    if(mousePressBackgroud.visible){
                        background.color = "#ffffff"
                        mousePressBackgroud.visible = false
                    }else{
                        background.color = "#cdcdcd"
                        mousePressBackgroud.visible = true
                    }

                    if(model.modelData.id==="2"){
                        pageStack.push(Qt.resolvedUrl("CDoodGroupListPage.qml"));
                        return;
                    }else if(model.modelData.id==="6"){
                        chatManager.switchToChatPage(loginManager.userId,model.modelData.name,"6",0,"");
                        return;
                    }

                    bMove  = false;
                    bPress = true;
                    pressTimer.start();
                }

                onPositionChanged: {
                    bMove = true;
                }

                onReleased: {
                    background.color = "#ffffff"
                    mousePressBackgroud.visible = false

                    if(model.modelData.id==="2"){
                        return;
                    }
                    bPress = false;
                    bMove  = false;
                    if(pressTimer.running){
                        pressTimer.stop();
                        userdataManager.setName(model.modelData.name);
                        userdataManager.setGender(model.modelData.gender);
                        userdataManager.setThumbAvatar(model.modelData.thumbAvatar);
                        userdataManager.setId(model.modelData.id);
                        userdataManager.setIsFriend(contactManager.isFriend(model.modelData.id));
                        contactManager.getContactInfo(model.modelData.id);
                        pageStack.push(Qt.resolvedUrl("CDoodUserDataPage.qml"));
                    }
                }

                onCanceled: {
                    background.color = "#ffffff"
                    mousePressBackgroud.visible = false
                }
            }

            Rectangle {
                width: contactListDelegate.width
                height: contactListDelegate.height


                Rectangle {
                    id : mousePressBackgroud
                    anchors.fill: parent
                    visible: false
                    color: "#cdcdcd"
                }

                Rectangle {
                    id : background
                    anchors.fill: parent
                    anchors.top:parent.top
                    anchors.bottom: parent.bottom
                    //                    anchors.topMargin: 1
                    //                    anchors.bottomMargin: 3
                    anchors.leftMargin: 2
                    anchors.rightMargin:  2

                    CDoodHeaderImage {
                        id: headPortraitImage

                        anchors.left: parent.left
                        anchors.leftMargin: 25
                        anchors.verticalCenter: parent.verticalCenter
                        width: 90
                        height: 90
                        radius: 6
                        name:""
                        iconSource:setIcon(setType(),model.modelData.thumbAvatar)
                        function setType(){
                            if(model.modelData.id === "2"){
                                return "2";
                            }else if(model.modelData.id === "6"){
                                return "6";
                            }
                            return "1";
                        }

                        Rectangle{

                            visible: model.modelData.isStar ==="1"
                            width:36
                            height: width
                            radius: width/2
                            color: "#f9b230"
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            anchors.rightMargin: -width/2
                            Text{
                                color:"white"
                                text:qsTr("V")
                                font.pixelSize: 20
                                anchors.centerIn: parent
                            }
                            onVisibleChanged: {
                                if(indicatorDialog !== null){
                                    indicatorDialog.hide();
                                }
                            }
                        }
                    }
                    Text {
                        id: nameText
                        anchors.left: headPortraitImage.right
                        anchors.leftMargin: 30
                        anchors.rightMargin: 20
                        anchors.top: headPortraitImage.top
                        anchors.topMargin: model.modelData.sectionKey==="app"?28:10
                        font.pixelSize: model.modelData.sectionKey==="app"?28:24
                        clip: true
                        color: "#333333"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                        text: model.modelData.name
                    }
                    Text {
                        id: onLineText
                        anchors.left: headPortraitImage.right
                        anchors.leftMargin: 30
                        anchors.rightMargin: 20
                        anchors.top: nameText.bottom
                        anchors.topMargin: 10
                        font.pixelSize: 26
                        clip: true
                        color: "#777777"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                        text: model.modelData.onlineStatus
                    }
                    CLine {
                        width: parent.width
                        anchors.bottom: parent.bottom
                        z: parent.z+2
                    }

                }
            }
        }
        CScrollDecorator{
            flickableItem: contactListView
        }
    }
    IndicatorDialog{
        id:indicatorDialog

        messageText:qsTr("操作正在执行...")
        onBackKeyReleased: {
            indicatorDialog.hide();
        }
    }

    CDoodPopWndLayer{
        id:menu

        property string isStar
        property string id: ""
        property string name: ""
        contentItemBackGroundOpacity:0.73
        contentItem:Rectangle{

            color: "white"
            radius: 10
            width:489
            height: 410
            Text{
                id:title

                text:qsTr("好友操作")
                font.pixelSize: 36
                color:"#333333"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
            }
            CLine{
                id:line

                anchors.top:title.bottom
                anchors.topMargin: 10
                height: 2
            }
            UserProfileButton{
                id:btnStar

                width:parent.width
                height: 100
                leftText: menu.isStar ==="1"?qsTr("取消V标好友") :qsTr("标为V标好友") ;
                radius: 4

                anchors.top: line.bottom
                anchors.topMargin: 10

                onClicked: {
                    menu.hide();

                    console.log("33333333333333333333333333")
                    if(menu.isStar == "1"){
                        contactManager.updateContactInfo(menu.id,"2");
                    }else{
                        contactManager.updateContactInfo(menu.id,"1");
                    }
                    indicatorDialog.show();
                }
            }
            UserProfileButton{
                id:btnDel

                width:parent.width
                height: 100
                leftText: qsTr("删除好友") ;
                radius: 4

                anchors.top: btnStar.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu.hide();
                    alertDialog.show();
                }
            }
            UserProfileButton{
                id:btnRemark

                width:parent.width
                height:100
                leftText: qsTr("修改备注") ;
                radius: 4
                showLine:false

                anchors.top: btnDel.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu.hide();
                    inputDialog.setText(menu.name);
                    inputDialog.show();
                }
            }
        }

        onBackKeyReleased: {
            console.log("11111111111111111111111111111111111")
            menu.hide();
        }
        onOutAreaClicked: {
            console.log("222222222222222222222222222222")
            menu.hide();
        }
    }
    Connections{
        target: contactManager
        onRemoveContactResult:{
            indicatorDialog.hide();
        }
        onUpdateContactInfoResult:{
            indicatorDialog.hide();
        }
    }

    CInputDialog{
        id:inputDialog

        titleText: qsTr("修改备注")
        messageTextColor:"#777777"
        maximumLength:20
        onAccepted: {
            contactManager.updateContactInfo(menu.id,"",inputDialog.text());
            indicatorDialog.show();
        }
    }
    CDialog {
        id: alertDialog

        titleText: qsTr("提示")
        messageText: qsTr("您确定要删除该好友？")
        onAccepted: {
            contactManager.removeContact(menu.id);
            indicatorDialog.show();
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
}

