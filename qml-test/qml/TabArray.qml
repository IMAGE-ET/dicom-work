import QtQuick 2.0

Rectangle {
    property int wW: 50
    property int hH: 50
    property alias model: tabs.model
    property alias delegate: tabs.delegate

    width: wW * 1
    height: hH * 1.5
    color: "lightgray"
    clip: true

    Rectangle {
        id: slider
        width: wW * tabs.count;
        height: hH
        color: "green"
        Row {
            Repeater {
                id: tabs
            }
        }
        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }
    }

    function showTab(idx) {
        console.log("Show tab");
        slider.x = 0 - wW * idx;
    }
}
