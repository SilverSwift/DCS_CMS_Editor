import QtQuick 2.0

Rectangle {
    color: "green"
    implicitHeight: text.height
    width: 500
    Text {
        id: text
        text: "name: "+ model.name + "\nchaff: " + model.chaff + " flare: " + model.flare + " intv: " + model.intv + " cycle: " + model.cycle +
              "\ncomment: " + model.comment
    }

    MouseArea {
        anchors.fill: text
        onClicked: {
            model.flare *= 2;
        }
    }
}
