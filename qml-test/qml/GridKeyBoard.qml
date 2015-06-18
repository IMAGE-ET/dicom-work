import QtQuick 2.0

Grid {
    id: grid
    property int itemSize: 80
    property int itemMargin: 10
    property color borderBrightColor: "white"
    property color borderDarkColor: "gray"
    property color backgroundColor: "#002000"
    property color textColor: "lightgray"
    anchors {
        horizontalCenter: parent.horizontalCenter
        verticalCenter: parent.verticalCenter
    }
    columns: 3
    rows: 4

    signal clicked(string label)

    Repeater {
        model: ["1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#"]
        NumberButton {
            borderBrightColor: parent.borderBrightColor
            borderDarkColor: parent.borderDarkColor
            borderWidth: 1
            backgroundColor: parent.backgroundColor
            textColor: parent.textColor

            width: parent.itemSize
            text: modelData
            onClicked: {
                parent.clicked(text);
            }
        }
    }
}
