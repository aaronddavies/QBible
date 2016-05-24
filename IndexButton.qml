import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    id: root
    height: 30

    property int radius: 2
    property string border_color: font_color
    property int border_width: 1
    property alias text: text_item.text
    property bool highlight: false

    property var fetchOnClick: function () {}

    Rectangle {
        id: base_rect
        anchors.fill: parent
        border.color: root.border_color
        border.width: root.border_width
        radius: root.radius
        color: mouse.pressed || highlight ? highlight_color : background_color
    }

    Text {
        id: text_item
        color: font_color
        font.pointSize: font_size
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: {
            fetchOnClick();
        }
    }
}
