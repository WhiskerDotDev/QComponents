pragma ComponentBehavior: Bound
import QtQuick;

BasicButton{
      id: root;
      property int fallbackborderthickness: 1;

      Image{
            id: m_img
            anchors.fill: root;
            clip: root.clip;
            asynchronous: true;
            cache: false;
            fillMode: Image.PreserveAspectFit;
            antialiasing: root.antialiasing; smooth: root.smooth;
      } property alias img : m_img;
      property alias iconsrc: root.img.source;

      Loader{
            sourceComponent: Component{
                  Text{
                        parent: root;
                        renderType: Text.NativeRendering;
                        anchors.fill: parent;
                        anchors.margins: root.border.width;
                        text: root.img.status === Image.Error? "ERR" : root.img.status === Image.Null ? "NUL" : root.img.status === Image.Loading? "LDD" : null;
                        minimumPixelSize: 1;
                        fontSizeMode: Text.Fit;
                        verticalAlignment: Text.AlignVCenter;
                        visible: true; antialiasing: root.antialiasing; smooth: root.smooth;
                        wrapMode: Text.NoWrap;
                        textFormat: Text.PlainText;
                        color: "#000000";
                        // font.letterSpacing: -1;
                        // z: root.z;
                  }
            }
            active:  ( root.img.status === Image.Error || root.img.status === Image.Null || root.img.status === Image.Loading) ? true: false;
      }

      border.width: ( root.img.status === Image.Error || root.img.status === Image.Null || root.img.status === Image.Loading) ? fallbackborderthickness : 0;
      border.color: "#000000";
}
