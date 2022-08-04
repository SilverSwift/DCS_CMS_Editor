import QtQuick 2.15

Item {
    id: wrapper
    property alias source: image.source

    Item {
        id: imageItem
        anchors.fill: parent
        layer.enabled: true
        visible: false

        Image {
            id: image
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
        }
    }

    Rectangle {
        id: mask
        anchors.fill: parent
        radius: width / 2

        layer.enabled: true
        layer.samplerName: "mask"
        layer.effect: ShaderEffect {
            property var image: imageItem
            fragmentShader: "qrc:/shaders/roundel.frag.qsb"
            vertexShader: "qrc:/shaders/roundel.vert.qsb"
        }
    }
}
