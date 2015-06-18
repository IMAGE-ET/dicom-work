import QtQuick 2.0
import Gauge 1.0

Item {
    width: root.width
    height: root.height
    Rectangle {
        id: root
        color: "#002000"
        anchors {
            centerIn:parent
        }
        width: keyboard.width
        height: lcd.height + keyboard.height

        /*border {
            width: 2
            color: "#99FFFFFF"
        }*/

        Gauge {
            id: gauge
            height: 2
            width: parent.width
            anchors { top : parent.top; left: parent.left }
            onValueChanged: { console.log("value changed") }
        }

        NumberDisplay {
            anchors {
                leftMargin: 10
                rightMargin: 10
            }
            /*border {
                width: 2
                color: "white"
            }*/
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
            /*border {
                width: 2
                color: "green"
            }*/
            
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
                spacing: 30
                rows: 4
                onClicked: {
                    gauge.updateValue(Math.random());
                    lcd.addChar(label);
                }
            }
        }
    }
}
