import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    property string verse;

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello world!")
        anchors.centerIn: parent
    }
}
