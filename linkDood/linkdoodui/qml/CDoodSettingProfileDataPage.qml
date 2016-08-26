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
                    editable:false
                    rightImg: userProfileManager.thumbAvatar
                    anchors.top: parent.top
                    onClicked: {
                        var component = pageStack.getCachedPage(Qt.resolvedUrl("CDoodViewLocalImagePage.qml"),"CDoodViewLocalImagePage");
                        pageStack.push(component);
                    }
                }

                UserProfileButton{
                    id:btnName

                    leftText: qsTr("姓名")
                    editable:true
                    rigthText: userProfileManager.name
                    anchors.top: btnIcon.bottom
                    onClicked: {
                        inputDialog.titleText= qsTr("姓名");
                        inputDialog.setText(userProfileManager.name);
                        inputDialog.type = 1;
                        inputDialog.show();
                    }
                }
                UserProfileButton{
                    id:btnMap

                    leftText: qsTr("生日")
                    rigthText: userProfileManager.birth ===""?qsTr("设置生日"):userProfileManager.birth;
                    editable:true
                    anchors.top: btnName.bottom
                    onClicked: {
                        if(!datePicker.visible){
                            var mScons = userProfileManager.birthMScon();
                            var date = new Date();
                            date.setTime(mScons);
                            datePicker.setDate(date.getFullYear(),date.getMonth()+1,date.getDate());
                            datePicker.show()
                        }
                    }
                }
                UserProfileButton{
                    id:btnDD

                    leftText: qsTr("圆圆号")
                    rigthText: userProfileManager.nickId !== ""?userProfileManager.nickId:qsTr("请设置圆圆号");
                    radius:4
                    showLine:false
                    editable:userProfileManager.nickId ===""

                    anchors.top: btnMap.bottom
                    onClicked: {
                        if(userProfileManager.nickId !==""){
                            return ;
                        }

                        inputDialog.titleText= qsTr("圆圆号(设置后不能修改)");
                        inputDialog.setText(userProfileManager.nickId);
                        inputDialog.type = 2;
                        inputDialog.show();
                    }

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

                    leftText: qsTr("联系方式")
                    rigthText: userProfileManager.phone
                    anchors.top: btnSex.bottom
                    visible: userProfileManager.phone !== ""
                }
                UserProfileButton{
                    id:btnPhone

                    leftText: qsTr("邮箱")
                    rigthText: userProfileManager.email
                    visible: userProfileManager.email !== ""
                    anchors.top: btnBirth.bottom

                }
            }
        }
    }
    CInputDialog{
        id:inputDialog

        property int  type:1

        messageTextColor:"#777777"
        maximumLength: 20
        inputFontPixelSize:20
        titleTextPixelSize:30
        //validator:RegExpValidator{regExp:/^[a-zA-Z0-9][a-zA-Z0-9_-]*$/}
        validator:type===2 ? /^[a-zA-Z0-9][a-zA-Z0-9_-]*$/ :/^.{1,}$/
        placeholderText:type===2 ?qsTr("长度为6-20字母,以数字或字母开头，可包含一个'-'或'_'"):"";
        onAccepted: {
            if(type === 1){
                userProfileManager.updateAccountInfo(inputDialog.text(),"","");
            }
            if(type == 2){
                //TODO
                var tmp =""+inputDialog.text();
                if(tmp.length<6){
                    gToast.requestToast("最短长度为6位","","");
                }else{
                    userProfileManager.updateAccountInfo("","","",inputDialog.text());
                }
            }
        }
    }
    CDatePickerDialog{
        id: datePicker
        maximumYear:{new Date().getFullYear();}
        minimumYear:1896
        onDateAccepted: {
            btnMap.rigthText = year + "年" + month + "月" + day +"日"
            var theDate = new Date(year,month-1,day);
            var times = theDate.getTime();
            if(times === 0){
                times="";
            }else{
                times =times+"";
            }
            userProfileManager.updateAccountInfo("","","","",times);
        }
    }
    CDoodListDialog{
        id: sexListDialog

        titleText: qsTr("性别")
        onNotifySelectedItems:{
            console.log("xxxxxxxxx:"+model[curIndex]);
            userProfileManager.updateAccountInfo(btnName.rigthText,"",model[curIndex]);
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
