import QtQuick 2.0

Rectangle {
    property color textColor: "yellow"
    property alias text: numDisplay.text

    signal leftButtonClicked()
    signal rightButtonClicked()
    signal leftButtonLongClicked()
    signal rightButtonLongClicked()

    color: "transparent"
    height: 60

    anchors {
        top: parent.top
        horizontalCenter: parent.horizontalCenter
        leftMargin: 4
        rightMargin: leftMargin
    }
    width: parent.width - anchors.leftMargin - anchors.rightMargin

    Rectangle {
        id: leftbox
        color: parent.color
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }

        width: 60
        height: width
        radius: 0.5*width

        state: "NORMAL"
        states: [
            State {
                name: "NORMAL"
                when: leftMouseArea.pressed == false
            },
            State {
                name: "PRESSED"
                when: leftMouseArea.pressed == true
                PropertyChanges {target: leftbox; color: "lightgray"}
            }
        ]
        transitions: Transition {
            from: "PRESSED"
            to: "NORMAL"
            ColorAnimation { duration: 500 }
        }
        MouseArea {
            id:leftMouseArea
            anchors { fill: parent }
            onPressAndHold: { parent.parent.leftButtonLongClicked(); }
            onClicked: { parent.parent.leftButtonClicked(); }
        }

        Image {
            anchors.centerIn: parent
            source: "../img/call-fill-white-small.svg"
            sourceSize {
                width: parent.width - 20
                height: parent.height - 16
            }
        }
    }
    Rectangle {
        color: "#99FFFFFF"
        border {
            width: 0
            color: "#000000"
        }
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: leftbox.right
            right: rightbox.left
            topMargin: 6
            leftMargin: parent.anchors.leftMargin
            rightMargin: parent.anchors.leftMargin
        }

        Text {
            id: numDisplay
            anchors.centerIn: parent
            text: "0123456789"

            color: parent.parent.textColor;

            font {
                family: "Futura"
                pointSize: 24
            }
        }
    }
    Rectangle {
        id: rightbox
        color: parent.color
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
            leftMargin: parent.anchors.leftMargin
        }
        width: 60
        height: width
        radius: 0.5*width

        state: "NORMAL"
        states: [
            State {
                name: "NORMAL"
                when: rightMouseArea.pressed == false
            },
            State {
                name: "PRESSED"
                when: rightMouseArea.pressed == true
                PropertyChanges {target: rightbox; color: "lightgray"}
            }
        ]

        transitions: Transition {
            from: "PRESSED"
            to: "NORMAL"
            ColorAnimation { duration: 500 }
        }

        MouseArea {
            id:rightMouseArea
            anchors { fill: parent }
            onPressAndHold: { parent.parent.rightButtonLongClicked(); }
            onClicked: { parent.parent.rightButtonClicked(); }
        }

        Image {
            anchors.centerIn: parent
            source: "../img/backspace-fill-white-small.svg"
            sourceSize {
                width: parent.width - 30
            }
        }
    }
    property int textMaxLength: 12

    function addChar(symbol) {
        if (numDisplay.text.length < textMaxLength) {
            numDisplay.text += symbol;
        }
    }
}
