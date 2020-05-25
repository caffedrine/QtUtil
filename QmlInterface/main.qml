import QtQuick 2.11
import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Window 2.1

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button
    {
        text: "Click me"
        onPressed: {
            cpp.buttonClicked();
        }
    }

}
