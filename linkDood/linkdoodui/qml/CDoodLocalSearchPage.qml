import QtQuick 2.0
import com.syberos.basewidgets 2.0
CDoodPopWndLayer{
    id: searchMenu

    property string isStar
    property string id: ""
    property string name: ""
    contentItemBackGroundOpacity:0.73

//    onOutAreaClicked:{
//        editContactId.text=""
//        localSearchManager.contactListClear();
//        searchMenu.hide();
//        editContactId.text = "";
//    }

    onBackKeyReleased:{
        editContactId.text=""
        localSearchManager.contactListClear();
        searchMenu.hide();
        editContactId.text = "";
    }

    contentItem:Rectangle{
        id: pageBackground

        color: "transparent"
        anchors.fill: parent

        Rectangle{
            id: titleBackground

            color:"#003953"
            width:parent.width
            height:90
            anchors{
                topMargin: 49
                top:parent.top
                left:parent.left
            }
            IconButton{
                id:btnBack
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    editContactId.text=""
                    localSearchManager.contactListClear();
                    searchMenu.hide()
                    editContactId.text = "";
                }
            }

            Rectangle{
                id:searchContactId
                height: 65
                radius: 10
                color: "white"
                anchors.left: btnBack.right
                anchors.right: parent.right
                anchors.rightMargin: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.margins: 30
                CLineEdit {
                    id: editContactId
                    anchors.fill: parent
                    searchLabelEnabled:true
                    focus: true

                    textColor:"#787777"
                    font.pixelSize: 30
                    placeholderText:os.i18n.ctr(qsTr("搜索"))
                    inputMethodHints: Qt.ImhHiddenText/*|Qt.ImhPreferNumbers*/
                    inputMethodHintExtensions: {
                        var args = {};
                        args["enterKeyText"] = "search"
                        return args;
                    }
                    onKeyPressed: {
                        console.log("dood === onKeyPressed: key = ", key)

                        if (key === Qt.Key_Return)
                        {
                            console.log("dood === Key_Return !!!!")
                            localSearchManager.searchFromLocal(editContactId.text)
                        }
                    }
                }

            }
        }
        ListView {
            id: contactListView

            anchors.top: titleBackground.bottom
            width:parent.width
            height: getHeight()

            onCountChanged: {
                contactListView.height = getHeight()
                console.log("32442423423423424231121221 : " + searchMenu.height )
            }

            clip: true
            model:localSearchManager
            section.property: "modelData.searchKey"
            section.criteria: ViewSection.FullString
            section.delegate: Rectangle {
                width: contactListView.width
                height: 35
                color: "#F2F2F2"

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 25
                    anchors.verticalCenter: parent.verticalCenter
                    text: section
                    font.pixelSize: 22
                    color: "#333333"
                    onTextChanged: {
                        console.log("xxxxxx:"+text)
                    }
                }
            }

            function getHeight() {
                var maxLen = 1042;
                var len = contactListView.count*104+localSearchManager.searchKeyCount*35;
                if(len >= maxLen){
                    len = maxLen;
                }
                return len;
            }
            delegate:Item {
                id:contactListDelegate

                width: contactListView.width
                height: 104
                Rectangle {
                    id:background

                    anchors.fill: parent

                    MouseArea{
                        anchors.fill: parent
                        onPressed: {
                            background.color = "#CDCDCD";
                        }
                        onReleased: {
                            background.color = "#FFFFFF";

                        }
                        onCanceled: background.color = "#FFFFFF"
                        onClicked: {
                            editContactId.text = "";
                            if(model.modelData.userOrGroup === "2"){
                                chatManager.switchToChatPage(model.modelData.id,model.modelData.name,"2","0",0,model.modelData.thumbAvatar);
                            }else{
                                chatManager.switchToChatPage(model.modelData.id,model.modelData.name,"1","0",0,model.modelData.thumbAvatar);
                            }

                            localSearchManager.contactListClear();
                            searchMenu.hide();
                            editContactId.text = "";
                        }
                    }
                }
                CDoodHeaderImage {
                    id: headPortraitImage

                    anchors.left: parent.left
                    anchors.leftMargin: 25
                    anchors.verticalCenter: parent.verticalCenter
                    width: 90
                    height: 90
                    radius: 6
                    name:""
                    iconSource: setIcon(model.modelData.userOrGroup,model.modelData.thumbAvatar)
                    Text {
                        id: nameText
                        anchors.left: headPortraitImage.right
                        anchors.leftMargin: 30
                        anchors.rightMargin: 20
                        anchors.top: headPortraitImage.top
                        anchors.topMargin: 10
                        font.pixelSize: 26
                        clip: true
                        color: "#333333"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                        text: model.modelData.name
                    }
                }
                CLine {
                    width: parent.width
                    anchors.bottom: parent.bottom
                    z: parent.z+2
                }
            }
            CScrollDecorator{
                flickableItem: contactListView
            }
        }
    }
}
