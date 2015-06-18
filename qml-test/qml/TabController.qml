import QtQuick 2.0

Rectangle {
    signal clicked()
    signal longClicked()
    property bool value: false
    Rectangle {
        id: inner
        width: parent.width
        height: parent.height
        radius: parent.radius
        color: parent.color
    }
    MouseArea {
        id: mouseArea
        width: parent.width
        height: parent.height
        onClicked: {
            parent.value = !parent.value;
            parent.clicked();
        }
        onPressAndHold: {
            parent.longClicked();
        }
    }
    state: "OFF"

    states: [
        State {
            name: "OFF"
            when: value == false
        },
        State {
            name: "ON"
            when: value == true
            PropertyChanges {target: inner; color: "lightgray"}
        }
    ]

    transitions: [
        Transition {
            from: "ON"
            to: "OFF"
            ColorAnimation {duration: 200}
        },
        Transition {
            from: "OFF"
            to: "ON"
            ColorAnimation {duration: 200}
        }
    ]
}
