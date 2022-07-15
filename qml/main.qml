import QtQuick 2.0

import QtQuick.Controls 2.12
import SilverSwift.Application 0.1
import SilverSwift.Model 0.1

ApplicationWindow {
    visible: true

    menuBar: MenuBar {
        // ...
    }

    header: ToolBar {
        // ...
    }

    footer: TabBar {
        // ...
    }

    StackView {
        anchors.fill: parent

        Instance{
            id: app_instance
        }

        ListView{
            anchors.fill: parent
            model: app_instance.model
            delegate: CMSProgramDelegate { }
        }
    }
}
