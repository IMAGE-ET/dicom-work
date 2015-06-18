import Gauge 1.0
import QtQuick 2.0

Rectangle {
    width: 400
    height: 2 
    color: "transparent"
    Gauge {
        id: gauge
        anchors.fill: parent
        //onValueChanged: { console.log("Value changed"); }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            gauge.updateValue( Math.random() );
        }
    }
}
