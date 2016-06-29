import QtQuick 2.0
import com.syberos.basewidgets 2.0

CPage {
    id: userdataPage

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            userdataPage.statusBarHoldEnabled = true
            gScreenInfo.setStatusBar(userdataPage.statusBarHoldEnabled)
            userdataPage.statusBarHoldItemColor = "#edf0f0"
            gScreenInfo.setStatusBarStyle("black")
        }
    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: userdataBackground

            anchors.fill: parent
            color: "white"
            Rectangle{
                id: titleBarBk

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
                        pageStack.pop();
                    }
                }
                Text{
                    text:qsTr("个人信息")
                    color:"white"
                    font.pixelSize: 36

                    anchors.centerIn: parent
                }
            }
            Rectangle {
                id:bascicBackground

                color:"white"
                border.width: 1
                border.color: "#777777"
                radius: 10
                height: 430

                anchors.top: titleBarBk.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                anchors.topMargin: 20

                UserProfileButton{
                    id:btnIcon

                    leftText: qsTr("头像")
                    height: 120
                    radius: 4
                    rightImg: "qrc:/res/moren_icon_female.png"
                    anchors.top: parent.top
                }

                UserProfileButton{
                    id:btnName

                    leftText: qsTr("名字")
                    editable:true
                    rigthText: userProfileManager.name
                    anchors.top: btnIcon.bottom
                    onClicked: {
                        inputDialog.titleText= qsTr("名字");
                        inputDialog.setText(userProfileManager.name);
                        inputDialog.type = 1;
                        inputDialog.show();
                    }
                }
                UserProfileButton{
                    id:btnMap

                    leftText: qsTr("二维码")

                    anchors.top: btnName.bottom
                }
                UserProfileButton{
                    id:btnDD

                    leftText: qsTr("圆圆号")
                    radius: 4
                    showLine:false

                    anchors.top: btnMap.bottom

                }
            }

            Rectangle {
                id:moreBackground

                color:"white"
                border.width: 1
                border.color: "#777777"
                radius: 10
                height: 512

                anchors.top: bascicBackground.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 20
                anchors.rightMargin: 20
                anchors.topMargin: 10

                UserProfileButton{
                    id:btnSex

                    leftText: qsTr("性别")
                    editable:true
                    radius: 4
                    rigthText: userProfileManager.gender
                    anchors.top: parent.top
                    onClicked: {
                        sexListDialog.deselect();
                        sexListDialog.select(sexListDialog.initSelect(),true);
                        sexListDialog.show();
                    }
                }
                UserProfileButton{
                    id:btnBirth

                    leftText: qsTr("生日")

                    anchors.top: btnSex.bottom
                }
                UserProfileButton{
                    id:btnPhone

                    leftText: qsTr("联系方式")

                    anchors.top: btnBirth.bottom

                }
                UserProfileButton{
                    id:btnAddress

                    leftText: qsTr("地区")

                    anchors.top: btnPhone.bottom

                }
                UserProfileButton{
                    id:btnRemark

                    leftText: qsTr("个性签名")
                    radius: 4
                    showLine:false

                    anchors.top: btnAddress.bottom

                }
            }
        }
    }
    CInputDialog{
        id:inputDialog

        property int  type
        messageTextColor:"#777777"
        onAccepted: {
            if(type === 1){
                userProfileManager.updateAccountInfo(inputDialog.text(),"","");
            }
        }
    }
    CListDialog{
        id: sexListDialog

        titleText: qsTr("性别")
        onDelegateItemTriggered:{
            console.log("xxxxxxxxx:"+model[index]);
            userProfileManager.updateAccountInfo(btnName.rigthText,"",model[index]);
        }
        Component.onCompleted: {
            model = [qsTr("保密"),qsTr("男"),qsTr("女")]
        }
        function initSelect(){
            if(userProfileManager.gender === qsTr("女")){
                return 2;
            }
            if(userProfileManager.gender === qsTr("男")){
                return 1;
            }
            return 0;
        }
    }
}
