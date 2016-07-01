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
            height: 58
            color: "#e7e7e7"

            Text {
                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.verticalCenter: parent.verticalCenter
                text: section
                font.pixelSize: 32
                color: "#333333"
                onTextChanged: {
                    console.log("xxxxxx:"+text)
                }
            }
        }

        delegate:Item {
            id:contactListDelegate

            width: contactListView.width
            height: 104

            Timer {
                id:pressTimer

                interval: 1500
                repeat: false
                onTriggered:{
                    if(mouse.bPress && !mouse.bMove){
                        menu.id = model.modelData.id;
                        menu.isStar= model.modelData.isStar;
                        menu.show();
                    }
                    pressTimer.stop();
                }
            }
            MouseArea {
                id:mouse

                anchors.fill: parent

                property var pressTime;
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

                    bMove  = false;
                    bPress = true;
                    pressTimer.start();

                    pressTime = (new Date()).getTime();
                }

                onPositionChanged: {
                    bMove = true;
                }

                onReleased: {
                    var curTime = (new Date()).getTime();
                    var dx = (curTime - pressTime)/1000;

                    background.color = "#ffffff"
                    mousePressBackgroud.visible = false
                    bPress = false;
                    bMove  = false;
                    if(pressTimer.running){
                        pressTimer.stop();
                        userdataManager.setName(model.modelData.name);
                        userdataManager.setGender(model.modelData.gender);
                        userdataManager.setThumbAvatar(model.modelData.thumbAvatar);
                        userdataManager.setId(model.modelData.id);
                        pageStack.push(Qt.resolvedUrl("CDoodUserDataPage.qml"));
                    }

                    if(dx<0.5){

                    }else{

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
                    anchors.topMargin: 1
                    anchors.bottomMargin: 3
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
                        headerColor: sessionListManager.getHeaderColor(model.modelData.id)
                        iconSource: "qrc:/res/headerDefault.png"/*"file://"+ model.modelData.thumbAvatar*/
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
                                indicatorDialog.hide();
                            }
                        }
                    }
                    Text {
                        id: nameText
                        anchors.left: headPortraitImage.right
                        anchors.leftMargin: 30
                        anchors.rightMargin: 20
                        anchors.top: headPortraitImage.top
                        anchors.topMargin: 10
                        font.pixelSize: 32
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

        contentItem:Rectangle{

            color: "white"
            radius: 10
            width:489
            height: 190
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
                leftText: menu.isStar ==="1"?qsTr("取消V标好友") :qsTr("标为V标好友") ;
                radius: 4

                anchors.top: line.bottom
                anchors.topMargin: 10
                anchors.bottom:parent.bottom
                anchors.bottomMargin: 2
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
}

