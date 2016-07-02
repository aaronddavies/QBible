import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    id: root
    height: row_height

    property alias text: text_item.text
    property bool highlight: false

    property var fetchOnClick: function () {}

    Rectangle {
        id: base_rect
        anchors.fill: parent
        border.color: border_color
        border.width: border_width
        radius: rect_radius
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
