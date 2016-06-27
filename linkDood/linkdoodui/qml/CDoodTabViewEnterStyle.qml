//import QtQuick 2.0

//Item {
//    id:tabStyle

//    width: 100
//    height: 120
//    /**
//    @brief 被使用的CTabView
//    */
//    property Item tabview

//    /**
//    @brief 用于设置当前标签的数据，其有currentIndex，index以及title内容
//    */
//    property alias styleData:viewData
//    /*
//      * since 14.7.3
//    @brief 现实title的Text，用户可通过此设置text的相关属性
//    */
//    property alias text:txt

//    //property alias imgSource:img

//    QtObject{
//        id:viewData
//        property int index:-1
//        property int currentIndex:0
//        property string title
//    }

//    Rectangle {
//        anchors.top: parent.top
//        width: parent.width
//        height:parent.height
//        z:parent.z+2
//        radius: 5
//        color: index === tabview.currentIndex? "#32c2fe" : "white"
//    }

//    Text {
//        id:txt
//        //anchors.bottom: parent.bottom
//        //anchors.bottomMargin: 15
//        //anchors.horizontalCenter: parent.horizontalCenter
//        anchors.centerIn: parent
//        z:parent.z+2
//        width:Math.min(parent.width-2,implicitWidth)//margin
//        font.pixelSize: 32
//        clip:true
//        color:index === tabview.currentIndex? "#00afee" : "#777777"
//        text:tab.title
//    }

//    MouseArea {
//        anchors.fill: parent

//        onClicked: {
//            if(tabView.currentIndex != index)
//                tabView.currentIndex = index
//        }

//        onDoubleClicked: {
//            if(tabView.currentIndex != index) {
//                tabView.currentIndex = index
//            } else if(index === 0) {
//                console.log("sessionpage onDoubleClicked!!!")
//            }
//        }
//    }
//}

/*
 * This file is part of syberos-toolkit-core
 * Copyright (C) 2015 Beijing Yuan Xin Technology Co.,Ltd. All rights reserved.
 * Authors:
 *       Cai Zhenbin <caizhenbin@syberos.com>
 *
 * This software, including documentation, is protected by copyright controlled
 * by Beijing Yuan Xin Technology Co.,Ltd. All rights are reserved.
 */

import QtQuick 2.3

/*!
    \qmltype CTabBar
    \inqmlmodule com.syberos.basewidgets
    \since 2.0
    \ingroup viewaddons
    \brief CTabView的标签导航栏控件
*/

Rectangle {
    id: tabBar
    implicitHeight: 88
    anchors.left: parent.left
    anchors.right: parent.right
    color: "white"

    /*! TabBar所在的TabView，必须赋值 */
    property var tabView: null

    /*! 标签高度 */
    property real tabHeight: 64

    /*! 标签宽度 */
    property real tabWidth: 179

    /*! 字体大小 */
    property int titlePixelSize: gUiConst.getValue("S3")

    /*! 文字颜色 */
    property color titleColor: gUiConst.getValue("CT2")

    /*! 高亮文字颜色 */
    property color titleHighlightColor: gUiConst.getValue("CT5")

    /*! 标签颜色 */
    property color tabColor: "white"

    /*! 高亮标签颜色 */
    property color tabHighlightColor: "#F8F8F8"

    /*! 框线颜色 */
    property color borderColor: gUiConst.getValue("CB6")

    /*!
        \qmlproperty color CTabView::backgroundColor
        标签栏背景颜色
    */
    property alias backgroundColor: tabBar.color

    objectName: "CTabBar"

    /*!
        \qmlproperty string CTabView::theme
        外观风格样式

        \list
        \li "light" (default) - 白色风格
        \li "dark" - 黑色风格
        \endlist
    */
    property string theme: tabView.hasOwnProperty("theme") ? tabView.theme : "light"

    /*! 标识动画是否正在进行，只读属性。*/
    readonly property bool animating: anchorAnimation.running

    onThemeChanged: {
        if(theme == "light") {
            titleColor = gUiConst.getValue("CT2");
            //titleHighlightColor = gUiConst.getValue("CT5")
            tabColor = "white";
            tabHighlightColor = "#F8F8F8";
            borderColor = gUiConst.getValue("CB6");
            backgroundColor = "white";
        } else if(theme == "dark") {
            titleColor = gUiConst.getValue("CTB3");
           // titleHighlightColor = gUiConst.getValue("CTB1")
            tabColor = "black";
            tabHighlightColor = "#242424";
            borderColor = "#363636";
            backgroundColor = "black";
        }
    }

    Rectangle {
        id: bar
        anchors.centerIn: tabBar
        color: borderColor
        height: row.height+4
        width: row.width+4
//        border.color: borderColor
//        border.width: 2
        radius: height/2

        Row {
            id: row
            height: tabHeight
            anchors.centerIn: parent
            spacing: 1

            Repeater {
                id: repeater
                model: tabView.tabModel

                delegate: MouseArea {
                    width: tabWidth
                    height: tabHeight

                    Rectangle {
                        id: leftRec
                        anchors.left: parent.left
                        height: parent.height
                        width: index === 0 ? height : (index === repeater.count - 1 ? tabWidth - 0.5*height : tabWidth)
                        radius: index === 0 ? height/2 : 0
                        color: index === tabView.currentIndex ? tabHighlightColor : tabColor

                        Behavior on color {
                            ColorAnimation { duration: gSystemUtils.durationRatio*100 }
                        }
                    }
                    Rectangle {
                        id: rightRec
                        anchors.right: parent.right
                        height: parent.height
                        width: index === 0 ? tabWidth - 0.5*height : (index === repeater.count - 1 ? height : 0)
                        radius: index === repeater.count - 1 ? height/2 : 0
                        color: index === tabView.currentIndex ? tabHighlightColor : tabColor

                        Behavior on color {
                            ColorAnimation { duration: gSystemUtils.durationRatio*100 }
                        }
                    }

                    Text {
                        text: tab.title
                        anchors.centerIn: parent
                        color: index === tabView.currentIndex ? titleHighlightColor : titleColor //tabView.titleHighlightColor : tabView.titleColor
                        font.pixelSize: titlePixelSize //tabView.titlePixelSize

                        Behavior on color {
                            ColorAnimation { duration: gSystemUtils.durationRatio*100 }
                        }
                    }

                    onClicked: {
                        tabView.currentIndex = index;
                    }
                }
            }
        }
    }
    state: tabView.tabPosition === Qt.TopEdge ?
               (tabView.tabVisible ? "top" : "top-hide") : (tabView.tabVisible ? "bottom" : "bottom-hide")
    states: [
        State {
            name: "top"
            AnchorChanges {
                target: tabBar
                anchors.top: parent.top
                anchors.bottom: undefined
            }
        },
        State {
            name: "bottom"
            AnchorChanges {
                target: tabBar
                anchors.top: undefined
                anchors.bottom: parent.bottom
            }
        },
        State {
            name: "top-hide"
            AnchorChanges {
                target: tabBar
                anchors.bottom: parent.top
                anchors.top: undefined
            }
        },
        State {
            name: "bottom-hide"
            AnchorChanges {
                target: tabBar
                anchors.bottom: undefined
                anchors.top: parent.bottom
            }
        }
    ]
    transitions: Transition {
        AnchorAnimation {
            id: anchorAnimation
            duration: gSystemUtils.durationRatio*100; easing.type: Easing.OutExpo
            onStarted: if(tabView.tabVisible) tabBar.visible = true;
            onStopped: if(!tabView.tabVisible) tabBar.visible = false;
        }
    }
}
