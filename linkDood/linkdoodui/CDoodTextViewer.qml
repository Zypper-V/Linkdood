import QtQuick 2.0
import com.syberos.basewidgets 2.0
import com.syberos.filemanager 1.0

CPage {
    id: rootTextViewer
    statusBarHoldEnabled: true
    statusBarHoldItemColor: "white"
    //    orientationLock: CPageOrientation.LockPortrait

    property int page: -1
    property string fullfilepath: ""
    property string fileName: ""

    onStatusChanged: {
        if (status === CPageStatus.WillShow) {
            mainPageView.inputFactor = 1
        } else if (status === CPageStatus.WillHide) {
            mainPageView.inputFactor = 0
        }
    }

    CTxtEditor {
        id: txtEditor
        path: fullfilepath
        onPathChanged: {
            page = 0;
        }
    }
    contentAreaItem: Item {
        CTitleBar {
            id: titleBar

            height:86
            titleText: qsTr(rootTextViewer.fileName)
            titleTextColor: "white"
            titlePixelSize: 30
            leftItemEnabled: true
            rightItemEnabled: flase
            rightItemBackgroundEnabled: false
            titleAreaCentered: true
            spacingBetweenLeftBorderAndLeftItem: 30

            backgroundComponent:Rectangle{
                z: -1
                anchors.fill: parent
                color:"#003953"
            }

            //           leftItemText: os.i18n.ctr(qsTr("Cancel")) // 取消
            //           rightItemText: os.i18n.ctr(qsTr("Save")) // qsTr("保存")
            leftItemIcon: "qrc:/res/main_title_back_button.png"
            //            rightItemIcon: ""
            onLeftItemTriggered: pageStack.pop();
            onRightItemTriggered: {
                txtEditor.save(page, editor.text);
                //                editModel.updateTextFileDate(fullfilepath);
                //                rootWindow.updateTextTime(fullfilepath);
                pageStack.pop();
            }
        }
        CTextArea {
            id: editor
            anchors.top: titleBar.bottom
            //anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.bottom: navBar.top
            anchors.bottomMargin: 30
            readOnly: true
            font.pixelSize : gUiConst.getValue("font05")
            textColor : gUiConst.getValue("color05")
            text: txtEditor.getContent(page)
        }


        Rectangle {
            id: navBar
            width: parent.width
            height: txtEditor.pageCount > 1 ? previousBtn.height + 40 : 0
            anchors.bottom: parent.bottom
            //color: gUiConst.getValue("color11")
            clip: true

            CButton {
                id: previousBtn
                anchors.left: parent.left
                anchors.leftMargin: 40
                anchors.verticalCenter: parent.verticalCenter
                enabled: page > 0
                text: os.i18n.ctr(qsTr("上一页")) // qsTr("上一页")
                onClicked: {
                    page --;
                }
            }

            Text {
                anchors.centerIn: parent
                text: (page + 1) // + " / " + txtEditor.pageCount
            }

            CButton {
                id: nextBtn
                anchors.right: parent.right
                anchors.rightMargin: 40
                anchors.verticalCenter: parent.verticalCenter
                enabled: page < (txtEditor.pageCount - 1)
                text: os.i18n.ctr(qsTr("下一页")) // qsTr("下一页")
                onClicked: {
                    page ++;
                }
            }
        }
    }
}
