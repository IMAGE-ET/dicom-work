import QtQuick 2.0
Rectangle {
    anchors.centerIn: parent
    width: 200
    height: 200
    TabArray {
        id: slidingWindow
        wW: 100
        hH: 100
        VisualItemModel {
            id: tabs
            Rectangle {
                color: "yellow"
                border {
                    width: 2
                    color: "black"
                }
                width: slidingWindow.wW
                height: slidingWindow.hH
                Text {
                    anchors.centerIn: parent
                    text: "tab1"
                }
            }
            Rectangle {
                color: "pink"
                border {
                    width: 2
                    color: "black"
                }
                width: slidingWindow.wW
                height: slidingWindow.hH
                Text {
                    anchors.centerIn: parent
                    text: "tab2"
                }
            }
            
            Rectangle {
                color: "lime"
                border {
                    width: 2
                    color: "black"
                }
                width: slidingWindow.wW
                height: slidingWindow.hH
                Text {
                    anchors.centerIn: parent
                    text: "tab 3"
                }
            }
        }
        model: tabs
//        delegate: contentDelegate1
        anchors.centerIn: parent
    }
    MouseArea {
        property int idx;
        anchors.fill:parent
        onClicked: {
            idx = Math.round(Math.random()*10) % tabs.count;
            slidingWindow.showTab(idx);
        }
    }
}
