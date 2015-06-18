import QtQuick 2.0

Rectangle {
    signal clicked()
    signal longClicked()
    
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
            parent.clicked();
        }
        onPressAndHold: {
            parent.longClicked();
        }
    }
    state: "NORMAL"

    states: [
        State {
            name: "NORMAL"
            when: mouseArea.pressed == false
        },
        State {
            name: "PRESSED"
            when: mouseArea.pressed == true
            PropertyChanges {target: inner; color: "lightgray"}
        }
    ]

    transitions: [
        Transition {
            from: "PRESSED"
            to: "NORMAL"
            ColorAnimation {duration: 200}
        }
    ]
}
