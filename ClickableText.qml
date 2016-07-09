import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    id: root
    height: text_item.implicitHeight

    property alias text: text_item.text
    property bool highlight: false

    property var fetchOnClick: function () {}

    Rectangle {
        id: base_rect
        width: parent.width
        anchors.fill: parent
        color: mouse.pressed || highlight ? highlight_color : background_color
    }

    Text {
        id: text_item
        width: parent.width
        color: font_color
        font.pointSize: font_size
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignJustify
        wrapMode: Text.WordWrap
    }

    MouseArea {
        id: mouse
        width: parent.width
        anchors.fill: parent
        onClicked: {
            fetchOnClick();
        }
    }
}
