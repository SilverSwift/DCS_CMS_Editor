import QtQuick 2.0

Rectangle {
    color: "green"
    implicitHeight: text.height
    width: 500
    Text {
        id: text
        text: "chaff: " + model.chaff + " flare: " + model.flare
    }

    MouseArea {
        anchors.fill: text
        onClicked: {
            model.flare *= 2;
        }
    }
}
