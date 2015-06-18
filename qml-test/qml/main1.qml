import QtQuick 2.0

Rectangle {
    width: keyboard.width
    height: lcd.height + keyboard.height
    color: "#002000"

    NumberDisplay {
        anchors {
            leftMargin: 10
            rightMargin: 10
        }
        id: lcd
        color: "transparent"
        textColor: "white"
        text: "01252465677"
        textMaxLength: 14
        height: 80
        onLeftButtonClicked: { console.log("Left button clicked") }
        onRightButtonClicked: { 
            console.log("Right button clicked");
            text = text.slice(0, -1);
        }
        onRightButtonLongClicked: {
            console.log("Right button long clicked");
            text = "";
        }
    }
    Rectangle {
        id: keyboard
        
        color: "transparent"
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }

        width: querty.itemSize * querty.columns + (querty.columns + 1)*querty.spacing
        height: querty.itemSize * querty.rows + (querty.rows + 1) * querty.spacing

        GridKeyBoard {
            id: querty
            itemSize: 80
            spacing: 20
            rows: 4
            onClicked: {
                console.log("kakakaka: " + label);
                lcd.addChar(label);
            }
        }
    }
}
