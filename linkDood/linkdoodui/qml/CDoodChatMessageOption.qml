import QtQuick 2.0
import com.syberos.basewidgets 2.0
CDoodPopWndLayer{
    id:menu

    property string id: ""
    property int    index:-1
    property bool   isVisibleCopy :false
    property bool   isCanTrans:true
    property bool   isCanRevoke:false
    function caluHeigth(){
        var tmp = 130;
        if(isCanTrans){
            tmp+=100;
        }
        if(isVisibleCopy){
            tmp+=100;
        }
        if(isCanRevoke){
            if(isVisibleCopy){
                tmp+=10;
            }
            tmp+=100;
        }
        return tmp;
    }

    contentItemBackGroundOpacity:0.73
    contentItem:Rectangle{
        id:backItem

        color: "white"
        radius: 10
        width: 389
        height: caluHeigth()
        anchors.centerIn: parent
        UserProfileButton{
            id:btnCopy

            width:parent.width
            height: 100
            leftText: qsTr("复制")
            radius: 4
            visible: isVisibleCopy

            anchors.top:parent.top
            anchors.topMargin: 10

            onClicked: {

                index = 0;
                inerClicked();
            }
        }
        UserProfileButton{
            id:btnDel

            width:parent.width
            height: 100
            leftText: qsTr("删除") ;
            radius: 4
            anchors.top:isVisibleCopy ? btnCopy.bottom :parent.top
            anchors.topMargin: 10
            onClicked: {

                index = 1;
                inerClicked();
            }
        }
        UserProfileButton{
            id:btnRepost

            width:parent.width
            height:100
            leftText: qsTr("转发") ;
            radius: 4
            showLine:isCanRevoke
            visible: isCanTrans
            anchors.top: btnDel.bottom
            anchors.topMargin: 10
            onClicked: {
                index = 2;
                inerClicked();
            }
        }
        UserProfileButton{
            id:btnRevoke

            width:parent.width
            height:100
            leftText: qsTr("撤回") ;
            radius: 4
            showLine:false
            visible: isCanRevoke
            anchors.top: btnRepost.bottom
            anchors.topMargin: 10
            onClicked: {
                index = 3;
                inerClicked();
            }
        }
    }
    onBackKeyReleased: {
        menu.hide();
    }
    onOutAreaClicked: {
        menu.hide();
    }
}
