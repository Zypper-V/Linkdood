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
    Connections {
        target: contactManager
        onContactInfoChanged:{
            if(userdataManager.buttonType==="3"){
                contactManager.getContactInfo(userdataManager.id);
            }
        }
    }
    Connections{
        target: memberManager
        onWordsOutOfLimited:{
            gToast.requestToast(tip,"","");
        }
        onGetMemberInfoResult:{
            userdataManager.setName(name);
        }
        onRemoveMemberResult:{
            gToast.requestToast(result,"","");
            if(result==="移除群成员成功"){
                userdataManager.clearData();
                pageStack.pop();
            }
        }
        onSetMemberInfoResult:{
            if(id===userdataManager.id){
                userdataManager.setRemark(remark);
                gToast.requestToast("设置成功","","");
            }
        }
    }
    Connections {
        target: groupManager
        onTransferGroupResult:{
            gToast.requestToast(result,"","");
        }
    }
    contentAreaItem:Item {
        anchors.fill :parent
        Rectangle {
            id: userdataBackground
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
                    userdataManager.clearData();
                    pageStack.pop();
                }
            }
            Text{
                text:qsTr("详细资料")
                color:"white"
                font.pixelSize: 36
                anchors.centerIn: parent
            }
            Image{
                id:settingButton
                anchors.right: parent.right
                anchors.rightMargin: 30
                visible: userdataManager.buttonType===""||userdataManager.buttonType==="m"?false:true
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/res/main_title_setting_button.png"
                MouseArea{
                    anchors.fill: parent
                    onPressed: {
                        settingButton.source="qrc:/res/main_title_setting_button_press.png"
                    }
                    onReleased: {
                        settingButton.source="qrc:/res/main_title_setting_button.png"
                    }

                    onClicked: {
                      if(userdataManager.buttonType==="1"){
                          menu1.id=userdataManager.id;
                          menu1.groupid=userdataManager.groupid;
                          if(userdataManager.remark!==""){
                          menu1.name=userdataManager.remark;
                          }
                          else{
                              menu1.name=userdataManager.name;
                          }
                          menu1.show();
                      }
                      else if(userdataManager.buttonType==="2"){
                          menu.id = userdataManager.id;
                          menu.member_type= userdataManager.memberType;
                          if(userdataManager.remark!==""){
                          menu.name=userdataManager.remark;
                          }
                          else{
                              menu.name=userdataManager.name;
                          }
                          menu.groupid=userdataManager.groupid;
                          menu.show()
                      }
                      else if(userdataManager.buttonType==="3"){
                          menu2.id = userdataManager.id;
                          menu2.isStar= userdataManager.memberType;
                          if(userdataManager.remark!==""){
                          menu2.name=userdataManager.remark;
                          }
                          else{
                              menu2.name=userdataManager.name;
                          }
                          menu2.show();
                      }
                    }
                }
            }
        }
        Rectangle{
            id:userdatapic
            anchors.top:titleBackground.bottom
            height:309
            width:parent.width
            color: "#f2f2f2"
            Image{
                id:headimagebackgroud
                width:parent.width
                anchors.top:parent.top
                height:215
                z: 5
//                source: "qrc:/res/descbgtop.jpg"
                source: "qrc:/res/friend_info_bg.png"
                Text{
                    id:username
                    anchors.bottom: parent.bottom
                    anchors.left:parent.left
                    anchors{
                        leftMargin: 210
                        bottomMargin: 24
                    }
                    text:getname()
                    function getname(){
                        if(userdataManager.buttonType==="m"||userdataManager.buttonType==="1"||userdataManager.buttonType==="2"){
                            if(userdataManager.remark===""){
                               return "群名片："+userdataManager.name;
                            }
                            return "群名片："+userdataManager.remark;
                        }
                        else{
                            if(userdataManager.remark===""){
                                return "备注："+userdataManager.name
                            }
                            return "备注："+userdataManager.remark;
                        }
                    }
                    color:"white"
                    font.pixelSize: 32
                }
            }
            CDoodHeaderImage {
                id:headImage
                anchors.top:parent.top
                anchors.left:parent.left
                width:160
                height: 160
                radius:10
                z:100
                anchors{
                    topMargin:138
                    leftMargin:36
                }
                name:""
                iconSource: setIcon("1",userdataManager.thumbAvatar)
            }
            CLine {
                width: parent.width
                z: parent.z+10

                anchors.bottom: parent.bottom
            }
        }
        Rectangle{
            id:userdata
            width: parent.width
            anchors.top:userdatapic.bottom
            color:"white"
            height: 249
            Rectangle{
                id:name
                width: parent.width
                anchors.top:parent.top
                height: 83
                Text{
                    anchors{
                        left:parent.left
                        leftMargin:39
                        verticalCenter: parent.verticalCenter
                    }

                    text:qsTr("姓名")
                    font.pixelSize: 30
                }
                Text{
                    anchors{
                        right:parent.right
                        rightMargin:20
                        verticalCenter: parent.verticalCenter
                    }

                    text:userdataManager.name
                    font.pixelSize: 30
                }
                CLine {
                    width: parent.width
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 39
                    z: parent.z+10

                    anchors.bottom: parent.bottom
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        console.log(userdataManager.name);
                    }
                }
            }
            Rectangle{
                id:sex
                width: parent.width
                anchors.top:name.bottom
                height: 83
                Text{
                    anchors{
                        left:parent.left
                        leftMargin:39
                        verticalCenter: parent.verticalCenter
                    }

                    text:qsTr("性别")
                    font.pixelSize: 30
                }
                Text{
                    anchors{
                        right:parent.right
                        rightMargin:20
                        verticalCenter: parent.verticalCenter
                    }

                    text:userdataManager.gender
                    font.pixelSize: 30
                    onTextChanged: {
                        console.log("XXXXXXXXXXXXXXX:"+userdataManager.gender)
                    }
                }
                CLine {
                    width: parent.width
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: 39
                    z: parent.z+10

                    anchors.bottom: parent.bottom
                }
            }
            Rectangle{
                id:phone
                visible: userdataManager.phone !== ""
                width: parent.width
                anchors.top:sex.bottom
                height: 83
                Text{
                    anchors{
                        left:parent.left
                        leftMargin:39
                        verticalCenter: parent.verticalCenter
                    }

                    text:qsTr("联系方式")
                    font.pixelSize: 30
                }
                Text{
                    id:phoneText

                    anchors{
                        right:parent.right
                        rightMargin:20
                        verticalCenter: parent.verticalCenter
                    }

                    text:userdataManager.phone
                    font.pixelSize: 30
                }
                CLine {
                    width: parent.width
                    anchors.left: parent.left
                    anchors.right: parent.right
                    z: parent.z+10

                    anchors.bottom: parent.bottom
                }
            }
        }
        CButton{
            id:sendmessage

            anchors.top:userdata.bottom
            anchors.topMargin: 140
            anchors.horizontalCenter: parent.horizontalCenter

            width: parent.width - 40
            height: 90
            opacity : pressed ? 0.7: 1
            visible: userdataManager.isFriend && userdataManager.id !== userProfileManager.id
            text:os.i18n.ctr(qsTr("发消息"))
            textColor:  "#ffffff"
            pixelSize:34
            backgroundComponent: Rectangle {
                anchors.fill: parent
                color:"#32c2fe"
                radius: 10
            }
            onClicked: {
                console.log("org name:"+userdataManager.name+"thm:"+userdataManager.thumbAvatar);
                chatManager.switchToChatPage(userdataManager.id,userdataManager.name,"1","0",0,userdataManager.thumbAvatar);
            }
        }
        CButton{
            id:addBuddy

            visible: !userdataManager.isFriend
            anchors.top:userdata.bottom
            anchors.topMargin: 140
            anchors.horizontalCenter: parent.horizontalCenter

            width: parent.width - 40
            height: 90
            opacity : pressed ? 0.7: 1
            text:os.i18n.ctr(qsTr("添加好友"))
            textColor:  "#ffffff"
            pixelSize:34
            backgroundComponent: Rectangle {
                anchors.fill: parent
                color:"#32c2fe"
                radius: 10
            }
            onClicked: {
                //TODO
                addContactManager.getVerifyType(userdataManager.id)
            }
        }
    }
    Connections{
        target: addContactManager
        onGetVerifyResult:{
            if(code !== 0)
            {
                gToast.requestToast("获取验证方式失败","","");
                return;
            }
            if(type === 2) //2:不允许任何人添加
            {
                gToast.requestToast("不允许任何人添加","","");
            }
            else if(type === 1) //1:需要验证信息
            {
                friendVericationManager.setName(userdataManager.name);
                friendVericationManager.setThumbAvatar(userdataManager.thumbAvatar);
                friendVericationManager.setMyName(userProfileManager.name);
                friendVericationManager.setId(userdataManager.id);
                pageStack.push(Qt.resolvedUrl("CDoodFriendVerificationPage.qml"));
            }
            else if(type === 3) //3:允许任何人添加
            {
                 addContactManager.addContact(userdataManager.id,"","");
                 gToast.requestToast("添加好友成功","","");
                 pageStack.pop();
            }
        }
    }
    CDoodPopWndLayer{
        id:menu
        property string member_type
        property string id: ""
        property string name: ""
        property string groupid: ""
        contentItemBackGroundOpacity:0.73
        contentItem:Rectangle{

            color: "white"
            radius: 10
            width:489
            height: memberManager.my_Type==="3"?510:310
            Text{
                id:title

                text:qsTr("提示")
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
                visible: memberManager.my_Type==="3" ? true : false
                width:parent.width
                height: 100
                leftText: menu.member_type ==="1"?qsTr("提升为管理员") :qsTr("取消管理员") ;
                radius: 4

                anchors.top: line.bottom
                anchors.topMargin: 10

                onClicked: {
                    menu.hide();

                    console.log("33333333333333333333333333")
                    alertDialog_Mem.id=menu.id;
                    alertDialog_Mem.groupid=menu.groupid;
                    alertDialog_Mem.member_type=menu.member_type;
                    if(menu.member_type == "1"){
                        alertDialog_Mem.operate="是否提升 "+menu.name+" 为管理员"
                        //                        memberManager.setMemberInfo(menu.groupid,menu.id,"管理员设置","2");
                    }else{
                        alertDialog_Mem.operate="是否取消 "+menu.name+" 管理员权限"
                        //                        memberManager.setMemberInfo(menu.groupid,menu.id,"管理员设置","1");
                    }
                    alertDialog_Mem.show();
                    //                    indicatorDialog.show();
                }
            }
            UserProfileButton{
                id:btntran

                width:parent.width
                height: 100
                leftText: qsTr("修改群名片")
                radius: 4

                anchors.top: memberManager.my_Type==="3" ?btnStar.bottom:line.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu.hide();

                    inputDialog.id=menu.id;
                    inputDialog.groupid=menu.groupid;
                    inputDialog.remark=menu.name;
                    inputDialog.setText(menu.name);
                    inputDialog.show();
                }
            }
            UserProfileButton{
                id:btnDel

                width:parent.width
                height: 100
                leftText: qsTr("移除群成员")
                radius: 4
                showLine:memberManager.my_Type==="3" ? true : false
                anchors.top: btntran.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu.hide();
                    alertDialog_deleMem.operate="是否移除群成员 "+menu.name;
                    alertDialog_deleMem.id=menu.id;
                    alertDialog_deleMem.groupid=menu.groupid;
                    alertDialog_deleMem.show();
                }
            }
            UserProfileButton{
                id:btnRemark
                visible: memberManager.my_Type==="3" ? true : false
                width:parent.width
                height:100
                leftText: qsTr("转让该群") ;
                radius: 4
                showLine:false

                anchors.top: btnDel.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu.hide();
                    alertDialog_trans.operate="是否将本群转让给 "+menu.name;
                    alertDialog_trans.id=menu.id;
                    alertDialog_trans.groupid=menu.groupid;
                    alertDialog_trans.show();
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
    CDoodPopWndLayer{
        id:menu1
        property string id: ""
        property string groupid: ""
        property string name: ""
        contentItemBackGroundOpacity:0.73
        contentItem:Rectangle{

            color: "white"
            radius: 10
            width:489
            height: 190
            Text{
                id:title1

                text:qsTr("提示")
                font.pixelSize: 36
                color:"#333333"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
            }
            CLine{
                id:line1

                anchors.top:title1.bottom
                anchors.topMargin: 10
                height: 2
            }
            UserProfileButton{
                id:btntran1

                width:parent.width
                height: 100
                leftText: qsTr("修改群名片")
                radius: 4

                anchors.top: line1.bottom
                anchors.topMargin: 10
                showLine:false
                onClicked: {
                    menu1.hide();

                    inputDialog.id=menu1.id;
                    inputDialog.groupid=menu1.groupid;
                    inputDialog.remark=menu1.name;
                    inputDialog.setText(menu1.name);
                    inputDialog.show();
                }
            }
        }
        onBackKeyReleased: {
            console.log("11111111111111111111111111111111111")
            menu1.hide();
        }
        onOutAreaClicked: {
            console.log("222222222222222222222222222222")
            menu1.hide();
        }
    }
    CInputDialog{
        id:inputDialog
        property string id: ""
        property string groupid: ""
        property string remark: ""
        titleText: qsTr("修改群名片")
        messageTextColor:"#777777"
        onAccepted: {
            if(inputDialog.text()===inputDialog.remark){
                return;
            }
            memberManager.setMemberInfo(inputDialog.groupid,inputDialog.id,"修改备注",inputDialog.text());
        }
    }
    CDialog {
        property string operate: ""
        property string id: ""
        property string groupid: ""
        id: alertDialog_deleMem

        titleText: qsTr("提示")
        messageText: alertDialog_deleMem.operate
        onAccepted: {
            memberManager.removeMember(alertDialog_deleMem.groupid,alertDialog_deleMem.id);

        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
    CDialog {
        property string operate: ""
        property string id: ""
        property string groupid: ""
        id: alertDialog_trans

        titleText: qsTr("提示")
        messageText: alertDialog_trans.operate
        onAccepted: {

            groupManager.transferGroup(menu.groupid,menu.id);
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
    CDialog {
        property string operate: ""
        property string id: ""
        property string groupid: ""
        property string member_type: ""
        id: alertDialog_Mem

        titleText: qsTr("提示")
        messageText: alertDialog_Mem.operate
        onAccepted: {
            if(alertDialog_Mem.member_type == "1"){
                memberManager.setMemberInfo(menu.groupid,menu.id,"管理员设置","2");
            }else{
                memberManager.setMemberInfo(menu.groupid,menu.id,"管理员设置","1");
            }

        }
        onCanceled: {
            console.log("onCanceled")
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
        id:menu2

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
                id:title2

                text:qsTr("好友操作")
                font.pixelSize: 36
                color:"#333333"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 20
            }
            CLine{
                id:line2

                anchors.top:title2.bottom
                anchors.topMargin: 10
                height: 2
            }
            UserProfileButton{
                id:btnStar2

                width:parent.width
                height: 100
                leftText: menu2.isStar ==="1"?qsTr("取消V标好友") :qsTr("标为V标好友") ;
                radius: 4

                anchors.top: line2.bottom
                anchors.topMargin: 10

                onClicked: {
                    menu2.hide();

                    console.log("33333333333333333333333333")
                    if(menu2.isStar == "1"){
                        contactManager.updateContactInfo(menu2.id,"2");
                    }else{
                        contactManager.updateContactInfo(menu2.id,"1");
                    }
                    indicatorDialog.show();
                }
            }
            UserProfileButton{
                id:btnDel2

                width:parent.width
                height: 100
                leftText: qsTr("删除好友") ;
                radius: 4

                anchors.top: btnStar2.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu2.hide();
                    alertDialog.show();
                }
            }
            UserProfileButton{
                id:btnRemark2

                width:parent.width
                height:100
                leftText: qsTr("修改备注") ;
                radius: 4
                showLine:false

                anchors.top: btnDel2.bottom
                anchors.topMargin: 10
                onClicked: {
                    menu2.hide();
                    inputDialog2.setText(menu2.name);
                    inputDialog2.show();
                }
            }
        }

        onBackKeyReleased: {
            console.log("11111111111111111111111111111111111")
            menu2.hide();
        }
        onOutAreaClicked: {
            console.log("222222222222222222222222222222")
            menu2.hide();
        }
    }
    Connections{
        target: contactManager
        onRemoveContactResult:{
            indicatorDialog.hide();
            pageStack.pop();
        }
        onUpdateContactInfoResult:{
            indicatorDialog.hide();
            gToast.requestToast(qsTr("设置成功"),"","");
        }
    }

    CInputDialog{
        id:inputDialog2
        titleText: qsTr("修改备注")
        messageTextColor:"#777777"
        maximumLength:20
        onAccepted: {
            if(inputDialog2.text()===menu2.name){
                return;
            }
            contactManager.updateContactInfo(menu2.id,"",inputDialog2.text());
            indicatorDialog.show();
        }
    }
    CDialog {
        id: alertDialog

        titleText: qsTr("提示")
        messageText: qsTr("您确定要删除该好友？")
        onAccepted: {
            contactManager.removeContact(menu2.id);
            indicatorDialog.show();
        }
        onCanceled: {
            console.log("onCanceled")
        }
    }
}
