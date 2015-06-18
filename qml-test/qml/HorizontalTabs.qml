import QtQuick 2.0

Item {
    property int totalWidth: 500
    width: root.width
    height: root.height
    Rectangle {
        id: root
        width: tabBar.width
        height: tabBar.height + tabContent.height
        Rectangle {
            id: tabBar
            width: totalWidth
        }
        Rectangle {
            id: tabContent
            
        }
    }
}
