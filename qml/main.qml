import QtQuick 2.0

import QtQuick.Controls 2.12

import SilverSwift.Model 0.1

ApplicationWindow {
    visible: true
    minimumWidth: 500
    width: 500
    height: 600

    Facade{
        id: app_instance
    }

    menuBar: MenuBar {
        // ...
    }

    StackView {
        id: stack
        anchors.fill: parent
        clip: true


        ListView{
            id: view
            anchors.fill: parent
            anchors.margins: 5
            model: app_instance.model
            spacing: 5
            delegate: CMSProgramDelegate { width: view.width}
        }
    }
}
