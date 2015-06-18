import QtQuick 2.0

Rectangle {
    width: 280
    height: 140
    color: "#002000"
    Rectangle {
        width: 140
        height: 70
        radius: 3
        color: parent.color
        anchors.centerIn:parent
        Row {
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            ToggleButton {
                width: 40
                height: parent.height
                radius: 3
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    text: "<"
                    color: "white"
                    font {
                        pointSize: 24
                    }
                }
                onClicked: {
                    console.log("left button clicked")
                }
            }
            ToggleButton {
                width: 60
                height: 70
                radius: 3
                color: "transparent"
                Image {
                    anchors.centerIn: parent
                    width: 60
                    height: 70
                    source: "../img/Speaker-fill-white-small.svg"
                    sourceSize {
                        width: parent.height - 10
                        height: width
                    }
                }
                onClicked: {
                    console.log("center button clicked");
                }
            }
            ToggleButton {
                width: 40
                radius: 3
                height: parent.height
                color: "transparent"
                Text {
                    anchors.centerIn: parent
                    text: ">"
                    color: "white"
                    font {
                        pointSize: 24
                    }
                }
                onClicked: {
                    console.log("right button clicked")
                }
            }
        }
    }
}

